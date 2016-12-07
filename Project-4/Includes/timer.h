#ifndef TIMER
#define TIMER
#include "MKL25Z4.h"

void delay_init(void);
//uint32_t start_timer(void);
//uint32_t stop_timer(void);
void delay_ms(uint32_t delay);
void delay_us(uint32_t delay);
#endif
