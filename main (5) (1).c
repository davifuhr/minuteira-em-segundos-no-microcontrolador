/*****************************************************************************
@Saidas - HIGH
     LED_LED_CARGA
      PC8

@Display - HIGH
      A   B   C   D   E   F   G  PONTO
     PC0 PC1 PC2 PC3 PC4 PC5 PC6 PB0

@Entradas - PULL-DOWN
     S/R   B+   B-
     PB8  PB9  PB10
*****************************************************************************/

#include "stm32f4xx.h"

int display[10] = {
  0x3f,
  0x06,
  0x5b,
  0x4f,
  0x66,
  0x6d,
  0x7d,
  0x07,
  0x7f,
  0x6f};

int digito_display = 1;
int valor_inicial =1;
int x1,x2,x3;
int sistema = 0;

#define PSC_INICIAL    (15999)
#define ARR_999    (999)
#define ARR_99     (99)
#define ARR_14    (14)


void SET_RESET (void){
	if ( TIM11->SR & TIM_SR_UIF ){
		 TIM11->SR &=~TIM_SR_UIF;

		 	 if (!(GPIOB->IDR & GPIO_IDR_IDR_8)){
		 		 x1 = 1;
		 	 }
		 	 if((GPIOB->IDR & GPIO_IDR_IDR_8)&&x1){
		 		 if(sistema==0){
		 			 x1=0;
/*
		 			 if(digito_display==0)
		 				 digito_display=valor_inicial;
		 			 else
		 				 valor_inicial=digito_display;
		 				 sistema=1;
*/
		 			 if(digito_display>0)
		 				sistema=1;
		 		 }
		 	 if((sistema==1)&&(x1)){
		 		 digito_display=1;
		 		 	 x1=0;
		 		 	 	 sistema=0;
}
}
}
}
void B_MAIS(void){
	if ( TIM11->SR & TIM_SR_UIF ){
		 TIM11->SR &=~TIM_SR_UIF;

			 if(sistema == 0){
				 	 if (!(GPIOB->IDR & GPIO_IDR_IDR_9)){
				 		   x2
              =1;
}
				 	 if((GPIOB->IDR & GPIO_IDR_IDR_9)&&x2){
				 		   x2=0;
				 		 	 digito_display++;
				 		 	 	 if(digito_display == 10){
				 		 	 		 digito_display=0;
}
}
}
}
}
void B_MENOS(void){
	if ( TIM11->SR & TIM_SR_UIF ){
			 TIM11->SR &=~TIM_SR_UIF;

				 if(sistema == 0){
					 if (!(GPIOB->IDR & GPIO_IDR_IDR_10)){
					 	 	x3=1;
}
					 if((GPIOB->IDR & GPIO_IDR_IDR_10)&&x3){
					 	 	x3=0;
					 	      digito_display--;
					 	 	 	  if(digito_display == -1){
					 	 	 		  digito_display=9;
}
}
}
}
}
void TIM1_UP_TIM10_IRQHandler(void){
 		TIM10->SR &=~TIM_SR_UIF;
 		if (sistema==1)
 		{
 			if (--digito_display<1)
 				sistema=0;
 		}

}
void LED_CARGA (void){
	if(sistema==1){
		GPIOC->ODR|=GPIO_ODR_ODR_8;
}
}
void LED_PONTO (void){
 		if ( TIM9->SR & TIM_SR_UIF ){
 			 	TIM9->SR &=~TIM_SR_UIF;

 			 		if(sistema==1){
 			 			GPIOB->ODR^=GPIO_ODR_ODR_0;
}
 			 		if(sistema==0){
 			 			GPIOB->ODR=~GPIO_ODR_ODR_0;
}
}
}



int main(void)
{
	RCC->AHB1ENR=0x87;

	GPIOB->MODER= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;
 	GPIOB->PUPDR= GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1 | GPIO_MODER_MODER10_1;
 	GPIOB->MODER &=~ (GPIO_MODER_MODER0);
 	GPIOB->MODER |= (GPIO_MODER_MODER0_0);

 	GPIOC->MODER &=~ (GPIO_MODER_MODER0|GPIO_MODER_MODER1|GPIO_MODER_MODER2|GPIO_MODER_MODER3|GPIO_MODER_MODER4|GPIO_MODER_MODER5|
  GPIO_MODER_MODER6|GPIO_MODER_MODER8);
 	GPIOC->MODER |= (GPIO_MODER_MODER0_0|GPIO_MODER_MODER1_0|GPIO_MODER_MODER2_0|GPIO_MODER_MODER3_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER8_0);

 	RCC->APB2ENR|= RCC_APB2ENR_TIM11EN | RCC_APB2ENR_TIM10EN | RCC_APB2ENR_TIM9EN;

  TIM9->PSC= PSC_INICIAL;
 	TIM9->ARR= ARR_99;
 	TIM10->PSC= PSC_INICIAL;
 	TIM10->ARR= ARR_999;
  TIM11->PSC= PSC_INICIAL;
 	TIM11->ARR= ARR_14;

  TIM9->CR1  |= (TIM_CR1_CEN | TIM_CR1_ARPE);
  TIM10->CR1 |= (TIM_CR1_CEN | TIM_CR1_ARPE);
 	TIM11->CR1 |= (TIM_CR1_CEN | TIM_CR1_ARPE);

 	TIM10->DIER |= TIM_DIER_UIE;
 	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
 	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);


 while (1){
	SET_RESET ();

  B_MENOS();
	B_MAIS();

	LED_PONTO ();

  LED_CARGA ();

  GPIOC->ODR &= 0X0;
  GPIOC->ODR |= display[digito_display];
  }
}
