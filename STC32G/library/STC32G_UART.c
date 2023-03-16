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

#include "STC32G_UART.h"

//========================================================================
//                               ���ر�������
//========================================================================

#ifdef UART1
COMx_Define	COM1;
u8	UART_BUF_type TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
u8 	UART_BUF_type RX1_Buffer[COM_RX1_Lenth];	//���ջ���
#endif
#ifdef UART2
COMx_Define	COM2;
u8	UART_BUF_type TX2_Buffer[COM_TX2_Lenth];	//���ͻ���
u8 	UART_BUF_type RX2_Buffer[COM_RX2_Lenth];	//���ջ���
#endif
#ifdef UART3
COMx_Define	COM3;
u8	UART_BUF_type TX3_Buffer[COM_TX3_Lenth];	//���ͻ���
u8 	UART_BUF_type RX3_Buffer[COM_RX3_Lenth];	//���ջ���
#endif
#ifdef UART4
COMx_Define	COM4;
u8	UART_BUF_type TX4_Buffer[COM_TX4_Lenth];	//���ͻ���
u8 	UART_BUF_type RX4_Buffer[COM_RX4_Lenth];	//���ջ���
#endif

//========================================================================
// ����: UART_Configuration
// ����: UART��ʼ������.
// ����: UARTx: UART���, COMx�ṹ����,��ο�UART.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
u8 UART_Configuration(u8 UARTx, COMx_InitDefine *COMx)
{
#if  defined( UART1 ) || defined( UART2 ) || defined( UART3 ) || defined( UART4 )
	u16	i;
	u32	j;
#else
	UARTx = NULL;
	COMx = NULL;
#endif

#ifdef UART1
	if(UARTx == UART1)
	{
		COM1.TX_send    = 0;
		COM1.TX_write   = 0;
		COM1.B_TX_busy  = 0;
		COM1.RX_Cnt     = 0;
		COM1.RX_TimeOut = 0;
		
		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		SCON = (SCON & 0x3f) | COMx->UART_Mode;	//ģʽ����
		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return FAIL;	//����
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				T2R = 0;		//Timer stop
				S1BRT = 1;	//S1 BRT Use Timer2;
				T2_CT = 0;	//Timer2 set As Timer
				T2x12 = 1;	//Timer2 set as 1T mode
				T2H = (u8)(j>>8);
				T2L = (u8)j;
				T2R = 1;		//Timer run enable
			}
			else
			{
				TR1 = 0;
				S1BRT = 0;		//S1 BRT Use Timer1;
				T1_CT = 0;		//Timer1 set As Timer
				TMOD &= ~0x30;//Timer1_16bitAutoReload;
				T1x12 = 1;		//Timer1 set as 1T mode
				TH1 = (u8)(j>>8);
				TL1 = (u8)j;
				TR1  = 1;
			}
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	S1M0x6 = 1;	//�̶�������SysClk/2
			else								S1M0x6 = 0;	//�̶�������SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//�̶�������SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	SMOD = 1;	//�̶�������SysClk/32
			else								SMOD = 0;	//�̶�������SysClk/64
		}
		UART1_RxEnable(COMx->UART_RxEnable);	//UART����ʹ��

		return SUCCESS;
	}
#endif
#ifdef UART2
	if(UARTx == UART2)
	{
		COM2.TX_send    = 0;
		COM2.TX_write   = 0;
		COM2.B_TX_busy  = 0;
		COM2.RX_Cnt     = 0;
		COM2.RX_TimeOut = 0;

		for(i=0; i<COM_TX2_Lenth; i++)	TX2_Buffer[i] = 0;
		for(i=0; i<COM_RX2_Lenth; i++)	RX2_Buffer[i] = 0;

		S2CON = (S2CON & 0x3f) | COMx->UART_Mode;	//ģʽ����
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return FAIL;	//����
			j = 65536UL - j;
			T2R = 0;		//Timer stop
			T2_CT = 0;	//Timer2 set As Timer
			T2x12 = 1;	//Timer2 set as 1T mode
			T2H = (u8)(j>>8);
			T2L = (u8)j;
			T2R = 1;		//Timer run enable
		}
		else	return FAIL;	//ģʽ����
		UART2_RxEnable(COMx->UART_RxEnable);	//UART����ʹ��

		return SUCCESS;
	}
#endif
#ifdef UART3
	if(UARTx == UART3)
	{
		COM3.TX_send    = 0;
		COM3.TX_write   = 0;
		COM3.B_TX_busy  = 0;
		COM3.RX_Cnt     = 0;
		COM3.RX_TimeOut = 0;
		for(i=0; i<COM_TX3_Lenth; i++)	TX3_Buffer[i] = 0;
		for(i=0; i<COM_RX3_Lenth; i++)	RX3_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			if(COMx->UART_Mode == UART_9bit_BRTx)	S3_9bit();	//9bit
			else									S3_8bit();	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return FAIL;	//����
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				T2R = 0;		//Timer stop
				S3_BRT_UseTimer2();	//S3 BRT Use Timer2;
				T2_CT = 0;	//Timer2 set As Timer
				T2x12 = 1;	//Timer2 set as 1T mode
				T2H = (u8)(j>>8);
				T2L = (u8)j;
				T2R = 1;		//Timer run enable
			}
			else
			{
				T3R = 0;		//Timer stop
				S3_BRT_UseTimer3();		//S3 BRT Use Timer3;
				T3H = (u8)(j>>8);
				T3L = (u8)j;
				T3_CT = 0;	//Timer3 set As Timer
				T3x12 = 1;	//Timer3 set as 1T mode
				T3R = 1;		//Timer run enable
			}
		}
		else	return FAIL;	//ģʽ����
		UART3_RxEnable(COMx->UART_RxEnable);	//UART����ʹ��

		return SUCCESS;
	}
#endif
#ifdef UART4
	if(UARTx == UART4)
	{
		COM4.TX_send    = 0;
		COM4.TX_write   = 0;
		COM4.B_TX_busy  = 0;
		COM4.RX_Cnt     = 0;
		COM4.RX_TimeOut = 0;
		for(i=0; i<COM_TX4_Lenth; i++)	TX4_Buffer[i] = 0;
		for(i=0; i<COM_RX4_Lenth; i++)	RX4_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			if(COMx->UART_Mode == UART_9bit_BRTx)	S4_9bit();	//9bit
			else									S4_8bit();	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return FAIL;	//����
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				T2R = 0;		//Timer stop
				S4_BRT_UseTimer2();	//S4 BRT Use Timer2;
				T2_CT = 0;	//Timer2 set As Timer
				T2x12 = 1;	//Timer2 set as 1T mode
				T2H = (u8)(j>>8);
				T2L = (u8)j;
				T2R = 1;		//Timer run enable
			}
			else
			{
				T4R = 0;		//Timer stop
				S4_BRT_UseTimer4();		//S4 BRT Use Timer4;
				T4H = (u8)(j>>8);
				T4L = (u8)j;
				T4_CT = 0;	//Timer4 set As Timer
				T4x12 = 1;	//Timer4 set as 1T mode
				T4R = 1;		//Timer run enable
			}
		}
		else	return FAIL;	//ģʽ����
		UART4_RxEnable(COMx->UART_RxEnable);	//UART����ʹ��
		
		return SUCCESS;
	}
#endif
	return FAIL;	//����
}

/*********************************************************/

/********************* UART1 ���� ************************/
#ifdef UART1
void TX1_write2buff(u8 dat)	//����1���ͺ���
{
	TX1_Buffer[COM1.TX_write] = dat;	//װ���ͻ��壬ʹ�ö���ʽ���ݷ��ͣ�һ���Է������ݳ��Ȳ�Ҫ������������С��COM_TXn_Lenth��
	if(++COM1.TX_write >= COM_TX1_Lenth)	COM1.TX_write = 0;

	if(COM1.B_TX_busy == 0)		//����
	{  
		COM1.B_TX_busy = 1;		//��־æ
		TI = 1;					//���������ж�
	}

    //������������ʽ���ͷ������ڴ��ڽ����ж������B_TX_busy����
//	SBUF = dat;
//	COM1.B_TX_busy = 1;		//��־æ
//	while(COM1.B_TX_busy);
}

void PrintString1(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX1_write2buff(*puts); 	//����ֹͣ��0����
}

#endif

/********************* UART2 ���� ************************/
#ifdef UART2
void TX2_write2buff(u8 dat)	//����2���ͺ���
{
	TX2_Buffer[COM2.TX_write] = dat;	//װ���ͻ��壬ʹ�ö���ʽ���ݷ��ͣ�һ���Է������ݳ��Ȳ�Ҫ������������С��COM_TXn_Lenth��
	if(++COM2.TX_write >= COM_TX2_Lenth)	COM2.TX_write = 0;

	if(COM2.B_TX_busy == 0)		//����
	{  
		COM2.B_TX_busy = 1;		//��־æ
		S2TI = 1;				//���������ж�
	}

    //������������ʽ���ͷ������ڴ��ڽ����ж������B_TX_busy����
//	S2BUF = dat;
//	COM2.B_TX_busy = 1;		//��־æ
//	while(COM2.B_TX_busy);
}

void PrintString2(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX2_write2buff(*puts); 	//����ֹͣ��0����
}

#endif

/********************* UART3 ���� ************************/
#ifdef UART3
void TX3_write2buff(u8 dat)	//����3���ͺ���
{
	TX3_Buffer[COM3.TX_write] = dat;	//װ���ͻ��壬ʹ�ö���ʽ���ݷ��ͣ�һ���Է������ݳ��Ȳ�Ҫ������������С��COM_TXn_Lenth��
	if(++COM3.TX_write >= COM_TX3_Lenth)	COM3.TX_write = 0;

	if(COM3.B_TX_busy == 0)		//����
	{  
		COM3.B_TX_busy = 1;		//��־æ
		S3TI = 1;				//���������ж�
	}

    //������������ʽ���ͷ������ڴ��ڽ����ж������B_TX_busy����
//	S3BUF = dat;
//	COM3.B_TX_busy = 1;		//��־æ
//	while(COM3.B_TX_busy);
}

void PrintString3(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX3_write2buff(*puts); 	//����ֹͣ��0����
}

#endif

/********************* UART4 ���� ************************/
#ifdef UART4
void TX4_write2buff(u8 dat)	//����4���ͺ���
{
	TX4_Buffer[COM4.TX_write] = dat;	//װ���ͻ��壬ʹ�ö���ʽ���ݷ��ͣ�һ���Է������ݳ��Ȳ�Ҫ������������С��COM_TXn_Lenth��
	if(++COM4.TX_write >= COM_TX4_Lenth)	COM4.TX_write = 0;

	if(COM4.B_TX_busy == 0)		//����
	{  
		COM4.B_TX_busy = 1;		//��־æ
		S4TI = 1;				//���������ж�
	}

    //������������ʽ���ͷ������ڴ��ڽ����ж������B_TX_busy����
//	S4BUF = dat;
//	COM4.B_TX_busy = 1;		//��־æ
//	while(COM4.B_TX_busy);
}

void PrintString4(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX4_write2buff(*puts); 	//����ֹͣ��0����
}

#endif

/*********************************************************/
/*
void COMx_write2buff(COMx_Define *COMx, u8 dat)	//д�뷢�ͻ��壬ָ��+1
{
	if(COMx->id == 1)	TX1_write2buff(dat);
	if(COMx->id == 2)	TX2_write2buff(dat);
	if(COMx->id == 3)	TX3_write2buff(dat);
	if(COMx->id == 4)	TX4_write2buff(dat);
}

void PrintString(COMx_Define *COMx, u8 *puts)
{
    for (; *puts != 0;	puts++)  COMx_write2buff(COMx,*puts); 	//����ֹͣ��0����
}
*/

/********************* Printf ���� ************************/
#if(PRINTF_SELECT == 1)

char putchar(char c)
{
	TX1_write2buff(c);
	return c;
}

#elif(PRINTF_SELECT == 2)

char putchar(char c)
{
	TX2_write2buff(c);
	return c;
}

#elif(PRINTF_SELECT == 3)

char putchar(char c)
{
	TX3_write2buff(c);
	return c;
}

#elif(PRINTF_SELECT == 4)

char putchar(char c)
{
	TX4_write2buff(c);
	return c;
}

#endif
