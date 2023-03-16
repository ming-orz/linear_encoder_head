/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include	"STC32G_RTC.h"

//========================================================================
// 函数: u8	ADC_Inilize(ADC_InitTypeDef *ADCx)
// 描述: ADC初始化程序.
// 参数: ADCx: 结构参数,请参考adc.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	RTC_Inilize(RTC_InitTypeDef *RTCx)
{
	if(RTCx->RTC_Year > 99)	return FAIL;	//错误
	if(RTCx->RTC_Month > 12)	return FAIL;	//错误
	if(RTCx->RTC_Day > 31)	return FAIL;	//错误
	if(RTCx->RTC_Hour > 23)	return FAIL;	//错误
	if(RTCx->RTC_Min > 59)	return FAIL;	//错误
	if(RTCx->RTC_Sec > 59)	return FAIL;	//错误
	if(RTCx->RTC_Ssec > 127)	return FAIL;	//错误
	if(RTCx->RTC_ALAHour > 23)	return FAIL;	//错误
	if(RTCx->RTC_ALAMin > 59)	return FAIL;	//错误
	if(RTCx->RTC_ALASec > 59)	return FAIL;	//错误
	if(RTCx->RTC_ALASsec > 127)	return FAIL;	//错误

	INIYEAR = RTCx->RTC_Year;
	INIMONTH = RTCx->RTC_Month;
	INIDAY = RTCx->RTC_Day;
	INIHOUR = RTCx->RTC_Hour;
	INIMIN = RTCx->RTC_Min;
	INISEC = RTCx->RTC_Sec;
	INISSEC = RTCx->RTC_Ssec;

	ALAHOUR = RTCx->RTC_ALAHour;	//闹钟小时
	ALAMIN  = RTCx->RTC_ALAMin;		//闹钟分钟
	ALASEC  = RTCx->RTC_ALASec;		//闹钟秒
	ALASSEC = RTCx->RTC_ALASsec;	//闹钟1/128秒

	if(RTCx->RTC_Clock == RTC_IRC32KCR)
	{
    //STC32G 芯片使用内部32K时钟，休眠无法唤醒
		IRC32KCR = 0x80;   //启动内部32K晶振.
		while (!(IRC32KCR & 1));  //等待时钟稳定
		RTCCFG = 0x03;    //选择内部32K时钟源，触发RTC寄存器初始化
	}
	else
	{
		X32KCR = 0x80 + 0x40;   //启动外部32K晶振, 低增益+0x00, 高增益+0x40.
		while (!(X32KCR & 1));  //等待时钟稳定
		RTCCFG = 0x01;    //选择外部32K时钟源，触发RTC寄存器初始化
	}

	if(RTCx->RTC_Enable == ENABLE)
	{
		RTCCR = 0x01;     //RTC使能
		while(RTCCFG & 0x01);	//等待初始化完成,需要在 "RTC使能" 之后判断. 
		//设置RTC时间需要32768Hz的1个周期时间,大约30.5us. 由于同步, 所以实际等待时间是0~30.5us.
		//如果不等待设置完成就睡眠, 则RTC会由于设置没完成, 停止计数, 唤醒后才继续完成设置并继续计数.
	}
	else
	{
		RTCCR = 0x00;     //RTC关闭
	}
	
	return SUCCESS;
}


