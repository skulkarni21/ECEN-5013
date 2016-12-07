#ifndef MSG
#define MSG

#include "MKL25Z4.h"
#include "circbuff.h"
#include "LED.h"
#include "log.h"
#include "ADC.h"
#include "I2C.h"
#include "TSL2561.h"
#include "humidity.h"

#define MAX_SIZE_DATA 2

typedef enum Cmds_t{
	LED_RED = 0x01,
	LED_BLUE = 0x02,
	LED_GREEN = 0x03,
	LED_CYAN = 0x04,
	LED_MAGENTA=0x05,
	LED_YELLOW=0x06,
	LED_WHITE=0x07,
	LIGHT=0x08,
	HUMIDITY=0x09
}Cmds;

typedef struct CI_Msg_t{
	Cmds command;
	uint8_t length;
	uint8_t data[MAX_SIZE_DATA];
	uint8_t checksum;
}CI_Msg;

void Decode_CI_Msg(CI_Msg* msg);
void Read_CI_Msg(CI_Msg*msg);

#endif
