#ifndef Conversion_h
#define Conversion_h

#include <stdio.h>
#include <stdint.h>

uint8_t *my_itoa( uint8_t * str, int32_t data, int32_t base );

int32_t my_atoi(uint8_t * str);

float TransferFloatingToDecimal(uint8_t s[32]);

void reverse(uint8_t *str, uint32_t len);
uint8_t intToStr(uint16_t x, uint8_t str[], uint32_t d);
void my_ftoa(float n, uint8_t *res, uint16_t afterpoint);


#endif
