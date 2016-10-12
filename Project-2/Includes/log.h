#ifndef LOG
#define LOG

#include "MKL25Z4.h"
#include "UART.h"
#include <string.h>
#include "circbuff.h"
#include "conversion.h"

void write_string(uint8_t *str);
void log1(uint8_t * str, uint32_t param);
void process(uint8_t value);

#endif
