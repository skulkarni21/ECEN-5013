/***************************************************************************
 *
 *  	Filename: UART.c
 *      Description:  This file contains the drivers for UART
 *
 *      Author: Sarang Kulkarni
 *
 ****************************************************************************/

#include "MKL25Z4.h"
#include "UART.h"


void UART0_init(void){
	uint16_t sbr;
	uint8_t temp;

	//Set clock frequency for PORTA
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Set clock frequency
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);// Select the clock as PLL/2

	PORTA_PCR1 = PORT_PCR_MUX(2);// Set the alternate function for PORTA
	PORTA_PCR2 = PORT_PCR_MUX(2);

	UART0_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK); // Switch off UART before setting
	UART0_C1_REG(UART0_BASE_PTR)=0x00; //Set all default configuration

	//SBR calculation

	sbr= (uint16_t)(DEFAULT_SYSTEM_CLOCK/(BAUD *16));

	/* Save off the current value of the uartx_BDH except for the SBR field */
	temp = UART_BDH_REG(UART0_BASE_PTR) & ~(UART_BDH_SBR(0x1F));
	UART_BDH_REG(UART0_BASE_PTR) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));//set SBR field for Baud rate
	UART_BDL_REG(UART0_BASE_PTR) = (uint8_t)(sbr & UART_BDL_SBR_MASK);

	//Set NVIC interrupts and set priority
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn,2);

	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK; //Setup receiver interrupt

    UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK ); //Switch on transmitter and receiver
  }


void UART0_IRQHandler(void){
	__asm("cpsid i");
	if((UART0_S1 & UART_S1_TDRE_MASK) && !(IfEmpty(&tx_buff))){
		remove_item(&tx_buff, &UART0_D);

		if(IfEmpty(&tx_buff))
			UART0_C2 &= ~UART_C2_TIE_MASK;	//disable transmitter interrupts if empty
	}

	if((UART0_S1 & UART_S1_RDRF_MASK) && !(IfFull(&rx_buff))){
		add_item(&rx_buff,(uint8_t)UART0_D);

		if(IfFull(&tx_buff))
			UART0_C2 &= ~UART_C2_RIE_MASK;	//disable receiver interrupts if full
	}
	__asm("cpsie i");
}
