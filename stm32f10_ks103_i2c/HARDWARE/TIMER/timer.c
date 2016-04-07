#include "timer.h"

void TIM_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	
	TIM_DeInit(TIM2);
	//72M�¶�ʱֵ�ļ��㣨��1+Ԥ��ƵTIM_Prescaler��/72*(1+��ʱ����TIM_Period)��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);            //����RCC��ʹ��TIMx
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_BaseInitStructure.TIM_Prescaler = 35;                       //ʱ��Ԥ��Ƶ�� ����:ʱ��Ƶ��=36/(ʱ��Ԥ��Ƶ+1)
  TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down;   //��ʱ��ģʽ ���¼���
  TIM_BaseInitStructure.TIM_Period = 10000;                       //��ʱ5ms
  TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //ʱ��ָ�
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure);                 //��ʼ����ʱ��2

	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                      //ʹ���ж�����
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
