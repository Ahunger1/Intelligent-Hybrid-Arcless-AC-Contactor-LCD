// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "AD.h"
#include "LCD.h"
#include "DELAY.h"
#include "BUTTON.h"

#include <stdio.h>  
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/*#define Fosc =4000000 //��Ƶ��4M Hz
//Tosc =1/Foscʱ������0.25��s
//Tcy =4*Tosc ָ������ 1��s
#define Fv = 50 //��ѹƵ��50Hz 
//Tv = 0.02s  =20ms=20000us
 */


#define SIGN_Si PORTCbits.RC0

#define SIGN_BREAK PORTCbits.RC2 //�������ʾ
//#define V0 2 //����ѹֵ
#define AD0 409//���ADresult   
//��AD=11  T=171us
#define AD0ub 414//upper bound ��ȷ��
#define AD0lb 403//lower bound ��ȷ��

#define T 20 //20ms
#define BREAKTIME 7//7ms
#define ProgDelay T-BREAKTIME

//��ʱ��155us
char flag_br_end;//�ֶ���ϱ�־                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
char isPhPositive;//�������־
char flag_ph_end;//��������ϱ�־
char DetectFlag;//�����������Ǵ�

void LED_MCU_INIT(void)                    
{
    //LED
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC2=0;
    TRISCbits.TRISC1=0;
    SIGN_Si=0;
    SIGN_BREAK=0;
    BUT_LED=0;
}

void main(void)
{
    //LCD
    LCD_MCU_init();
    LCD_init();
    InitScrn();
    //AD
    AD_MCU_INIT();
    //LED
    LED_MCU_INIT();
    //Break Button
    BUTTONMCUInit();
    while(1)
    {
        ButtonDetect();//17us
        if(flag_ph_st&(!flag_ph_end))//����ֻ���1�� 14us
        {
            //������
            AD_SUB(1);//��һ���ߣ���ΪA��  104us+33+17+14=168~176us  �����������ѡȡ��AD
            if(ADresult<= AD0ub && ADresult>AD0lb)//�������   41us  ������ֵ�䣬Ҫ����
            {
                ADtemp=ADresult;
                AD_SUB(1);//104us
                if(ADresult>ADtemp)//�Ӹ����� 21us
                {
                    AD_SUB(2);//�ڶ�����
                    if(ADresult>409)//��ڶ�����ΪC��  5ms
                        isPhPositive=0;
                    else
                        isPhPositive=1;
                    flag_ph_end=1;//���������
                }
            }
        }
        if(flag_ph_end&(!flag_br_end))//��ʼ�ֶϳ���
          {
            SIGN_Si=1;//��ɫ
              if(!isPhPositive)//������ʱ
              {
                  delay_ms(20);
              }
            SIGN_Si=0;
              delay_ms(BREAKTIME);//������ʱ
              SIGN_BREAK=1;//��ɫ
              delay_ms(ProgDelay);//�����ʱ
              SIGN_BREAK=0;
              if(isPhPositive)
              {
                  LCD_write_string(1,LINE1,"abc");
                  LCD_write_string(1,LINE2,"POSITIVE");

              }
              else
              {
                  LCD_write_string(1,LINE1,"acb");
                  LCD_write_string(1,LINE2,"NEGATIVE");
              }
              flag_br_end=1;
              NOP();
        }
    }
}
