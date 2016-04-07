/*HW_I2C2init.c*/
#include "HW_I2C2init.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "math.h"

void HW_I2C2_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2 , ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11); 	  //PB10,PB11输出高

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0xc0;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 10000;  

	I2C_Init(I2C2, &I2C_InitStructure);
	I2C_Cmd(I2C2, ENABLE);
}

void I2C_ByteWrite(u8 slaveAddr, u8 pBuffer, u8 writeAddr)
{
  /* Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);         // 发送开始信号
  /* Test on EV5 and clear it */
	printf("ok 2\r\n");
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	printf("ok 3\r\n");
  /* Send MPU6050 address for write */
  I2C_Send7bitAddress(I2C2, slaveAddr, I2C_Direction_Transmitter);         //发送从机地址
	printf("ok 4\r\n");
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	printf("ok 5\r\n");
  /* Send the MPU6050's internal address to write to */
  I2C_SendData(I2C2, writeAddr);           //发送寄存器地址
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	printf("ok 6\r\n");
  /* Send the byte to be written */
  I2C_SendData(I2C2, pBuffer);             //发送数据
	printf("ok 7\r\n");
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	printf("ok 8\r\n");
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C2, ENABLE);          //发送停止信号
}

void I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead)
{
  /* While the bus is busy */  
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MPU6050 address for write */
  I2C_Send7bitAddress(I2C2, slaveAddr, I2C_Direction_Transmitter); 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C2, ENABLE);
  /* Send the MPU6050's internal address to write to */
  I2C_SendData(I2C2, readAddr);
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* Send STRAT condition a second time */
  I2C_GenerateSTART(I2C2, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MPU6050 address for read */
  I2C_Send7bitAddress(I2C2, slaveAddr, I2C_Direction_Receiver);
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2C2, DISABLE);

      /* Send STOP Condition */
      I2C_GenerateSTOP(I2C2, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the MPU6050 */
      *pBuffer = I2C_ReceiveData(I2C2);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C2, ENABLE);
}
