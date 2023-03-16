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

#include "STC32G_CAN.h"

CAN_DataDef CAN1_Tx;
CAN_DataDef CAN1_Rx[8];

CAN_DataDef CAN2_Tx;
CAN_DataDef CAN2_Rx[8];

//========================================================================
// 函数: u8 ReadReg(u8 addr)
// 描述: CAN功能寄存器读取函数。
// 参数: CAN功能寄存器地址.
// 返回: CAN功能寄存器数据.
// 版本: VER1.0
// 日期: 2020-11-16
// 备注: 
//========================================================================
u8 CanReadReg(u8 addr)
{
    u8 dat;
    CANAR = addr;
    dat = CANDR;
    return dat;
}

//========================================================================
// 函数: void WriteReg(u8 addr, u8 dat)
// 描述: CAN功能寄存器配置函数。
// 参数: CAN功能寄存器地址, CAN功能寄存器数据.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-11-16
// 备注: 
//========================================================================
void CanWriteReg(u8 addr, u8 dat)
{
    CANAR = addr;
    CANDR = dat;
}

//========================================================================
// 函数: void CAN_Inilize(u8 CANx, CAN_InitTypeDef *CAN)
// 描述: CAN 初始化程序.
// 参数: CAN: 结构参数,请参考CAN.h里的定义.
// 返回: none.
// 版本: V1.0, 2021-06-02
//========================================================================
void CAN_Inilize(u8 CANx, CAN_InitTypeDef *CAN)
{
    if(CANx == CAN1)
    {
        CANSEL = CAN1;		//选择CAN1模块
        CanWriteReg(MR  ,0x04);		//使能 Reset Mode

        if(CAN->CAN_Enable == ENABLE)	CANEN = 1;		//使能CAN1模块
        else								CANEN = 0;		//关闭CAN1模块
        
        CanWriteReg(BTR0,(u8)((CAN->CAN_SJW << 6) + CAN->CAN_BRP));
        CanWriteReg(BTR1,(u8)((CAN->CAN_SAM << 7) + (CAN->CAN_TSG2 << 4) + CAN->CAN_TSG1));

        CanWriteReg(ACR0,CAN->CAN_ACR0);		//总线验收代码寄存器
        CanWriteReg(ACR1,CAN->CAN_ACR1);
        CanWriteReg(ACR2,CAN->CAN_ACR2);
        CanWriteReg(ACR3,CAN->CAN_ACR3);
        CanWriteReg(AMR0,CAN->CAN_AMR0);		//总线验收屏蔽寄存器
        CanWriteReg(AMR1,CAN->CAN_AMR1);
        CanWriteReg(AMR2,CAN->CAN_AMR2);
        CanWriteReg(AMR3,CAN->CAN_AMR3);

        CanWriteReg(ISR ,0xff);		//清中断标志
        CanWriteReg(IMR ,CAN->CAN_IMR);			//中断寄存器设置
        CanWriteReg(MR  ,0x00);		//退出 Reset Mode
    }
    else if(CANx == CAN2)
    {
        CANSEL = CAN2;		//选择CAN2模块
        
        CanWriteReg(MR  ,0x04);		//使能 Reset Mode

        if(CAN->CAN_Enable == ENABLE)	CAN2EN = 1;		//使能CAN2模块
        else								CAN2EN = 0;		//关闭CAN2模块
        
        CanWriteReg(BTR0,(u8)((CAN->CAN_SJW << 6) + CAN->CAN_BRP));
        CanWriteReg(BTR1,(u8)((CAN->CAN_SAM << 7) + (CAN->CAN_TSG2 << 4) + CAN->CAN_TSG1));

        CanWriteReg(ACR0,CAN->CAN_ACR0);		//总线验收代码寄存器
        CanWriteReg(ACR1,CAN->CAN_ACR1);
        CanWriteReg(ACR2,CAN->CAN_ACR2);
        CanWriteReg(ACR3,CAN->CAN_ACR3);
        CanWriteReg(AMR0,CAN->CAN_AMR0);		//总线验收屏蔽寄存器
        CanWriteReg(AMR1,CAN->CAN_AMR1);
        CanWriteReg(AMR2,CAN->CAN_AMR2);
        CanWriteReg(AMR3,CAN->CAN_AMR3);

        CanWriteReg(ISR ,0xff);		//清中断标志
        CanWriteReg(IMR ,CAN->CAN_IMR);			//中断寄存器设置
        CanWriteReg(MR  ,0x00);		//退出 Reset Mode
    }
}

//========================================================================
// 函数: void CanReadFifo(CAN_DataDef *CANx)
// 描述: 读取CAN缓冲区数据函数。
// 参数: *CANx: 存放CAN总线读取数据.
// 返回: none.
// 版本: VER2.0
// 日期: 2023-01-31
// 备注: 
//========================================================================
void CanReadFifo(CAN_DataDef *CAN)
{
    u8 i;
    u8 pdat[5];
    u8 RX_Index=0;

    pdat[0] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));

    if(pdat[0] & 0x80)  //判断是标准帧还是扩展帧
    {
        pdat[1] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));   //扩展帧ID占4个字节
        pdat[2] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        pdat[3] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        pdat[4] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        CAN->ID = (((u32)pdat[1] << 24) + ((u32)pdat[2] << 16) + ((u32)pdat[3] << 8) + pdat[4]) >> 3;
    }
    else
    {
        pdat[1] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));   //标准帧ID占2个字节
        pdat[2] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        CAN->ID = ((pdat[1] << 8) + pdat[2]) >> 5;
    }

    CAN->FF = pdat[0] & 0x80;    //帧格式
    CAN->DLC = pdat[0] & 0x0f;   //数据长度

    for(i=0;((i<CAN->DLC&0x0f) && (i<8));i++)        //读取数据长度为len，最多不超过8
    {
        CAN->DataBuffer[i] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));   //读取有效数据
    }
    while(RX_Index&3)   //判断已读数据长度是否4的整数倍
    {
        CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));  //读取填充数据，一帧数据占据4的整数倍缓冲区空间，不足补0
    }
}

//========================================================================
// 函数: u8 CanReadMsg(void)
// 描述: CAN接收数据函数。
// 参数: *CANx: 存放CAN总线读取数据..
// 返回: 帧个数.
// 版本: VER2.0
// 日期: 2023-01-31
// 备注: 
//========================================================================
u8 CanReadMsg(CAN_DataDef *CAN)
{
    u8 i;
    u8 n=0;

    do{
        CanReadFifo(&CAN[n++]);  //读取接收缓冲区数据
        i = CanReadReg(SR);
    }while(i&0x80);     //判断接收缓冲区里是否还有数据，有的话继续读取

    return n;   //返回帧个数
}

//========================================================================
// 函数: void CanSendMsg(CAN_DataDef *CAN)
// 描述: CAN发送标准帧函数。
// 参数: *CANx: 存放CAN总线发送数据..
// 返回: none.
// 版本: VER1.0
// 日期: 2020-11-19
// 备注: 
//========================================================================
void CanSendMsg(CAN_DataDef *CAN)
{
	u32 CanID;
    u8 RX_Index,i;

    if(CAN->FF)     //判断是否扩展帧
    {
        CanID = CAN->ID << 3;
        CanWriteReg(TX_BUF0,(CAN->DLC&0x0f)|0x80);	//bit7: 标准帧(0)/扩展帧(1), bit6: 数据帧(0)/远程帧(1), bit3~bit0: 数据长度(DLC)
        CanWriteReg(TX_BUF1,(u8)(CanID>>24));
        CanWriteReg(TX_BUF2,(u8)(CanID>>16));
        CanWriteReg(TX_BUF3,(u8)(CanID>>8));

        CanWriteReg(TX_BUF0,(u8)CanID);

        RX_Index = 1;
        for(i=0;((i<CAN->DLC&0x0f) && (i<8));i++)        //数据长度为DLC，最多不超过8
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),CAN->DataBuffer[i]);   //写入有效数据
        }
        while(RX_Index&3)   //判断已读数据长度是否4的整数倍
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),0x00);  //写入填充数据，一帧数据占据4的整数倍缓冲区空间，不足补0
        }
    }
    else    //发送标准帧
    {
        CanID = (u16)(CAN->ID << 5);
        CanWriteReg(TX_BUF0,CAN->DLC&0x0f);  //bit7: 标准帧(0)/扩展帧(1), bit6: 数据帧(0)/远程帧(1), bit3~bit0: 数据长度(DLC)
        CanWriteReg(TX_BUF1,(u8)(CanID>>8));
        CanWriteReg(TX_BUF2,(u8)CanID);

        RX_Index = 3;
        for(i=0;((i<CAN->DLC&0x0f) && (i<8));i++)        //数据长度为DLC，最多不超过8
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),CAN->DataBuffer[i]);   //写入有效数据
        }
        while(RX_Index&3)   //判断已读数据长度是否4的整数倍
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),0x00);  //写入填充数据，一帧数据占据4的整数倍缓冲区空间，不足补0
        }
    }
	CanWriteReg(CMR ,0x04);		//发起一次帧传输
}
