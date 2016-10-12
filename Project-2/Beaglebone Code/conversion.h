
#include <stdio.h>
#include <stdint.h>

#ifndef Conversion_h
#define Conversion_h

int8_t *my_itoa( uint8_t * str, int32_t data, int32_t base );

int32_t my_atoi(uint8_t * str);

float TransferFloatingToDecimal(uint8_t s[32]);

int8_t my_ftoa(uint8_t* str, float data);


#endif