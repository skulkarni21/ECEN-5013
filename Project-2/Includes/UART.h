#ifndef UART
#define UART

#include "MKL25Z4.h"
#include "circbuff.h"

#define BAUD 38400
CircBuff_t tx_buff,  rx_buff;

void UART0_init(void);
void write_string(uint8_t *str);
#endif
