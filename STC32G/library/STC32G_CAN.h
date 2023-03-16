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

#ifndef	__STC32G_CAN_H
#define	__STC32G_CAN_H

#include	"config.h"

//========================================================================
//                              定义声明
//========================================================================

#define	CAN1	0
#define	CAN2	1

#define	STANDARD_FRAME   0x00    //帧格式：标准帧
#define	EXTENDED_FRAME   0x80    //帧格式：扩展帧

//========================================================================
//                              常量声明
//========================================================================

#define CAN_DOIM     0x01  //接收溢出中断
#define CAN_BEIM     0x02  //总线错位中断
#define CAN_TIM      0x04  //发送中断
#define CAN_RIM      0x08  //接收中断
#define CAN_EPIM     0x10  //被动错位中断
#define CAN_EWIM     0x20  //错位警告中断
#define CAN_ALIM     0x40  //仲裁丢失中断
#define CAN_ALLIM    0x7F  //所有中断

//========================================================================
//                              变量声明
//========================================================================

typedef struct
{
	u8	CAN_Enable;					//CAN功能使能  	ENABLE,DISABLE
	u8	CAN_IMR;						//CAN中断寄存器 	CAN_DOIM,CAN_BEIM,CAN_TIM,CAN_RIM,CAN_EPIM,CAN_EWIM,CAN_ALIM,CAN_ALLIM,DISABLE
	u8	CAN_SJW;						//重新同步跳跃宽度  0~3
	u8	CAN_BRP;						//波特率分频系数    0~63
	u8	CAN_SAM;						//总线电平采样次数  0:采样1次; 1:采样3次
	u8	CAN_TSG1;						//同步采样段1       0~15
	u8	CAN_TSG2;						//同步采样段2       1~7 (TSG2 不能设置为0)

	u8	CAN_ACR0;						//总线验收代码寄存器 0~0xFF
	u8	CAN_ACR1;						//总线验收代码寄存器 0~0xFF
	u8	CAN_ACR2;						//总线验收代码寄存器 0~0xFF
	u8	CAN_ACR3;						//总线验收代码寄存器 0~0xFF
	u8	CAN_AMR0;						//总线验收屏蔽寄存器 0~0xFF
	u8	CAN_AMR1;						//总线验收屏蔽寄存器 0~0xFF
	u8	CAN_AMR2;						//总线验收屏蔽寄存器 0~0xFF
	u8	CAN_AMR3;						//总线验收屏蔽寄存器 0~0xFF
} CAN_InitTypeDef;

typedef struct
{
	u8	FF;             //帧格式
	u32	ID;             //CAN ID
	u8	DLC;            //数据长度
	u8	DataBuffer[8];  //数据缓存
}CAN_DataDef;


//========================================================================
//                              外部声明
//========================================================================
extern bit B_Can1Read;     //CAN 收到数据标志
extern bit B_Can2Read;     //CAN 收到数据标志

extern CAN_DataDef CAN1_Tx;
extern CAN_DataDef CAN1_Rx[8];
extern CAN_DataDef CAN2_Tx;
extern CAN_DataDef CAN2_Rx[8];


u8 CanReadReg(u8 addr);
void CAN_Inilize(u8 CANx, CAN_InitTypeDef *CAN);
u8 CanReadMsg(CAN_DataDef *CAN);
void CanSendMsg(CAN_DataDef *CAN);

#endif
