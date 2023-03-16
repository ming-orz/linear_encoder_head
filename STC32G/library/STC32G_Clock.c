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
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"STC32G_Clock.h"
#include	"STC32G_Delay.h"

//========================================================================
// ����: void HIRCClkConfig(u8 div)
// ����: ����IRCʱ�ӳ�ʼ������.
// ����: div: ʱ�ӷ�Ƶϵ��.
// ����: none.
// �汾: V1.0, 2022-04-03
//========================================================================
void HIRCClkConfig(u8 div)
{
	HIRCCR = 0x80; //�����ڲ� IRC
	while (!(HIRCCR & 1)); //�ȴ�ʱ���ȶ�
	CLKDIV = div;
	CLKSEL = 0x00; //ѡ���ڲ� IRC ( Ĭ�� )
}

//========================================================================
// ����: void XOSCClkConfig(u8 div)
// ����: �ⲿ����ʱ�ӳ�ʼ������.
// ����: div: ʱ�ӷ�Ƶϵ��.
// ����: none.
// �汾: V1.0, 2022-04-03
//========================================================================
void XOSCClkConfig(u8 div)
{
	XOSCCR = 0xc0; //�����ⲿ����
	while (!(XOSCCR & 1)); //�ȴ�ʱ���ȶ�
	CLKDIV = div;  //ʱ�ӷ�Ƶ
	CLKSEL = 0x01; //ѡ���ⲿ����
}

//========================================================================
// ����: void IRC32KClkConfig(u8 div)
// ����: ����32K IRCʱ�ӳ�ʼ������.
// ����: div: ʱ�ӷ�Ƶϵ��.
// ����: none.
// �汾: V1.0, 2022-04-03
//========================================================================
void IRC32KClkConfig(u8 div)
{
	IRC32KCR = 0x80; //�����ڲ� 32K IRC
	while (!(IRC32KCR & 1)); //�ȴ�ʱ���ȶ�
	CLKDIV = div;  //ʱ�ӷ�Ƶ
	CLKSEL = 0x03; //ѡ���ڲ� 32K
}

//========================================================================
// ����: void HSPllClkConfig(u8 clksrc, u8 pcki, u8 pllsel, u8 div)
// ����: ����IOʱ�ӳ�ʼ������.
// ����: clksrc: ϵͳʱ��ѡ��, MCLKSEL_HIRC/MCLKSEL_XIRC/MCLKSEL_X32K/MCLKSEL_I32K/MCLKSEL_PLL/MCLKSEL_PLL2/MCLKSEL_I48M.
// ����: pllsel: PLLʱ��ѡ��, PLL_96M/PLL_144M.
// ����: div: ����IOʱ�ӷ�Ƶϵ��.
// ����: none.
// �汾: V1.0, 2022-04-03
//========================================================================
void HSPllClkConfig(u8 clksrc, u8 pllsel, u8 div)
{
	MainClockSel(clksrc);			//ϵͳʱ��ѡ��, MCLKSEL_HIRC/MCLKSEL_XIRC/MCLKSEL_X32K/MCLKSEL_I32K/MCLKSEL_PLL/MCLKSEL_PLL2/MCLKSEL_I48M

	//ϵͳʱ�� n ��Ƶ��ΪPLLʱ��Դ,ȷ����Ƶ��Ϊ12M
    USBCLK &= ~PCKI_MSK;
#if (MAIN_Fosc == 12000000UL)
    USBCLK |= PCKI_D1;          //PLL����ʱ��1��Ƶ
#elif (MAIN_Fosc == 24000000UL)
    USBCLK |= PCKI_D2;          //PLL����ʱ��2��Ƶ
#elif (MAIN_Fosc == 48000000UL)
    USBCLK |= PCKI_D4;          //PLL����ʱ��4��Ƶ
#elif (MAIN_Fosc == 96000000UL)
    USBCLK |= PCKI_D8;          //PLL����ʱ��8��Ƶ
#else
    USBCLK |= PCKI_D1;          //Ĭ��PLL����ʱ��1��Ƶ
#endif

	PLLClockSel(pllsel);			//PLLʱ��ѡ��, PLL_96M/PLL_144M
	PLLEnable(ENABLE);				//PLL��Ƶʹ��, ENABLE/DISABLE
	delay_ms(1);              //�ȴ�PLL��Ƶ
	HSIOClockSel(HSCK_PLL);		//����IOʱ��ѡ��, HSCK_MCLK/HSCK_PLL
	HSClockDiv(div);					//����IOʱ�ӷ�Ƶϵ��
}


