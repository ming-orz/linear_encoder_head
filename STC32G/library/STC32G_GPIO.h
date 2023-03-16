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

#ifndef	__STC32G_GPIO_H
#define	__STC32G_GPIO_H

#include "config.h"

//========================================================================
//                            端口模式设置
//========================================================================
//准双向口
#define  P0_MODE_IO_PU(Pin)				{P0M1 &= ~(Pin), P0M0 &= ~(Pin);}
#define  P1_MODE_IO_PU(Pin)				{P1M1 &= ~(Pin), P1M0 &= ~(Pin);}
#define  P2_MODE_IO_PU(Pin)				{P2M1 &= ~(Pin), P2M0 &= ~(Pin);}
#define  P3_MODE_IO_PU(Pin)				{P3M1 &= ~(Pin), P3M0 &= ~(Pin);}
#define  P4_MODE_IO_PU(Pin)				{P4M1 &= ~(Pin), P4M0 &= ~(Pin);}
#define  P5_MODE_IO_PU(Pin)				{P5M1 &= ~(Pin), P5M0 &= ~(Pin);}
#define  P6_MODE_IO_PU(Pin)				{P6M1 &= ~(Pin), P6M0 &= ~(Pin);}
#define  P7_MODE_IO_PU(Pin)				{P7M1 &= ~(Pin), P7M0 &= ~(Pin);}
//高阻输入
#define  P0_MODE_IN_HIZ(Pin)			{P0M1 |= (Pin), P0M0 &= ~(Pin);}
#define  P1_MODE_IN_HIZ(Pin)			{P1M1 |= (Pin), P1M0 &= ~(Pin);}
#define  P2_MODE_IN_HIZ(Pin)			{P2M1 |= (Pin), P2M0 &= ~(Pin);}
#define  P3_MODE_IN_HIZ(Pin)			{P3M1 |= (Pin), P3M0 &= ~(Pin);}
#define  P4_MODE_IN_HIZ(Pin)			{P4M1 |= (Pin), P4M0 &= ~(Pin);}
#define  P5_MODE_IN_HIZ(Pin)			{P5M1 |= (Pin), P5M0 &= ~(Pin);}
#define  P6_MODE_IN_HIZ(Pin)			{P6M1 |= (Pin), P6M0 &= ~(Pin);}
#define  P7_MODE_IN_HIZ(Pin)			{P7M1 |= (Pin), P7M0 &= ~(Pin);}
//漏极开路
#define  P0_MODE_OUT_OD(Pin)			{P0M1 |= (Pin), P0M0 |= (Pin);}
#define  P1_MODE_OUT_OD(Pin)			{P1M1 |= (Pin), P1M0 |= (Pin);}
#define  P2_MODE_OUT_OD(Pin)			{P2M1 |= (Pin), P2M0 |= (Pin);}
#define  P3_MODE_OUT_OD(Pin)			{P3M1 |= (Pin), P3M0 |= (Pin);}
#define  P4_MODE_OUT_OD(Pin)			{P4M1 |= (Pin), P4M0 |= (Pin);}
#define  P5_MODE_OUT_OD(Pin)			{P5M1 |= (Pin), P5M0 |= (Pin);}
#define  P6_MODE_OUT_OD(Pin)			{P6M1 |= (Pin), P6M0 |= (Pin);}
#define  P7_MODE_OUT_OD(Pin)			{P7M1 |= (Pin), P7M0 |= (Pin);}
//推挽输出
#define  P0_MODE_OUT_PP(Pin)			{P0M1 &= ~(Pin), P0M0 |= (Pin);}
#define  P1_MODE_OUT_PP(Pin)			{P1M1 &= ~(Pin), P1M0 |= (Pin);}
#define  P2_MODE_OUT_PP(Pin)			{P2M1 &= ~(Pin), P2M0 |= (Pin);}
#define  P3_MODE_OUT_PP(Pin)			{P3M1 &= ~(Pin), P3M0 |= (Pin);}
#define  P4_MODE_OUT_PP(Pin)			{P4M1 &= ~(Pin), P4M0 |= (Pin);}
#define  P5_MODE_OUT_PP(Pin)			{P5M1 &= ~(Pin), P5M0 |= (Pin);}
#define  P6_MODE_OUT_PP(Pin)			{P6M1 &= ~(Pin), P6M0 |= (Pin);}
#define  P7_MODE_OUT_PP(Pin)			{P7M1 &= ~(Pin), P7M0 |= (Pin);}

//========================================================================
//                         端口内部4.1K上拉设置
//========================================================================
//上拉使能
#define P0_PULL_UP_ENABLE(Pin)		P0PU |= (Pin)
#define P1_PULL_UP_ENABLE(Pin)		P1PU |= (Pin)
#define P2_PULL_UP_ENABLE(Pin)		P2PU |= (Pin)
#define P3_PULL_UP_ENABLE(Pin)		P3PU |= (Pin)
#define P4_PULL_UP_ENABLE(Pin)		P4PU |= (Pin)
#define P5_PULL_UP_ENABLE(Pin)		P5PU |= (Pin)
#define P6_PULL_UP_ENABLE(Pin)		P6PU |= (Pin)
#define P7_PULL_UP_ENABLE(Pin)		P7PU |= (Pin)
//上拉禁止
#define P0_PULL_UP_DISABLE(Pin)		P0PU &= ~(Pin)
#define P1_PULL_UP_DISABLE(Pin)		P1PU &= ~(Pin)
#define P2_PULL_UP_DISABLE(Pin)		P2PU &= ~(Pin)
#define P3_PULL_UP_DISABLE(Pin)		P3PU &= ~(Pin)
#define P4_PULL_UP_DISABLE(Pin)		P4PU &= ~(Pin)
#define P5_PULL_UP_DISABLE(Pin)		P5PU &= ~(Pin)
#define P6_PULL_UP_DISABLE(Pin)		P6PU &= ~(Pin)
#define P7_PULL_UP_DISABLE(Pin)		P7PU &= ~(Pin)

//========================================================================
//                           端口施密特触发设置
//========================================================================
//施密特触发使能
#define P0_ST_ENABLE(Pin)					P0NCS &= ~(Pin)
#define P1_ST_ENABLE(Pin)					P1NCS &= ~(Pin)
#define P2_ST_ENABLE(Pin)					P2NCS &= ~(Pin)
#define P3_ST_ENABLE(Pin)					P3NCS &= ~(Pin)
#define P4_ST_ENABLE(Pin)					P4NCS &= ~(Pin)
#define P5_ST_ENABLE(Pin)					P5NCS &= ~(Pin)
#define P6_ST_ENABLE(Pin)					P6NCS &= ~(Pin)
#define P7_ST_ENABLE(Pin)					P7NCS &= ~(Pin)
//施密特触发禁止
#define P0_ST_DISABLE(Pin)				P0NCS |= (Pin)
#define P1_ST_DISABLE(Pin)				P1NCS |= (Pin)
#define P2_ST_DISABLE(Pin)				P2NCS |= (Pin)
#define P3_ST_DISABLE(Pin)				P3NCS |= (Pin)
#define P4_ST_DISABLE(Pin)				P4NCS |= (Pin)
#define P5_ST_DISABLE(Pin)				P5NCS |= (Pin)
#define P6_ST_DISABLE(Pin)				P6NCS |= (Pin)
#define P7_ST_DISABLE(Pin)				P7NCS |= (Pin)

//========================================================================
//                          端口电平转换速度设置
//========================================================================
//电平转换慢速，相应的上下冲比较小
#define P0_SPEED_LOW(Pin)					P0SR |= (Pin) 
#define P1_SPEED_LOW(Pin)					P1SR |= (Pin) 
#define P2_SPEED_LOW(Pin)					P2SR |= (Pin) 
#define P3_SPEED_LOW(Pin)					P3SR |= (Pin) 
#define P4_SPEED_LOW(Pin)					P4SR |= (Pin) 
#define P5_SPEED_LOW(Pin)					P5SR |= (Pin) 
#define P6_SPEED_LOW(Pin)					P6SR |= (Pin) 
#define P7_SPEED_LOW(Pin)					P7SR |= (Pin) 
//电平转换快速，相应的上下冲比较大
#define P0_SPEED_HIGH(Pin)				P0SR &= ~(Pin) 
#define P1_SPEED_HIGH(Pin)				P1SR &= ~(Pin) 
#define P2_SPEED_HIGH(Pin)				P2SR &= ~(Pin) 
#define P3_SPEED_HIGH(Pin)				P3SR &= ~(Pin) 
#define P4_SPEED_HIGH(Pin)				P4SR &= ~(Pin) 
#define P5_SPEED_HIGH(Pin)				P5SR &= ~(Pin) 
#define P6_SPEED_HIGH(Pin)				P6SR &= ~(Pin) 
#define P7_SPEED_HIGH(Pin)				P7SR &= ~(Pin) 

//========================================================================
//                          端口驱动电流控制设置
//========================================================================
//一般驱动能力
#define P0_DRIVE_MEDIUM(Pin)			P0DR |= (Pin)
#define P1_DRIVE_MEDIUM(Pin)			P1DR |= (Pin)
#define P2_DRIVE_MEDIUM(Pin)			P2DR |= (Pin)
#define P3_DRIVE_MEDIUM(Pin)			P3DR |= (Pin)
#define P4_DRIVE_MEDIUM(Pin)			P4DR |= (Pin)
#define P5_DRIVE_MEDIUM(Pin)			P5DR |= (Pin)
#define P6_DRIVE_MEDIUM(Pin)			P6DR |= (Pin)
#define P7_DRIVE_MEDIUM(Pin)			P7DR |= (Pin)
//增强驱动能力
#define P0_DRIVE_HIGH(Pin)				P0DR &= ~(Pin)
#define P1_DRIVE_HIGH(Pin)				P1DR &= ~(Pin)
#define P2_DRIVE_HIGH(Pin)				P2DR &= ~(Pin)
#define P3_DRIVE_HIGH(Pin)				P3DR &= ~(Pin)
#define P4_DRIVE_HIGH(Pin)				P4DR &= ~(Pin)
#define P5_DRIVE_HIGH(Pin)				P5DR &= ~(Pin)
#define P6_DRIVE_HIGH(Pin)				P6DR &= ~(Pin)
#define P7_DRIVE_HIGH(Pin)				P7DR &= ~(Pin)

//========================================================================
//                          端口数字信号输入使能
//========================================================================
//使能数字信号输入
#define P0_DIGIT_IN_ENABLE(Pin)		P0IE |= (Pin)
#define P1_DIGIT_IN_ENABLE(Pin)		P1IE |= (Pin)
#define P2_DIGIT_IN_ENABLE(Pin)		P2IE |= (Pin)
#define P3_DIGIT_IN_ENABLE(Pin)		P3IE |= (Pin)
#define P4_DIGIT_IN_ENABLE(Pin)		P4IE |= (Pin)
#define P5_DIGIT_IN_ENABLE(Pin)		P5IE |= (Pin)
#define P6_DIGIT_IN_ENABLE(Pin)		P6IE |= (Pin)
#define P7_DIGIT_IN_ENABLE(Pin)		P7IE |= (Pin)
//禁止数字信号输入
#define P0_DIGIT_IN_DISABLE(Pin)	P0IE &= ~(Pin)
#define P1_DIGIT_IN_DISABLE(Pin)	P1IE &= ~(Pin)
#define P2_DIGIT_IN_DISABLE(Pin)	P2IE &= ~(Pin)
#define P3_DIGIT_IN_DISABLE(Pin)	P3IE &= ~(Pin)
#define P4_DIGIT_IN_DISABLE(Pin)	P4IE &= ~(Pin)
#define P5_DIGIT_IN_DISABLE(Pin)	P5IE &= ~(Pin)
#define P6_DIGIT_IN_DISABLE(Pin)	P6IE &= ~(Pin)
#define P7_DIGIT_IN_DISABLE(Pin)	P7IE &= ~(Pin)

//========================================================================
//                              定义声明
//========================================================================

#define	GPIO_PullUp		0	//上拉准双向口
#define	GPIO_HighZ		1	//浮空输入
#define	GPIO_OUT_OD		2	//开漏输出
#define	GPIO_OUT_PP		3	//推挽输出

#define	GPIO_Pin_0		0x01	//IO引脚 Px.0
#define	GPIO_Pin_1		0x02	//IO引脚 Px.1
#define	GPIO_Pin_2		0x04	//IO引脚 Px.2
#define	GPIO_Pin_3		0x08	//IO引脚 Px.3
#define	GPIO_Pin_4		0x10	//IO引脚 Px.4
#define	GPIO_Pin_5		0x20	//IO引脚 Px.5
#define	GPIO_Pin_6		0x40	//IO引脚 Px.6
#define	GPIO_Pin_7		0x80	//IO引脚 Px.7
#define	GPIO_Pin_LOW	0x0F	//IO低4位引脚
#define	GPIO_Pin_HIGH	0xF0	//IO高4位引脚
#define	GPIO_Pin_All	0xFF	//IO所有引脚

#define	GPIO_P0			0		//
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5
#define	GPIO_P6			6
#define	GPIO_P7			7


typedef struct
{
	u8	Mode;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	u8	Pin;		//要设置的端口	
} GPIO_InitTypeDef;

u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx);

#endif
