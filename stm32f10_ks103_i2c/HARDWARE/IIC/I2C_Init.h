/*I2C_Init.h*/
#ifndef I2C_INIT_H
#define I2C_INIT_H

#include "sys.h"

#define USE_I2C1            //使用I2C1

#ifdef USE_I2C1

//IO方向设置
#define SDA_IN()  {GPIOB->CRL &= 0X0FFFFFFF; GPIOB->CRL |= 8<<28;}
#define SDA_OUT() {GPIOB->CRL &= 0X0FFFFFFF; GPIOB->CRL |= 3<<28;}

#define SCL_IN()   {GPIOB->CRL &= 0XF0FFFFFF; GPIOB->CRL |= 8<<24;}
#define SCL_OUT()  {GPIOB->CRL &= 0XF0FFFFFF; GPIOB->CRL |= 3<<24;}

//IO操作函数	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SCL   PBin(6)  //输入SCL
#define READ_SDA   PBin(7)  //输入SDA 

#else

//IO方向设置
#define SDA_IN()  {GPIOB->CRH &= 0XFFFF0FFF; GPIOB->CRH |= 8<<12;}
#define SDA_OUT() {GPIOB->CRH &= 0XFFFF0FFF; GPIOB->CRH |= 3<<12;}

//IO操作函数	 
#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //输入SDA 

#endif

void SW_I2C_Init(void);

void IIC_Start(void);               //发送IIC开始信号
void IIC_Stop(void);                //发送IIC停止信号
void IIC_Send_Byte(u8 txd);         //IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void);              //IIC等待ACK信号
void IIC_Ack(void);                 //IIC发送ACK信号
void IIC_NAck(void);                //IIC不发送ACK信号

#endif
