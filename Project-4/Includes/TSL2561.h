#ifndef tsl
#define tsl

#include "I2C.h"
#include "math.h"

#define TSL2561_CMD           0x80
#define TSL2561_CMD_CLEAR     0xC0
#define	TSL2561_REG_CONTROL   0x00
#define	TSL2561_REG_TIMING    0x01
#define	TSL2561_REG_THRESH_L  0x02
#define	TSL2561_REG_THRESH_H  0x04
#define	TSL2561_REG_INTCTL    0x06
#define	TSL2561_REG_ID        0x0A
#define	TSL2561_REG_DATA_0_LOW    0x0C
#define	TSL2561_REG_DATA_0_HIGH    0x0D
#define	TSL2561_REG_DATA_1_LOW    0x0E
#define	TSL2561_REG_DATA_1_HIGH    0x0F

#define TSL2561_ADDR			  0x39

void tsl_init(void);
float tsl_getLux(void);

#endif
