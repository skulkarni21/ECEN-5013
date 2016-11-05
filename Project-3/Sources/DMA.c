/*
 * DMA_profile_test.c
 *
 *  Created on: Nov 1, 2016
 *      Author: Joyce
 */

#include "DMA.h"

/*********************************************************************************************************
 ** Function name:           dmaInitMemToMem
 ** Descriptions:            Initialize DMA memory to memory
 ** input parameters:        ucDMAn：
 **                          pulSrcAddress：  source address
 **                          pulDestAddress： destination address
 **                          ulDMASize：  data size for transmitting
 **                          ucIntCon: interrupt
 ** output parameters:       none
 ** Returned value:          succeed：1; fail：0
 ** Created by:              Yu-Chih Cho
--------------------------------------------------------------------------------------------------------*/
uint8_t  dmaInitMemToMem (uint8_t  ucDMAn, void  *pulSrcAddress, void  *pulDestAddress, uint32_t  ulDMASize, uint32_t  ucIntCon)
{
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK; //set the clock

    DMA_SAR_REG(DMA_BASE_PTR, ucDMAn) = (uint32_t)pulSrcAddress;  //set the source address
    DMA_DAR_REG(DMA_BASE_PTR, ucDMAn) = (uint32_t)pulDestAddress; //set the destination address

    DMA_DSR_BCR_REG(DMA_BASE_PTR, ucDMAn) |= DMA_DSR_BCR_DONE_MASK;   //Clear Mark of Done

    DMA_DSR_BCR_REG(DMA_BASE_PTR, ucDMAn) = DMA_DSR_BCR_BCR(ulDMASize); //Set the data transfer size

    DMA_DCR_REG(DMA_BASE_PTR, ucDMAn) =  (ucIntCon << 31)|       //set for interrupt
                                         //DMA_DCR_SINC_MASK|      //automatically increase for source address (clear for memzero)
                                         DMA_DCR_SSIZE(1)|       //00-32bits 01-8bits 10-16bits
                                         DMA_DCR_DINC_MASK|      //automatically increase for destination address
                                         DMA_DCR_DSIZE(1);       //00-32bits 01-8bits 10-16bits

    if (DMA_DSR_BCR_REG(DMA_BASE_PTR, ucDMAn) & DMA_DSR_BCR_CE_MASK) {
        return 0;
    } else {
        return 1;
    }

}

/*********************************************************************************************************
 ** Function name:           dmaStartTran
 ** Descriptions:            DMA starts to transfer data
 ** input parameters:        ucDMAn
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:              Yu-Chih Cho
*********************************************************************************************************/
void dmaStartTran(uint8_t ucDMAn)
{
    DMA_DCR_REG(DMA_BASE_PTR, ucDMAn) |= (1 << 16);
}


/********************************************************************************************************
 ** Function name:           dmaStatus
 ** Descriptions:            The status for DMA transmission
 ** input parameters:        ucDMAn
 ** output parameters:       none
 ** Returned value:          current status of DMA
 ** Created by:              Yu-Chih Cho
*********************************************************************************************************/
uint8_t  dmaStatus (uint8_t  ucDMAn)
{
    if (DMA_DSR_BCR_REG(DMA_BASE_PTR, ucDMAn) &
        (DMA_DSR_BCR_BES_MASK|DMA_DSR_BCR_BED_MASK|DMA_DSR_BCR_CE_MASK)) {
        return DMA_ERROR;
    }
    if (DMA_DSR_BCR_REG(DMA_BASE_PTR, ucDMAn) & DMA_DSR_BCR_BSY_MASK ) {
        return DMA_BUSY;
    }
    if (DMA_DSR_BCR_REG(DMA_BASE_PTR, ucDMAn) & DMA_DSR_BCR_DONE_MASK ) {
        return DMA_DONE;
    }
    return DMA_ERROR;
}
