#include "stc.h"
#include "usb.h"
#include "STC32G_PWM.h"
#include "STC32G_NVIC.h"
#include "oled.h"
#include	"STC32G_Delay.h"

#define ONE_STEP_UNIT 70.5555555f
#define FACTOR 1456L
#define PI2_FACTOR 524280L
#define PI_FACTOR 262140L
#define PI05_FACTOR 131070L

#define KP 3000
#define KI 10000
#define KD 0

char *USER_DEVICEDESC = NULL;
char *USER_PRODUCTDESC = NULL;
char *USER_STCISPCMD = "@STCISP#";

BYTE xdata adcValues0[24];
BYTE xdata adcValues1[24];
int16_t encoderPoints[4];
extern uint16_t code tanTable[];
extern uint16_t code angleTable[];
uint8_t adcChs[4] = {0x01, 0x04, 0x05, 0x06};
uint8_t currentCh = 0;
volatile uint8_t currentBufferIndex = 0;
volatile uint8_t bufferAsk = 0;
char positionString[64];
volatile char updateFlag = 0;

void systemInit()
{
  EAXFR = 1;
  CKCON = 0X00;
  WTST = 0X00;
  P0M1 = 0x00;   P0M0 = 0x00;
  P1M1 = 0x00;   P1M0 = 0x00;
  P2M1 = 0x00;   P2M0 = 0x00;
  P3M1 = 0x00;   P3M0 = 0x00;
  P4M1 = 0x00;   P4M0 = 0x00;
  P5M1 = 0x00;   P5M0 = 0x00;
  P6M1 = 0x00;   P6M0 = 0x00;
  P7M1 = 0x00;   P7M0 = 0x00;
  
}
void samplePinInit()
{
  P4M1 &= ~0X01;
  P4M0 |= 0X01;
  P40 = 0;
}
void adcSampleHold(uint16_t number)
{
  uint16_t i;
  P40 = 1;
  for (i = 0; i < number; ++i)
    _nop_();
  P40 = 0;
}
void adcInit()
{
  P1M1 |= 0X72;
  P1M0 &= ~0X72;
  ADCTIM = 0x1f;
  ADCCFG = 0X21;
  ADC_FLAG = 0;
  ADC_POWER = 1;
  EADC = 0;
  delay_ms(1);
}
void adcDMAInit()
{
  DMA_ADC_CR = 0X80;
  DMA_ADC_RXAH = (WORD)adcValues0 >> 8;
  DMA_ADC_RXAL = (BYTE)adcValues0;
  DMA_ADC_CFG2 = 0X00;
  DMA_ADC_CHSW0 = 0XF0;
  DMA_ADC_CHSW1 = 0X00;
  DMA_ADC_STA = 0X00;
  DMA_ADC_CFG = 0X8F;
}
//arctan查表法，，输入放大65535倍的tan值，返回放大(65535/45)倍后的角度
uint16_t findAngleTable(uint32_t x)
{
  uint16_t start = 0, end = 2048;
  uint16_t i = ((start + end) >> 1);
  uint16_t detaA, detaB;
  do{
    if (tanTable[i] >= x)
      end = i;
    else if (tanTable[i] < x)
      start = i;
    i = ((start + end) >> 1);
  }while((i != end) && (i != start));
  detaA = x - tanTable[start];
  detaB = tanTable[end] - x;
  return detaA < detaB? angleTable[start] : angleTable[end];
}
//计算角度，返回角度制的角度，角度放大了（65535/45）倍
int32_t getAngle(int32_t x, int32_t y)
{
  uint8_t area = 0x00;
  int32_t absAngle = 0;
  //将角度转化到0°-45°之间，并记录象限
  if (x < 0){
    area |= 0x04;
    x = -x;
  }
  if (y <= 0){
    area |= 0x02;
    y = -y;
  }
  if (y > x){
    area |= 0x01;
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
  }
  if (x != 0)
    //查表法的tan值放大了65535倍，所以这里也要放大65535倍
    absAngle = findAngleTable(((((uint32_t)y) << 16) - y) / ((uint32_t)x)); 
  switch (area){
    case 0x00:
      return absAngle;
      break;
    case 0x01:
      return PI05_FACTOR - absAngle;
      break;
    case 0x02:
      return - absAngle;
      break;
    case 0x03:
      return absAngle - PI05_FACTOR;
      break;
    case 0x04:
      return PI_FACTOR - absAngle;
      break;
    case 0x05:
      return PI05_FACTOR + absAngle;
      break;
    case 0x06:
      return absAngle - PI_FACTOR;
      break;
    case 0x07:
      return - PI05_FACTOR - absAngle;
      break;
    default:
      return 0;
  }
  return 0;
}
//重整角度至+-180°之间(也是放大了的角度)
int32_t reForm(int32_t detaPhy)
{
  if (detaPhy > PI_FACTOR)
    detaPhy -= PI2_FACTOR;
  else if (detaPhy < -PI_FACTOR)
    detaPhy += PI2_FACTOR;
  return detaPhy;
}
uint8_t fitstRunning = 1;
int32_t phy0, phyA, phyB, counts = 0, detaPhyB = 0, detaPhyAB, detaPhyA, phase = 0, counts1 = 0, phase1 = 0;
int32_t speed = 0;
int32_t aimCount = 0, aimPhase = 0;
int32_t error, error1, error2;
int32_t Kp = KP, Ki = KI, Kd = KD;
int32_t Kpi = KI * KP, Kpd = KD * KP;
int32_t pwmOut = 0, pidPOut = 0, pidIOut = 0, pidDOut = 0, pwmOutTemp = 0;
uint8_t calculateAlerm = 0;
uint8_t errorInRange = 0, errorInRange1 = 0;
void pidReinit()
{
  pidPOut = 0;
  pidIOut = 0;
  pidDOut = 0;
  errorInRange = 0;
  errorInRange1 = 0;
  error = 0;
  error1 = 0;
  error2 = 0;
}
//获取定时器4的计数值，用于计算速度
uint16_t getTimer4Counts()
{
  volatile uint8_t T4LTemp, T4HTemp;
  do{
    T4LTemp = T4L;
    T4HTemp = T4H;
  }while((T4LTemp != T4L) || (T4HTemp != T4H));
  return ((uint16_t)T4HTemp) + T4LTemp;
}
//更新速度值
uint16_t timestamp1 = 0;
void updateSpeed()
{
  uint16_t detaTime, timestamp = getTimer4Counts();
  if (timestamp >= timestamp1)
    detaTime = timestamp - timestamp1;
  else
    detaTime = (0xFFFF - timestamp1) + timestamp + 1;
  speed = ((counts - counts1) * PI2_FACTOR + phase - phase1) / detaTime;
  timestamp1 = timestamp;
}
//计算PID，每采集4次计算一次（每次采集只计算一部分），9k速率
void calculatePid()
{
  switch (calculateAlerm){
    case 0:   //计算误差，并限制误差幅值，然后放大1024倍，保证不会溢出
      error = (aimCount - counts) * PI2_FACTOR + aimPhase - phase;
      errorInRange1 = errorInRange;
      errorInRange = 0;
      if (error >= 1048560)
        error = 1048560;
      else if (error <= -1048560)
        error = -1048560;
      else
        errorInRange = 1;
      error <<= 10;
      break;
    case 1:   //计算比例项并限制幅值
      pidPOut += (error - error1) / Kp;
      if (pidPOut > 1792000)
        pidPOut = 1792000;
      else if (pidPOut < -1792000)
        pidPOut = -1792000;
      break;
    case 2:   //计算积分项并限制幅值，当误差在限制范围内则清零积分项输出，避免超调
      if (Ki != 0){
        pidIOut += error / Kpi;
        if (pidIOut > 1792000)
          pidIOut = 1792000;
        else if (pidIOut < -1792000)
          pidIOut = -1792000;
        if ((errorInRange == 1) && (errorInRange1 == 0))
          pidIOut = 0;
      }
      break;
    case 3:   //计算微分项并限制幅值
      if (Kd != 0){
        pidDOut += ((error - error1) - (error1 - error2)) / Kpd;
        if (pidDOut > 1792000)
          pidDOut = 1792000;
        else if (pidDOut < -1792000)
          pidDOut = -1792000;
      }
      error2 = error1;
      error1 = error;
      //计算总输出，并限制幅值
      pwmOut = pidPOut + pidIOut + pidDOut;
      if (pwmOut > 1792000)
         pwmOut = 1792000;
      else if (pwmOut < -1792000)
        pwmOut = -1792000;
      //上面的计算输出是放大了的，所以这里进行缩小
      pwmOutTemp = pwmOut >> 10;
      //在控制运动方向里面切换左右限位的输入
      if (pwmOutTemp < 0){
        P_SW2 |= 0X08; //AD0_INT
        CMPEXCFG = 0X07; //ad0
        PWMA_Duty4((1750 + pwmOutTemp));
      }
      else if (pwmOutTemp > 0){
        P_SW2 &= ~0X08; //AD5_INT
        CMPEXCFG = 0X05; //ad5
        PWMA_Duty4((1750 + pwmOutTemp));
      }
      else{
        PWMA_Duty4(1750);
      }
      break;
  }
  ++calculateAlerm;
  if (calculateAlerm == 4)
    calculateAlerm = 0;
}
void adcDMAInterrput(void) interrupt 13
{
  //P40控制外部采样保持器进行采样，这里采样时间约为2us
  //采用1nF的保持电容，对应的充电时间约为2us，而且内部ADC采样也还要进行采样保持，内部ADC采样保持时间设置为2us故，总的时间有4us足以保持电容充满
  P40 = 1;
  //记录四个光电二极管的ADC采样值
  if (currentBufferIndex == 0){
    encoderPoints[0] = ((uint16_t *)adcValues0)[0];
    encoderPoints[1] = ((uint16_t *)adcValues0)[6];
    encoderPoints[2] = ((uint16_t *)adcValues0)[3];
    encoderPoints[3] = ((uint16_t *)adcValues0)[9];
  }
  else if(currentBufferIndex == 1){
    encoderPoints[0] = ((uint16_t *)adcValues1)[0];
    encoderPoints[1] = ((uint16_t *)adcValues1)[6];
    encoderPoints[2] = ((uint16_t *)adcValues1)[3];
    encoderPoints[3] = ((uint16_t *)adcValues1)[9];
  }
  //当USB请求时，切换缓冲区，避免数据不一致
  if (bufferAsk == 1){
    if (currentBufferIndex == 0){
      DMA_ADC_RXAH = (WORD)adcValues1 >> 8;
      DMA_ADC_RXAL = (BYTE)adcValues1;
      currentBufferIndex = 1;
    }
    else if(currentBufferIndex == 1){
      DMA_ADC_RXAH = (WORD)adcValues0 >> 8;
      DMA_ADC_RXAL = (BYTE)adcValues0;
      currentBufferIndex = 0;
    }
    bufferAsk = 0;
  }
  //结束外部的采样保持
  P40 = 0;
  //开始新的一轮ADC采样
  DMA_ADC_STA = 0X00;
  DMA_ADC_CR |= 0X40;
  //细分的逻辑处理部分
  counts1 = counts;
  phase1 = phase;
  if (fitstRunning != 1){
    //计算绝对相位
    phyB = getAngle(encoderPoints[1] - encoderPoints[3], encoderPoints[0] - encoderPoints[2]);
    //计算相对上次位置和初始位置的相位差
    detaPhyAB = phyB - phyA;
    detaPhyA = detaPhyB;
    detaPhyB = phyB - phy0;
    detaPhyAB = reForm(detaPhyAB);
    detaPhyB = reForm(detaPhyB);
    //辨向
    if (((detaPhyB < 0) && (detaPhyAB > 0) && (detaPhyA > 0)) ||
         (detaPhyB > 0) && (detaPhyAB < 0) && (detaPhyA < 0)){
      if (detaPhyAB > 0)
        counts += 1;
      else
        counts -= 1;
    }
    phase = detaPhyB;
    phyA = phyB;
  }
  else{
    //初始化
    fitstRunning = 0;
    phy0 = getAngle(encoderPoints[1] - encoderPoints[3], encoderPoints[0] - encoderPoints[2]);
    phyA = phy0;
    counts = 0;
    phase = 0;
    detaPhyB = 0;
  }
  updateSpeed();
  calculatePid();
  //标志有新的数据
  updateFlag = 1;
}
void usbInit()
{
  P3M0 &= ~0x03;
  P3M1 |= 0x03;
  
  IRC48MCR = 0x80;
  while (!(IRC48MCR & 0x01));
  
  USBCLK = 0x00;
  USBCON = 0x90;
  
  usb_init();
  
  while(DeviceState == DEVSTATE_CONFIGURED);
}
//定时器4定时，1us频率，用作速度计算
void timer4Init()
{
  TM4PS = 35 - 1;
  T4L = 0X00;
  T4H = 0X00;
  T4T3M &= 0X0F;
  T4T3M |= 0XA0;
}
//比较器初始化，用于左右限位检测，但没调，中断也没开
void compareInit()
{
  P_SW2 |= 0X08; //AD0_INT
  CMPEXCFG = 0X07; //ad0
  //P_SW2 &= ~0X08; //AD5_INT
  //CMPEXCFG = 0X05; //ad5
  CMPCR1 = 0X82;
  CMPCR2 = 0X40 + 16;
}
void CMP_Routine(void) interrupt 21
{
  CMPCR1 &= ~0X40;
}
//pwm4初始化，互补输出，10k周期，Duty值为1750时，为外部电机静止点，刹车功能还没调
void pwmInit()
{
  PWMx_InitDefine		PWMx_InitStructure;
  PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE2;	
	PWMx_InitStructure.PWM_Duty    = 1750;	
	PWMx_InitStructure.PWM_EnoSelect   = ENO4P | ENO4N;	
	PWM_Configuration(PWM4, &PWMx_InitStructure);
  PWM4_USE_P26P27();
  PWMA_OC4_ReloadEnable();
  PWMx_InitStructure.PWM_Period   = 3500 - 1;						
	PWMx_InitStructure.PWM_DeadTime = 0;
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;
	PWM_Configuration(PWMA, &PWMx_InitStructure);
  //PWMA_ETRPS |= 0X04;
  //PWMA_IOAUX |= 0XC0;
  //PWMA_BRK = 0XD3;
  
  NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}
//检查P32是否为低，为低则进入下载模式
bit Key_Flag;
u16 Key_cnt;
void KeyResetScan(void)
{
  if(!P32){
    if(!Key_Flag)
    {
      Key_cnt++;
      if(Key_cnt >= 100){
        Key_Flag = 1;
        USBCON = 0x00;
        USBCLK = 0x00;
        IRC48MCR = 0x00;
        delay_ms(10);
        IAP_CONTR = 0x60;
        while (1);
      }
    }
  }
  else{
    Key_cnt = 0;
    Key_Flag = 0;
  }
}
void main()
{
  int32_t phaseTemp = 0, countsTemp = 0;
  uint8_t i = 0;
  systemInit();
  timer4Init();
  compareInit();
  delay_ms(1000);
  OLEDInit();
  usbInit();
  samplePinInit();
  adcInit();
  adcDMAInit();
  pwmInit();
  EA = 1;
  
  adcSampleHold(35);
  DMA_ADC_CR |= 0X40;
  
  while(1){
    KeyResetScan();
    while(!updateFlag);
    countsTemp = counts;
    phaseTemp = phase;
    //oled显示，最后调用OLEDFlush进行缓冲区刷新
    sprintf(positionString, "pos:%10.1fum", (((float)phaseTemp) / PI2_FACTOR + countsTemp) * ONE_STEP_UNIT);
    OLEDShow(positionString, 1, 1);
    sprintf(positionString, "speed:%6.0fmm/s", ((float)speed) / PI2_FACTOR * ONE_STEP_UNIT * 1000);
    OLEDShow(positionString, 1, 2);
    sprintf(positionString, "pwm:%12ld", pwmOutTemp);
    OLEDShow(positionString, 1, 3);
    sprintf(positionString, "e:%14ld", error);
    OLEDShow(positionString, 1, 4);
    sprintf(positionString, "aC:%13ld", aimCount, counts);
    OLEDShow(positionString, 1, 5);
    sprintf(positionString, "nC:%13ld", counts);
    OLEDShow(positionString, 1, 6);
    sprintf(positionString, "aP:%13ld", aimPhase);
    OLEDShow(positionString, 1, 7);
    sprintf(positionString, "nP:%13ld", phase);
    OLEDShow(positionString, 1, 8);
    OLEDFlush();
    if(DeviceState != DEVSTATE_CONFIGURED)
       continue;
    //收到USB请求就进行对应的处理
    //c开头的数据用于更新ADC采样周期和保持时间，格式'c''寄存器ADCTIM的值''寄存器ADCCFG的值'
    //s开头则返回原始数据
    //p开头的为修改比例系数，比例系数做的是除法，需要注意的是发送的数据最后要是空格，格式'p''整型值''空格'
    //i开头的为修改积分系数，值大于0，积分系数做除法，值小于0，积分系数做乘法，需要注意的是发送的数据最后要是空格，格式'i''整型值''空格'
    //d开头的为修改微分系数，值大于0，微分系数做除法，值小于0，微分系数做乘法，需要注意的是发送的数据最后要是空格，格式'd''整型值''空格'
    //最后会输出当前位置
    if (bUsbOutReady){
      usb_OUT_done();
      bufferAsk = 1;
      while(bufferAsk == 1);
      if (UsbOutBuffer[0] == 'c'){
        ADCTIM = UsbOutBuffer[1];
        ADCCFG = UsbOutBuffer[2];
      }
      else if(UsbOutBuffer[0] == 's'){
        if (currentBufferIndex == 0){
          UsbInBuffer[0] = adcValues1[0];
          UsbInBuffer[1] = adcValues1[1];
          UsbInBuffer[2] = adcValues1[12];
          UsbInBuffer[3] = adcValues1[13];
          UsbInBuffer[4] = adcValues1[6];
          UsbInBuffer[5] = adcValues1[7];
          UsbInBuffer[6] = adcValues1[18];
          UsbInBuffer[7] = adcValues1[19];
        }
        else if(currentBufferIndex == 1){
          UsbInBuffer[0] = adcValues0[0];
          UsbInBuffer[1] = adcValues0[1];
          UsbInBuffer[2] = adcValues0[12];
          UsbInBuffer[3] = adcValues0[13];
          UsbInBuffer[4] = adcValues0[6];
          UsbInBuffer[5] = adcValues0[7];
          UsbInBuffer[6] = adcValues0[18];
          UsbInBuffer[7] = adcValues0[19];
        }
        usb_IN(8);
      }
      else if(UsbOutBuffer[0] == 'p'){
        sscanf(UsbOutBuffer+1, "%ld", &Kp);
        printf("%ld\r\n", Kp);
        if (Kd >= 0)
          Kpd = Kp * Kd;
        else
          Kpd = -(Kp / Kd);
        if (Ki >= 0)
          Kpi =  Kp * Ki;
        else
          Kpi = -(Kp / Ki);
        pidReinit();
      }
      else if(UsbOutBuffer[0] == 'i'){
        sscanf(UsbOutBuffer+1, "%ld", &Ki);
        printf("%ld\r\n", Ki);
        if (Ki >= 0)
          Kpi =  Kp * Ki;
        else
          Kpi = -(Kp / Ki);
        pidReinit();
      }
      else if(UsbOutBuffer[0] == 'd'){
        sscanf(UsbOutBuffer+1, "%ld", &Kd);
        printf("%ld\r\n", Kd);
        if (Kd >= 0)
          Kpd = Kp * Kd;
        else
          Kpd = -(Kp / Kd);
        pidReinit();
      }
      else if(UsbOutBuffer[0] == 'a'){
        sscanf(UsbOutBuffer+1, "%ld,%ld", &aimCount, &aimPhase);
        printf("%ld,%ld\r\n", aimCount, aimPhase);
        pidReinit();
      }
      printf("%f\r\n", (((float)phaseTemp) / PI2_FACTOR + countsTemp) * ONE_STEP_UNIT);
    }
    updateFlag = 0;
  }
}