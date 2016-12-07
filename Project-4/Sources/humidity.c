#include "humidity.h"

float readHumidity(void){
	uint16_t rawdata;
	float voltage,rh;

	rawdata = read_channel(8);
	voltage = rawdata *3.3/65536;
	rh = (voltage-0.8)/0.03;

	return rh;
}
