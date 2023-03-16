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

#include	"STC32G_Timer.h"

//========================================================================
// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回 SUCCESS, 错误返回 FAIL.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM == Timer0)
	{
		Timer0_Stop();		//停止计数
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return FAIL;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 不可屏蔽16位自动重装
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer0_CLK_Select(TIMx->TIM_ClkSource);	//对外计数或分频, 定时12T/1T
		Timer0_CLK_Output(TIMx->TIM_ClkOut);		//输出时钟使能
		T0_Load(TIMx->TIM_Value);
		Timer0_Run(TIMx->TIM_Run);
		return	SUCCESS;		//成功
	}

	if(TIM == Timer1)
	{
		Timer1_Stop();		//停止计数
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return FAIL;	//错误
		TMOD = (TMOD & ~0x30) | (TIMx->TIM_Mode << 4);	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 停止工作
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer1_CLK_Select(TIMx->TIM_ClkSource);	//对外计数或分频, 定时12T/1T
		Timer1_CLK_Output(TIMx->TIM_ClkOut);		//输出时钟使能
		T1_Load(TIMx->TIM_Value);
		Timer1_Run(TIMx->TIM_Run);
		return	SUCCESS;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		Timer2_Stop();	//停止计数
		Timer2_CLK_Select(TIMx->TIM_ClkSource);	//对外计数或分频, 定时12T/1T
		Timer2_CLK_Output(TIMx->TIM_ClkOut);		//输出时钟使能

		T2_Load(TIMx->TIM_Value);
		Timer2_Run(TIMx->TIM_Run);
		return	SUCCESS;		//成功
	}

	if(TIM == Timer3)		//Timer3,固定为16位自动重装, 中断无优先级
	{
		Timer3_Stop();	//停止计数
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer3_CLK_Select(TIMx->TIM_ClkSource);	//对外计数或分频, 定时12T/1T
		Timer3_CLK_Output(TIMx->TIM_ClkOut);		//输出时钟使能

		T3_Load(TIMx->TIM_Value);
		Timer3_Run(TIMx->TIM_Run);
		return	SUCCESS;		//成功
	}

	if(TIM == Timer4)		//Timer3,固定为16位自动重装, 中断无优先级
	{
		Timer4_Stop();	//停止计数
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer4_CLK_Select(TIMx->TIM_ClkSource);	//对外计数或分频, 定时12T/1T
		Timer4_CLK_Output(TIMx->TIM_ClkOut);		//输出时钟使能

		T4_Load(TIMx->TIM_Value);
		Timer4_Run(TIMx->TIM_Run);
		return	SUCCESS;		//成功
	}
	return FAIL;	//错误
}
