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

#include	"STC32G_Compare.h"

//========================================================================
// ����:void	CMP_Inilize(CMP_InitDefine *CMPx)
// ����: �Ƚ�����ʼ������.
// ����: CMPx: �ṹ����,��ο�compare.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void	CMP_Inilize(CMP_InitDefine *CMPx)
{
	CMPCR1 &= 0x30;
	CMPCR2 = CMPx->CMP_OutDelayDuty & 0x3f;							//�ȽϽ���仯��ʱ������, 0~63
	if(CMPx->CMP_EN == ENABLE)				CMPEN = 1;				//����Ƚ���		ENABLE,DISABLE
	if(CMPx->CMP_Outpt_En == ENABLE)		CMPOE = 1;			//����ȽϽ�������P3.4/P4.1,   ENABLE,DISABLE
	if(CMPx->CMP_InvCMPO     == ENABLE)		INVCMPO = 1;	//�Ƚ������ȡ��, 	ENABLE,DISABLE
	if(CMPx->CMP_100nsFilter == DISABLE)	DISFLT = 1;		//�ڲ�0.1us�˲�,  	ENABLE,DISABLE

	if(CMPx->CMP_P_Select  <= CMP_P_ADC)	CMPEXCFG = (CMPEXCFG & ~0x03) | (CMPx->CMP_P_Select);			//�Ƚ�����������ѡ��, CMP_P_P37/CMP_P_P50/CMP_P_P51, CMP_P_ADC: ��ADCģ���������������.
	if(CMPx->CMP_N_Select  <= CMP_N_GAP)	CMPEXCFG = (CMPEXCFG & ~0x04) | (CMPx->CMP_N_Select << 2);	//�Ƚ������븺��ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap����OP��ĵ�ѹ��������, CMP_N_P36: ѡ��P3.6��������.
}
