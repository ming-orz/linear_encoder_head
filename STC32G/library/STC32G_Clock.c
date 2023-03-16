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

#include	"STC32G_Clock.h"
#include	"STC32G_Delay.h"

//========================================================================
// 函数: void HIRCClkConfig(u8 div)
// 描述: 高速IRC时钟初始化程序.
// 参数: div: 时钟分频系数.
// 返回: none.
// 版本: V1.0, 2022-04-03
//========================================================================
void HIRCClkConfig(u8 div)
{
	HIRCCR = 0x80; //启动内部 IRC
	while (!(HIRCCR & 1)); //等待时钟稳定
	CLKDIV = div;
	CLKSEL = 0x00; //选择内部 IRC ( 默认 )
}

//========================================================================
// 函数: void XOSCClkConfig(u8 div)
// 描述: 外部晶振时钟初始化程序.
// 参数: div: 时钟分频系数.
// 返回: none.
// 版本: V1.0, 2022-04-03
//========================================================================
void XOSCClkConfig(u8 div)
{
	XOSCCR = 0xc0; //启动外部晶振
	while (!(XOSCCR & 1)); //等待时钟稳定
	CLKDIV = div;  //时钟分频
	CLKSEL = 0x01; //选择外部晶振
}

//========================================================================
// 函数: void IRC32KClkConfig(u8 div)
// 描述: 低速32K IRC时钟初始化程序.
// 参数: div: 时钟分频系数.
// 返回: none.
// 版本: V1.0, 2022-04-03
//========================================================================
void IRC32KClkConfig(u8 div)
{
	IRC32KCR = 0x80; //启动内部 32K IRC
	while (!(IRC32KCR & 1)); //等待时钟稳定
	CLKDIV = div;  //时钟分频
	CLKSEL = 0x03; //选择内部 32K
}

//========================================================================
// 函数: void HSPllClkConfig(u8 clksrc, u8 pcki, u8 pllsel, u8 div)
// 描述: 高速IO时钟初始化程序.
// 参数: clksrc: 系统时钟选择, MCLKSEL_HIRC/MCLKSEL_XIRC/MCLKSEL_X32K/MCLKSEL_I32K/MCLKSEL_PLL/MCLKSEL_PLL2/MCLKSEL_I48M.
// 参数: pllsel: PLL时钟选择, PLL_96M/PLL_144M.
// 参数: div: 高速IO时钟分频系数.
// 返回: none.
// 版本: V1.0, 2022-04-03
//========================================================================
void HSPllClkConfig(u8 clksrc, u8 pllsel, u8 div)
{
	MainClockSel(clksrc);			//系统时钟选择, MCLKSEL_HIRC/MCLKSEL_XIRC/MCLKSEL_X32K/MCLKSEL_I32K/MCLKSEL_PLL/MCLKSEL_PLL2/MCLKSEL_I48M

	//系统时钟 n 分频作为PLL时钟源,确保分频后为12M
    USBCLK &= ~PCKI_MSK;
#if (MAIN_Fosc == 12000000UL)
    USBCLK |= PCKI_D1;          //PLL输入时钟1分频
#elif (MAIN_Fosc == 24000000UL)
    USBCLK |= PCKI_D2;          //PLL输入时钟2分频
#elif (MAIN_Fosc == 48000000UL)
    USBCLK |= PCKI_D4;          //PLL输入时钟4分频
#elif (MAIN_Fosc == 96000000UL)
    USBCLK |= PCKI_D8;          //PLL输入时钟8分频
#else
    USBCLK |= PCKI_D1;          //默认PLL输入时钟1分频
#endif

	PLLClockSel(pllsel);			//PLL时钟选择, PLL_96M/PLL_144M
	PLLEnable(ENABLE);				//PLL倍频使能, ENABLE/DISABLE
	delay_ms(1);              //等待PLL锁频
	HSIOClockSel(HSCK_PLL);		//高速IO时钟选择, HSCK_MCLK/HSCK_PLL
	HSClockDiv(div);					//高速IO时钟分频系数
}


