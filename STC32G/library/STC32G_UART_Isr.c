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

#include "STC32G_UART.h"

bit B_ULinRX1_Flag;
bit B_ULinRX2_Flag;

//========================================================================
// 函数: UART1_ISR_Handler
// 描述: UART1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART1
void UART1_ISR_Handler (void) interrupt UART1_VECTOR
{
	u8 Status;

	if(RI)
	{
		RI = 0;

		//--------USART LIN---------------
		Status = USARTCR5;
		if(Status & 0x02)     //if LIN header is detected
		{
			B_ULinRX1_Flag = 1;
		}

		if(Status & 0xc0)     //if LIN break is detected / LIN header error is detected
		{
			COM1.RX_Cnt = 0;
		}
		USARTCR5 &= ~0xcb;    //Clear flag
		//--------------------------------
		
        if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
        RX1_Buffer[COM1.RX_Cnt++] = SBUF;
        COM1.RX_TimeOut = TimeOutSet1;
	}

	if(TI)
	{
		TI = 0;
//        COM1.B_TX_busy = 0; //使用阻塞方式发送直接清除繁忙标志，屏蔽下面那段代码
		
		if(COM1.TX_send != COM1.TX_write)
		{
		 	SBUF = TX1_Buffer[COM1.TX_send];
			if(++COM1.TX_send >= COM_TX1_Lenth)		COM1.TX_send = 0;
		}
		else	COM1.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// 函数: UART2_ISR_Handler
// 描述: UART2中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART2
void UART2_ISR_Handler (void) interrupt UART2_VECTOR
{
	u8 Status;

	if(S2RI)
	{
		CLR_RI2();

		//--------USART LIN---------------
		Status = USART2CR5;
		if(Status & 0x02)     //if LIN header is detected
		{
			B_ULinRX2_Flag = 1;
		}

		if(Status & 0xc0)     //if LIN break is detected / LIN header error is detected
		{
			COM2.RX_Cnt = 0;
		}
		USART2CR5 &= ~0xcb;   //Clear flag
		//--------------------------------
		
        if(COM2.RX_Cnt >= COM_RX2_Lenth)	COM2.RX_Cnt = 0;
        RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
        COM2.RX_TimeOut = TimeOutSet2;
	}

	if(S2TI)
	{
		CLR_TI2();
//        COM2.B_TX_busy = 0; //使用阻塞方式发送直接清除繁忙标志，屏蔽下面那段代码
		
		if(COM2.TX_send != COM2.TX_write)
		{
		 	S2BUF = TX2_Buffer[COM2.TX_send];
			if(++COM2.TX_send >= COM_TX2_Lenth)		COM2.TX_send = 0;
		}
		else	COM2.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// 函数: UART3_ISR_Handler
// 描述: UART3中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART3
void UART3_ISR_Handler (void) interrupt UART3_VECTOR
{
	if(S3RI)
	{
		CLR_RI3();

        if(COM3.RX_Cnt >= COM_RX3_Lenth)	COM3.RX_Cnt = 0;
        RX3_Buffer[COM3.RX_Cnt++] = S3BUF;
        COM3.RX_TimeOut = TimeOutSet3;
	}

	if(S3TI)
	{
		CLR_TI3();
//        COM3.B_TX_busy = 0; //使用阻塞方式发送直接清除繁忙标志，屏蔽下面那段代码
		
		if(COM3.TX_send != COM3.TX_write)
		{
		 	S3BUF = TX3_Buffer[COM3.TX_send];
			if(++COM3.TX_send >= COM_TX3_Lenth)		COM3.TX_send = 0;
		}
		else	COM3.B_TX_busy = 0;
	}
}
#endif

//========================================================================
// 函数: UART4_ISR_Handler
// 描述: UART4中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART4
void UART4_ISR_Handler (void) interrupt UART4_VECTOR
{
	if(S4RI)
	{
		CLR_RI4();

        if(COM4.RX_Cnt >= COM_RX4_Lenth)	COM4.RX_Cnt = 0;
        RX4_Buffer[COM4.RX_Cnt++] = S4BUF;
        COM4.RX_TimeOut = TimeOutSet4;
	}

	if(S4TI)
	{
		CLR_TI4();
//        COM4.B_TX_busy = 0; //使用阻塞方式发送直接清除繁忙标志，屏蔽下面那段代码
		
		if(COM4.TX_send != COM4.TX_write)
		{
		 	S4BUF = TX4_Buffer[COM4.TX_send];
			if(++COM4.TX_send >= COM_TX4_Lenth)		COM4.TX_send = 0;
		}
		else	COM4.B_TX_busy = 0;
	}
}
#endif
