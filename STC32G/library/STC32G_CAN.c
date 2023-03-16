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

#include "STC32G_CAN.h"

CAN_DataDef CAN1_Tx;
CAN_DataDef CAN1_Rx[8];

CAN_DataDef CAN2_Tx;
CAN_DataDef CAN2_Rx[8];

//========================================================================
// ����: u8 ReadReg(u8 addr)
// ����: CAN���ܼĴ�����ȡ������
// ����: CAN���ܼĴ�����ַ.
// ����: CAN���ܼĴ�������.
// �汾: VER1.0
// ����: 2020-11-16
// ��ע: 
//========================================================================
u8 CanReadReg(u8 addr)
{
    u8 dat;
    CANAR = addr;
    dat = CANDR;
    return dat;
}

//========================================================================
// ����: void WriteReg(u8 addr, u8 dat)
// ����: CAN���ܼĴ������ú�����
// ����: CAN���ܼĴ�����ַ, CAN���ܼĴ�������.
// ����: none.
// �汾: VER1.0
// ����: 2020-11-16
// ��ע: 
//========================================================================
void CanWriteReg(u8 addr, u8 dat)
{
    CANAR = addr;
    CANDR = dat;
}

//========================================================================
// ����: void CAN_Inilize(u8 CANx, CAN_InitTypeDef *CAN)
// ����: CAN ��ʼ������.
// ����: CAN: �ṹ����,��ο�CAN.h��Ķ���.
// ����: none.
// �汾: V1.0, 2021-06-02
//========================================================================
void CAN_Inilize(u8 CANx, CAN_InitTypeDef *CAN)
{
    if(CANx == CAN1)
    {
        CANSEL = CAN1;		//ѡ��CAN1ģ��
        CanWriteReg(MR  ,0x04);		//ʹ�� Reset Mode

        if(CAN->CAN_Enable == ENABLE)	CANEN = 1;		//ʹ��CAN1ģ��
        else								CANEN = 0;		//�ر�CAN1ģ��
        
        CanWriteReg(BTR0,(u8)((CAN->CAN_SJW << 6) + CAN->CAN_BRP));
        CanWriteReg(BTR1,(u8)((CAN->CAN_SAM << 7) + (CAN->CAN_TSG2 << 4) + CAN->CAN_TSG1));

        CanWriteReg(ACR0,CAN->CAN_ACR0);		//�������մ���Ĵ���
        CanWriteReg(ACR1,CAN->CAN_ACR1);
        CanWriteReg(ACR2,CAN->CAN_ACR2);
        CanWriteReg(ACR3,CAN->CAN_ACR3);
        CanWriteReg(AMR0,CAN->CAN_AMR0);		//�����������μĴ���
        CanWriteReg(AMR1,CAN->CAN_AMR1);
        CanWriteReg(AMR2,CAN->CAN_AMR2);
        CanWriteReg(AMR3,CAN->CAN_AMR3);

        CanWriteReg(ISR ,0xff);		//���жϱ�־
        CanWriteReg(IMR ,CAN->CAN_IMR);			//�жϼĴ�������
        CanWriteReg(MR  ,0x00);		//�˳� Reset Mode
    }
    else if(CANx == CAN2)
    {
        CANSEL = CAN2;		//ѡ��CAN2ģ��
        
        CanWriteReg(MR  ,0x04);		//ʹ�� Reset Mode

        if(CAN->CAN_Enable == ENABLE)	CAN2EN = 1;		//ʹ��CAN2ģ��
        else								CAN2EN = 0;		//�ر�CAN2ģ��
        
        CanWriteReg(BTR0,(u8)((CAN->CAN_SJW << 6) + CAN->CAN_BRP));
        CanWriteReg(BTR1,(u8)((CAN->CAN_SAM << 7) + (CAN->CAN_TSG2 << 4) + CAN->CAN_TSG1));

        CanWriteReg(ACR0,CAN->CAN_ACR0);		//�������մ���Ĵ���
        CanWriteReg(ACR1,CAN->CAN_ACR1);
        CanWriteReg(ACR2,CAN->CAN_ACR2);
        CanWriteReg(ACR3,CAN->CAN_ACR3);
        CanWriteReg(AMR0,CAN->CAN_AMR0);		//�����������μĴ���
        CanWriteReg(AMR1,CAN->CAN_AMR1);
        CanWriteReg(AMR2,CAN->CAN_AMR2);
        CanWriteReg(AMR3,CAN->CAN_AMR3);

        CanWriteReg(ISR ,0xff);		//���жϱ�־
        CanWriteReg(IMR ,CAN->CAN_IMR);			//�жϼĴ�������
        CanWriteReg(MR  ,0x00);		//�˳� Reset Mode
    }
}

//========================================================================
// ����: void CanReadFifo(CAN_DataDef *CANx)
// ����: ��ȡCAN���������ݺ�����
// ����: *CANx: ���CAN���߶�ȡ����.
// ����: none.
// �汾: VER2.0
// ����: 2023-01-31
// ��ע: 
//========================================================================
void CanReadFifo(CAN_DataDef *CAN)
{
    u8 i;
    u8 pdat[5];
    u8 RX_Index=0;

    pdat[0] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));

    if(pdat[0] & 0x80)  //�ж��Ǳ�׼֡������չ֡
    {
        pdat[1] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));   //��չ֡IDռ4���ֽ�
        pdat[2] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        pdat[3] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        pdat[4] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        CAN->ID = (((u32)pdat[1] << 24) + ((u32)pdat[2] << 16) + ((u32)pdat[3] << 8) + pdat[4]) >> 3;
    }
    else
    {
        pdat[1] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));   //��׼֡IDռ2���ֽ�
        pdat[2] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));
        CAN->ID = ((pdat[1] << 8) + pdat[2]) >> 5;
    }

    CAN->FF = pdat[0] & 0x80;    //֡��ʽ
    CAN->DLC = pdat[0] & 0x0f;   //���ݳ���

    for(i=0;((i<CAN->DLC&0x0f) && (i<8));i++)        //��ȡ���ݳ���Ϊlen����಻����8
    {
        CAN->DataBuffer[i] = CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));   //��ȡ��Ч����
    }
    while(RX_Index&3)   //�ж��Ѷ����ݳ����Ƿ�4��������
    {
        CanReadReg((u8)(RX_BUF0 + (RX_Index++&3)));  //��ȡ������ݣ�һ֡����ռ��4���������������ռ䣬���㲹0
    }
}

//========================================================================
// ����: u8 CanReadMsg(void)
// ����: CAN�������ݺ�����
// ����: *CANx: ���CAN���߶�ȡ����..
// ����: ֡����.
// �汾: VER2.0
// ����: 2023-01-31
// ��ע: 
//========================================================================
u8 CanReadMsg(CAN_DataDef *CAN)
{
    u8 i;
    u8 n=0;

    do{
        CanReadFifo(&CAN[n++]);  //��ȡ���ջ���������
        i = CanReadReg(SR);
    }while(i&0x80);     //�жϽ��ջ��������Ƿ������ݣ��еĻ�������ȡ

    return n;   //����֡����
}

//========================================================================
// ����: void CanSendMsg(CAN_DataDef *CAN)
// ����: CAN���ͱ�׼֡������
// ����: *CANx: ���CAN���߷�������..
// ����: none.
// �汾: VER1.0
// ����: 2020-11-19
// ��ע: 
//========================================================================
void CanSendMsg(CAN_DataDef *CAN)
{
	u32 CanID;
    u8 RX_Index,i;

    if(CAN->FF)     //�ж��Ƿ���չ֡
    {
        CanID = CAN->ID << 3;
        CanWriteReg(TX_BUF0,(CAN->DLC&0x0f)|0x80);	//bit7: ��׼֡(0)/��չ֡(1), bit6: ����֡(0)/Զ��֡(1), bit3~bit0: ���ݳ���(DLC)
        CanWriteReg(TX_BUF1,(u8)(CanID>>24));
        CanWriteReg(TX_BUF2,(u8)(CanID>>16));
        CanWriteReg(TX_BUF3,(u8)(CanID>>8));

        CanWriteReg(TX_BUF0,(u8)CanID);

        RX_Index = 1;
        for(i=0;((i<CAN->DLC&0x0f) && (i<8));i++)        //���ݳ���ΪDLC����಻����8
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),CAN->DataBuffer[i]);   //д����Ч����
        }
        while(RX_Index&3)   //�ж��Ѷ����ݳ����Ƿ�4��������
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),0x00);  //д��������ݣ�һ֡����ռ��4���������������ռ䣬���㲹0
        }
    }
    else    //���ͱ�׼֡
    {
        CanID = (u16)(CAN->ID << 5);
        CanWriteReg(TX_BUF0,CAN->DLC&0x0f);  //bit7: ��׼֡(0)/��չ֡(1), bit6: ����֡(0)/Զ��֡(1), bit3~bit0: ���ݳ���(DLC)
        CanWriteReg(TX_BUF1,(u8)(CanID>>8));
        CanWriteReg(TX_BUF2,(u8)CanID);

        RX_Index = 3;
        for(i=0;((i<CAN->DLC&0x0f) && (i<8));i++)        //���ݳ���ΪDLC����಻����8
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),CAN->DataBuffer[i]);   //д����Ч����
        }
        while(RX_Index&3)   //�ж��Ѷ����ݳ����Ƿ�4��������
        {
            CanWriteReg((u8)(TX_BUF0 + (RX_Index++&3)),0x00);  //д��������ݣ�һ֡����ռ��4���������������ռ䣬���㲹0
        }
    }
	CanWriteReg(CMR ,0x04);		//����һ��֡����
}
