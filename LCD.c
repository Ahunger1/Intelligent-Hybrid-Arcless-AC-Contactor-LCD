#include"LCD.h"
#include"DELAY.h"


//--------------LCDдָ���--------------------//
void LCD_en_command(uchar command)//����Ϊ �������ߵĵ�ַ
{
    LCD1602_EN=LOW;
    LCD1602_RS=LOW;//RS,RW ͬʱΪ�͵�ƽ������д��ָ��
    LCD1602_RW=LOW;
    LCDIO=command;
    //0.5ms
    delay100us;
    delay100us;
    delay100us;
    delay100us;
    delay100us;
    delay100us;

    LCD1602_EN=HIGH;//E�õ͵�ƽ
    delay_ms(1);//1100us
    delay100us;
    LCD1602_EN=LOW;//дָ�RS=0��R/w=0��E�½���
}

//------------------LCD��ʼ��----------------------//
void LCD_init(void)
{
    CLEARSCREEN;//���� 0x01
    LCD_en_command(DATA_MODE);//����8λ���ݴ���ģʽ
    LCD_en_command(OPEN_SCREEN);//��ʾ����������ʾ���
    LCD_en_command(DISPLAY_ADDRESS);//����LCD������ʾ��ַ
    CLEARSCREEN;
}

//------------------LCDд���ݺ���-------------------//
void LCD_en_dat(uchar dat)
{
    LCD1602_EN=LOW;//����
    LCD1602_RS=HIGH;//RSΪ�ߵ�ƽ��RWΪ�͵�ƽ������д������
    LCD1602_RW=LOW;
    LCDIO=dat;//д��
    LCD1602_EN=HIGH;
    delay100us;
    LCD1602_EN=LOW;
}

//-------LCD������/��־------//
char LCD_Read_dat(void)
{
    char dat;
    LCDIO|=0xff;//D������
    LCD1602_RS=LOW;
    LCD1602_RW=HIGH;NOP();
    LCD1602_EN=HIGH;//NOP();
    dat=LCDIO;//��
    //delay_ms(1);
    
    LCD1602_EN=LOW;NOP();//����
    LCD1602_RW=LOW;
    LCDIO=0;//D�����
    return dat;

}

//-------���õ�ַ----------------//
void LCD_set_xy(uchar x, uchar y)
{
    uchar address;
    if(y==LINE1)//LINE1=1 LINE2=2
    {address = (uchar)LINE1_HEAD+x;}//LINE1_HEAD=0x80=0b10000000 DDRAM��ַ���� ��ʾ����RAM
    //��һ�е�ַΪ00H��27H��0b00100111=32+7=39���ڶ���Ϊ40H��67H
    else
    {address = LINE2_HEAD+x;}//0xc0=0x80+0x40
    LCD_en_command(DISPLAY_ADDRESS|address);//DISPLAY_ADDRESS=0x80
}
/*//-----------------д�ַ�-------------------//
void LCD_write_char(uchar x, uchar y, uchar dat)
{
    LCD_Busy();
    LCD_set_xy(x,y);
    LCD_en_dat(dat);
}*/


//-----------------д�ַ���-------------------//
void LCD_write_string(uchar X, uchar Y, uchar *s)
{
    LCD_Busy();//��æ
    LCD_set_xy(X,Y);
    while(*s)
    {
        LCDIO=*s;
        LCD_en_dat(*s);
        s++;
    }
}



//-------LCD��ʼ������-------//
void LCD_MCU_init(void)
{
    TRISE&=0b11111000;
    ANSEL=0;
    ANSELH=0;//B��Ҫ��ģ��
    TRISD=0;//D�����

}

//-----����------//
void InitScrn(void)
{
    CLEARSCREEN;
    delay_ms(10);//��ʼ��
    
}

//------��æ---------//
void LCD_Busy(void)
{
    char busyFlag;
    while(1)
    {
        busyFlag=LCD_Read_dat();
        if((busyFlag&0x80)==0)
        {
            break;
        }
    }
}

