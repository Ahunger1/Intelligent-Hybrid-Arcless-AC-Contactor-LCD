
#ifndef __BUTTON_H_
#define	__BUTTON_H_
#include <xc.h>
#define BUTTON PORTBbits.RB7
#define AD2_5V  512
#define BUT_LED PORTCbits.RC1
char flag_but_once=0;//��ť���±�־
char flag_ph_st;//�������ʼ��־

void BUTTONMCUInit (void);
char isBUTTONOn(void);
void ButtonDetect(void);
#endif	

