#include "LPC17xx.h"
#define MR2_H 1220
#define MR2_L 2440

void Init_Timer2(){
	LPC_PINCON->PINSEL0 |= (0x3<<16);							//Select PIN0.8 as MAT2.2
	LPC_SC->PCLKSEL1 |= (0x3<<2);									//Selelect Peripheral clock as cpu clock(1/8)
	LPC_TIM2->PR = 0;
	LPC_TIM2->MR2 = MR2_H;
	LPC_TIM2->MCR = (0x3<<6);											//To set with intrrupt & reset
	LPC_TIM2->EMR=(0x3<<8);                       //To toggle MR2
  NVIC_EnableIRQ(TIMER2_IRQn);
}
void TIMER2_IRQHandler(){
	  LPC_TIM2->IR =  1<<2;
	  if(LPC_TIM2->MR2 == MR2_H){
		LPC_TIM2->MR2 = MR2_L;
	}
	else 
		LPC_TIM2->MR2 = MR2_H;
}

int main(){
	Init_Timer2();
	LPC_TIM2->TCR = 1;
	while(1){}
	return 0;
}