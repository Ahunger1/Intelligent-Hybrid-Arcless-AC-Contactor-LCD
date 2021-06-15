#include "AD.h"
#include "LCD.h"
#include "DELAY.h"
/*测试时用
 * void BCD(unsigned int R1)
{
    U_QW=0;U_BW=0;U_SW=0;U_GW=0; //清转换初值
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
    BCD((result*5*1000)>>10);              //算出实际电压的1000倍        
    U_A[0]=U_QW;U_A[1]=U_BW;U_A[2]=U_SW;U_A[3]=U_GW;
}*/




void AD_SUB(char k)//选择k为AD通道
{
    char i;
    ADCON0=0b01000000;                  //AD转换时钟选择FOSC/8，模拟通道选择AN0
    ADCON0 |=(k<<2);//设置通道
    ADCON0bits.ADON=1;//打开通道
    delay_us(0);//延时20μs
    ADCON0bits.GO=1;//开始转换
    while(ADCON0bits.GO==1);//等待A/D转换结束
    PIR1bits.ADIF=0;
    ADCON0bits.GO=0; 
    ADCON0bits.ADON=0;
    ADresult= (ADRESH<<8)|ADRESL;
    
}
//详情见MATLAB

void AD_MCU_INIT(void)
{
    //  I/O口设置
	TRISA=0b00001111;                    //设置A0~3口为输入口
	ANSEL=0b00001111;                    //设置A0~3口为模拟输入
//  模拟引脚/基准电压/AD格式

    ADCON1=0b10000000;                  //结果右对齐，参考电压VSS,VDD
}
