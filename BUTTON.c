#include<xc.h>
#include"BUTTON.h"
#include"DELAY.h"
#include "AD.h"

void BUTTONMCUInit (void)
{
    TRISBbits.TRISB7=1;//读 数位
    OPTION_REG&=0x7f;//B口上拉使能
}
char isBUTTONOn(void)
{
    if(!BUTTON)
    {
        delay_ms(15);//防抖
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
       //接触器电源
       AD_SUB(0);//104us
       if(ADresult <= AD2_5V)//20us
       {
           flag_ph_st=1;//相序程序开始
           flag_but_once=1;
           BUT_LED=1;
       }
    }
}


