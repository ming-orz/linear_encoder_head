#ifndef __OLED_H__
#define __OLED_H__

#include "stc.h"

#define OLED_CS_PIN P22
#define OLED_DC_PIN P24
#define OLED_RST_PIN P45

void OLEDInit(void);
void OLEDFill(uint8_t Data);
void OLEDShow(uint8_t *Data,uint8_t x,uint8_t y);   //显示字符，x是第几个(1-16)，y是第几行(1-8)，
void OLEDFlush();   //把缓冲区的数据刷新到OLED屏幕


#endif