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
#include "STC32G_USART.h"

//========================================================================
//                               本地变量声明
//========================================================================

//========================================================================
// 函数: void UsartLinSendByte(u8 USARTx, u8 dat)
// 描述: 发送一个字节函数。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-10-28
// 备注: 
//========================================================================
void UsartLinSendByte(u8 USARTx, u8 dat)
{
	if(USARTx == USART1)
	{
		COM1.B_TX_busy = 1;
		SBUF = dat;
		while(COM1.B_TX_busy);
	}
	else if(USARTx == USART2)
	{
		COM2.B_TX_busy = 1;
		S2BUF = dat;
		while(COM2.B_TX_busy);
	}
}

//========================================================================
// 函数: void UsartLinSendData(u8 USARTx, u8 *pdat)
// 描述: Lin发送数据函数。
// 参数: *pdat: 设置数据缓冲区.
// 返回: Lin ID.
// 版本: VER1.0
// 日期: 2021-10-28
// 备注: 
//========================================================================
void UsartLinSendData(u8 USARTx, u8 *pdat)
{
	u8 i;

	for(i=0;i<FRAME_LEN;i++)
	{
		UsartLinSendByte(USARTx,pdat[i]);
	}
}

//========================================================================
// 函数: void UsartLinSendChecksum(u8 USARTx, u8 *dat)
// 描述: 计算校验码并发送。
// 参数: 数据场传输的数据.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-12-2
// 备注: 
//========================================================================
void UsartLinSendChecksum(u8 USARTx, u8 *dat)
{
  u16 sum = 0;
  u8 i;

  for(i = 0; i < FRAME_LEN; i++)
  {
    sum += dat[i];
    if(sum & 0xFF00)
    {
      sum = (sum & 0x00FF) + 1;
    }
  }
  sum ^= 0x00FF;
	UsartLinSendByte(USARTx,(u8)sum);
}

//========================================================================
// 函数: void UsartSendBreak(void)
// 描述: 主模式发送Lin总线Break函数。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-10-28
// 备注: 
//========================================================================
void UsartSendBreak(u8 USARTx)
{
	if(USARTx == USART1)
	{
		USARTCR5 |= 0x04;		//主模式 Send Break
	}
	else if(USARTx == USART2)
	{
		USART2CR5 |= 0x04;		//主模式 Send Break
	}
	UsartLinSendByte(USARTx,0x00);
}

//========================================================================
// 函数: void UsartLinSendPID(u8 id)
// 描述: ID码加上校验符，转成PID码并发送。
// 参数: ID码.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-12-2
// 备注: 
//========================================================================
void UsartLinSendPID(u8 USARTx, u8 id)
{
	u8 P0 ;
	u8 P1 ;
	
	P0 = (((id)^(id>>1)^(id>>2)^(id>>4))&0x01)<<6 ;
	P1 = ((~((id>>1)^(id>>3)^(id>>4)^(id>>5)))&0x01)<<7 ;
	
	UsartLinSendByte(USARTx,id|P0|P1);
}

//========================================================================
// 函数: void UsartLinSendHeader(u8 lid)
// 描述: Lin主机发送帧头函数。
// 参数: ID码.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-10-28
// 备注: 
//========================================================================
void UsartLinSendHeader(u8 USARTx, u8 lid)
{
	UsartSendBreak(USARTx);						//Send Break
	UsartLinSendByte(USARTx,0x55);		//Send Sync Field
	UsartLinSendPID(USARTx,lid);			//设置总线ID
}

//========================================================================
// 函数: void UsartLinSendFrame(u8 USARTx, u8 lid, u8 *pdat)
// 描述: Lin主机发送完整帧函数。
// 参数: lid: Lin ID; *pdat: 发送数据缓冲区.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-10-28
// 备注: 
//========================================================================
void UsartLinSendFrame(u8 USARTx, u8 lid, u8 *pdat)
{
	UsartSendBreak(USARTx);						//Send Break
	UsartLinSendByte(USARTx,0x55);		//Send Sync Field

	UsartLinSendPID(USARTx,lid);			//设置总线ID
	UsartLinSendData(USARTx,pdat);
	UsartLinSendChecksum(USARTx,pdat);
}

//========================================================================
// 函数: void UsartLinBaudrate(u8 USARTx, u16 brt)
// 描述: Lin总线波特率设置函数。
// 参数: brt: 波特率.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-10-28
// 备注: 
//========================================================================
void UsartLinBaudrate(u8 USARTx, u16 brt)
{
	u16 tmp;
	
	tmp = (MAIN_Fosc >> 4) / brt;
	if(USARTx == USART1)
	{
		USARTBRH = (u8)(tmp>>8);
		USARTBRL = (u8)tmp;
	}
	else if(USARTx == USART2)
	{
		USART2BRH = (u8)(tmp>>8);
		USART2BRL = (u8)tmp;
	}
}

//========================================================================
// 函数: UASRT_LIN_Configuration
// 描述: USART初始化程序.
// 参数: USARTx: UART组号, USART结构参数,请参考USART.h里的定义.
// 返回: none.
// 版本: V1.0, 2022-03-30
//========================================================================
u8 UASRT_LIN_Configuration(u8 USARTx, USARTx_LIN_InitDefine *USART)
{
	if(USARTx == USART1)
	{
		SCON = (SCON & 0x3f) | 0x40;    //USART1模式, 0x00: 同步移位输出, 0x40: 8位数据,可变波特率, 0x80: 9位数据,固定波特率, 0xc0: 9位数据,可变波特率
		SMOD = 1;
		TI = 0;
		REN = 1;    //允许接收
		ES  = 1;    //允许中断

		if(USART->LIN_Enable == ENABLE)	USARTCR1 |= 0x80;		//使能LIN模块
		else								USARTCR1 &= ~0x80;		//关闭LIN模块
		if(USART->LIN_Mode == LinSlaveMode)	USARTCR5 |= 0x20;		//LIN模块从机模式
		else								USARTCR5 &= ~0x20;		//LIN模块主机模式
		if(USART->LIN_AutoSync == ENABLE)	USARTCR5 |= 0x10;		//使能自动同步
		else								USARTCR5 &= ~0x10;		//关闭自动同步

		UsartLinBaudrate(USART1,USART->LIN_Baudrate);			//设置波特率

		return SUCCESS;
	}

	if(USARTx == USART2)
	{
		S2CON = (S2CON & 0x3f) | 0x50;
		T2x12 = 1;   //定时器2时钟1T模式
		T2R = 1;     //开始计时
		ES2 = 1;     //允许中断
		S2CFG |= 0x80;				//S2MOD = 1

		if(USART->LIN_Enable == ENABLE)	USART2CR1 |= 0x80;		//使能LIN模块
		else								USART2CR1 &= ~0x80;		//关闭LIN模块
		if(USART->LIN_Mode == LinSlaveMode)	USART2CR5 |= 0x20;		//LIN模块从机模式
		else								USART2CR5 &= ~0x20;		//LIN模块主机模式
		if(USART->LIN_AutoSync == ENABLE)	USART2CR5 |= 0x10;		//使能自动同步
		else								USART2CR5 &= ~0x10;		//关闭自动同步

		UsartLinBaudrate(USART2,USART->LIN_Baudrate);			//设置波特率

		return SUCCESS;
	}
	return FAIL;	//错误
}

/*********************************************************/
