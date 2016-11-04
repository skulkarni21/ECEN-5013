#include "SPI.h"

void SPI_init(void){

	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; //Turn on clock to C module
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;  //Enable SPI0 clock

	PORTC_PCR4 = PORT_PCR_MUX(0x01);
	GPIOC_PDDR = (1<<4);				//Set PortC pin 4 as output
	GPIOC_PSOR = (1<<4);				//keep SS high initially
	PORTC_PCR5 = PORT_PCR_MUX(0x02);    //Set PTC5 to mux 2 [SPI0_SCK]
	PORTC_PCR6 = PORT_PCR_MUX(0x02);    //Set PTC6 to mux 2 [SPI0_MOSI]
	PORTC_PCR7 = PORT_PCR_MUX(0x02);    //Set PTC7 to mux 2 [SPIO_MISO]

	SPI0_C1 = SPI_C1_MSTR_MASK;		//Enable SPI as master

	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x01)); //Setting Bitrate to 1Mbps

	SPI0_C1 |= SPI_C1_SPE_MASK;    //Enable SPI0
}

uint8_t SPI_transfer(uint8_t data){
	while(!(SPI_S_SPTEF_MASK & SPI0_S));
	SPI0_D = data;    //Write char to SPI
	while(!(SPI_S_SPRF_MASK & SPI0_S));
	return SPI0_D;
}

void cs_low(void){
	GPIOC_PCOR = (1<<4);
}

void cs_high(void){
	GPIOC_PSOR = (1<<4);
}
