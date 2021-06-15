#include"DELAY.h"
//--------¼ÆÊıÑÓÊ±--------//
void delay_ms(unsigned int n)// n ms
{
    unsigned int j;
    char k;
    for(j=0;j<n;j++)
        for(k=108;k>0;k--)
        {
            NOP();
        }
}
void delay_us(unsigned char n)//n*10us +20us
{

    NOP();
    while(n>0)
    {
        n--;
    }   

}
