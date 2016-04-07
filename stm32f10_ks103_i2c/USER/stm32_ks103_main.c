/*main.c*/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "I2C2init.h"
#include "KS10X.h"

u32 sum1,sum2,sum3,sum4,sum5,sum6,sum7,sum8,sum9,sum10,sum11,sum12,sum13,sum14,sum15,
    sum16,sum17,sum18,sum19,sum20;
float sum_1,sum_2;

int main()
{
      Stm32_Clock_Init(9);
      delay_init(72);
      uart_init(72,9600);
      I2C2_Init();

//    KS10X_Change_Addr_Init(SlaveAddress3,SlaveAddress2);
      //在换了KS10X后才执行，且执行一次  ,执行完一次后就消去
      //这样这个模块将有固定的地址

      while(1)
      {
             sum_2=Read_KS10X_Data(SlaveAddress2);
             sum_1=Read_KS10X_Data(SlaveAddress1);

             printf(\"%lf\r\n",sum_1);
             printf(\"%lf\r\n\r\n",sum_2);
      }
}