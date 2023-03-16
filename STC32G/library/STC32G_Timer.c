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

#include	"STC32G_Timer.h"

//========================================================================
// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM == Timer0)
	{
		Timer0_Stop();		//ֹͣ����
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return FAIL;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: ��������16λ�Զ���װ
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer0_CLK_Select(TIMx->TIM_ClkSource);	//����������Ƶ, ��ʱ12T/1T
		Timer0_CLK_Output(TIMx->TIM_ClkOut);		//���ʱ��ʹ��
		T0_Load(TIMx->TIM_Value);
		Timer0_Run(TIMx->TIM_Run);
		return	SUCCESS;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		Timer1_Stop();		//ֹͣ����
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return FAIL;	//����
		TMOD = (TMOD & ~0x30) | (TIMx->TIM_Mode << 4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: ֹͣ����
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer1_CLK_Select(TIMx->TIM_ClkSource);	//����������Ƶ, ��ʱ12T/1T
		Timer1_CLK_Output(TIMx->TIM_ClkOut);		//���ʱ��ʹ��
		T1_Load(TIMx->TIM_Value);
		Timer1_Run(TIMx->TIM_Run);
		return	SUCCESS;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		Timer2_Stop();	//ֹͣ����
		Timer2_CLK_Select(TIMx->TIM_ClkSource);	//����������Ƶ, ��ʱ12T/1T
		Timer2_CLK_Output(TIMx->TIM_ClkOut);		//���ʱ��ʹ��

		T2_Load(TIMx->TIM_Value);
		Timer2_Run(TIMx->TIM_Run);
		return	SUCCESS;		//�ɹ�
	}

	if(TIM == Timer3)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		Timer3_Stop();	//ֹͣ����
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer3_CLK_Select(TIMx->TIM_ClkSource);	//����������Ƶ, ��ʱ12T/1T
		Timer3_CLK_Output(TIMx->TIM_ClkOut);		//���ʱ��ʹ��

		T3_Load(TIMx->TIM_Value);
		Timer3_Run(TIMx->TIM_Run);
		return	SUCCESS;		//�ɹ�
	}

	if(TIM == Timer4)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		Timer4_Stop();	//ֹͣ����
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return FAIL;
		Timer4_CLK_Select(TIMx->TIM_ClkSource);	//����������Ƶ, ��ʱ12T/1T
		Timer4_CLK_Output(TIMx->TIM_ClkOut);		//���ʱ��ʹ��

		T4_Load(TIMx->TIM_Value);
		Timer4_Run(TIMx->TIM_Run);
		return	SUCCESS;		//�ɹ�
	}
	return FAIL;	//����
}
