#ifndef LED
#define LED

#include "MKL25Z4.h"
#include "circbuff.h"
#include "UART.h"


 enum color{
	OFF,
	RED,
	YELLOW,
	MAGENTA,
	GREEN,
	CYAN,
	BLUE,
	WHITE
};

void led_gpio_init(void);
void LED_select(uint8_t choice, uint16_t bright);
void led_pwm_init(void);
void process(uint8_t value);

#endif
