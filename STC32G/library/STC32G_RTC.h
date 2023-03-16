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

#ifndef	__STC32G_RTC_H
#define	__STC32G_RTC_H

#include	"config.h"

//========================================================================
//                              定义声明
//========================================================================

#define RTC_IRC32KCR		0		//RTC时钟源使用内部32K时钟
#define RTC_X32KCR			1		//RTC时钟源使用外部32K晶振

//中断使能, 0x80:闹钟中断, 0x40:日中断, 0x20:小时中断, 0x10:分钟中断, 0x08:秒中断, 0x04:1/2秒中断, 0x02:1/8秒中断, 0x01:1/32秒中断
#define RTC_ALARM_INT		0x80		//RTC 闹钟中断
#define RTC_DAY_INT			0x40		//RTC 日中断
#define RTC_HOUR_INT		0x20		//RTC 小时中断
#define RTC_MIN_INT			0x10		//RTC 分钟中断
#define RTC_SEC_INT			0x08		//RTC 秒中断
#define RTC_SEC2_INT		0x04		//RTC 1/2秒中断
#define RTC_SEC8_INT		0x02		//RTC 1/8秒中断
#define RTC_SEC32_INT		0x01		//RTC 1/32秒中断

typedef struct
{
	u8	RTC_Enable;		//RTC 使能, ENABLE, DISABLE
	u8	RTC_Clock;		//RTC 时钟, RTC_IRC32KCR, RTC_X32KCR
	u8	RTC_Year;			//RTC 年, 00~99, 对应2000~2099年
	u8	RTC_Month;		//RTC 月, 01~12
	u8	RTC_Day;			//RTC 日, 01~31
	u8	RTC_Hour;			//RTC 时, 00~23
	u8	RTC_Min;			//RTC 分, 00~59
	u8	RTC_Sec;			//RTC 秒, 00~59
	u8	RTC_Ssec;			//RTC 1/128秒, 00~127

	u8	RTC_ALAHour;	//RTC 闹钟时, 00~23
	u8	RTC_ALAMin;		//RTC 闹钟分, 00~59
	u8	RTC_ALASec;		//RTC 闹钟秒, 00~59
	u8	RTC_ALASsec;	//RTC 闹钟1/128秒, 00~127
} RTC_InitTypeDef;

u8	RTC_Inilize(RTC_InitTypeDef *RTCx);

#endif
