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

#include "STC32G_DMA.h"
#include "STC32G_SPI.h"
#include "STC32G_LCM.h"

//========================================================================
// ����: DMA_ADC_ISR_Handler
// ����: DMA ADC �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_ADC_ISR_Handler (void) interrupt DMA_ADC_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(DMA_ADC_STA & 0x01)	//ADת�����
	{
		DMA_ADC_STA &= ~0x01;	//���־λ
		DmaADCFlag = 1;
	}
}

//========================================================================
// ����: DMA_M2M_ISR_Handler
// ����: DMA M2M �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_M2M_ISR_Handler (void) interrupt DMA_M2M_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(DMA_M2M_STA & 0x01)	//M2M�������
	{
		DMA_M2M_STA &= ~0x01;	//���־λ
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
// ����: DMA_UART1TX_ISR_Handler
// ����: DMA UART1 TX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART1TX_ISR_Handler (void) interrupt DMA_UR1T_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR1T_STA & 0x01)	//�������
	{
		DMA_UR1T_STA &= ~0x01;	//���־λ
		DmaTx1Flag = 1;
	}
	if (DMA_UR1T_STA & 0x04)	//���ݸ���
	{
		DMA_UR1T_STA &= ~0x04;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART1RX_ISR_Handler
// ����: DMA UART1 RX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART1RX_ISR_Handler (void) interrupt DMA_UR1R_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR1R_STA & 0x01)	//�������
	{
		DMA_UR1R_STA &= ~0x01;	//���־λ
		DmaRx1Flag = 1;
	}
	if (DMA_UR1R_STA & 0x02)	//���ݶ���
	{
		DMA_UR1R_STA &= ~0x02;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART2TX_ISR_Handler
// ����: DMA UART2 TX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART2TX_ISR_Handler (void) interrupt DMA_UR2T_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR2T_STA & 0x01)	//�������
	{
		DMA_UR2T_STA &= ~0x01;	//���־λ
		DmaTx2Flag = 1;
	}
	if (DMA_UR2T_STA & 0x04)	//���ݸ���
	{
		DMA_UR2T_STA &= ~0x04;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART2RX_ISR_Handler
// ����: DMA UART2 RX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART2RX_ISR_Handler (void) interrupt DMA_UR2R_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR2R_STA & 0x01)	//�������
	{
		DMA_UR2R_STA &= ~0x01;	//���־λ
		DmaRx2Flag = 1;
	}
	if (DMA_UR2R_STA & 0x02)	//���ݶ���
	{
		DMA_UR2R_STA &= ~0x02;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART3TX_ISR_Handler
// ����: DMA UART3 TX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART3TX_ISR_Handler (void) interrupt DMA_UR3T_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR3T_STA & 0x01)	//�������
	{
		DMA_UR3T_STA &= ~0x01;	//���־λ
		DmaTx3Flag = 1;
	}
	if (DMA_UR3T_STA & 0x04)	//���ݸ���
	{
		DMA_UR3T_STA &= ~0x04;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART3RX_ISR_Handler
// ����: DMA UART3 RX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART3RX_ISR_Handler (void) interrupt DMA_UR3R_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR3R_STA & 0x01)	//�������
	{
		DMA_UR3R_STA &= ~0x01;	//���־λ
		DmaRx3Flag = 1;
	}
	if (DMA_UR3R_STA & 0x02)	//���ݶ���
	{
		DMA_UR3R_STA &= ~0x02;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART4TX_ISR_Handler
// ����: DMA UART4 TX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART4TX_ISR_Handler (void) interrupt DMA_UR4T_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR4T_STA & 0x01)	//�������
	{
		DMA_UR4T_STA &= ~0x01;	//���־λ
		DmaTx4Flag = 1;
	}
	if (DMA_UR4T_STA & 0x04)	//���ݸ���
	{
		DMA_UR4T_STA &= ~0x04;	//���־λ
	}
}

//========================================================================
// ����: DMA_UART4RX_ISR_Handler
// ����: DMA UART4 RX �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_UART4RX_ISR_Handler (void) interrupt DMA_UR4R_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if (DMA_UR4R_STA & 0x01)	//�������
	{
		DMA_UR4R_STA &= ~0x01;	//���־λ
		DmaRx4Flag = 1;
	}
	if (DMA_UR4R_STA & 0x02)	//���ݶ���
	{
		DMA_UR4R_STA &= ~0x02;	//���־λ
	}
}

//========================================================================
// ����: DMA_SPI_ISR_Handler
// ����: DMA SPI �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_SPI_ISR_Handler (void) interrupt DMA_SPI_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(DMA_SPI_STA & 0x01)	//ͨ�����
	{
		DMA_SPI_STA &= ~0x01;	//���־λ
		if(SPCTL & 0x10) 
		{ //����ģʽ
			SpiTxFlag = 1;
			SPI_SS_2 = 1;
		}
		else 
		{ //�ӻ�ģʽ
			SpiRxFlag = 1;
		}
	}
	if(DMA_SPI_STA & 0x02)	//���ݶ���
	{
		DMA_SPI_STA &= ~0x02;	//���־λ
	}
	if(DMA_SPI_STA & 0x04)	//���ݸ���
	{
		DMA_SPI_STA &= ~0x04;	//���־λ
	}
}

//========================================================================
// ����: DMA_I2C_ISR_Handler
// ����: DMA I2C �����жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-25
//========================================================================
void DMA_I2CT_ISR_Handler (void) interrupt DMA_I2CT_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(DMA_I2CT_STA & 0x01)   //�������
	{
		DMA_I2CT_STA &= ~0x01;  //�����־λ
		DmaI2CTFlag = 0;
	}
	if(DMA_I2CT_STA & 0x04)   //���ݸ���
	{
		DMA_I2CT_STA &= ~0x04;  //�����־λ
	}
}

//========================================================================
// ����: DMA_I2CR_ISR_Handler
// ����: DMA I2C �����жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-25
//========================================================================
void DMA_I2CR_ISR_Handler (void) interrupt DMA_I2CR_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(DMA_I2CR_STA & 0x01)   //�������
	{
		DMA_I2CR_STA &= ~0x01;  //�����־λ
		DmaI2CRFlag = 0;
	}
	if(DMA_I2CR_STA & 0x02)   //���ݶ���
	{
		DMA_I2CR_STA &= ~0x02;  //�����־λ
	}
}

//========================================================================
// ����: DMA_LCM_ISR_Handler
// ����: DMA LCM �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void DMA_LCM_ISR_Handler (void) interrupt DMA_LCM_VECTOR
{
	// TODO: �ڴ˴�����û�����
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
		DMA_LCM_STA = 0;		//���־λ
	}
}

//========================================================================
// ����: DMA_ISR_Handler
// ����: DMA�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-05-25
//========================================================================
void DMA_ISR_Handler (void) interrupt 13
{
	// TODO: �ڴ˴�����û�����
	
	//----------- DMA ADC --------------
	if(DMA_ADC_STA & 0x01)	//ADת�����
	{
		DMA_ADC_STA &= ~0x01;	//���־λ
		DmaADCFlag = 1;
	}

	//----------- DMA M2M --------------
	if(DMA_M2M_STA & 0x01)	//M2M�������
	{
		DMA_M2M_STA &= ~0x01;	//���־λ
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
	if (DMA_UR1T_STA & 0x01)	//�������
	{
		DMA_UR1T_STA &= ~0x01;	//���־λ
		DmaTx1Flag = 1;
	}
	if (DMA_UR1T_STA & 0x04)	//���ݸ���
	{
		DMA_UR1T_STA &= ~0x04;	//���־λ
	}
	
	if (DMA_UR1R_STA & 0x01)	//�������
	{
		DMA_UR1R_STA &= ~0x01;	//���־λ
		DmaRx1Flag = 1;
	}
	if (DMA_UR1R_STA & 0x02)	//���ݶ���
	{
		DMA_UR1R_STA &= ~0x02;	//���־λ
	}
	//---------- DMA UART2 -------------
	if (DMA_UR2T_STA & 0x01)	//�������
	{
		DMA_UR2T_STA &= ~0x01;	//���־λ
		DmaTx2Flag = 1;
	}
	if (DMA_UR2T_STA & 0x04)	//���ݸ���
	{
		DMA_UR2T_STA &= ~0x04;	//���־λ
	}
	
	if (DMA_UR2R_STA & 0x01)	//�������
	{
		DMA_UR2R_STA &= ~0x01;	//���־λ
		DmaRx2Flag = 1;
	}
	if (DMA_UR2R_STA & 0x02)	//���ݶ���
	{
		DMA_UR2R_STA &= ~0x02;	//���־λ
	}
	//---------- DMA UART3 -------------
	if (DMA_UR3T_STA & 0x01)	//�������
	{
		DMA_UR3T_STA &= ~0x01;	//���־λ
		DmaTx3Flag = 1;
	}
	if (DMA_UR3T_STA & 0x04)	//���ݸ���
	{
		DMA_UR3T_STA &= ~0x04;	//���־λ
	}
	
	if (DMA_UR3R_STA & 0x01)	//�������
	{
		DMA_UR3R_STA &= ~0x01;	//���־λ
		DmaRx3Flag = 1;
	}
	if (DMA_UR3R_STA & 0x02)	//���ݶ���
	{
		DMA_UR3R_STA &= ~0x02;	//���־λ
	}
	//---------- DMA UART4 -------------
	if (DMA_UR4T_STA & 0x01)	//�������
	{
		DMA_UR4T_STA &= ~0x01;	//���־λ
		DmaTx4Flag = 1;
	}
	if (DMA_UR4T_STA & 0x04)	//���ݸ���
	{
		DMA_UR4T_STA &= ~0x04;	//���־λ
	}
	
	if (DMA_UR4R_STA & 0x01)	//�������
	{
		DMA_UR4R_STA &= ~0x01;	//���־λ
		DmaRx4Flag = 1;
	}
	if (DMA_UR4R_STA & 0x02)	//���ݶ���
	{
		DMA_UR4R_STA &= ~0x02;	//���־λ
	}

	//---------- DMA SPI -------------
	if(DMA_SPI_STA & 0x01)	//ͨ�����
	{
		DMA_SPI_STA &= ~0x01;	//���־λ
		if(SPCTL & 0x10) 
		{ //����ģʽ
			SpiTxFlag = 1;
			SPI_SS_2 = 1;
		}
		else 
		{ //�ӻ�ģʽ
			SpiRxFlag = 1;
		}
	}
	if(DMA_SPI_STA & 0x02)	//���ݶ���
	{
		DMA_SPI_STA &= ~0x02;	//���־λ
	}
	if(DMA_SPI_STA & 0x04)	//���ݸ���
	{
		DMA_SPI_STA &= ~0x04;	//���־λ
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
		DMA_LCM_STA = 0;		//���־λ
	}
}
