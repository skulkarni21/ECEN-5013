/*
 * ADC.h
 *
 *  Created on: Nov 21, 2016
 *      Author: Yu-Chih Cho
 */

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

#include "MKL25Z4.h"
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "UART.h"
#include "log.h"
#include "circbuff.h"
//#include "memory.h"

/****************************************************************************************************
 ** Function name:           ADC_temperature_test
 ** Descriptions:            Use ADC transfer to get voltage data and convert it into temperature result
 ** input parameters:        none
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:              Yu-Chih Cho
****************************************************************************************************/
void ADC_temperature_test(void);


/****************************************************************************************************
 ** Function name:           delayMs
 ** Descriptions:            Use the delay function to show temperature data regularly
 ** input parameters:        n: millisecond
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:              Yu-Chih Cho
****************************************************************************************************/
void delayMs(int32_t n);


/****************************************************************************************************
 ** Function name:           ADC_Init
 ** Descriptions:            ADC initialize
 ** input parameters:        none
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:              Yu-Chih Cho
****************************************************************************************************/
void ADC_Init(void);

uint16_t read_channel(uint8_t channel);

#endif /* INCLUDES_ADC_H_ */
