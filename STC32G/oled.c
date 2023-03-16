#include "oled.h"
#include	"STC32G_Delay.h"

extern const uint8_t code Ma[95][8];
uint8_t xdata OLEDBuffer[8][128]={0};
void OLEDGPIOInit(void)
{
  P_SW1 &= ~0X0C;
  P_SW1 |= 0X04;
  SPCTL = 0XDF;
  SPSTAT = 0XC0;
  
  P2M1 &= ~0X14;
  P2M0 |= 0X14;
  
  P4M1 &= ~0X20;
  P4M0 |= 0X20;
  
  OLED_CS_PIN = 0;
	OLED_RST_PIN = 0;
	delay_ms(100);
	OLED_RST_PIN = 1;
	delay_ms(10);
}
void OLEDWriteCom(uint8_t Command)
{
	OLED_DC_PIN = 0;
	SPDAT = Command;
	while(!SPIF);
  SPIF = 1;
}
void OLEDWriteData(uint8_t Data)
{
	OLED_DC_PIN = 1;
	SPDAT = Data;
	while(!SPIF);
  SPIF = 1;
}

void OLEDSetPos(unsigned char x, unsigned char y)
{
	OLEDWriteCom(0xb0+y);
	OLEDWriteCom(((x&0xf0)>>4)|0x10);
	OLEDWriteCom((x&0x0f)|0x01);
}
void OLEDFill(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++){
		OLEDWriteCom(0xb0+m);
		OLEDWriteCom(0x00);
		OLEDWriteCom(0x10);
		for(n=0;n<128;n++){
			OLEDWriteData(fill_Data);
		}
	}
}
void OLEDCLS(void)
{
	OLEDFill(0x00);
}
void OLEDON(void)
{
	OLEDWriteCom(0X8D);
	OLEDWriteCom(0X14);
	OLEDWriteCom(0XAF);
}
void OLEDOFF(void)
{
	OLEDWriteCom(0X8D);
	OLEDWriteCom(0X10);
	OLEDWriteCom(0XAE);
}
void OLEDInit(void)
{
	OLEDGPIOInit();
	delay_ms(100);
	OLEDWriteCom(0xAE);
	OLEDWriteCom(0x20);
	OLEDWriteCom(0x10);
	OLEDWriteCom(0xb0);
	OLEDWriteCom(0xC0);
	OLEDWriteCom(0x00);
	OLEDWriteCom(0x10);
	OLEDWriteCom(0x40);
	OLEDWriteCom(0x81);
	OLEDWriteCom(0xff);
	OLEDWriteCom(0xa0);
	OLEDWriteCom(0xa6);
	OLEDWriteCom(0xa8);
	OLEDWriteCom(0x3F);
	OLEDWriteCom(0xa4);
	OLEDWriteCom(0xd3);
	OLEDWriteCom(0x00);
	OLEDWriteCom(0xd5);
	OLEDWriteCom(0xf0);
	OLEDWriteCom(0xd9);
	OLEDWriteCom(0x22);
	OLEDWriteCom(0xda);
	OLEDWriteCom(0x12);
	OLEDWriteCom(0xdb);
	OLEDWriteCom(0x20);
	OLEDWriteCom(0x8d);
	OLEDWriteCom(0x14);
	OLEDWriteCom(0xaf);
	OLEDFill(0x00);
	
}
void OLEDFlush()
{
  unsigned char m,n;
  OLEDSetPos(0,0);
	OLED_DC_PIN = 1;
  for(m=0;m<8;m++){
		for(n=0;n<128;n++){
			OLEDWriteData(OLEDBuffer[m][n]);
		}
	}
}
void OLEDShow(uint8_t *Data,uint8_t x,uint8_t y)
{
	unsigned char i,j;
	x--;
	y--;
	for(i=x*8;(*Data!='\0') && (i < 128);i+=8,Data++){
		for(j=0;j<8;j++)
			OLEDBuffer[y][j+i]=Ma[*Data-32][j];
	}
}