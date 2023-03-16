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

#ifndef	__STC32G_CLOCK_H
#define	__STC32G_CLOCK_H

#include	"config.h"

//========================================================================
//                              时钟设置
//========================================================================

#define		MainClockSel(n)	CLKSEL = (CLKSEL & ~0x0f) | (n)				/* 系统时钟选择 */
#define		PLLClockSel(n)	CLKSEL = (CLKSEL & ~0x80) | (n<<7)		/* PLL时钟选择 */
#define		HSIOClockSel(n)	CLKSEL = (CLKSEL & ~0x40) | (n<<6)		/* 高速IO时钟选择 */
#define		PLLClockIn(n)		USBCLK = (USBCLK & ~0x60) | (n<<4)		/* 系统时钟 n 分频作为PLL时钟源,确保分频后为12M */
#define		PLLEnable(n)		USBCLK = (USBCLK & ~0x80) | (n<<7)		/* PLL倍频使能 */
#define		HSClockDiv(n)		HSCLKDIV = (n)		/* 高速IO时钟分频系数 */

//========================================================================
//                              定义声明
//========================================================================

/* 系统时钟选择参数 */
#define MCLKSEL_HIRC       0x00
#define MCLKSEL_XIRC       0x01
#define MCLKSEL_X32K       0x02
#define MCLKSEL_I32K       0x03
#define MCLKSEL_PLL        0x04
#define MCLKSEL_PLL2       0x08
#define MCLKSEL_I48M       0x0c

/* PLL时钟选择参数 */
#define PLL_96M         0
#define PLL_144M        1

/* 高速IO时钟选择参数 */
#define HSCK_MCLK       0
#define HSCK_PLL        1

/* 系统时钟 n 分频作为PLL时钟源参数,确保分频后为12M */
#define ENCKM           0x80
#define PCKI_MSK        0x60
#define PCKI_D1         0x00
#define PCKI_D2         0x20
#define PCKI_D4         0x40
#define PCKI_D8         0x60

//========================================================================
//                              外部声明
//========================================================================

void HSPllClkConfig(u8 clksrc, u8 pllsel, u8 div);

#endif
