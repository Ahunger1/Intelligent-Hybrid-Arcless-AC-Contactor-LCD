#include "AD.h"
#include "LCD.h"
#include "DELAY.h"
/*����ʱ��
 * void BCD(unsigned int R1)
{
    U_QW=0;U_BW=0;U_SW=0;U_GW=0; //��ת����ֵ
    while(R1>=1000)
    {R1-=1000;U_QW++;}
    while(R1>=100)
    {R1-=100;U_BW++;}
    while(R1>=10)
    {R1-=10;U_SW++;}
    U_GW=R1;
}
void ADdisplay(void)
{
    LCD_write_char(3, LINE2, U_A[0]+'0');
    LCD_write_char(4, LINE2, '.');
    LCD_write_char(5, LINE2, U_A[1]+'0');
    LCD_write_char(6, LINE2, U_A[2]+'0');
    LCD_write_char(7, LINE2, U_A[3]+'0');
}
void ADread(long unsigned int result)
{
    BCD((result*5*1000)>>10);              //���ʵ�ʵ�ѹ��1000��        
    U_A[0]=U_QW;U_A[1]=U_BW;U_A[2]=U_SW;U_A[3]=U_GW;
}*/




void AD_SUB(char k)//ѡ��kΪADͨ��
{
    char i;
    ADCON0=0b01000000;                  //ADת��ʱ��ѡ��FOSC/8��ģ��ͨ��ѡ��AN0
    ADCON0 |=(k<<2);//����ͨ��
    ADCON0bits.ADON=1;//��ͨ��
    delay_us(0);//��ʱ20��s
    ADCON0bits.GO=1;//��ʼת��
    while(ADCON0bits.GO==1);//�ȴ�A/Dת������
    PIR1bits.ADIF=0;
    ADCON0bits.GO=0; 
    ADCON0bits.ADON=0;
    ADresult= (ADRESH<<8)|ADRESL;
    
}
//�����MATLAB

void AD_MCU_INIT(void)
{
    //  I/O������
	TRISA=0b00001111;                    //����A0~3��Ϊ�����
	ANSEL=0b00001111;                    //����A0~3��Ϊģ������
//  ģ������/��׼��ѹ/AD��ʽ

    ADCON1=0b10000000;                  //����Ҷ��룬�ο���ѹVSS,VDD
}
