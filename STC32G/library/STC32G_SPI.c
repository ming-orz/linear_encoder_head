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

#include	"STC32G_SPI.h"

u8 	SPI_RxTimerOut;
u8 	SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];
bit B_SPI_Busy; //����æ��־


//========================================================================
// ����: void	SPI_Init(SPI_InitTypeDef *SPIx)
// ����: SPI��ʼ������.
// ����: SPIx: �ṹ����,��ο�spi.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	SPI_Init(SPI_InitTypeDef *SPIx)
{
	if(SPIx->SPI_SSIG == ENABLE)			SSIG = 0; 	//enable SS, conform Master or Slave by SS pin.
	else									SSIG = 1; 	//disable SS, conform Master or Slave by SPI_Mode
	SPI_Start(SPIx->SPI_Enable);
	SPI_FirstBit_Set(SPIx->SPI_FirstBit);
	SPI_Mode_Set(SPIx->SPI_Mode);
	SPI_CPOL_Set(SPIx->SPI_CPOL);
	SPI_CPHA_Set(SPIx->SPI_CPHA);
	SPI_Clock_Select(SPIx->SPI_Speed);
	
	SPI_RxTimerOut = 0;
	B_SPI_Busy = 0;
}

//========================================================================
// ����: void SPI_SetMode(u8 mode)
// ����: SPI��������ģʽ����.
// ����: mode: ָ��ģʽ, ȡֵ SPI_Mode_Master �� SPI_Mode_Slave.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void SPI_SetMode(u8 mode)
{
	if(mode == SPI_Mode_Slave)
	{
		MSTR = 0; 	//��������Ϊ�ӻ�����
		SSIG = 0; 	//SS����ȷ������
	}
	else
	{
		MSTR = 1; 	//ʹ�� SPI ����ģʽ
		SSIG = 1; 	//����SS���Ź���
	}
}

//========================================================================
// ����: void SPI_WriteByte(u8 dat)
// ����: SPI����һ���ֽ�����.
// ����: dat: Ҫ���͵�����.
// ����: none.
// �汾: V1.0, 2020-09-14
//========================================================================
void SPI_WriteByte(u8 dat)		//SPI����һ���ֽ�����
{
	if(ESPI)
	{
		B_SPI_Busy = 1;
		SPDAT = dat;
		while(B_SPI_Busy);  //�ж�ģʽ
	}
	else
	{
		SPDAT = dat;
		while(SPIF == 0); //��ѯģʽ
		SPI_ClearFlag();   //���SPIF��WCOL��־
	}
}

//========================================================================
// ����: void SPI_ReadByte(u8 dat)
// ����: SPI��ѯģʽ��ȡһ���ֽ�����.
// ����: none.
// ����: ��ȡ������.
// �汾: V1.0, 2020-09-14
//========================================================================
u8 SPI_ReadByte(void)
{
	SPDAT = 0xff;
	while(SPIF == 0) ;
	SPI_ClearFlag();   //��0 SPIF��WCOL��־
	return (SPDAT);
}
