#include "timer.h"

void TIM_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	
	TIM_DeInit(TIM2);
	//72M下定时值的计算（（1+预分频TIM_Prescaler）/72*(1+定时周期TIM_Period)）
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);            //配置RCC，使能TIMx
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_BaseInitStructure.TIM_Prescaler = 35;                       //时钟预分频数 例如:时钟频率=36/(时钟预分频+1)
  TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;   //定时器模式 向下计数
  TIM_BaseInitStructure.TIM_Period = 10000;                       //定时5ms
  TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //时间分割
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure);                 //初始化定时器2

	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                      //使能中断请求
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
