#include<xc.h>
#include"BUTTON.h"
#include"DELAY.h"
#include "AD.h"

void BUTTONMCUInit (void)
{
    TRISBbits.TRISB7=1;//�� ��λ
    OPTION_REG&=0x7f;//B������ʹ��
}
char isBUTTONOn(void)
{
    if(!BUTTON)
    {
        delay_ms(15);//����
        if(!BUTTON)
        {
            return 1;
        }
    }
    return 0;
}
void ButtonDetect(void)
{
    if(flag_but_once)
        return;
    else if(isBUTTONOn())
    {
       //�Ӵ�����Դ
       AD_SUB(0);//104us
       if(ADresult <= AD2_5V)//20us
       {
           flag_ph_st=1;//�������ʼ
           flag_but_once=1;
           BUT_LED=1;
       }
    }
}


