
/***************************************************************************
 *
 *  	Filename: conversion.c
 *      Description:  itoa, atoi, and ftoa conversions as well as convert 32-bit floating point fractional number (BIN) to decimal
 *
 *      Author: Yu-Chih Cho
 *
 ****************************************************************************/


#include "conversion.h"




// Convert data from a standard integer type into an asci string
int8_t *my_itoa( uint8_t * str, int32_t data, int32_t base )
{
    uint8_t *ptr;
    uint8_t *firstdig;
    uint8_t temp;
    int32_t digval;
    
    ptr = str;
    
    //change the data to an unsigned value if it is negative
    if (data<0)
    {
        *ptr++ = '-';
        data = (uint32_t)(-data);
    }
    
    firstdig = ptr;
    
    do{
        //deal with the base (radix)
        digval = (int32_t)(data % base);
        data /= base;
        
        //transfer to ascii
        if (digval>9)
            *ptr++ = (uint8_t)(digval - 10 + 'a');
        
        else
            *ptr++ = (uint8_t)(digval + '0');
        
    }while (data>0);
    
    //terminate
    *ptr-- = '\0';
    
    //reverse the ascii to correct order
    do{
        temp = *ptr;
        *ptr = *firstdig;
        *firstdig = temp;
        --ptr;
        ++firstdig;
    }while(firstdig < ptr);
    
    return str;
}



// Convert data from an ascii represented string into an integer type
int32_t my_atoi(uint8_t * str)
{
    uint32_t result = 0;
    uint32_t sign = 0;
    
    // whitespace characters
    while (*str==' ' || *str=='\t' || *str=='\n')
        ++str;
    
    //sign character
    if (*str=='-')
    {
        sign = 1;
        ++str;
    }
    else if (*str=='+')
    {
        ++str;
    }
    
    //numbers
    while (*str>='0' && *str<='9')
    {
        result = result*10 + *str - '0';
        ++str;
    }
    
    // return result
    if (sign==1)
        return -result;
    else
        return result;
}


//onvert 32-bit floating point fractional (HEX) number to decimal (DEC) numbers
float TransferFloatingToDecimal(uint8_t s[32])
{
    float f;
    int16_t sign, exp;
    uint32_t mant;
    int16_t i;
    
    //The first bit  is "SIGN"
    sign = s[0] - '0';
    
    exp = 0;
    for (i = 1; i <= 8; i++)
        exp = exp * 2 + (s[i] - '0');
    
    // Remove the exponent bias
    exp -= 127;
    

    // Should really check for +/-Infinity and NaNs here
    
    if (exp > -127)
    {
        // Normal(ized) numbers
        mant = 1; // The implicit "1."
        // Account for "1." being in bit position 23 instead of bit position 0
        exp -= 23;
    }
    else
    {
        // Subnormal numbers
        mant = 0; // No implicit "1."
        exp = -126; // See your IEEE-54 formulas
        // Account for ".1" being in bit position 22 instead of bit position -1
        exp -= 23;
    }

    
    //Deal with Mantissa
    for (i = 9; i <= 31; i++)
        mant = mant * 2 + (s[i] - '0');
    
    f = mant;
    
    while (exp > 0)
        f *= 2, exp--;
    
    // Or here?
    while (exp < 0)
        f /= 2, exp++;
    
    if (sign)
        f = -f;
    
    return f;
}



//Convert data from a standard float type into an asci string
int8_t my_ftoa(uint8_t* ptr, float data)
{
    uint16_t int_part;
    uint16_t i=0,k=0;
    
    //Deal with the integer
    int_part=(uint16_t)data;
    while(int_part>0)
    {
        data/=10;
        int_part=(uint16_t)data;
        i++;
    }
    *(ptr+i) = '.';
    
    data *= 10;
    int_part = (uint16_t)data;
    data = data-int_part;
    
    //transfer to ascii
    while(int_part>0)
    {
        if(k == i)
            k++;
        *(ptr+k)=48+int_part;
        
        data *= 10;
        int_part = (uint16_t)data;
        data = data-int_part;
        k++;
    }
    
    *(ptr+k) = '\0';
    return data;
}

