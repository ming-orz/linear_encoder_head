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
#include "STC32G_SPI.h"
#include "STC32G_LCM.h"

//========================================================================
// 函数: DMA_ADC_ISR_Handler
// 描述: DMA ADC 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_ADC_ISR_Handler (void) interrupt DMA_ADC_VECTOR
{
	// TODO: 在此处添加用户代码
	if(DMA_ADC_STA & 0x01)	//AD转换完成
	{
		DMA_ADC_STA &= ~0x01;	//清标志位
		DmaADCFlag = 1;
	}
}

//========================================================================
// 函数: DMA_M2M_ISR_Handler
// 描述: DMA M2M 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_M2M_ISR_Handler (void) interrupt DMA_M2M_VECTOR
{
	// TODO: 在此处添加用户代码
	if(DMA_M2M_STA & 0x01)	//M2M传输完成
	{
		DMA_M2M_STA &= ~0x01;	//清标志位
		DmaM2MFlag = 1;
		if(u2sFlag)
		{
			u2sFlag = 0;
			SpiSendFlag = 1;
		}
		if(s2uFlag)
		{
			s2uFlag = 0;
			UartSendFlag = 1;
		}
	}
}

//========================================================================
// 函数: DMA_UART1TX_ISR_Handler
// 描述: DMA UART1 TX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART1TX_ISR_Handler (void) interrupt DMA_UR1T_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR1T_STA & 0x01)	//发送完成
	{
		DMA_UR1T_STA &= ~0x01;	//清标志位
		DmaTx1Flag = 1;
	}
	if (DMA_UR1T_STA & 0x04)	//数据覆盖
	{
		DMA_UR1T_STA &= ~0x04;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART1RX_ISR_Handler
// 描述: DMA UART1 RX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART1RX_ISR_Handler (void) interrupt DMA_UR1R_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR1R_STA & 0x01)	//接收完成
	{
		DMA_UR1R_STA &= ~0x01;	//清标志位
		DmaRx1Flag = 1;
	}
	if (DMA_UR1R_STA & 0x02)	//数据丢弃
	{
		DMA_UR1R_STA &= ~0x02;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART2TX_ISR_Handler
// 描述: DMA UART2 TX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART2TX_ISR_Handler (void) interrupt DMA_UR2T_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR2T_STA & 0x01)	//发送完成
	{
		DMA_UR2T_STA &= ~0x01;	//清标志位
		DmaTx2Flag = 1;
	}
	if (DMA_UR2T_STA & 0x04)	//数据覆盖
	{
		DMA_UR2T_STA &= ~0x04;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART2RX_ISR_Handler
// 描述: DMA UART2 RX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART2RX_ISR_Handler (void) interrupt DMA_UR2R_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR2R_STA & 0x01)	//接收完成
	{
		DMA_UR2R_STA &= ~0x01;	//清标志位
		DmaRx2Flag = 1;
	}
	if (DMA_UR2R_STA & 0x02)	//数据丢弃
	{
		DMA_UR2R_STA &= ~0x02;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART3TX_ISR_Handler
// 描述: DMA UART3 TX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART3TX_ISR_Handler (void) interrupt DMA_UR3T_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR3T_STA & 0x01)	//发送完成
	{
		DMA_UR3T_STA &= ~0x01;	//清标志位
		DmaTx3Flag = 1;
	}
	if (DMA_UR3T_STA & 0x04)	//数据覆盖
	{
		DMA_UR3T_STA &= ~0x04;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART3RX_ISR_Handler
// 描述: DMA UART3 RX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART3RX_ISR_Handler (void) interrupt DMA_UR3R_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR3R_STA & 0x01)	//接收完成
	{
		DMA_UR3R_STA &= ~0x01;	//清标志位
		DmaRx3Flag = 1;
	}
	if (DMA_UR3R_STA & 0x02)	//数据丢弃
	{
		DMA_UR3R_STA &= ~0x02;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART4TX_ISR_Handler
// 描述: DMA UART4 TX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART4TX_ISR_Handler (void) interrupt DMA_UR4T_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR4T_STA & 0x01)	//发送完成
	{
		DMA_UR4T_STA &= ~0x01;	//清标志位
		DmaTx4Flag = 1;
	}
	if (DMA_UR4T_STA & 0x04)	//数据覆盖
	{
		DMA_UR4T_STA &= ~0x04;	//清标志位
	}
}

//========================================================================
// 函数: DMA_UART4RX_ISR_Handler
// 描述: DMA UART4 RX 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_UART4RX_ISR_Handler (void) interrupt DMA_UR4R_VECTOR
{
	// TODO: 在此处添加用户代码
	if (DMA_UR4R_STA & 0x01)	//接收完成
	{
		DMA_UR4R_STA &= ~0x01;	//清标志位
		DmaRx4Flag = 1;
	}
	if (DMA_UR4R_STA & 0x02)	//数据丢弃
	{
		DMA_UR4R_STA &= ~0x02;	//清标志位
	}
}

//========================================================================
// 函数: DMA_SPI_ISR_Handler
// 描述: DMA SPI 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_SPI_ISR_Handler (void) interrupt DMA_SPI_VECTOR
{
	// TODO: 在此处添加用户代码
	if(DMA_SPI_STA & 0x01)	//通信完成
	{
		DMA_SPI_STA &= ~0x01;	//清标志位
		if(SPCTL & 0x10) 
		{ //主机模式
			SpiTxFlag = 1;
			SPI_SS_2 = 1;
		}
		else 
		{ //从机模式
			SpiRxFlag = 1;
		}
	}
	if(DMA_SPI_STA & 0x02)	//数据丢弃
	{
		DMA_SPI_STA &= ~0x02;	//清标志位
	}
	if(DMA_SPI_STA & 0x04)	//数据覆盖
	{
		DMA_SPI_STA &= ~0x04;	//清标志位
	}
}

//========================================================================
// 函数: DMA_I2C_ISR_Handler
// 描述: DMA I2C 发送中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-25
//========================================================================
void DMA_I2CT_ISR_Handler (void) interrupt DMA_I2CT_VECTOR
{
	// TODO: 在此处添加用户代码
	if(DMA_I2CT_STA & 0x01)   //发送完成
	{
		DMA_I2CT_STA &= ~0x01;  //清除标志位
		DmaI2CTFlag = 0;
	}
	if(DMA_I2CT_STA & 0x04)   //数据覆盖
	{
		DMA_I2CT_STA &= ~0x04;  //清除标志位
	}
}

//========================================================================
// 函数: DMA_I2CR_ISR_Handler
// 描述: DMA I2C 接收中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-25
//========================================================================
void DMA_I2CR_ISR_Handler (void) interrupt DMA_I2CR_VECTOR
{
	// TODO: 在此处添加用户代码
	if(DMA_I2CR_STA & 0x01)   //接收完成
	{
		DMA_I2CR_STA &= ~0x01;  //清除标志位
		DmaI2CRFlag = 0;
	}
	if(DMA_I2CR_STA & 0x02)   //数据丢弃
	{
		DMA_I2CR_STA &= ~0x02;  //清除标志位
	}
}

//========================================================================
// 函数: DMA_LCM_ISR_Handler
// 描述: DMA LCM 中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-23
//========================================================================
void DMA_LCM_ISR_Handler (void) interrupt DMA_LCM_VECTOR
{
	// TODO: 在此处添加用户代码
	if(DMA_LCM_STA & 0x01)
	{
		if(DmaLcmFlag)
		{
			DmaLcmFlag = 0;
			DMA_LCM_CR = 0;
		}
		else
		{
			LCM_Cnt--;
			if(LCM_Cnt == 0)
			{
				DMA_LCM_CR = 0;
				LCD_CS=1;
			}
			else
			{
				DMA_LCM_CR = 0xa0;	//Write dat
			}
		}
		DMA_LCM_STA = 0;		//清标志位
	}
}

//========================================================================
// 函数: DMA_ISR_Handler
// 描述: DMA中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2021-05-25
//========================================================================
void DMA_ISR_Handler (void) interrupt 13
{
	// TODO: 在此处添加用户代码
	
	//----------- DMA ADC --------------
	if(DMA_ADC_STA & 0x01)	//AD转换完成
	{
		DMA_ADC_STA &= ~0x01;	//清标志位
		DmaADCFlag = 1;
	}

	//----------- DMA M2M --------------
	if(DMA_M2M_STA & 0x01)	//M2M传输完成
	{
		DMA_M2M_STA &= ~0x01;	//清标志位
		DmaM2MFlag = 1;
		if(u2sFlag)
		{
			u2sFlag = 0;
			SpiSendFlag = 1;
		}
		if(s2uFlag)
		{
			s2uFlag = 0;
			UartSendFlag = 1;
		}
	}

	//---------- DMA UART1 -------------
	if (DMA_UR1T_STA & 0x01)	//发送完成
	{
		DMA_UR1T_STA &= ~0x01;	//清标志位
		DmaTx1Flag = 1;
	}
	if (DMA_UR1T_STA & 0x04)	//数据覆盖
	{
		DMA_UR1T_STA &= ~0x04;	//清标志位
	}
	
	if (DMA_UR1R_STA & 0x01)	//接收完成
	{
		DMA_UR1R_STA &= ~0x01;	//清标志位
		DmaRx1Flag = 1;
	}
	if (DMA_UR1R_STA & 0x02)	//数据丢弃
	{
		DMA_UR1R_STA &= ~0x02;	//清标志位
	}
	//---------- DMA UART2 -------------
	if (DMA_UR2T_STA & 0x01)	//发送完成
	{
		DMA_UR2T_STA &= ~0x01;	//清标志位
		DmaTx2Flag = 1;
	}
	if (DMA_UR2T_STA & 0x04)	//数据覆盖
	{
		DMA_UR2T_STA &= ~0x04;	//清标志位
	}
	
	if (DMA_UR2R_STA & 0x01)	//接收完成
	{
		DMA_UR2R_STA &= ~0x01;	//清标志位
		DmaRx2Flag = 1;
	}
	if (DMA_UR2R_STA & 0x02)	//数据丢弃
	{
		DMA_UR2R_STA &= ~0x02;	//清标志位
	}
	//---------- DMA UART3 -------------
	if (DMA_UR3T_STA & 0x01)	//发送完成
	{
		DMA_UR3T_STA &= ~0x01;	//清标志位
		DmaTx3Flag = 1;
	}
	if (DMA_UR3T_STA & 0x04)	//数据覆盖
	{
		DMA_UR3T_STA &= ~0x04;	//清标志位
	}
	
	if (DMA_UR3R_STA & 0x01)	//接收完成
	{
		DMA_UR3R_STA &= ~0x01;	//清标志位
		DmaRx3Flag = 1;
	}
	if (DMA_UR3R_STA & 0x02)	//数据丢弃
	{
		DMA_UR3R_STA &= ~0x02;	//清标志位
	}
	//---------- DMA UART4 -------------
	if (DMA_UR4T_STA & 0x01)	//发送完成
	{
		DMA_UR4T_STA &= ~0x01;	//清标志位
		DmaTx4Flag = 1;
	}
	if (DMA_UR4T_STA & 0x04)	//数据覆盖
	{
		DMA_UR4T_STA &= ~0x04;	//清标志位
	}
	
	if (DMA_UR4R_STA & 0x01)	//接收完成
	{
		DMA_UR4R_STA &= ~0x01;	//清标志位
		DmaRx4Flag = 1;
	}
	if (DMA_UR4R_STA & 0x02)	//数据丢弃
	{
		DMA_UR4R_STA &= ~0x02;	//清标志位
	}

	//---------- DMA SPI -------------
	if(DMA_SPI_STA & 0x01)	//通信完成
	{
		DMA_SPI_STA &= ~0x01;	//清标志位
		if(SPCTL & 0x10) 
		{ //主机模式
			SpiTxFlag = 1;
			SPI_SS_2 = 1;
		}
		else 
		{ //从机模式
			SpiRxFlag = 1;
		}
	}
	if(DMA_SPI_STA & 0x02)	//数据丢弃
	{
		DMA_SPI_STA &= ~0x02;	//清标志位
	}
	if(DMA_SPI_STA & 0x04)	//数据覆盖
	{
		DMA_SPI_STA &= ~0x04;	//清标志位
	}

	//------------- LCM --------------
	if(LCMIFSTA & 0x01)
	{
		LCMIFSTA = 0x00;
		LcmFlag = 0;
	}
	
	//---------- DMA LCM -------------
	if(DMA_LCM_STA & 0x01)
	{
		if(DmaLcmFlag)
		{
			DmaLcmFlag = 0;
			DMA_LCM_CR = 0;
		}
		else
		{
			LCM_Cnt--;
			if(LCM_Cnt == 0)
			{
				DMA_LCM_CR = 0;
				LCD_CS=1;
			}
			else
			{
				DMA_LCM_CR = 0xa0;	//Write dat
			}
		}
		DMA_LCM_STA = 0;		//清标志位
	}
}
