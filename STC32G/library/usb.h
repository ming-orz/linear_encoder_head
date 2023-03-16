#ifndef __USB_H__
#define __USB_H__

//#define PRINTF_SEGLED         //printf输出重定向到ISP下载软件中的7段数码管
#define PRINTF_HID              //printf输出直接重定向到USB HID接口

#define DEVSTATE_ATTACHED       0
#define DEVSTATE_POWERED        1
#define DEVSTATE_DEFAULT        2
#define DEVSTATE_ADDRESS        3
#define DEVSTATE_CONFIGURED     4
#define DEVSTATE_SUSPENDED      5

void usb_init();
void usb_IN(BYTE cnt);
void usb_OUT_done();

int SEG7_ShowString(const char *fmt, ...);
void SEG7_ShowLong(long n, char radix);
void SEG7_ShowFloat(float f);
void SEG7_ShowCode(BYTE *cod);

void LED40_SendData(BYTE *dat, BYTE size);
void LED64_SendData(BYTE *dat, BYTE size);

void LCD12864_DisplayOff();
void LCD12864_DisplayOn();
void LCD12864_CursorOff();
void LCD12864_CursorOn();
void LCD12864_CursorMoveLeft();
void LCD12864_CursorMoveRight();
void LCD12864_CursorReturnHome();
void LCD12864_ScrollLeft();
void LCD12864_ScrollRight();
void LCD12864_ScrollUp(BYTE line);
void LCD12864_AutoWrapOff();
void LCD12864_AutoWrapOn();
void LCD12864_ReverseLine(BYTE line);
void LCD12864_DisplayClear();
void LCD12864_ShowString(BYTE x, BYTE y, char *str);
void LCD12864_ShowPicture(BYTE x, BYTE y, BYTE cx, BYTE cy, BYTE *dat);

void OLED12864_DisplayOff();
void OLED12864_DisplayOn();
void OLED12864_DisplayContent();
void OLED12864_DisplayEntire();
void OLED12864_HorizontalMirror();
void OLED12864_VerticalMirror();
void OLED12864_DisplayReverse();
void OLED12864_SetContrast(BYTE bContrast);
void OLED12864_SetAddressMode(BYTE bMode);
void OLED12864_ScrollLeft(BYTE bPageStart, BYTE bPageEnd, WORD nInterval);
void OLED12864_ScrollRight(BYTE bPageStart, BYTE bPageEnd, WORD nInterval);
void OLED12864_ScrollUp(BYTE bPageStart, BYTE bPageEnd, WORD nInterval);
void OLED12864_ScrollStart();
void OLED12864_ScrollStop();
void OLED12864_ShowPicture(BYTE x, BYTE y, BYTE cx, BYTE cy, BYTE *dat);

int printf_hid (const char *fmt, ...);

#if defined PRINTF_SEGLED
#define printf  SEG7_ShowString
#elif defined PRINTF_HID
#define printf  printf_hid
#endif


extern BYTE xdata UsbFeatureBuffer[64];
extern BYTE xdata UsbInBuffer[64];
extern BYTE xdata UsbOutBuffer[64];
extern BOOL bUsbFeatureReady;
extern BOOL bUsbInBusy;
extern BOOL bUsbOutReady;
extern BYTE DeviceState;
extern BYTE OutNumber;

#endif
