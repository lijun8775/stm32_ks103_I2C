/*HW_I2C2init.h*/
#ifndef HW_I2C2_H
#define HW_I2C2_H

#include "sys.h"
#include "stm32f10x_i2c.h"

void HW_I2C2_Init(void);
void I2C_ByteWrite(u8 slaveAddr, u8 pBuffer, u8 writeAddr);
void I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead);

#endif
