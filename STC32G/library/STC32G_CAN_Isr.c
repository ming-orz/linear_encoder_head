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

#include	"STC32G_CAN.h"

bit B_Can1Read;     //CAN1 �յ����ݱ�־
bit B_Can2Read;     //CAN2 �յ����ݱ�־

//========================================================================
// ����: CAN1_ISR_Handler
// ����: CAN1�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-27
//========================================================================
void CAN1_ISR_Handler (void) interrupt CAN1_VECTOR
{
	u8 isr;
	u8 store;
	u8 arTemp;

	arTemp = CANAR;     //��CANAR�ֳ����棬������ѭ����д�� CANAR ������жϣ����ж����޸��� CANAR ����
	store = AUXR2;      //��AUXR2�ֳ�����
	
	AUXR2 &= ~0x08;		//ѡ��CAN1ģ��
	isr = CanReadReg(ISR);

	if((isr & 0x04) == 0x04)  //TI
	{
		CANAR = ISR;
		CANDR = 0x04;    //CLR FLAG
  }	
	if((isr & 0x08) == 0x08)  //RI
	{
		CANAR = ISR;
		CANDR = 0x08;    //CLR FLAG
	
		B_Can1Read = 1;
	}

	if((isr & 0x40) == 0x40)  //ALI
	{
		CANAR = ISR;
		CANDR = 0x40;    //CLR FLAG
	}	

	if((isr & 0x20) == 0x20)  //EWI
	{
		CANAR = MR;
		CANDR &= ~0x04;  //��� Reset Mode, ��BUS-OFF״̬�˳�
		
		CANAR = ISR;
		CANDR = 0x20;    //CLR FLAG
	}	

	if((isr & 0x10) == 0x10)  //EPI
	{
		CANAR = ISR;
		CANDR = 0x10;    //CLR FLAG
	}	

	if((isr & 0x02) == 0x02)  //BEI
	{
		CANAR = ISR;
		CANDR = 0x02;    //CLR FLAG
	}	

	if((isr & 0x01) == 0x01)  //DOI
	{
		CANAR = ISR;
		CANDR = 0x01;    //CLR FLAG
	}	

	AUXR2 = store;     //��AUXR2�ֳ��ָ�
	CANAR = arTemp;    //��CANAR�ֳ��ָ�
}

//========================================================================
// ����: CAN2_ISR_Handler
// ����: CAN2�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-27
//========================================================================
void CAN2_ISR_Handler (void) interrupt CAN2_VECTOR
{
	u8 isr;
	u8 store;
	u8 arTemp;

	arTemp = CANAR;     //��CANAR�ֳ����棬������ѭ����д�� CANAR ������жϣ����ж����޸��� CANAR ����
	store = AUXR2;      //��AUXR2�ֳ�����
	
	AUXR2 |= 0x08;		//ѡ��CAN2ģ��
	isr = CanReadReg(ISR);

	if((isr & 0x04) == 0x04)  //TI
	{
		CANAR = ISR;
		CANDR = 0x04;    //CLR FLAG
  }	
	if((isr & 0x08) == 0x08)  //RI
	{
		CANAR = ISR;
		CANDR = 0x08;    //CLR FLAG
	
		B_Can2Read = 1;
	}

	if((isr & 0x40) == 0x40)  //ALI
	{
		CANAR = ISR;
		CANDR = 0x40;    //CLR FLAG
	}	

	if((isr & 0x20) == 0x20)  //EWI
	{
		CANAR = MR;
		CANDR &= ~0x04;  //��� Reset Mode, ��BUS-OFF״̬�˳�
		
		CANAR = ISR;
		CANDR = 0x20;    //CLR FLAG
	}	

	if((isr & 0x10) == 0x10)  //EPI
	{
		CANAR = ISR;
		CANDR = 0x10;    //CLR FLAG
	}	

	if((isr & 0x02) == 0x02)  //BEI
	{
		CANAR = ISR;
		CANDR = 0x02;    //CLR FLAG
	}	

	if((isr & 0x01) == 0x01)  //DOI
	{
		CANAR = ISR;
		CANDR = 0x01;    //CLR FLAG
	}	

	AUXR2 = store;     //��AUXR2�ֳ��ָ�
	CANAR = arTemp;    //��CANAR�ֳ��ָ�
}


