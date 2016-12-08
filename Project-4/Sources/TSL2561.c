#include "TSL2561.h"
#include "timer.h"

void tsl_init(void){
	i2c_writeByte(TSL2561_ADDR, TSL2561_REG_TIMING|TSL2561_CMD, 0x02); //setting gain =0 and time=2 ie 402ms
	i2c_writeByte(TSL2561_ADDR, TSL2561_REG_CONTROL|TSL2561_CMD, 0x03);//power up
}

float tsl_getLux(void){
	uint8_t data0l,data0h,data1l,data1h;
	float lux,ratio,power;
	double d1,d0;
	//delay_ms(402);

	data0l = i2c_readByte(TSL2561_ADDR,TSL2561_REG_DATA_0_LOW|TSL2561_CMD);
	data0h = i2c_readByte(TSL2561_ADDR,TSL2561_REG_DATA_0_HIGH|TSL2561_CMD);
	data1l = i2c_readByte(TSL2561_ADDR,TSL2561_REG_DATA_1_LOW|TSL2561_CMD);
	data1h = i2c_readByte(TSL2561_ADDR,TSL2561_REG_DATA_1_HIGH|TSL2561_CMD);

	d0 = data0h<<8 | data0l;
	d1 = data1h<<8 | data1l;
	//calculate the ratio of both the numbers
	ratio = (d1/d0);

	if (ratio < 0.5){
		lux = 3.04 * d0 - 6.2 * d0 ;
	}

	if (ratio < 0.61){
		lux = 2.24 * d0 - 3.1 * d1;
	}

	if (ratio < 0.80){
		lux = 1.28 * d0 - 1.53 * d1;
	}

	if (ratio < 1.30){
		lux = 0.146 * d0 - 0.112 * d1;
	}
	return lux;
}
