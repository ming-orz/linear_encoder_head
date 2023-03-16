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

#include	"STC32G_CAN.h"

bit B_Can1Read;     //CAN1 收到数据标志
bit B_Can2Read;     //CAN2 收到数据标志

//========================================================================
// 函数: CAN1_ISR_Handler
// 描述: CAN1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-27
//========================================================================
void CAN1_ISR_Handler (void) interrupt CAN1_VECTOR
{
	u8 isr;
	u8 store;
	u8 arTemp;

	arTemp = CANAR;     //先CANAR现场保存，避免主循环里写完 CANAR 后产生中断，在中断里修改了 CANAR 内容
	store = AUXR2;      //后AUXR2现场保存
	
	AUXR2 &= ~0x08;		//选择CAN1模块
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
		CANDR &= ~0x04;  //清除 Reset Mode, 从BUS-OFF状态退出
		
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

	AUXR2 = store;     //先AUXR2现场恢复
	CANAR = arTemp;    //后CANAR现场恢复
}

//========================================================================
// 函数: CAN2_ISR_Handler
// 描述: CAN2中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-03-27
//========================================================================
void CAN2_ISR_Handler (void) interrupt CAN2_VECTOR
{
	u8 isr;
	u8 store;
	u8 arTemp;

	arTemp = CANAR;     //先CANAR现场保存，避免主循环里写完 CANAR 后产生中断，在中断里修改了 CANAR 内容
	store = AUXR2;      //后AUXR2现场保存
	
	AUXR2 |= 0x08;		//选择CAN2模块
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
		CANDR &= ~0x04;  //清除 Reset Mode, 从BUS-OFF状态退出
		
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

	AUXR2 = store;     //先AUXR2现场恢复
	CANAR = arTemp;    //后CANAR现场恢复
}


