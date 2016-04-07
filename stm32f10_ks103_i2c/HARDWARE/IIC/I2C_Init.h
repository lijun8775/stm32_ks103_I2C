/*I2C_Init.h*/
#ifndef I2C_INIT_H
#define I2C_INIT_H

#include "sys.h"

#define USE_I2C1            //ʹ��I2C1

#ifdef USE_I2C1

//IO��������
#define SDA_IN()  {GPIOB->CRL &= 0X0FFFFFFF; GPIOB->CRL |= 8<<28;}
#define SDA_OUT() {GPIOB->CRL &= 0X0FFFFFFF; GPIOB->CRL |= 3<<28;}

#define SCL_IN()   {GPIOB->CRL &= 0XF0FFFFFF; GPIOB->CRL |= 8<<24;}
#define SCL_OUT()  {GPIOB->CRL &= 0XF0FFFFFF; GPIOB->CRL |= 3<<24;}

//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SCL   PBin(6)  //����SCL
#define READ_SDA   PBin(7)  //����SDA 

#else

//IO��������
#define SDA_IN()  {GPIOB->CRH &= 0XFFFF0FFF; GPIOB->CRH |= 8<<12;}
#define SDA_OUT() {GPIOB->CRH &= 0XFFFF0FFF; GPIOB->CRH |= 3<<12;}

//IO��������	 
#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //����SDA 

#endif

void SW_I2C_Init(void);

void IIC_Start(void);               //����IIC��ʼ�ź�
void IIC_Stop(void);                //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);         //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void IIC_Ack(void);                 //IIC����ACK�ź�
void IIC_NAck(void);                //IIC������ACK�ź�

#endif
