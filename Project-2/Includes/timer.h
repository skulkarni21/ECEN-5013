#ifndef timer_h
#define timer_h

#include "MKL25Z4.h"

void pit_init(void);
void start_timer(void);
uint32_t stop_timer(void);

#endif
