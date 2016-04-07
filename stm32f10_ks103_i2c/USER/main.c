#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "I2C_Init.h"
#include "HW_I2C2init.h"
#include "ks103.h"
#include "timer.h"

u8 distance_flag = 1, light_flag = 0;  //默认测距离
u16 t1 = 0, t2 = 0;
u16 tick = 0;

int main(void)
{
	u32 i = 0, j = 0;
	float distance = 0.0;
	float light = 0.0;
	
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//SysTick_Config(72);
	
	delay_init();	    	   //延时函数初始化
	NVIC_Configuration();  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	TIM_Config();
	uart_init(115200);	 	 //串口初始化为115200
	KEY_Init();
 	LED_Init();			       //LED端口初始化
	SW_I2C_Init();
//	HW_I2C2_Init();

	Single_WriteI2C(SlaveAddress1, 0x02, 0x72);

	while(1)
	{
		distance = 0.0;
		light = 0.0;
		
		delay_ms(400);			
		
		// ks103测距
		if (distance_flag)
		{
			distance = Read_KS10X_Data(SlaveAddress1, 0xb0);
			printf("-%04d- distance: %04.3f  cm\r\n", i++, distance);
		}
		
		// ks103测光强
		if (light_flag)
		{
			light = Read_KS10X_Data(SlaveAddress1, 0xa0);
			printf("-%04d- light: %04.3f  cd\r\n", j++, light);
		}
		
		if (distance_flag | distance_flag)
			LED0 = !LED0;
/*
		t1 = tick;
		delay2x(1000);  // 延时167us
		t2 = tick;

		printf("time: %d us\r\n", t2 - t1);
*/
	}
}
