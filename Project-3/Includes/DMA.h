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
//#include "memory.h"

#define MKL25Z_DMA0 0
typedef enum states{
	DMA_BUSY=0x00,
	DMA_DONE=0x01,
	DMA_ERROR=0x02
}dma_status;

typedef enum func{
	MEM_MOVE=0x01,
	MEM_ZERO=0x02
}Opt;

extern uint8_t dmaInitMemToMem(uint8_t ucDMAn, void *pulSrcAddress, void *pulDestAddress, uint32_t ulDMASize, uint32_t ucIntCon,Opt option);
extern void dmaStartTran(uint8_t ucDMAn);
extern dma_status dmaStatus(uint8_t ucDMAn);
uint32_t dma_memzero(uint8_t  ucDMAn, uint8_t  *pulSrcAddress, uint8_t  *pulDestAddress, uint32_t  ulDMASize);
uint32_t dma_memmove(uint8_t  ucDMAn, void  *pulSrcAddress, void  *pulDestAddress, uint32_t  ulDMASize);

#endif /* INCLUDES_DMA_H_ */
