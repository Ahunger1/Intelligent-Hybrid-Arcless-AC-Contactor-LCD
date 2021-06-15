
#ifndef __AD_H_
#define	__AD_H_
#include <xc.h>

char U_QW,U_BW,U_SW,U_GW,U_A[4]={1,2,3,4}; 
long unsigned int ADresult;
long unsigned int ADtemp;

/*void BCD(unsigned int R1);
void ADdisplay(void);
void ADread(long unsigned int result);*/

void AD_SUB(char k);
void AD_MCU_INIT(void);

#endif	
