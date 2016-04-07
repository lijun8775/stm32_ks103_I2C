#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "I2C_Init.h"
#include "HW_I2C2init.h"
#include "ks103.h"
#include "timer.h"

u8 distance_flag = 1, light_flag = 0;  //Ĭ�ϲ����
u16 t1 = 0, t2 = 0;
u16 tick = 0;

int main(void)
{
	u32 i = 0, j = 0;
	float distance = 0.0;
	float light = 0.0;
	
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//SysTick_Config(72);
	
	delay_init();	    	   //��ʱ������ʼ��
	NVIC_Configuration();  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	TIM_Config();
	uart_init(115200);	 	 //���ڳ�ʼ��Ϊ115200
	KEY_Init();
 	LED_Init();			       //LED�˿ڳ�ʼ��
	SW_I2C_Init();
//	HW_I2C2_Init();

	Single_WriteI2C(SlaveAddress1, 0x02, 0x72);

	while(1)
	{
		distance = 0.0;
		light = 0.0;
		
		delay_ms(400);			
		
		// ks103���
		if (distance_flag)
		{
			distance = Read_KS10X_Data(SlaveAddress1, 0xb0);
			printf("-%04d- distance: %04.3f  cm\r\n", i++, distance);
		}
		
		// ks103���ǿ
		if (light_flag)
		{
			light = Read_KS10X_Data(SlaveAddress1, 0xa0);
			printf("-%04d- light: %04.3f  cd\r\n", j++, light);
		}
		
		if (distance_flag | distance_flag)
			LED0 = !LED0;
/*
		t1 = tick;
		delay2x(1000);  // ��ʱ167us
		t2 = tick;

		printf("time: %d us\r\n", t2 - t1);
*/
	}
}
