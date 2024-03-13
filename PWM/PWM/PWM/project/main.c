#include "stm32f10x.h"

/*Khai bao bien*/
GPIO_InitTypeDef					GPIO_InitStructure;
TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
TIM_OCInitTypeDef					TIM_OCInitStructure; 

void Delay_ms(uint16_t time);
void TIM4_Configuraion(void);

int main(void)
{
	TIM4_Configuraion();
	
  while (1)
  {
		//TIM_SetCompare4(TIM4,50);
		TIM4->CCR4 = 45;//50~1ms
		Delay_ms(1000);
		TIM4->CCR4 = 115;
		Delay_ms(1000);
		TIM4->CCR4 = 70;
		Delay_ms(1000);
		TIM4->CCR4 = 200;//100~2ms
		Delay_ms(1000);
		
		
		
	}
}

void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}

void TIM4_Configuraion(void)
{
	/*Cap clock*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*Cau hinh chân*/
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*led 13*/
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	 /* cau hinh timer base */
	// TIM2 initialization for overflow every 1us
	// Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * (TIM_Period + 1))
	// Update Event (Hz) = 36MHz / ((719 + 1) * (999 + 1)) = 50Hz (20ms)
  TIM_TimeBaseStructure.TIM_Prescaler = 719;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 999;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* cau hinh channel4 o mode PWM */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 500;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	/* cho phep TIM4 hoat dong */
  TIM_Cmd(TIM4, ENABLE);
}
