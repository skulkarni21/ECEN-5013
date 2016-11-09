#include "nRF24L01.h"
#include "SPI.h"

void ce_low(void){
	GPIOC_PCOR = (1<<0);
}

void ce_high(void){
	GPIOC_PSOR = (1<<0);
}

uint8_t write_register(uint8_t reg,uint8_t value ){
	uint8_t status;

	cs_low();
	status = SPI_transfer(W_REGISTER | ( REGISTER_MASK & reg ));
	SPI_transfer(value);
	cs_high();

	return status;
}

uint8_t read_register(uint8_t reg){
	uint8_t result;

	cs_low();
	SPI_transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
	result = SPI_transfer(0xff);
	cs_high();

	return result;
}

uint8_t write_register_multi(uint8_t reg,uint8_t* value,uint8_t len ){
	uint8_t status;

	cs_low();
	status = SPI_transfer(W_REGISTER | ( REGISTER_MASK & reg ));

	while(len--)
		SPI_transfer(*value++);

	cs_high();

	return status;
}

uint8_t read_register_multi(uint8_t reg, uint8_t* buf, uint8_t len){
	uint8_t status;

	cs_low();
	status=SPI_transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
	while(len--)
		*buf++ = SPI_transfer(0xff);
	cs_high();

	return status;
}
