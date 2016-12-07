#ifndef LOG
#define LOG

#include "MKL25Z4.h"
#include "UART.h"
#include <string.h>
#include "circbuff.h"
#include "conversion.h"
//#include "main.h"

void log0(uint8_t *str);
void log3(uint8_t *str, float param);

#endif
