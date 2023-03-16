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

#include "STC32G_DMA.h"
#include "STC32G_UART.h"

//========================================================================
// 函数: void DMA_ADC_Inilize(DMA_ADC_InitTypeDef *DMA)
// 描述: DMA ADC 初始化程序.
// 参数: DMA: 结构参数,请参考DMA.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void DMA_ADC_Inilize(DMA_ADC_InitTypeDef *DMA)
{
	DMA_ADC_STA = 0x00;
	DMA_ADC_CHSW1 = (u8)(DMA->DMA_Channel>>8);
	DMA_ADC_CHSW0 = (u8)(DMA->DMA_Channel);
	DMA_ADC_RXAH = (u8)(DMA->DMA_Buffer>>8);
	DMA_ADC_RXAL = (u8)(DMA->DMA_Buffer);
	DMA_ADC_CFG2 = DMA->DMA_Times;

	if(DMA->DMA_Enable == ENABLE)		DMA_ADC_CR |= 0x80;	//使能ADC DMA
	else DMA_ADC_CR &= ~0x80;	//禁止ADC DMA
}

//========================================================================
// 函数: void DMA_M2M_Inilize(DMA_M2M_InitTypeDef *DMA)
// 描述: DMA M2M 初始化程序.
// 参数: DMA: 结构参数,请参考DMA.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void DMA_M2M_Inilize(DMA_M2M_InitTypeDef *DMA)
{
	DMA_M2M_STA = 0x00;
	DMA_M2M_RXAH = (u8)(DMA->DMA_Rx_Buffer>>8);
	DMA_M2M_RXAL = (u8)(DMA->DMA_Rx_Buffer);
	DMA_M2M_TXAH = (u8)(DMA->DMA_Tx_Buffer>>8);
	DMA_M2M_TXAL = (u8)(DMA->DMA_Tx_Buffer);
	DMA_M2M_AMT = (u8)DMA->DMA_Length;				//设置传输总字节数(低8位)：n+1
	DMA_M2M_AMTH = (u8)(DMA->DMA_Length>>8);	//设置传输总字节数(高8位)：n+1
	
	if(DMA->DMA_SRC_Dir == M2M_ADDR_DEC)		DMA_M2M_CFG |= 0x20;	//数据读完后地址自减
	else DMA_M2M_CFG &= ~0x20;	//数据读完后地址自减
	if(DMA->DMA_DEST_Dir == M2M_ADDR_DEC)		DMA_M2M_CFG |= 0x10;	//数据写入后地址自减
	else DMA_M2M_CFG &= ~0x10;	//数据写入后地址自减
	
	if(DMA->DMA_Enable == ENABLE)		DMA_M2M_CR |= 0x80;	//使能M2M DMA
	else DMA_M2M_CR &= ~0x80;	//禁止M2M DMA
}

//========================================================================
// 函数: void DMA_SPI_Inilize(DMA_SPI_InitTypeDef *DMA)
// 描述: DMA SPI 初始化程序.
// 参数: DMA: 结构参数,请参考DMA.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void DMA_SPI_Inilize(DMA_SPI_InitTypeDef *DMA)
{
	DMA_SPI_STA = 0x00;
	DMA_SPI_RXAH = (u8)(DMA->DMA_Rx_Buffer>>8);
	DMA_SPI_RXAL = (u8)(DMA->DMA_Rx_Buffer);
	DMA_SPI_TXAH = (u8)(DMA->DMA_Tx_Buffer>>8);
	DMA_SPI_TXAL = (u8)(DMA->DMA_Tx_Buffer);
	DMA_SPI_AMT = (u8)DMA->DMA_Length;				//设置传输总字节数(低8位)：n+1
	DMA_SPI_AMTH = (u8)(DMA->DMA_Length>>8);	//设置传输总字节数(高8位)：n+1
	
	if(DMA->DMA_SS_Sel <= SPI_SS_P35) DMA_SPI_CFG2 = (DMA_SPI_CFG2 & 0xfc) | DMA->DMA_SS_Sel;	//自动控制SS脚选择

	if(DMA->DMA_Tx_Enable == ENABLE)		DMA_SPI_CFG |= 0x40;	//使能SPI发送数据
	else DMA_SPI_CFG &= ~0x40;	//禁止SPI发送数据
	
	if(DMA->DMA_Rx_Enable == ENABLE)		DMA_SPI_CFG |= 0x20;	//使能SPI接收数据
	else DMA_SPI_CFG &= ~0x20;	//禁止SPI接收数据
	
	if(DMA->DMA_AUTO_SS == ENABLE)		DMA_SPI_CFG2 |= 0x04;	//使能SS自动控制
	else DMA_SPI_CFG2 &= ~0x04;	//禁止SS自动控制
	
	if(DMA->DMA_Enable == ENABLE)		DMA_SPI_CR |= 0x80;	//使能SPI DMA
	else DMA_SPI_CR &= ~0x80;	//禁止SPI DMA
}

//========================================================================
// 函数: void DMA_UART_Inilize(u8 UARTx, DMA_UART_InitTypeDef *DMA)
// 描述: DMA UART 初始化程序.
// 参数: UARTx: UART组号, DMA: 结构参数,请参考DMA.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void DMA_UART_Inilize(u8 UARTx, DMA_UART_InitTypeDef *DMA)
{
#ifdef UART1
	if(UARTx == UART1)
	{
		DMA_UR1T_STA = 0x00;
		DMA_UR1R_STA = 0x00;
		DMA_UR1T_AMT = DMA->DMA_TX_Length;
		DMA_UR1T_TXAH = (u8)(DMA->DMA_TX_Buffer>>8);
		DMA_UR1T_TXAL = (u8)(DMA->DMA_TX_Buffer);
		DMA_UR1R_RXAH = (u8)(DMA->DMA_RX_Buffer>>8);
		DMA_UR1R_RXAL = (u8)(DMA->DMA_RX_Buffer);
		DMA_UR1R_AMT = (u8)DMA->DMA_RX_Length;				//设置传输总字节数(低8位)：n+1
		DMA_UR1R_AMTH = (u8)(DMA->DMA_RX_Length>>8);	//设置传输总字节数(高8位)：n+1

		if(DMA->DMA_TX_Enable == ENABLE)		DMA_UR1T_CR |= 0x80;	//使能UART1 TX DMA
		else DMA_UR1T_CR &= ~0x80;	//禁止UART1 TX DMA
		if(DMA->DMA_RX_Enable == ENABLE)		DMA_UR1R_CR |= 0x80;	//使能UART1 RX DMA
		else DMA_UR1R_CR &= ~0x80;	//禁止UART1 RX DMA
	}
#endif
#ifdef UART2
	if(UARTx == UART2)
	{
		DMA_UR2T_STA = 0x00;
		DMA_UR2R_STA = 0x00;
		DMA_UR2T_AMT = DMA->DMA_TX_Length;
		DMA_UR2T_TXAH = (u8)(DMA->DMA_TX_Buffer>>8);
		DMA_UR2T_TXAL = (u8)(DMA->DMA_TX_Buffer);
		DMA_UR2R_RXAH = (u8)(DMA->DMA_RX_Buffer>>8);
		DMA_UR2R_RXAL = (u8)(DMA->DMA_RX_Buffer);
		DMA_UR2R_AMT = (u8)DMA->DMA_RX_Length;				//设置传输总字节数(低8位)：n+1
		DMA_UR2R_AMTH = (u8)(DMA->DMA_RX_Length>>8);	//设置传输总字节数(高8位)：n+1

		if(DMA->DMA_TX_Enable == ENABLE)		DMA_UR2T_CR |= 0x80;	//使能UART2 TX DMA
		else DMA_UR2T_CR &= ~0x80;	//禁止UART2 TX DMA
		if(DMA->DMA_RX_Enable == ENABLE)		DMA_UR2R_CR |= 0x80;	//使能UART2 RX DMA
		else DMA_UR2R_CR &= ~0x80;	//禁止UART2 RX DMA
	}
#endif
#ifdef UART3
	if(UARTx == UART3)
	{
		DMA_UR3T_STA = 0x00;
		DMA_UR3R_STA = 0x00;
		DMA_UR3T_AMT = DMA->DMA_TX_Length;
		DMA_UR3T_TXAH = (u8)(DMA->DMA_TX_Buffer>>8);
		DMA_UR3T_TXAL = (u8)(DMA->DMA_TX_Buffer);
		DMA_UR3R_RXAH = (u8)(DMA->DMA_RX_Buffer>>8);
		DMA_UR3R_RXAL = (u8)(DMA->DMA_RX_Buffer);
		DMA_UR3R_AMT = (u8)DMA->DMA_RX_Length;				//设置传输总字节数(低8位)：n+1
		DMA_UR3R_AMTH = (u8)(DMA->DMA_RX_Length>>8);	//设置传输总字节数(高8位)：n+1

		if(DMA->DMA_TX_Enable == ENABLE)		DMA_UR3T_CR |= 0x80;	//使能UART3 TX DMA
		else DMA_UR3T_CR &= ~0x80;	//禁止UART3 TX DMA
		if(DMA->DMA_RX_Enable == ENABLE)		DMA_UR3R_CR |= 0x80;	//使能UART3 RX DMA
		else DMA_UR3R_CR &= ~0x80;	//禁止UART3 RX DMA
	}
#endif
#ifdef UART4
	if(UARTx == UART4)
	{
		DMA_UR4T_STA = 0x00;
		DMA_UR4R_STA = 0x00;
		DMA_UR4T_AMT = DMA->DMA_TX_Length;
		DMA_UR4T_TXAH = (u8)(DMA->DMA_TX_Buffer>>8);
		DMA_UR4T_TXAL = (u8)(DMA->DMA_TX_Buffer);
		DMA_UR4R_RXAH = (u8)(DMA->DMA_RX_Buffer>>8);
		DMA_UR4R_RXAL = (u8)(DMA->DMA_RX_Buffer);
		DMA_UR4R_AMT = (u8)DMA->DMA_RX_Length;				//设置传输总字节数(低8位)：n+1
		DMA_UR4R_AMTH = (u8)(DMA->DMA_RX_Length>>8);	//设置传输总字节数(高8位)：n+1

		if(DMA->DMA_TX_Enable == ENABLE)		DMA_UR4T_CR |= 0x80;	//使能UART4 TX DMA
		else DMA_UR4T_CR &= ~0x80;	//禁止UART4 TX DMA
		if(DMA->DMA_RX_Enable == ENABLE)		DMA_UR4R_CR |= 0x80;	//使能UART4 RX DMA
		else DMA_UR4R_CR &= ~0x80;	//禁止UART4 RX DMA
	}
#endif
}

//========================================================================
// 函数: void DMA_LCM_Inilize(DMA_LCM_InitTypeDef *DMA)
// 描述: DMA LCM 初始化程序.
// 参数: DMA: 结构参数,请参考DMA.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void DMA_LCM_Inilize(DMA_LCM_InitTypeDef *DMA)
{
	DMA_LCM_STA = 0x00;
	DMA_LCM_RXAH = (u8)(DMA->DMA_Rx_Buffer>>8);
	DMA_LCM_RXAL = (u8)(DMA->DMA_Rx_Buffer);
	DMA_LCM_TXAH = (u8)(DMA->DMA_Tx_Buffer>>8);
	DMA_LCM_TXAL = (u8)(DMA->DMA_Tx_Buffer);
	DMA_LCM_AMT = (u8)DMA->DMA_Length;				//设置传输总字节数(低8位)：n+1
	DMA_LCM_AMTH = (u8)(DMA->DMA_Length>>8);	//设置传输总字节数(高8位)：n+1
	
	if(DMA->DMA_Enable == ENABLE)		DMA_LCM_CR |= 0x80;	//使能LCM DMA
	else DMA_LCM_CR &= ~0x80;	//禁止LCM DMA
}

//========================================================================
// 函数: void DMA_I2C_Inilize(DMA_I2C_InitTypeDef *DMA)
// 描述: DMA I2C 初始化程序.
// 参数: DMA: 结构参数,请参考DMA.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-05-17
//========================================================================
void DMA_I2C_Inilize(DMA_I2C_InitTypeDef *DMA)
{
	DMA_I2CT_STA = 0x00;
	DMA_I2CT_TXAH = (u8)(DMA->DMA_TX_Buffer>>8);
	DMA_I2CT_TXAL = (u8)(DMA->DMA_TX_Buffer);
	DMA_I2CT_AMT = (u8)DMA->DMA_TX_Length;				//设置传输总字节数(低8位)：n+1
	DMA_I2CT_AMTH = (u8)(DMA->DMA_TX_Length>>8);	//设置传输总字节数(高8位)：n+1

	DMA_I2CR_STA = 0x00;
	DMA_I2CR_RXAH = (u8)(DMA->DMA_RX_Buffer>>8);
	DMA_I2CR_RXAL = (u8)(DMA->DMA_RX_Buffer);
	DMA_I2CR_AMT = (u8)DMA->DMA_RX_Length;				//设置传输总字节数(低8位)：n+1
	DMA_I2CR_AMTH = (u8)(DMA->DMA_RX_Length>>8);	//设置传输总字节数(高8位)：n+1
	
	if(DMA->DMA_TX_Enable == ENABLE)		DMA_I2CT_CR |= 0x80;	//使能I2CT DMA
	else DMA_I2CT_CR &= ~0x80;	//禁止I2CT DMA
	if(DMA->DMA_RX_Enable == ENABLE)		DMA_I2CR_CR |= 0x80;	//使能I2CR DMA
	else DMA_I2CR_CR &= ~0x80;	//禁止I2CT DMA
}

