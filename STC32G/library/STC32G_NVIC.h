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

#ifndef	__STC32G_NVIC_H
#define	__STC32G_NVIC_H

#include	"config.h"

//========================================================================
//                              定义声明
//========================================================================

#define	FALLING_EDGE		1		//产生下降沿中断
#define	RISING_EDGE			2		//产生上升沿中断

//========================================================================
//                              定时器中断设置
//========================================================================

#define 	Timer0_Interrupt(n)		(n==0?(ET0 = 0):(ET0 = 1))				/* Timer0中断使能 */
#define 	Timer1_Interrupt(n)		(n==0?(ET1 = 0):(ET1 = 1))				/* Timer1中断使能 */
#define 	Timer2_Interrupt(n)		(n==0?(ET2 = 0):(ET2 = 1))				/* Timer2中断使能 */
#define 	Timer3_Interrupt(n)		(n==0?(ET3 = 0):(ET3 = 1))				/* Timer3中断使能 */
#define 	Timer4_Interrupt(n)		(n==0?(ET4 = 0):(ET4 = 1))				/* Timer4中断使能 */

//========================================================================
//                             外部中断设置
//========================================================================

#define 	INT0_Interrupt(n)		(n==0?(EX0 = 0):(EX0 = 1))			/* INT0中断使能 */
#define 	INT1_Interrupt(n)		(n==0?(EX1 = 0):(EX1 = 1))			/* INT1中断使能 */
#define 	INT2_Interrupt(n)		(n==0?(EX2 = 0):(EX2 = 1))			/* INT2中断使能 */
#define 	INT3_Interrupt(n)		(n==0?(EX3 = 0):(EX3 = 1))			/* INT3中断使能 */
#define 	INT4_Interrupt(n)		(n==0?(EX4 = 0):(EX4 = 1))			/* INT4中断使能 */

//========================================================================
//                              ADC中断设置
//========================================================================

#define 	ADC_Interrupt(n)		(n==0?(EADC = 0):(EADC = 1))	/* ADC中断控制 */

//========================================================================
//                              SPI中断设置
//========================================================================

#define 	SPI_Interrupt(n)		(n==0?(ESPI = 0):(ESPI = 1))	/* SPI中断使能 */

//========================================================================
//                              RTC中断设置
//========================================================================

#define 	RTC_Interrupt(n)				RTCIEN = (n)		/* RTC中断使能 */

//========================================================================
//                              UART中断设置
//========================================================================

#define		UART1_Interrupt(n)	(n==0?(ES = 0):(ES = 1))					/* UART1中断使能 */
#define		UART2_Interrupt(n)	(n==0?(ES2 = 0):(ES2 = 1))				/* UART2中断使能 */
#define		UART3_Interrupt(n)	(n==0?(ES3 = 0):(ES3 = 1))				/* UART3中断使能 */
#define		UART4_Interrupt(n)	(n==0?(ES4 = 0):(ES4 = 1))				/* UART4中断使能 */

//========================================================================
//                              I2C中断设置
//========================================================================

#define		I2C_Master_Inturrupt(n)	(n==0?(I2CMSCR &= ~0x80):(I2CMSCR |= 0x80))	//0：禁止 I2C 功能；1：使能 I2C 功能

//========================================================================
//                              LIN中断设置
//========================================================================

#define 	LIN_Interrupt(n)				(n==0?(LINIE = 0):(LINIE = 1))					/* LIN中断使能 */

//========================================================================
//                            中断优先级定义
//========================================================================

//串口2中断优先级控制
#define 	UART2_Priority(n)			do{if(n == 0) PS2H = 0, PS2 = 0; \
																if(n == 1) PS2H = 0, PS2 = 1; \
																if(n == 2) PS2H = 1, PS2 = 0; \
																if(n == 3) PS2H = 1, PS2 = 1; \
															}while(0)
//SPI中断优先级控制
#define 	SPI_Priority(n)				do{if(n == 0) PSPIH = 0, PSPI = 0; \
																if(n == 1) PSPIH = 0, PSPI = 1; \
																if(n == 2) PSPIH = 1, PSPI = 0; \
																if(n == 3) PSPIH = 1, PSPI = 1; \
															}while(0)
//外部中断4中断优先级控制
#define 	INT4_Priority(n)				do{if(n == 0) PX4H = 0, PX4 = 0; \
																if(n == 1) PX4H = 0, PX4 = 1; \
																if(n == 2) PX4H = 1, PX4 = 0; \
																if(n == 3) PX4H = 1, PX4 = 1; \
															}while(0)
//比较器中断优先级控制
#define 	CMP_Priority(n)				do{if(n == 0) PCMPH = 0, PCMP = 0; \
																if(n == 1) PCMPH = 0, PCMP = 1; \
																if(n == 2) PCMPH = 1, PCMP = 0; \
																if(n == 3) PCMPH = 1, PCMP = 1; \
															}while(0)
//I2C中断优先级控制
#define 	I2C_Priority(n)				do{if(n == 0) PI2CH = 0, PI2C = 0; \
																if(n == 1) PI2CH = 0, PI2C = 1; \
																if(n == 2) PI2CH = 1, PI2C = 0; \
																if(n == 3) PI2CH = 1, PI2C = 1; \
															}while(0)
//串口3中断优先级控制
#define 	UART3_Priority(n)			do{if(n == 0) PS3H = 0, PS3 = 0; \
																if(n == 1) PS3H = 0, PS3 = 1; \
																if(n == 2) PS3H = 1, PS3 = 0; \
																if(n == 3) PS3H = 1, PS3 = 1; \
															}while(0)
//串口4中断优先级控制
#define 	UART4_Priority(n)			do{if(n == 0) PS4H = 0, PS4 = 0; \
																if(n == 1) PS4H = 0, PS4 = 1; \
																if(n == 2) PS4H = 1, PS4 = 0; \
																if(n == 3) PS4H = 1, PS4 = 1; \
															}while(0)

//外部中断0中断优先级控制
#define 	INT0_Priority(n)			do{if(n == 0) PX0H = 0, PX0 = 0; \
																if(n == 1) PX0H = 0, PX0 = 1; \
																if(n == 2) PX0H = 1, PX0 = 0; \
																if(n == 3) PX0H = 1, PX0 = 1; \
															}while(0)
//外部中断1中断优先级控制
#define 	INT1_Priority(n)			do{if(n == 0) PX1H = 0, PX1 = 0; \
																if(n == 1) PX1H = 0, PX1 = 1; \
																if(n == 2) PX1H = 1, PX1 = 0; \
																if(n == 3) PX1H = 1, PX1 = 1; \
															}while(0)
//定时器0中断优先级控制
#define 	Timer0_Priority(n)		do{if(n == 0) PT0H = 0, PT0 = 0; \
																if(n == 1) PT0H = 0, PT0 = 1; \
																if(n == 2) PT0H = 1, PT0 = 0; \
																if(n == 3) PT0H = 1, PT0 = 1; \
															}while(0)
//定时器1中断优先级控制
#define 	Timer1_Priority(n)		do{if(n == 0) PT1H = 0, PT1 = 0; \
																if(n == 1) PT1H = 0, PT1 = 1; \
																if(n == 2) PT1H = 1, PT1 = 0; \
																if(n == 3) PT1H = 1, PT1 = 1; \
															}while(0)
//串口1中断优先级控制
#define 	UART1_Priority(n)			do{if(n == 0) PSH = 0, PS = 0; \
																if(n == 1) PSH = 0, PS = 1; \
																if(n == 2) PSH = 1, PS = 0; \
																if(n == 3) PSH = 1, PS = 1; \
															}while(0)
//ADC中断优先级控制
#define 	ADC_Priority(n)				do{if(n == 0) PADCH = 0, PADC = 0; \
																if(n == 1) PADCH = 0, PADC = 1; \
																if(n == 2) PADCH = 1, PADC = 0; \
																if(n == 3) PADCH = 1, PADC = 1; \
															}while(0)
//低压检测中断优先级控制
#define 	LVD_Priority(n)				do{if(n == 0) PLVDH = 0, PADC = 0; \
																if(n == 1) PLVDH = 0, PADC = 1; \
																if(n == 2) PLVDH = 1, PADC = 0; \
																if(n == 3) PLVDH = 1, PADC = 1; \
															}while(0)
//高级PWMA中断优先级控制
#define 	PWMA_Priority(n)			do{if(n == 0) PPWMAH = 0, PPWMA = 0; \
																if(n == 1) PPWMAH = 0, PPWMA = 1; \
																if(n == 2) PPWMAH = 1, PPWMA = 0; \
																if(n == 3) PPWMAH = 1, PPWMA = 1; \
															}while(0)

//高级PWMB中断优先级控制
#define 	PWMB_Priority(n)			do{if(n == 0) PPWMBH = 0, PPWMB = 0; \
																if(n == 1) PPWMBH = 0, PPWMB = 1; \
																if(n == 2) PPWMBH = 1, PPWMB = 0; \
																if(n == 3) PPWMBH = 1, PPWMB = 1; \
															}while(0)

//RTC中断优先级控制
#define 	RTC_Priority(n)			do{if(n == 0) PRTCH = 0, PRTC = 0; \
																if(n == 1) PRTCH = 0, PRTC = 1; \
																if(n == 2) PRTCH = 1, PRTC = 0; \
																if(n == 3) PRTCH = 1, PRTC = 1; \
															}while(0)

//CAN1中断优先级控制
#define 	CAN1_Priority(n)		do{if(n == 0) PCANH = 0, PCANL = 0; \
																if(n == 1) PCANH = 0, PCANL = 1; \
																if(n == 2) PCANH = 1, PCANL = 0; \
																if(n == 3) PCANH = 1, PCANL = 1; \
															}while(0)

//CAN2中断优先级控制
#define 	CAN2_Priority(n)		do{if(n == 0) PCAN2H = 0, PCAN2L = 0; \
																if(n == 1) PCAN2H = 0, PCAN2L = 1; \
																if(n == 2) PCAN2H = 1, PCAN2L = 0; \
																if(n == 3) PCAN2H = 1, PCAN2L = 1; \
															}while(0)

//LIN中断优先级控制
#define 	LIN_Priority(n)		do{if(n == 0) PLINH = 0, PLINL = 0; \
																if(n == 1) PLINH = 0, PLINL = 1; \
																if(n == 2) PLINH = 1, PLINL = 0; \
																if(n == 3) PLINH = 1, PLINL = 1; \
															}while(0)


//========================================================================
//                           外部函数和变量声明
//========================================================================

u8 NVIC_Timer0_Init(u8 State, u8 Priority);
u8 NVIC_Timer1_Init(u8 State, u8 Priority);
u8 NVIC_Timer2_Init(u8 State, u8 Priority);
u8 NVIC_Timer3_Init(u8 State, u8 Priority);
u8 NVIC_Timer4_Init(u8 State, u8 Priority);
u8 NVIC_INT0_Init(u8 State, u8 Priority);
u8 NVIC_INT1_Init(u8 State, u8 Priority);
u8 NVIC_INT2_Init(u8 State, u8 Priority);
u8 NVIC_INT3_Init(u8 State, u8 Priority);
u8 NVIC_INT4_Init(u8 State, u8 Priority);
u8 NVIC_ADC_Init(u8 State, u8 Priority);
u8 NVIC_SPI_Init(u8 State, u8 Priority);
u8 NVIC_RTC_Init(u8 State, u8 Priority);
u8 NVIC_CMP_Init(u8 State, u8 Priority);
u8 NVIC_I2C_Init(u8 Mode, u8 State, u8 Priority);
u8 NVIC_UART1_Init(u8 State, u8 Priority);
u8 NVIC_UART2_Init(u8 State, u8 Priority);
u8 NVIC_UART3_Init(u8 State, u8 Priority);
u8 NVIC_UART4_Init(u8 State, u8 Priority);
u8 NVIC_PWM_Init(u8 Channel, u8 State, u8 Priority);
u8 NVIC_DMA_ADC_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_M2M_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_SPI_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_LCM_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_I2CT_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_I2CR_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART1_Tx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART1_Rx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART2_Tx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART2_Rx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART3_Tx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART3_Rx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART4_Tx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_DMA_UART4_Rx_Init(u8 State, u8 Priority, u8 Bus_Priority);
u8 NVIC_LCM_Init(u8 State, u8 Priority);
u8 NVIC_CAN_Init(u8 Channel, u8 State, u8 Priority);
u8 NVIC_LIN_Init(u8 State, u8 Priority);

#endif

