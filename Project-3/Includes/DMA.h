/*
 * DMA_profile_test.h
 *
 *  Created on: Nov 1, 2016
 *      Author: Joyce
 */

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

#include "MKL25Z4.h"
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "UART.h"
#include "log.h"
#include "circbuff.h"
#include "memory.h"

#define MKL_DMA0        0
#define MKL_DMA1        1
#define MKL_DMA2        2
#define MKL_DMA3        3

#define DMA_BUSY            0
#define DMA_DONE            1
#define DMA_ERROR           2

extern uint8_t dmaInitMemToMem(uint8_t ucDMAn, void *pulSrcAddress, void *pulDestAddress, uint32_t ulDMASize, uint32_t ucIntCon);
extern void dmaStartTran(uint8_t ucDMAn);
extern uint8_t dmaStatus(uint8_t ucDMAn);

#endif /* INCLUDES_DMA_H_ */
