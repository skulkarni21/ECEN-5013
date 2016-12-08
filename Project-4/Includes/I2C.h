#ifndef I2C
#define I2C
#include "MKL25Z4.h"
#include "timer.h"

void i2c_init(void);
void i2c_writeByte(uint8_t slave_addr,uint8_t mem_addr,uint8_t data);
uint8_t i2c_readByte(uint8_t slave_addr,uint8_t mem_addr);
void i2c_delay(int number);
void i2c_read_multi(uint8_t slave_addr,uint8_t cmd,uint8_t* var, uint8_t number);

#endif
