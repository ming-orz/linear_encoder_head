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

#ifndef __STC32G_PWM_H
#define __STC32G_PWM_H	 

#include	"config.h"

//========================================================================
//                               PWM设置
//========================================================================

//						               7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_ENO = 0xFEB1H;  ENO4N ENO4P ENO3N ENO3P ENO2N ENO2P ENO1N ENO1P  0000,0000  /* 输出使能寄存器 */ 
//sfr PWMB_ENO = 0xFEB5H;    -   ENO8P   -   ENO7P   -   ENO6P   -   ENO5P  0000,0000  /* 输出使能寄存器 */ 
#define		PWM1P_OUT_EN()	PWMA_ENO |= 0x01	/* 使能 PWM1P 输出 */
#define		PWM1P_OUT_DIS()	PWMA_ENO &= ~0x01	/* 禁止 PWM1P 输出 */
#define		PWM1N_OUT_EN()	PWMA_ENO |= 0x02	/* 使能 PWM1N 输出 */
#define		PWM1N_OUT_DIS()	PWMA_ENO &= ~0x02	/* 禁止 PWM1N 输出 */
#define		PWM2P_OUT_EN()	PWMA_ENO |= 0x04	/* 使能 PWM2P 输出 */
#define		PWM2P_OUT_DIS()	PWMA_ENO &= ~0x04	/* 禁止 PWM2P 输出 */
#define		PWM2N_OUT_EN()	PWMA_ENO |= 0x08	/* 使能 PWM2N 输出 */
#define		PWM2N_OUT_DIS()	PWMA_ENO &= ~0x08	/* 禁止 PWM2N 输出 */
#define		PWM3P_OUT_EN()	PWMA_ENO |= 0x10	/* 使能 PWM3P 输出 */
#define		PWM3P_OUT_DIS()	PWMA_ENO &= ~0x10	/* 禁止 PWM3P 输出 */
#define		PWM3N_OUT_EN()	PWMA_ENO |= 0x20	/* 使能 PWM3N 输出 */
#define		PWM3N_OUT_DIS()	PWMA_ENO &= ~0x20	/* 禁止 PWM3N 输出 */
#define		PWM4P_OUT_EN()	PWMA_ENO |= 0x40	/* 使能 PWM3P 输出 */
#define		PWM4P_OUT_DIS()	PWMA_ENO &= ~0x40	/* 禁止 PWM3P 输出 */
#define		PWM4N_OUT_EN()	PWMA_ENO |= 0x80	/* 使能 PWM3N 输出 */
#define		PWM4N_OUT_DIS()	PWMA_ENO &= ~0x80	/* 禁止 PWM3N 输出 */

#define		PWM5P_OUT_EN()	PWMB_ENO |= 0x01	/* 使能 PWM5P 输出 */
#define		PWM5P_OUT_DIS()	PWMB_ENO &= ~0x01	/* 禁止 PWM5P 输出 */
#define		PWM6P_OUT_EN()	PWMB_ENO |= 0x04	/* 使能 PWM6P 输出 */
#define		PWM6P_OUT_DIS()	PWMB_ENO &= ~0x04	/* 禁止 PWM6P 输出 */
#define		PWM7P_OUT_EN()	PWMB_ENO |= 0x10	/* 使能 PWM7P 输出 */
#define		PWM7P_OUT_DIS()	PWMB_ENO &= ~0x10	/* 禁止 PWM7P 输出 */
#define		PWM8P_OUT_EN()	PWMB_ENO |= 0x40	/* 使能 PWM8P 输出 */
#define		PWM8P_OUT_DIS()	PWMB_ENO &= ~0x40	/* 禁止 PWM8P 输出 */

#define		PWMA_OutChannelSel(n)		PWMA_ENO = n	//选择输出通道
#define		PWMB_OutChannelSel(n)		PWMB_ENO = n	//选择输出通道

//						              7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_PS = 0xFEB2H;  C4PS1 C4PS0 C3PS1 C3PS0 C2PS1 C2PS0 C1PS1 C1PS0  0000,0000  /* 输出使能寄存器 */ 
//sfr PWMB_PS = 0xFEB6H;  C8PS1 C8PS0 C7PS1 C7PS0 C6PS1 C6PS0 C5PS1 C5PS0  0000,0000  /* 输出使能寄存器 */ 

#define		PWM1_USE_P10P11()		PWMA_PS = (PWMA_PS & ~0x03)					/* PWM 通道 1 输出脚切换到P10(PWM1P) P11(PWM1N) */ 
#define		PWM1_USE_P20P21()		PWMA_PS = (PWMA_PS & ~0x03) | 0x01	/* PWM 通道 1 输出脚切换到P20(PWM1P) P21(PWM1N) */ 
#define		PWM1_USE_P60P61()		PWMA_PS = (PWMA_PS & ~0x03) | 0x02	/* PWM 通道 1 输出脚切换到P60(PWM1P) P61(PWM1N) */ 

#define		PWM2_USE_P12P13()		PWMA_PS = (PWMA_PS & ~0x0C)					/* PWM 通道 2 输出脚切换到P12/P54(PWM2P) P13(PWM2N) */ 
#define		PWM2_USE_P22P23()		PWMA_PS = (PWMA_PS & ~0x0C) | 0x04	/* PWM 通道 2 输出脚切换到P22(PWM2P) P23(PWM2N) */ 
#define		PWM2_USE_P62P63()		PWMA_PS = (PWMA_PS & ~0x0C) | 0x08	/* PWM 通道 2 输出脚切换到P62(PWM2P) P63(PWM2N) */ 

#define		PWM3_USE_P14P15()		PWMA_PS = (PWMA_PS & ~0x30)					/* PWM 通道 3 输出脚切换到P14(PWM3P) P15(PWM3N) */ 
#define		PWM3_USE_P24P25()		PWMA_PS = (PWMA_PS & ~0x30) | 0x10	/* PWM 通道 3 输出脚切换到P24(PWM3P) P25(PWM3N) */ 
#define		PWM3_USE_P64P65()		PWMA_PS = (PWMA_PS & ~0x30) | 0x20	/* PWM 通道 3 输出脚切换到P64(PWM3P) P65(PWM3N) */ 

#define		PWM4_USE_P16P17()		PWMA_PS = (PWMA_PS & ~0xC0)					/* PWM 通道 4 输出脚切换到P16(PWM4P) P17(PWM4N) */ 
#define		PWM4_USE_P26P27()		PWMA_PS = (PWMA_PS & ~0xC0) | 0x40	/* PWM 通道 4 输出脚切换到P26(PWM4P) P27(PWM4N) */ 
#define		PWM4_USE_P66P67()		PWMA_PS = (PWMA_PS & ~0xC0) | 0x80	/* PWM 通道 4 输出脚切换到P66(PWM4P) P67(PWM4N) */ 
#define		PWM4_USE_P34P33()		PWMA_PS = (PWMA_PS | 0xC0)					/* PWM 通道 4 输出脚切换到P34(PWM4P) P33(PWM4N) */ 

#define		PWM5_USE_P20()			PWMB_PS = (PWMB_PS & ~0x03)					/* PWM 通道 5 输出脚切换到P20(PWM5) */ 
#define		PWM5_USE_P17()			PWMB_PS = (PWMB_PS & ~0x03) | 0x01	/* PWM 通道 5 输出脚切换到P17(PWM5) */ 
#define		PWM5_USE_P00()			PWMB_PS = (PWMB_PS & ~0x03) | 0x02	/* PWM 通道 5 输出脚切换到P00(PWM5) */ 
#define		PWM5_USE_P74()			PWMB_PS = (PWMB_PS | 0x03)					/* PWM 通道 5 输出脚切换到P74(PWM5) */ 

#define		PWM6_USE_P21()			PWMB_PS = (PWMB_PS & ~0x0C)					/* PWM 通道 6 输出脚切换到P21(PWM6) */ 
#define		PWM6_USE_P54()			PWMB_PS = (PWMB_PS & ~0x0C) | 0x04	/* PWM 通道 6 输出脚切换到P54(PWM6) */ 
#define		PWM6_USE_P01()			PWMB_PS = (PWMB_PS & ~0x0C) | 0x08	/* PWM 通道 6 输出脚切换到P01(PWM6) */ 
#define		PWM6_USE_P75()			PWMB_PS = (PWMB_PS | 0x0C)					/* PWM 通道 6 输出脚切换到P75(PWM6) */ 

#define		PWM7_USE_P22()			PWMB_PS = (PWMB_PS & ~0x30)					/* PWM 通道 7 输出脚切换到P22(PWM7) */ 
#define		PWM7_USE_P33()			PWMB_PS = (PWMB_PS & ~0x30) | 0x10	/* PWM 通道 7 输出脚切换到P33(PWM7) */ 
#define		PWM7_USE_P02()			PWMB_PS = (PWMB_PS & ~0x30) | 0x20	/* PWM 通道 7 输出脚切换到P02(PWM7) */ 
#define		PWM7_USE_P76()			PWMB_PS = (PWMB_PS | 0x30)					/* PWM 通道 7 输出脚切换到P76(PWM7) */ 

#define		PWM8_USE_P23()			PWMB_PS = (PWMB_PS & ~0xC0)					/* PWM 通道 8 输出脚切换到P23(PWM8) */ 
#define		PWM8_USE_P34()			PWMB_PS = (PWMB_PS & ~0xC0) | 0x40	/* PWM 通道 8 输出脚切换到P34(PWM8) */ 
#define		PWM8_USE_P03()			PWMB_PS = (PWMB_PS & ~0xC0) | 0x80	/* PWM 通道 8 输出脚切换到P03(PWM8) */ 
#define		PWM8_USE_P77()			PWMB_PS = (PWMB_PS | 0xC0)					/* PWM 通道 8 输出脚切换到P77(PWM8) */ 

//						                 7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_IOAUX = 0xFEB3H;  AUX4N AUX4P AUX3N AUX3P AUX2N AUX2P AUX1N AUX1P  0000,0000  /* 输出附加使能寄存器 */ 
//sfr PWMB_IOAUX = 0xFEB7H;    -   AUX8P   -   AUX7P   -   AUX6P   -   AUX5P  0000,0000  /* 输出附加使能寄存器 */ 
#define AUX4N			(1<<7)
#define AUX4P			(1<<6)
#define AUX3N			(1<<5)
#define AUX3P			(1<<4)
#define AUX2N			(1<<3)
#define AUX2P			(1<<2)
#define AUX1N			(1<<1)
#define AUX1P			(1)

#define AUX8P			(1<<6)
#define AUX7P			(1<<4)
#define AUX6P			(1<<2)
#define AUX5P			(1)


//						               7     6     5    4    3    2    1     0    Reset Value
//sfr PWMA_CR1 = 0xFEC0H;  ARPEA CMSA1 CMSA0 DIRA OPMA URSA UDISA CENA  0000,0000  /* 控制寄存器 1 */ 
//sfr PWMB_CR1 = 0xFEE0H;  ARPEB CMSB1 CMSB0 DIRB OPMB URSB UDISB CENB  0000,0000  /* 控制寄存器 1 */ 
#define ARPE1			(1<<7)
#define ARPE2			(1<<7)
#define PWMA_AlignMode_Edge()			PWMA_CR1 = (PWMA_CR1 & ~0x60)
#define PWMA_AlignMode_Mid1()			PWMA_CR1 = (PWMA_CR1 & ~0x60) | 0x20
#define PWMA_AlignMode_Mid2()			PWMA_CR1 = (PWMA_CR1 & ~0x60) | 0x40
#define PWMA_AlignMode_Mid3()			PWMA_CR1 = (PWMA_CR1 | 0x60)
#define PWMA_DIR_UP()							PWMA_CR1 &= ~0x10
#define PWMA_DIR_DN()							PWMA_CR1 |= 0x10
#define PWMA_OPMA(n)							(n==1?(PWMA_CR1 |= 0x08):(PWMA_CR1 &= ~0x08))	//单脉冲模式 0：在发生更新事件时，计数器不停止；1：在发生下一次更新事件时，清除 CEN 位，计数器停止
#define PWMA_URSA(n)							(n==1?(PWMA_CR1 |= 0x04):(PWMA_CR1 &= ~0x04))	//更新请求源
#define PWMA_UDISA(n)							(n==1?(PWMA_CR1 |= 0x02):(PWMA_CR1 &= ~0x02))	//禁止更新 0：产生更新（UEV）事件；1：不产生更新事件
//#define PWMA_CEN_Enable()					PWMA_CR1 |= 0x01		//1：使能计数器
#define PWMA_CEN_Disable()				PWMA_CR1 &= ~0x01		//0：禁止计数器
#define PWMA_CEN_Enable(n)				(n==1?(PWMA_CR1 |= 0x01):(PWMA_CR1 &= ~0x01))		//1：使能计数器

#define PWMB_AlignMode_Edge()			PWMB_CR1 = (PWMB_CR1 & ~0x60)
#define PWMB_AlignMode_Mid1()			PWMB_CR1 = (PWMB_CR1 & ~0x60) | 0x20
#define PWMB_AlignMode_Mid2()			PWMB_CR1 = (PWMB_CR1 & ~0x60) | 0x40
#define PWMB_AlignMode_Mid3()			PWMB_CR1 = (PWMB_CR1 | 0x60)
#define PWMB_DIR_UP()							PWMB_CR1 &= ~0x10
#define PWMB_DIR_DN()							PWMB_CR1 |= 0x10
#define PWMB_OPMB(n)							(n==1?(PWMB_CR1 |= 0x08):(PWMB_CR1 &= ~0x08))	//单脉冲模式 0：在发生更新事件时，计数器不停止；1：在发生下一次更新事件时，清除 CEN 位，计数器停止
#define PWMB_URSB(n)							(n==1?(PWMB_CR1 |= 0x04):(PWMB_CR1 &= ~0x04))	//更新请求源
#define PWMB_UDISB(n)							(n==1?(PWMB_CR1 |= 0x02):(PWMB_CR1 &= ~0x02))	//禁止更新 0：产生更新（UEV）事件；1：不产生更新事件
//#define PWMB_CEN_Enable()					PWMB_CR1 |= 0x01		//1：使能计数器
#define PWMB_CEN_Disable()				PWMB_CR1 &= ~0x01		//0：禁止计数器
#define PWMB_CEN_Enable(n)				(n==1?(PWMB_CR1 |= 0x01):(PWMB_CR1 &= ~0x01))		//1：使能计数器


//						               7     6     5    4    3    2    1    0    Reset Value
//sfr PWMA_CR2 = 0xFEC1H;  TI1S MMSA2 MMSA1 MMSA0  -  COMSA  -  CCPCA  0000,x0x0  /* 控制寄存器 2 */ 
//sfr PWMB_CR2 = 0xFEE1H;  TI5S MMSB2 MMSB1 MMSB0  -  COMSB  -  CCPCB  0000,x0xx  /* 控制寄存器 2 */ 
#define PWM1P_TI1()							PWMA_CR2 &= ~0x80
#define PWM1P2P3P_XOR_TI1()			PWMA_CR2 |= 0x80
#define PWM5P_TI2()							PWMB_CR2 &= ~0x80
#define PWM5P6P7P_XOR_TI2()			PWMB_CR2 |= 0x80

#define MMSn_RESET					0		//复位
#define MMSn_ENABLE					1		//使能
#define MMSn_UPDATE					2		//更新
#define MMSn_COMP_TRGO			3		//比较脉冲
#define MMSn_OC1REF_TRGO		4		//比较
#define MMSn_OC2REF_TRGO		5		//比较
#define MMSn_OC3REF_TRGO		6		//比较
#define MMSn_OC4REF_TRGO		7		//比较

#define PWMA_MainModeSel(n)		PWMA_CR2 = (PWMA_CR2 & ~0x70) | (n<<4)	//主模式选择
#define PWMB_MainModeSel(n)		PWMB_CR2 = (PWMB_CR2 & ~0x70) | (n<<4)	//主模式选择

//0：当 CCPC=1 时，只有在 COMG 位置 1 的时候这些控制位才被更新
//1：当 CCPC=1 时，只有在 COMG 位置 1 或 TRGI 发生上升沿的时候这些控制位才被更新
#define PWMA_COMSUpdateCtrl(n)		PWMA_CR2 = (n==1?(PWMA_CR2 |= 0x04):(PWMA_CR2 &= ~0x04))	//捕获/比较控制位的更新控制选择
#define PWMB_COMSUpdateCtrl(n)		PWMB_CR2 = (n==1?(PWMB_CR2 |= 0x04):(PWMB_CR2 &= ~0x04))	//捕获/比较控制位的更新控制选择
//0： CCIE， CCINE， CCiP， CCiNP 和 OCIM 位不是预装载的
//1： CCIE， CCINE， CCiP， CCiNP 和 OCIM 位是预装载的；设置该位后，它们只在设置了 COMG位后被更新。
#define PWMA_CCPCAPreloaded(n)		PWMA_CR2 = (n==1?(PWMA_CR2 |= 0x01):(PWMA_CR2 &= ~0x01))	//捕获/比较预装载控制位(该位只对具有互补输出的通道起作用)
#define PWMB_CCPCBPreloaded(n)		PWMA_CR2 = (n==1?(PWMA_CR2 |= 0x01):(PWMA_CR2 &= ~0x01))	//捕获/比较预装载控制位(该位只对具有互补输出的通道起作用)


//						               7    6    5    4    3    2     1     0    Reset Value
//sfr PWMA_SMCR = 0xFEC2H;  MSMA TSA2 TSA1 TSA0  -  SMSA2 SMSA1 SMSA0  0000,x000  /* 从模式控制寄存器 */ 
//sfr PWMB_SMCR = 0xFEE2H;  MSMB TSB2 TSB1 TSB0  -  SMSB2 SMSB1 SMSB0  0000,x000  /* 从模式控制寄存器 */ 
#define SMCR_TSn_ITR2				2
#define SMCR_TSn_EDGE				4
#define SMCR_TSn_TIMER1			5
#define SMCR_TSn_TIMER2			6
#define SMCR_TSn_ETRF				7

#define PWMA_SMCR_Source(n)		PWMA_SMCR = (PWMA_SMCR & ~0x70) | (n<<4)	//触发源选择
#define PWMB_SMCR_Source(n)		PWMB_SMCR = (PWMB_SMCR & ~0x70) | (n<<4)	//触发源选择

#define SMCR_SMSA_INSIDE_CLK			0
#define SMCR_SMSA_ENCODER_M1			1
#define SMCR_SMSA_ENCODER_M2			2
#define SMCR_SMSA_ENCODER_M3			3
#define SMCR_SMSA_RESET						4
#define SMCR_SMSA_GATE						5
#define SMCR_SMSA_TRIG						6
#define SMCR_SMSA_EXT_CLK					7

#define PWMA_SMCR_SMS(n)		PWMA_SMCR = (PWMA_SMCR & ~0x07) | (n & 7)	//时钟/触发/从模式选择
#define PWMB_SMCR_SMS(n)		PWMB_SMCR = (PWMB_SMCR & ~0x07) | (n & 7)	//时钟/触发/从模式选择

//						               7    6    5      4     3     2     1     0     Reset Value
//sfr PWMA_ETR = 0xFEC3H;  ETP1 ECE1 ETPS11 ETPS10 ETF13 ETF12 ETF11 ETF10  0000,0000  /* 外部触发寄存器 */ 
//sfr PWMB_ETR = 0xFEE3H;  ETP2 ECE2 ETPS21 ETPS20 ETF23 ETF22 ETF21 ETF20  0000,0000  /* 外部触发寄存器 */ 

//						               7    6    5      4     3     2     1    0    Reset Value
//sfr PWMA_IER = 0xFEC4H;  BIEA TIEA COMIEA CC4IE CC3IE CC2IE CC1IE UIEA  0000,0000  /* 中断使能寄存器 */ 
//sfr PWMB_IER = 0xFEE4H;  BIEB TIEB COMIEB CC8IE CC7IE CC6IE CC5IE UIEB  0000,0000  /* 中断使能寄存器 */ 
#define PWMA_UIEA_Enable()		PWMA_IER |= 0x01		//1：允许更新中断
#define PWMA_UIEA_Disable()		PWMA_IER &= ~0x01		//0：禁止更新中断
#define PWMA_CC1IE_Enable()		PWMA_IER |= 0x02		//1：允许捕获/比较中断
#define PWMA_CC1IE_Disable()	PWMA_IER &= ~0x02		//0：禁止捕获/比较中断
#define PWMA_CC2IE_Enable()		PWMA_IER |= 0x04		//1：允许捕获/比较中断
#define PWMA_CC2IE_Disable()	PWMA_IER &= ~0x04		//0：禁止捕获/比较中断
#define PWMA_CC3IE_Enable()		PWMA_IER |= 0x08		//1：允许捕获/比较中断
#define PWMA_CC3IE_Disable()	PWMA_IER &= ~0x08		//0：禁止捕获/比较中断
#define PWMA_CC4IE_Enable()		PWMA_IER |= 0x10		//1：允许捕获/比较中断
#define PWMA_CC4IE_Disable()	PWMA_IER &= ~0x10		//0：禁止捕获/比较中断
#define PWMA_COMIEA_Enable()	PWMA_IER |= 0x20		//1：允许COM中断
#define PWMA_COMIEA_Disable()	PWMA_IER &= ~0x20		//0：禁止COM中断
#define PWMA_TIEA_Enable()		PWMA_IER |= 0x40		//1：允许触发中断
#define PWMA_TIEA_Disable()		PWMA_IER &= ~0x40		//0：禁止触发中断
#define PWMA_BIEA_Enable()		PWMA_IER |= 0x80		//1：允许刹车中断
#define PWMA_BIEA_Disable()		PWMA_IER &= ~0x80		//0：禁止刹车中断

//						               7    6    5      4     3     2     1    0    Reset Value
//sfr PWMA_SR1 = 0xFEC5H;  BIF1 TIF1 COMIF1 CC4IF CC3IF CC2IF CC1IF UIF1  0000,0000  /* 状态寄存器 1 */ 
//sfr PWMB_SR1 = 0xFEE5H;  BIF2 TIF2 COMIF2 CC8IF CC7IF CC6IF CC5IF UIF2  0000,0000  /* 状态寄存器 1 */ 
#define UIF1			1
#define CC1IF			(1<<1)
#define CC2IF			(1<<2)
#define CC3IF			(1<<3)
#define CC4IF			(1<<4)
#define COMIF1		(1<<5)
#define TIF1			(1<<6)
#define BIF1			(1<<7)

#define UIF2			1
#define CC5IF			(1<<1)
#define CC6IF			(1<<2)
#define CC7IF			(1<<3)
#define CC8IF			(1<<4)
#define COMIF2		(1<<5)
#define TIF2			(1<<6)
#define BIF2			(1<<7)

//						              7   6   5    4     3     2     1    0   Reset Value
//sfr PWMA_SR2 = 0xFEC6H;   -   -   -  CC4OF CC3OF CC2OF CC1OF  -   xxx0,000x  /* 状态寄存器 2 */ 
//sfr PWMB_SR2 = 0xFEE6H;   -   -   -  CC8OF CC7OF CC6OF CC5OF  -   xxx0,000x  /* 状态寄存器 2 */ 

//						              7   6    5    4    3    2    1    0   Reset Value
//sfr PWMA_EGR = 0xFEC7H;  BG1 TG1 COMG1 CC4G CC3G CC2G CC1G UG1  0000,0000  /* 事件产生寄存器 */ 
//sfr PWMB_EGR = 0xFEE7H;  BG2 TG2 COMG2 CC8G CC7G CC6G CC5G UG2  0000,0000  /* 事件产生寄存器 */ 

//						                 7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_CCMR1 = 0xFEC8H;  OC1CE OC1M2 OC1M1 OC1M0 OC1PE OC1FE CC1S1 CC1S0  0000,0000  /* 捕获/比较模式寄存器 1 - 通道配置为比较输出模式 */ 
//sfr PWMB_CCMR1 = 0xFEE8H;  OC5CE OC5M2 OC5M1 OC5M0 OC5PE OC5FE CC5S1 CC5S0  0000,0000  /* 捕获/比较模式寄存器 1 - 通道配置为比较输出模式 */ 
#define OCnCE			(1<<7)

#define CCMRn_FREEZE							0x00		//冻结
#define CCMRn_MATCH_VALID					0x10		//匹配时设置通道 n 的输出为有效电平
#define CCMRn_MATCH_INVALID				0x20		//匹配时设置通道 n 的输出为无效电平
#define CCMRn_ROLLOVER						0x30		//翻转
#define CCMRn_FORCE_INVALID				0x40		//强制为无效电平
#define CCMRn_FORCE_VALID					0x50		//强制为有效电平
#define CCMRn_PWM_MODE1						0x60		//PWM 模式 1
#define CCMRn_PWM_MODE2						0x70		//PWM 模式 2

#define PWMA_OC1ModeSet(n)				PWMA_CCMR1 = (PWMA_CCMR1 & ~0x70) | (n)		//输出比较模式设置
#define PWMB_OC5ModeSet(n)				PWMB_CCMR1 = (PWMB_CCMR1 & ~0x70) | (n)		//输出比较模式设置

#define PWMA_OC1_ReloadEnable(n)	(n==1?(PWMA_CCMR1 |= 0x08):(PWMA_CCMR1 &= ~0x08))		//开启 OC1PE 输出比较的预装载功能
#define PWMB_OC5_ReloadEnable(n)	(n==1?(PWMB_CCMR1 |= 0x08):(PWMB_CCMR1 &= ~0x08))		//开启 OC5PE 输出比较的预装载功能
//#define PWMA_OC1_ReloadEnable()		PWMA_CCMR1 |= 0x08		//1：开启 OC1PE 输出比较的预装载功能
//#define PWMA_OC1_RelosdDisable()	PWMA_CCMR1 &= ~0x08		//0：禁止 OC1PE 输出比较的预装载功能
//#define PWMB_OC5_ReloadEnable()		PWMB_CCMR1 |= 0x08		//1：开启 OC5PE 输出比较的预装载功能
//#define PWMB_OC5_RelosdDisable()	PWMB_CCMR1 &= ~0x08		//0：禁止 OC5PE 输出比较的预装载功能

#define PWMA_OC1_FastEnable(n)		(n==1?(PWMA_CCMR1 |= 0x04):(PWMA_CCMR1 &= ~0x04))		//1：开启 OC1FE 输出比较快速功能
#define PWMB_OC5_FastEnable(n)		(n==1?(PWMB_CCMR1 |= 0x04):(PWMB_CCMR1 &= ~0x04))		//1：开启 OC5FE 输出比较快速功能
//#define PWMA_OC1_FastEnable()			PWMA_CCMR1 |= 0x04		//1：开启 OC1FE 输出比较快速功能
//#define PWMA_OC1_FastDisable()		PWMA_CCMR1 &= ~0x04		//0：禁止 OC1FE 输出比较快速功能
//#define PWMB_OC5_FastEnable()			PWMB_CCMR1 |= 0x04		//1：开启 OC5FE 输出比较快速功能
//#define PWMB_OC5_FastDisable()		PWMB_CCMR1 &= ~0x04		//0：禁止 OC5FE 输出比较快速功能

#define CCAS_OUTPUT						0x00		//输出
#define CCAS_IUTPUT_TI1FP1		0x01		//输入，IC1/IC2/IC3/IC4 映射在 TI1FP1 上
#define CCAS_IUTPUT_TI2FP1		0x02		//输入，IC1/IC2/IC3/IC4 映射在 TI2FP1 上
#define CCAS_IUTPUT_TRC				0x03		//输入，IC1/IC2/IC3/IC4 映射在 TRC 上
#define CCBS_OUTPUT						0x00		//输出
#define CCBS_IUTPUT_TI5FP5		0x01		//输入，IC5/IC6/IC7/IC8 映射在 TI5FP5 上
#define CCBS_IUTPUT_TI6FP5		0x02		//输入，IC5/IC6/IC7/IC8 映射在 TI6FP5 上
#define CCBS_IUTPUT_TRC				0x03		//输入，IC5/IC6/IC7/IC8 映射在 TRC 上

#define PWMA_CC1S_Direction(n)		PWMA_CCMR1 = (PWMA_CCMR1 & ~0x03) | (n)		//捕获/比较 1 选择。这两位定义通道的方向（输入/输出），及输入脚的选择
#define PWMB_CC5S_Direction(n)		PWMB_CCMR1 = (PWMB_CCMR1 & ~0x03) | (n)		//捕获/比较 5 选择。这两位定义通道的方向（输入/输出），及输入脚的选择

//						                 7     6     5     4      3       2      1     0    Reset Value
//sfr PWMA_CCMR1 = 0xFEC8H;  IC1F3 IC1F2 IC1F1 IC1F0 IC1PSC1 IC1PSC0 CC1S1 CC1S0  0000,0000  /* 捕获/比较模式寄存器 1 - 通道配置为捕获输入模式 */ 
//sfr PWMB_CCMR1 = 0xFEE8H;  IC5F3 IC5F2 IC5F1 IC5F0 IC5PSC1 IC5PSC0 CC5S1 CC5S0  0000,0000  /* 捕获/比较模式寄存器 1 - 通道配置为捕获输入模式 */ 

#define ICnF_01_Clock			0
#define ICnF_02_Clock			1
#define ICnF_04_Clock			2
#define ICnF_08_Clock			3
#define ICnF_12_Clock			4
#define ICnF_16_Clock			5
#define ICnF_24_Clock			6
#define ICnF_32_Clock			7
#define ICnF_48_Clock			8
#define ICnF_64_Clock			9
#define ICnF_80_Clock			10
#define ICnF_96_Clock			11
#define ICnF_128_Clock		12
#define ICnF_160_Clock		13
#define ICnF_192_Clock		14
#define ICnF_256_Clock		15

#define PWMA_IC1F_FilterClock(n)	PWMA_CCMR1 = (PWMA_CCMR1 & 0x0F) | (n<<4)		//输入捕获 1 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度
#define PWMB_IC5F_FilterClock(n)	PWMB_CCMR1 = (PWMB_CCMR1 & 0x0F) | (n<<4)		//输入捕获 5 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度

#define PWMA_IC1PSC_PrescalerSet(n)		PWMA_CCMR1 = (PWMA_CCMR1 & 0xF3) | ((n&3)<<2)		//输入/捕获 1 预分频器，0~3
#define PWMB_IC5PSC_PrescalerSet(n)		PWMB_CCMR1 = (PWMB_CCMR1 & 0xF3) | ((n&3)<<2)		//输入/捕获 5 预分频器，0~3

//						                 7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_CCMR2 = 0xFEC9H;  OC2CE OC2M2 OC2M1 OC2M0 OC2PE OC2FE CC2S1 CC2S0  0000,0000  /* 捕获/比较模式寄存器 2 - 通道配置为比较输出模式 */ 
//sfr PWMB_CCMR2 = 0xFEE9H;  OC6CE OC6M2 OC6M1 OC6M0 OC6PE OC6FE CC6S1 CC6S0  0000,0000  /* 捕获/比较模式寄存器 2 - 通道配置为比较输出模式 */ 

#define PWMA_OC2ModeSet(n)				PWMA_CCMR2 = (PWMA_CCMR2 & ~0x70) | (n)		//输出比较模式设置
#define PWMB_OC6ModeSet(n)				PWMB_CCMR2 = (PWMB_CCMR2 & ~0x70) | (n)		//输出比较模式设置

#define PWMA_OC2_ReloadEnable()		PWMA_CCMR2 |= 0x08		//1：开启 OC2PE 输出比较的预装载功能
#define PWMA_OC2_RelosdDisable()	PWMA_CCMR2 &= ~0x08		//0：禁止 OC2PE 输出比较的预装载功能
#define PWMB_OC6_ReloadEnable()		PWMB_CCMR2 |= 0x08		//1：开启 OC6PE 输出比较的预装载功能
#define PWMB_OC6_RelosdDisable()	PWMB_CCMR2 &= ~0x08		//0：禁止 OC6PE 输出比较的预装载功能

#define PWMA_OC2_FastEnable()			PWMA_CCMR2 |= 0x04		//1：开启 OC2FE 输出比较快速功能
#define PWMA_OC2_FastDisable()		PWMA_CCMR2 &= ~0x04		//0：禁止 OC2FE 输出比较快速功能
#define PWMB_OC6_FastEnable()			PWMB_CCMR2 |= 0x04		//1：开启 OC6FE 输出比较快速功能
#define PWMB_OC6_FastDisable()		PWMB_CCMR2 &= ~0x04		//0：禁止 OC6FE 输出比较快速功能

#define PWMA_CC2S_Direction(n)		PWMA_CCMR2 = (PWMA_CCMR2 & ~0x03) | (n)		//捕获/比较 2 选择。这两位定义通道的方向（输入/输出），及输入脚的选择
#define PWMB_CC6S_Direction(n)		PWMB_CCMR2 = (PWMB_CCMR2 & ~0x03) | (n)		//捕获/比较 6 选择。这两位定义通道的方向（输入/输出），及输入脚的选择

//						                 7     6     5     4      3       2      1     0    Reset Value
//sfr PWMA_CCMR2 = 0xFEC9H;  IC2F3 IC2F2 IC2F1 IC2F0 IC2PSC1 IC2PSC0 CC2S1 CC2S0  0000,0000  /* 捕获/比较模式寄存器 2 - 通道配置为捕获输入模式 */ 
//sfr PWMB_CCMR2 = 0xFEE9H;  IC6F3 IC6F2 IC6F1 IC6F0 IC6PSC1 IC6PSC0 CC6S1 CC6S0  0000,0000  /* 捕获/比较模式寄存器 2 - 通道配置为捕获输入模式 */ 

#define PWMA_IC2F_FilterClock(n)	PWMA_CCMR2 = (PWMA_CCMR2 & 0x0F) | (n<<4)		//输入捕获 2 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度
#define PWMB_IC6F_FilterClock(n)	PWMB_CCMR2 = (PWMB_CCMR2 & 0x0F) | (n<<4)		//输入捕获 6 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度

#define PWMA_IC2PSC_PrescalerSet(n)		PWMA_CCMR2 = (PWMA_CCMR2 & 0xF3) | ((n&3)<<2)		//输入/捕获 2 预分频器，0~3
#define PWMB_IC6PSC_PrescalerSet(n)		PWMB_CCMR2 = (PWMB_CCMR2 & 0xF3) | ((n&3)<<2)		//输入/捕获 6 预分频器，0~3

//						                 7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_CCMR3 = 0xFECAH;  OC3CE OC3M2 OC3M1 OC3M0 OC3PE OC3FE CC3S1 CC3S0  0000,0000  /* 捕获/比较模式寄存器 3 - 通道配置为比较输出模式 */ 
//sfr PWMB_CCMR3 = 0xFEEAH;  OC7CE OC7M2 OC7M1 OC7M0 OC7PE OC7FE CC7S1 CC7S0  0000,0000  /* 捕获/比较模式寄存器 3 - 通道配置为比较输出模式 */ 

#define PWMA_OC3ModeSet(n)				PWMA_CCMR3 = (PWMA_CCMR3 & ~0x70) | (n)		//输出比较模式设置
#define PWMB_OC7ModeSet(n)				PWMB_CCMR3 = (PWMB_CCMR3 & ~0x70) | (n)		//输出比较模式设置

#define PWMA_OC3_ReloadEnable()		PWMA_CCMR3 |= 0x08		//1：开启 OC3PE 输出比较的预装载功能
#define PWMA_OC3_RelosdDisable()	PWMA_CCMR3 &= ~0x08		//0：禁止 OC3PE 输出比较的预装载功能
#define PWMB_OC7_ReloadEnable()		PWMB_CCMR3 |= 0x08		//1：开启 OC7PE 输出比较的预装载功能
#define PWMB_OC7_RelosdDisable()	PWMB_CCMR3 &= ~0x08		//0：禁止 OC7PE 输出比较的预装载功能

#define PWMA_OC3_FastEnable()			PWMA_CCMR3 |= 0x04		//1：开启 OC3FE 输出比较快速功能
#define PWMA_OC3_FastDisable()		PWMA_CCMR3 &= ~0x04		//0：禁止 OC3FE 输出比较快速功能
#define PWMB_OC7_FastEnable()			PWMB_CCMR3 |= 0x04		//1：开启 OC7FE 输出比较快速功能
#define PWMB_OC7_FastDisable()		PWMB_CCMR3 &= ~0x04		//0：禁止 OC7FE 输出比较快速功能

#define PWMA_CC3S_Direction(n)		PWMA_CCMR3 = (PWMA_CCMR3 & ~0x03) | (n)		//捕获/比较 3 选择。这两位定义通道的方向（输入/输出），及输入脚的选择
#define PWMB_CC7S_Direction(n)		PWMB_CCMR3 = (PWMB_CCMR3 & ~0x03) | (n)		//捕获/比较 7 选择。这两位定义通道的方向（输入/输出），及输入脚的选择

//						                 7     6     5     4      3       2      1     0    Reset Value
//sfr PWMA_CCMR3 = 0xFECAH;  IC3F3 IC3F2 IC3F1 IC3F0 IC3PSC1 IC3PSC0 CC3S1 CC3S0  0000,0000  /* 捕获/比较模式寄存器 3 - 通道配置为捕获输入模式 */ 
//sfr PWMB_CCMR3 = 0xFEEAH;  IC7F3 IC7F2 IC7F1 IC7F0 IC7PSC1 IC7PSC0 CC7S1 CC7S0  0000,0000  /* 捕获/比较模式寄存器 3 - 通道配置为捕获输入模式 */ 

#define PWMA_IC3F_FilterClock(n)	PWMA_CCMR3 = (PWMA_CCMR3 & 0x0F) | (n<<4)		//输入捕获 3 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度
#define PWMB_IC7F_FilterClock(n)	PWMB_CCMR3 = (PWMB_CCMR3 & 0x0F) | (n<<4)		//输入捕获 7 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度

#define PWMA_IC3PSC_PrescalerSet(n)		PWMA_CCMR3 = (PWMA_CCMR3 & 0xF3) | ((n&3)<<2)		//输入/捕获 3 预分频器，0~3
#define PWMB_IC7PSC_PrescalerSet(n)		PWMB_CCMR3 = (PWMB_CCMR3 & 0xF3) | ((n&3)<<2)		//输入/捕获 7 预分频器，0~3

//						                 7     6     5     4     3     2     1     0    Reset Value
//sfr PWMA_CCMR4 = 0xFECBH;  OC4CE OC4M2 OC4M1 OC4M0 OC4PE OC4FE CC4S1 CC4S0  0000,0000  /* 捕获/比较模式寄存器 4 - 通道配置为比较输出模式 */ 
//sfr PWMB_CCMR4 = 0xFEEBH;  OC8CE OC8M2 OC8M1 OC8M0 OC8PE OC8FE CC8S1 CC8S0  0000,0000  /* 捕获/比较模式寄存器 4 - 通道配置为比较输出模式 */ 

#define PWMA_OC4ModeSet(n)				PWMA_CCMR4 = (PWMA_CCMR4 & ~0x70) | (n)		//输出比较模式设置
#define PWMB_OC8ModeSet(n)				PWMB_CCMR4 = (PWMB_CCMR4 & ~0x70) | (n)		//输出比较模式设置

#define PWMA_OC4_ReloadEnable()		PWMA_CCMR4 |= 0x08		//1：开启 OC4PE 输出比较的预装载功能
#define PWMA_OC4_RelosdDisable()	PWMA_CCMR4 &= ~0x08		//0：禁止 OC4PE 输出比较的预装载功能
#define PWMB_OC8_ReloadEnable()		PWMB_CCMR4 |= 0x08		//1：开启 OC8PE 输出比较的预装载功能
#define PWMB_OC8_RelosdDisable()	PWMB_CCMR4 &= ~0x08		//0：禁止 OC8PE 输出比较的预装载功能

#define PWMA_OC4_FastEnable()			PWMA_CCMR4 |= 0x04		//1：开启 OC4FE 输出比较快速功能
#define PWMA_OC4_FastDisable()		PWMA_CCMR4 &= ~0x04		//0：禁止 OC4FE 输出比较快速功能
#define PWMB_OC8_FastEnable()			PWMB_CCMR4 |= 0x04		//1：开启 OC8FE 输出比较快速功能
#define PWMB_OC8_FastDisable()		PWMB_CCMR4 &= ~0x04		//0：禁止 OC8FE 输出比较快速功能

#define PWMA_CC4S_Direction(n)		PWMA_CCMR4 = (PWMA_CCMR4 & ~0x03) | (n)		//捕获/比较 4 选择。这两位定义通道的方向（输入/输出），及输入脚的选择
#define PWMB_CC8S_Direction(n)		PWMB_CCMR4 = (PWMB_CCMR4 & ~0x03) | (n)		//捕获/比较 8 选择。这两位定义通道的方向（输入/输出），及输入脚的选择

//						                 7     6     5     4      3       2      1     0    Reset Value
//sfr PWMA_CCMR4 = 0xFECBH;  IC4F3 IC4F2 IC4F1 IC4F0 IC4PSC1 IC4PSC0 CC4S1 CC4S0  0000,0000  /* 捕获/比较模式寄存器 4 - 通道配置为捕获输入模式 */ 
//sfr PWMB_CCMR4 = 0xFEEBH;  IC8F3 IC8F2 IC8F1 IC8F0 IC8PSC1 IC8PSC0 CC8S1 CC8S0  0000,0000  /* 捕获/比较模式寄存器 4 - 通道配置为捕获输入模式 */ 

#define PWMA_IC4F_FilterClock(n)	PWMA_CCMR4 = (PWMA_CCMR4 & 0x0F) | (n<<4)		//输入捕获 4 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度
#define PWMB_IC8F_FilterClock(n)	PWMB_CCMR4 = (PWMB_CCMR4 & 0x0F) | (n<<4)		//输入捕获 8 滤波器选择，该位域定义了 TIn 的采样频率及数字滤波器长度

#define PWMA_IC4PSC_PrescalerSet(n)		PWMA_CCMR4 = (PWMA_CCMR4 & 0xF3) | ((n&3)<<2)		//输入/捕获 4 预分频器，0~3
#define PWMB_IC8PSC_PrescalerSet(n)		PWMB_CCMR4 = (PWMB_CCMR4 & 0xF3) | ((n&3)<<2)		//输入/捕获 8 预分频器，0~3

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CCER1 = 0xFECCH;  CC2NP CC2NE CC2P CC2E CC1NP CC1NE CC1P CC1E  0000,0000  /* 捕获/比较使能寄存器 1 */ 
//sfr PWMB_CCER1 = 0xFEECH;    -     -   CC6P CC6E   -     -   CC5P CC5E  0000,0000  /* 捕获/比较使能寄存器 1 */ 

//#define PWMA_CC1E_Enable(n)				PWMA_CCER1 = (PWMA_CCER1 & ~0x01) | (n)				//开启输入捕获/比较输出
//#define PWMA_CC1NE_Enable(n)			PWMA_CCER1 = (PWMA_CCER1 & ~0x04) | (n << 2)	//开启比较输出

#define PWMA_CCER1_Disable()			PWMA_CCER1 = 0x00			//关闭所有输入捕获/比较输出
#define PWMA_CC1E_Enable()				PWMA_CCER1 |= 0x01		//1：开启输入捕获/比较输出
#define PWMA_CC1E_Disable()				PWMA_CCER1 &= ~0x01		//0：关闭输入捕获/比较输出
#define PWMA_CC1P_LowValid()			PWMA_CCER1 |= 0x02		//1：低电平有效
#define PWMA_CC1P_HighValid()			PWMA_CCER1 &= ~0x02		//0：高电平有效
#define PWMA_CC1P_CaptureRise()		PWMA_CCER1 |= 0x02		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMA_CC1P_CaptureFall()		PWMA_CCER1 &= ~0x02		//0：捕获发生在 TI1F 或 TI2F 的上升沿
#define PWMA_CC1NE_Enable()				PWMA_CCER1 |= 0x04		//1：开启比较输出
#define PWMA_CC1NE_Disable()			PWMA_CCER1 &= ~0x04		//0：关闭比较输出
#define PWMA_CC1NP_LowValid()			PWMA_CCER1 |= 0x08		//1：低电平有效
#define PWMA_CC1NP_HighValid()		PWMA_CCER1 &= ~0x08		//0：高电平有效

#define PWMA_CC2E_Enable()				PWMA_CCER1 |= 0x10		//1：开启输入捕获/比较输出
#define PWMA_CC2E_Disable()				PWMA_CCER1 &= ~0x10		//0：关闭输入捕获/比较输出
#define PWMA_CC2P_LowValid()			PWMA_CCER1 |= 0x20		//1：低电平有效
#define PWMA_CC2P_HighValid()			PWMA_CCER1 &= ~0x20		//0：高电平有效
#define PWMA_CC2P_CaptureRise()		PWMA_CCER1 |= 0x20		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMA_CC2P_CaptureFall()		PWMA_CCER1 &= ~0x20		//0：捕获发生在 TI1F 或 TI2F 的上升沿
#define PWMA_CC2NE_Enable()				PWMA_CCER1 |= 0x40		//1：开启比较输出
#define PWMA_CC2NE_Disable()			PWMA_CCER1 &= ~0x40		//0：关闭比较输出
#define PWMA_CC2NP_LowValid()			PWMA_CCER1 |= 0x80		//1：低电平有效
#define PWMA_CC2NP_HighValid()		PWMA_CCER1 &= ~0x80		//0：高电平有效

#define PWMB_CCER1_Disable()			PWMB_CCER1 = 0x00			//关闭所有输入捕获/比较输出
#define PWMB_CC5E_Enable()				PWMB_CCER1 |= 0x01		//1：开启输入捕获/比较输出
#define PWMB_CC5E_Disable()				PWMB_CCER1 &= ~0x01		//0：关闭输入捕获/比较输出
#define PWMB_CC5P_LowValid()			PWMB_CCER1 |= 0x02		//1：低电平有效
#define PWMB_CC5P_HighValid()			PWMB_CCER1 &= ~0x02		//0：高电平有效
#define PWMB_CC5P_CaptureRise()		PWMB_CCER1 |= 0x02		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMB_CC5P_CaptureFall()		PWMB_CCER1 &= ~0x02		//0：捕获发生在 TI1F 或 TI2F 的上升沿

#define PWMB_CC6E_Enable()				PWMB_CCER1 |= 0x10		//1：开启输入捕获/比较输出
#define PWMB_CC6E_Disable()				PWMB_CCER1 &= ~0x10		//0：关闭输入捕获/比较输出
#define PWMB_CC6P_LowValid()			PWMB_CCER1 |= 0x20		//1：低电平有效
#define PWMB_CC6P_HighValid()			PWMB_CCER1 &= ~0x20		//0：高电平有效
#define PWMB_CC6P_CaptureRise()		PWMB_CCER1 |= 0x20		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMB_CC6P_CaptureFall()		PWMB_CCER1 &= ~0x20		//0：捕获发生在 TI1F 或 TI2F 的上升沿

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CCER2 = 0xFECDH;  CC4NP CC4NE CC4P CC4E CC3NP CC3NE CC3P CC3E  0000,0000  /* 捕获/比较使能寄存器 2 */ 
//sfr PWMB_CCER2 = 0xFEEDH;    -     -   CC8P CC8E   -     -   CC7P CC7E  0000,0000  /* 捕获/比较使能寄存器 2 */ 

#define PWMA_CCER2_Disable()			PWMA_CCER2 = 0x00			//关闭所有输入捕获/比较输出
#define PWMA_CC3E_Enable()				PWMA_CCER2 |= 0x01		//1：开启输入捕获/比较输出
#define PWMA_CC3E_Disable()				PWMA_CCER2 &= ~0x01		//0：关闭输入捕获/比较输出
#define PWMA_CC3P_LowValid()			PWMA_CCER2 |= 0x02		//1：低电平有效
#define PWMA_CC3P_HighValid()			PWMA_CCER2 &= ~0x02		//0：高电平有效
#define PWMA_CC3P_CaptureRise()		PWMA_CCER2 |= 0x02		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMA_CC3P_CaptureFall()		PWMA_CCER2 &= ~0x02		//0：捕获发生在 TI1F 或 TI2F 的上升沿
#define PWMA_CC3NE_Enable()				PWMA_CCER2 |= 0x04		//1：开启比较输出
#define PWMA_CC3NE_Disable()			PWMA_CCER2 &= ~0x04		//0：关闭比较输出
#define PWMA_CC3NP_LowValid()			PWMA_CCER2 |= 0x08		//1：低电平有效
#define PWMA_CC3NP_HighValid()		PWMA_CCER2 &= ~0x08		//0：高电平有效

#define PWMA_CC4E_Enable()				PWMA_CCER2 |= 0x10		//1：开启输入捕获/比较输出
#define PWMA_CC4E_Disable()				PWMA_CCER2 &= ~0x10		//0：关闭输入捕获/比较输出
#define PWMA_CC4P_LowValid()			PWMA_CCER2 |= 0x20		//1：低电平有效
#define PWMA_CC4P_HighValid()			PWMA_CCER2 &= ~0x20		//0：高电平有效
#define PWMA_CC4P_CaptureRise()		PWMA_CCER2 |= 0x20		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMA_CC4P_CaptureFall()		PWMA_CCER2 &= ~0x20		//0：捕获发生在 TI1F 或 TI2F 的上升沿
#define PWMA_CC4NE_Enable()				PWMA_CCER2 |= 0x40		//1：开启比较输出
#define PWMA_CC4NE_Disable()			PWMA_CCER2 &= ~0x40		//0：关闭比较输出
#define PWMA_CC4NP_LowValid()			PWMA_CCER2 |= 0x80		//1：低电平有效
#define PWMA_CC4NP_HighValid()		PWMA_CCER2 &= ~0x80		//0：高电平有效

#define PWMB_CCER2_Disable()			PWMB_CCER2 = 0x00			//关闭所有输入捕获/比较输出
#define PWMB_CC7E_Enable()				PWMB_CCER2 |= 0x01		//1：开启输入捕获/比较输出
#define PWMB_CC7E_Disable()				PWMB_CCER2 &= ~0x01		//0：关闭输入捕获/比较输出
#define PWMB_CC7P_LowValid()			PWMB_CCER2 |= 0x02		//1：低电平有效
#define PWMB_CC7P_HighValid()			PWMB_CCER2 &= ~0x02		//0：高电平有效
#define PWMB_CC7P_CaptureRise()		PWMB_CCER2 |= 0x02		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMB_CC7P_CaptureFall()		PWMB_CCER2 &= ~0x02		//0：捕获发生在 TI1F 或 TI2F 的上升沿

#define PWMB_CC8E_Enable()				PWMB_CCER2 |= 0x10		//1：开启输入捕获/比较输出
#define PWMB_CC8E_Disable()				PWMB_CCER2 &= ~0x10		//0：关闭输入捕获/比较输出
#define PWMB_CC8P_LowValid()			PWMB_CCER2 |= 0x20		//1：低电平有效
#define PWMB_CC8P_HighValid()			PWMB_CCER2 &= ~0x20		//0：高电平有效
#define PWMB_CC8P_CaptureRise()		PWMB_CCER2 |= 0x20		//1：捕获发生在 TI1F 或 TI2F 的下降沿
#define PWMB_CC8P_CaptureFall()		PWMB_CCER2 &= ~0x20		//0：捕获发生在 TI1F 或 TI2F 的上升沿

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CNTRH = 0xFECEH;                   CNT1[15:8]                  0000,0000  /* 计数器高 8 位 */ 
//sfr PWMB_CNTRH = 0xFEEEH;                   CNT2[15:8]                  0000,0000  /* 计数器高 8 位 */ 
//sfr PWMA_CNTRL = 0xFECFH;                   CNT1[7:0]                   0000,0000  /* 计数器低 8 位 */ 
//sfr PWMB_CNTRL = 0xFEEFH;                   CNT2[7:0]                   0000,0000  /* 计数器低 8 位 */ 

#define PWMA_Counter(n)						PWMA_CNTR = n		//计数器设置
#define PWMB_Counter(n)						PWMB_CNTR = n		//计数器设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_PSCRH = 0xFED0H;                   PSC1[15:8]                  0000,0000  /* 预分频器高 8 位 */ 
//sfr PWMB_PSCRH = 0xFEF0H;                   PSC2[15:8]                  0000,0000  /* 预分频器高 8 位 */ 
//sfr PWMA_PSCRL = 0xFED1H;                   PSC1[7:0]                   0000,0000  /* 预分频器低 8 位 */ 
//sfr PWMB_PSCRL = 0xFEF1H;                   PSC2[7:0]                   0000,0000  /* 预分频器低 8 位 */ 

#define PWMA_Prescaler(n)					PWMA_PSCR = n		//预分频器设置
#define PWMB_Prescaler(n)					PWMB_PSCR = n		//预分频器设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_ARRH = 0xFED2H;                    ARR1[15:8]                  0000,0000  /* 自动重装载寄存器高 8 位 */ 
//sfr PWMB_ARRH = 0xFEF2H;                    ARR2[15:8]                  0000,0000  /* 自动重装载寄存器高 8 位 */ 
//sfr PWMA_ARRL = 0xFED3H;                    ARR1[7:0]                   0000,0000  /* 自动重装载寄存器低 8 位 */ 
//sfr PWMB_ARRL = 0xFEF3H;                    ARR2[7:0]                   0000,0000  /* 自动重装载寄存器低 8 位 */ 

#define PWMA_AutoReload(n)				{PWMA_ARRH = (n>>8); PWMA_ARRL = (n);}		//自动重装载寄存器设置
#define PWMB_AutoReload(n)				{PWMB_ARRH = (n>>8); PWMB_ARRL = (n);}		//自动重装载寄存器设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_RCR = 0xFED4H;                     REP1[7:0]                   0000,0000  /* 重复计数器寄存器 */ 
//sfr PWMB_RCR = 0xFEF4H;                     REP2[7:0]                   0000,0000  /* 重复计数器寄存器 */ 

#define PWMA_ReCounter(n)					PWMA_RCR = n		//重复计数器寄存器设置
#define PWMB_ReCounter(n)					PWMB_RCR = n		//重复计数器寄存器设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CCR1H = 0xFED5H;                   CCR1[15:8]                  0000,0000  /* 捕获/比较寄存器 1 高 8 位 */ 
//sfr PWMB_CCR5H = 0xFEF5H;                   CCR5[15:8]                  0000,0000  /* 捕获/比较寄存器 1 高 8 位 */ 
//sfr PWMA_CCR1L = 0xFED6H;                   CCR1[7:0]                   0000,0000  /* 捕获/比较寄存器 1 低 8 位 */ 
//sfr PWMB_CCR5L = 0xFEF6H;                   CCR5[7:0]                   0000,0000  /* 捕获/比较寄存器 1 低 8 位 */ 

#define PWMA_Duty1(n)							{PWMA_CCR1H = (n>>8); PWMA_CCR1L = (n);}		//捕获/比较寄存器 1 设置
#define PWMB_Duty5(n)							{PWMB_CCR5H = (n>>8); PWMB_CCR5L = (n);}		//捕获/比较寄存器 1 设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CCR2H = 0xFED7H;                   CCR2[15:8]                  0000,0000  /* 捕获/比较寄存器 2 高 8 位 */ 
//sfr PWMB_CCR6H = 0xFEF7H;                   CCR6[15:8]                  0000,0000  /* 捕获/比较寄存器 2 高 8 位 */ 
//sfr PWMA_CCR2L = 0xFED8H;                   CCR2[7:0]                   0000,0000  /* 捕获/比较寄存器 2 低 8 位 */ 
//sfr PWMB_CCR6L = 0xFEF8H;                   CCR6[7:0]                   0000,0000  /* 捕获/比较寄存器 2 低 8 位 */ 

#define PWMA_Duty2(n)							{PWMA_CCR2H = (n>>8); PWMA_CCR2L = (n);}		//捕获/比较寄存器 2 设置
#define PWMB_Duty6(n)							{PWMB_CCR6H = (n>>8); PWMB_CCR6L = (n);}		//捕获/比较寄存器 2 设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CCR3H = 0xFED9H;                   CCR3[15:8]                  0000,0000  /* 捕获/比较寄存器 3 高 8 位 */ 
//sfr PWMB_CCR7H = 0xFEF9H;                   CCR7[15:8]                  0000,0000  /* 捕获/比较寄存器 3 高 8 位 */ 
//sfr PWMA_CCR3L = 0xFEDAH;                   CCR3[7:0]                   0000,0000  /* 捕获/比较寄存器 3 低 8 位 */ 
//sfr PWMB_CCR7L = 0xFEFAH;                   CCR7[7:0]                   0000,0000  /* 捕获/比较寄存器 3 低 8 位 */ 

#define PWMA_Duty3(n)							{PWMA_CCR3H = (n>>8); PWMA_CCR3L = (n);}		//捕获/比较寄存器 3 设置
#define PWMB_Duty7(n)							{PWMB_CCR7H = (n>>8); PWMB_CCR7L = (n);}		//捕获/比较寄存器 3 设置

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_CCR4H = 0xFEDBH;                   CCR4[15:8]                  0000,0000  /* 捕获/比较寄存器 4 高 8 位 */ 
//sfr PWMB_CCR8H = 0xFEFBH;                   CCR8[15:8]                  0000,0000  /* 捕获/比较寄存器 4 高 8 位 */ 
//sfr PWMA_CCR4L = 0xFEDCH;                   CCR4[7:0]                   0000,0000  /* 捕获/比较寄存器 4 低 8 位 */ 
//sfr PWMB_CCR8L = 0xFEFCH;                   CCR8[7:0]                   0000,0000  /* 捕获/比较寄存器 4 低 8 位 */ 

#define PWMA_Duty4(n)							{PWMA_CCR4H = (n>>8); PWMA_CCR4L = (n);}		//捕获/比较寄存器 4 设置
#define PWMB_Duty8(n)							{PWMB_CCR8H = (n>>8); PWMB_CCR8L = (n);}		//捕获/比较寄存器 4 设置

//						              7    6    5    4     3     2     1      0     Reset Value
//sfr PWMA_BRK = 0xFEDDH;  MOE1 AOE1 BKP1 BKE1 OSSR1 OSSI1 LOCK11 LOCK10  0000,0000  /* 刹车寄存器 */ 
//sfr PWMB_BRK = 0xFEFDH;  MOE2 AOE2 BKP2 BKE2 OSSR2 OSSI2 LOCK21 LOCK20  0000,0000  /* 刹车寄存器 */ 

#define PWMA_BrakeOutputEnable(n)				(n==1?(PWMA_BRK |= 0x80):(PWMA_BRK &= ~0x80))		//1：主输出使能
#define PWMB_BrakeOutputEnable(n)				(n==1?(PWMB_BRK |= 0x80):(PWMB_BRK &= ~0x80))		//1：主输出使能
//#define PWMA_BrakeOutputEnable()				PWMA_BRK |= 0x80		//1：主输出使能
#define PWMA_BrakeOutputDisable()				PWMA_BRK &= ~0x80		//0：主输出禁止
//#define PWMB_BrakeOutputEnable()				PWMB_BRK |= 0x80		//1：主输出使能
#define PWMB_BrakeOutputDisable()				PWMB_BRK &= ~0x80		//0：主输出禁止

#define PWMA_BrakeAutoOutputEnable()		PWMA_BRK |= 0x40		//1：自动输出使能
#define PWMA_BrakeAutoOutputDisable()		PWMA_BRK &= ~0x40		//0：自动输出禁止
#define PWMB_BrakeAutoOutputEnable()		PWMB_BRK |= 0x40		//1：自动输出使能
#define PWMB_BrakeAutoOutputDisable()		PWMB_BRK &= ~0x40		//0：自动输出禁止

#define PWMA_BrakeHighValid()						PWMA_BRK |= 0x20		//1：刹车输入高电平有效
#define PWMA_BrakeLowValid()						PWMA_BRK &= ~0x20		//0：刹车输入低电平有效
#define PWMB_BrakeHighValid()						PWMB_BRK |= 0x20		//1：刹车输入高电平有效
#define PWMB_BrakeLowValid()						PWMB_BRK &= ~0x20		//0：刹车输入低电平有效

#define PWMA_BrakeEnable(n)							(n==1?(PWMA_BRK |= 0x10):(PWMA_BRK &= ~0x10))		//1：开启刹车输入
#define PWMB_BrakeEnable(n)							(n==1?(PWMB_BRK |= 0x10):(PWMB_BRK &= ~0x10))		//1：开启刹车输入
//#define PWMA_BrakeEnable()							PWMA_BRK |= 0x10		//1：开启刹车输入
#define PWMA_BrakeDisable()							PWMA_BRK &= ~0x10		//0：禁止刹车输入
//#define PWMB_BrakeEnable()							PWMB_BRK |= 0x10		//1：开启刹车输入
#define PWMB_BrakeDisable()							PWMB_BRK &= ~0x10		//0：禁止刹车输入

//运行模式下“关闭状态”选择
#define PWMA_OSSRnEnable()							PWMA_BRK |= 0x08		//1：当 PWM 不工作时，一旦 CCiE=1 或 CCiNE=1，首先开启 OC/OCN 并输出无效电平，然后置OC/OCN 使能输出信号=1
#define PWMA_OSSRnDisable()							PWMA_BRK &= ~0x08		//0：当 PWM 不工作时，禁止 OC/OCN 输出（OC/OCN 使能输出信号=0）
#define PWMB_OSSRnEnable()							PWMB_BRK |= 0x08		//1：当 PWM 不工作时，一旦 CCiE=1 或 CCiNE=1，首先开启 OC/OCN 并输出无效电平，然后置OC/OCN 使能输出信号=1
#define PWMB_OSSRnDisable()							PWMB_BRK &= ~0x08		//0：当 PWM 不工作时，禁止 OC/OCN 输出（OC/OCN 使能输出信号=0）
//空闲模式下“关闭状态”选择
#define PWMA_OSSInEnable()							PWMA_BRK |= 0x04		//1：当 PWM 不工作时，一旦 CCiE=1 或 CCiNE=1，OC/OCN 首先输出其空闲电平，然后 OC/OCN使能输出信号=1
#define PWMA_OSSInDisable()							PWMA_BRK &= ~0x04		//0：当 PWM 不工作时，禁止 OC/OCN 输出（OC/OCN 使能输出信号=0）
#define PWMB_OSSInEnable()							PWMB_BRK |= 0x04		//1：当 PWM 不工作时，一旦 CCiE=1 或 CCiNE=1，OC/OCN 首先输出其空闲电平，然后 OC/OCN使能输出信号=1
#define PWMB_OSSInDisable()							PWMB_BRK &= ~0x04		//0：当 PWM 不工作时，禁止 OC/OCN 输出（OC/OCN 使能输出信号=0）

#define PWMn_lock_L0			0		//寄存器无写保护
#define PWMn_lock_L1			1		//锁定级别 1：不能写入 PWMn_BKR 寄存器的 BKE、BKP、AOE 位和PWMn_OISR 寄存器的 OISI 位
#define PWMn_lock_L2			2		//锁定级别 2：不能写入锁定级别 1 中的各位，也不能写入 CC 极性位以及 OSSR/OSSI 位
#define PWMn_lock_L3			3		//锁定级别 3：不能写入锁定级别 2 中的各位，也不能写入 CC 控制位

#define PWMA_LockLevelSet(n)						PWMA_BRK = (PWMA_BRK & ~0x03) | (n&3)		//锁定设置。该位为防止软件错误而提供的写保护措施
#define PWMB_LockLevelSet(n)						PWMB_BRK = (PWMB_BRK & ~0x03) | (n&3)		//锁定设置。该位为防止软件错误而提供的写保护措施

//						                 7     6     5    4    3     2    1    0    Reset Value
//sfr PWMA_DTR = 0xFEDEH;                     DTG1[7:0]                   0000,0000  /* 死区寄存器 */ 
//sfr PWMB_DTR = 0xFEFEH;                     DTG2[7:0]                   0000,0000  /* 死区寄存器 */ 

//DTGn[7:5] = 000~011: 死区时间 = DTGn[7:0] * tCK_PSC
//DTGn[7:5] = 100~101: 死区时间 = (64 + DTGn[6:0]) * 2 * tCK_PSC
//DTGn[7:5] = 110:     死区时间 = (32 + DTGn[5:0]) * 8 * tCK_PSC
//DTGn[7:5] = 111:     死区时间 = (32 + DTGn[4:0]) * 16 * tCK_PSC

#define PWMA_DeadTime(n)					PWMA_DTR = n		//死区发生器设置
#define PWMB_DeadTime(n)					PWMB_DTR = n		//死区发生器设置

//						                7    6     5    4     3    2     1    0    Reset Value
//sfr PWMA_OISR = 0xFEDFH;  OIS4N OIS4 OIS3N OIS3 OIS2N OIS2 OIS1N OIS1  0000,0000  /* 输出空闲状态寄存器 */ 
//sfr PWMB_OISR = 0xFEFFH;    -   OIS8   -   OIS7   -   OIS6   -   OIS5  x0x0,x0x0  /* 输出空闲状态寄存器 */ 

#define PWMA_OC1_OUT_0()					PWMA_OISR &= ~0x01	/* 当 MOE=0 时，如果 OC1N 使能，则在一个死区后，OC1=0 */
#define PWMA_OC1_OUT_1()					PWMA_OISR |= 0x01		/* 当 MOE=0 时，如果 OC1N 使能，则在一个死区后，OC1=1 */
#define PWMA_OC1N_OUT_0()					PWMA_OISR &= ~0x02	/* 当 MOE=0 时，则在一个死区后，OC1N=0 */
#define PWMA_OC1N_OUT_1()					PWMA_OISR |= 0x02		/* 当 MOE=0 时，则在一个死区后，OC1N=1 */
#define PWMA_OC2_OUT_0()					PWMA_OISR &= ~0x04	/* 当 MOE=0 时，如果 OC2N 使能，则在一个死区后，OC2=0 */
#define PWMA_OC2_OUT_1()					PWMA_OISR |= 0x04		/* 当 MOE=0 时，如果 OC2N 使能，则在一个死区后，OC2=1 */
#define PWMA_OC2N_OUT_0()					PWMA_OISR &= ~0x08	/* 当 MOE=0 时，则在一个死区后，OC2N=0 */
#define PWMA_OC2N_OUT_1()					PWMA_OISR |= 0x08		/* 当 MOE=0 时，则在一个死区后，OC2N=1 */
#define PWMA_OC3_OUT_0()					PWMA_OISR &= ~0x10	/* 当 MOE=0 时，如果 OC3N 使能，则在一个死区后，OC3=0 */
#define PWMA_OC3_OUT_1()					PWMA_OISR |= 0x10		/* 当 MOE=0 时，如果 OC3N 使能，则在一个死区后，OC3=1 */
#define PWMA_OC3N_OUT_0()					PWMA_OISR &= ~0x20	/* 当 MOE=0 时，则在一个死区后，OC3N=0 */
#define PWMA_OC3N_OUT_1()					PWMA_OISR |= 0x20		/* 当 MOE=0 时，则在一个死区后，OC3N=1 */
#define PWMA_OC4_OUT_0()					PWMA_OISR &= ~0x40	/* 当 MOE=0 时，如果 OC4N 使能，则在一个死区后，OC4=0 */
#define PWMA_OC4_OUT_1()					PWMA_OISR |= 0x40		/* 当 MOE=0 时，如果 OC4N 使能，则在一个死区后，OC4=1 */
#define PWMA_OC4N_OUT_0()					PWMA_OISR &= ~0x80	/* 当 MOE=0 时，则在一个死区后，OC4N=0 */
#define PWMA_OC4N_OUT_1()					PWMA_OISR |= 0x80		/* 当 MOE=0 时，则在一个死区后，OC4N=1 */

#define PWMB_OC5_OUT_0()					PWMB_OISR &= ~0x01	/* 当 MOE=0 时，则在一个死区后，OC5=0 */
#define PWMB_OC5_OUT_1()					PWMB_OISR |= 0x01		/* 当 MOE=0 时，则在一个死区后，OC5=1 */
#define PWMB_OC6_OUT_0()					PWMB_OISR &= ~0x04	/* 当 MOE=0 时，则在一个死区后，OC6=0 */
#define PWMB_OC6_OUT_1()					PWMB_OISR |= 0x04		/* 当 MOE=0 时，则在一个死区后，OC6=1 */
#define PWMB_OC7_OUT_0()					PWMB_OISR &= ~0x10	/* 当 MOE=0 时，则在一个死区后，OC7=0 */
#define PWMB_OC7_OUT_1()					PWMB_OISR |= 0x10		/* 当 MOE=0 时，则在一个死区后，OC7=1 */
#define PWMB_OC8_OUT_0()					PWMB_OISR &= ~0x40	/* 当 MOE=0 时，则在一个死区后，OC8=0 */
#define PWMB_OC8_OUT_1()					PWMB_OISR |= 0x40		/* 当 MOE=0 时，则在一个死区后，OC8=1 */

//========================================================================
//                              定义声明
//========================================================================

#define ENO1P       0x01
#define ENO1N       0x02
#define ENO2P       0x04
#define ENO2N       0x08
#define ENO3P       0x10
#define ENO3N       0x20
#define ENO4P       0x40
#define ENO4N       0x80

#define ENO5P       0x01
#define ENO6P       0x04
#define ENO7P       0x10
#define ENO8P       0x40

#define	PWM1	1
#define	PWM2	2
#define	PWM3	3
#define	PWM4	4
#define	PWM5	5
#define	PWM6	6
#define	PWM7	7
#define	PWM8	8

#define	PWMA	9
#define	PWMB	10

#define PWM_BIE     0x80
#define PWM_TIE     0x40
#define PWM_COMIE   0x20
#define PWM_CC4IE   0x10
#define PWM_CC3IE   0x08
#define PWM_CC2IE   0x04
#define PWM_CC1IE   0x02
#define PWM_CC8IE   0x10
#define PWM_CC7IE   0x08
#define PWM_CC6IE   0x04
#define PWM_CC5IE   0x02
#define PWM_UIE     0x01

typedef struct
{ 
	u8	PWM_Mode;			//模式,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	u16	PWM_Period;		//周期时间,   0~65535
	u16	PWM_Duty;			//占空比时间, 0~Period
	u8	PWM_DeadTime;	//死区发生器设置, 0~255
//	u8	PWM_Reload;				//输出比较的预装载使能,   ENABLE,DISABLE
//	u8	PWM_Fast;					//输出比较快速功能使能,   ENABLE,DISABLE
//	u8	PWM_PreLoad;			//预装载,     ENABLE,DISABLE
//	u8	PWM_BrakeEnable;	//刹车输入使能,  ENABLE,DISABLE
	u8	PWM_EnoSelect;		//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	u8	PWM_CEN_Enable;		//使能计数器, ENABLE,DISABLE
	u8	PWM_MainOutEnable;//主输出使能,  ENABLE,DISABLE
} PWMx_InitDefine; 

typedef struct
{ 
	u16	PWM1_Duty;			//PWM1占空比时间, 0~Period
	u16	PWM2_Duty;			//PWM2占空比时间, 0~Period
	u16	PWM3_Duty;			//PWM3占空比时间, 0~Period
	u16	PWM4_Duty;			//PWM4占空比时间, 0~Period
	u16	PWM5_Duty;			//PWM5占空比时间, 0~Period
	u16	PWM6_Duty;			//PWM6占空比时间, 0~Period
	u16	PWM7_Duty;			//PWM7占空比时间, 0~Period
	u16	PWM8_Duty;			//PWM8占空比时间, 0~Period
} PWMx_Duty; 

typedef struct
{ 
//	u8	PWM_Mode;			//模式,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	u16	PWM_Period;		//周期时间,   0~65535
	u8	PWM_DeadTime;	//死区发生器设置, 0~255
	u8	PWM_EnoSelect;		//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	u8	PWM_CEN_Enable;		//使能计数器, ENABLE,DISABLE
	u8	PWM_MainOutEnable;//主输出使能,  ENABLE,DISABLE
} HSPWMx_InitDefine; 


u8	PWM_Configuration(u8 PWM, PWMx_InitDefine *PWMx);
void UpdatePwm(u8 PWM, PWMx_Duty *PWMx);

void HSPWM_Configuration(u8 PWM, HSPWMx_InitDefine *PWMx, PWMx_Duty *DUTYx);
void UpdateHSPwm(u8 PWM, PWMx_Duty *PWMx);

#endif

