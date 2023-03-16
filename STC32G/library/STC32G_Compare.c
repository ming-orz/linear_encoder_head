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

#include	"STC32G_Compare.h"

//========================================================================
// 函数:void	CMP_Inilize(CMP_InitDefine *CMPx)
// 描述: 比较器初始化程序.
// 参数: CMPx: 结构参数,请参考compare.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
void	CMP_Inilize(CMP_InitDefine *CMPx)
{
	CMPCR1 &= 0x30;
	CMPCR2 = CMPx->CMP_OutDelayDuty & 0x3f;							//比较结果变化延时周期数, 0~63
	if(CMPx->CMP_EN == ENABLE)				CMPEN = 1;				//允许比较器		ENABLE,DISABLE
	if(CMPx->CMP_Outpt_En == ENABLE)		CMPOE = 1;			//允许比较结果输出到P3.4/P4.1,   ENABLE,DISABLE
	if(CMPx->CMP_InvCMPO     == ENABLE)		INVCMPO = 1;	//比较器输出取反, 	ENABLE,DISABLE
	if(CMPx->CMP_100nsFilter == DISABLE)	DISFLT = 1;		//内部0.1us滤波,  	ENABLE,DISABLE

	if(CMPx->CMP_P_Select  <= CMP_P_ADC)	CMPEXCFG = (CMPEXCFG & ~0x03) | (CMPx->CMP_P_Select);			//比较器输入正极选择, CMP_P_P37/CMP_P_P50/CMP_P_P51, CMP_P_ADC: 由ADC模拟输入端做正输入.
	if(CMPx->CMP_N_Select  <= CMP_N_GAP)	CMPEXCFG = (CMPEXCFG & ~0x04) | (CMPx->CMP_N_Select << 2);	//比较器输入负极选择, CMP_N_GAP: 选择内部BandGap经过OP后的电压做负输入, CMP_N_P36: 选择P3.6做负输入.
}
