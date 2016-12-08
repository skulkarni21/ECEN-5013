#include "TSI.h"

uint16_t value[50];

void tsi_init(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;	//initialize port B mask
	SIM_SCGC5 |= SIM_SCGC5_TSI_MASK;	//initilaize the TSI module

	PORTB_PCR16 = PORT_PCR_MUX(0);		//set alternate function for TSI
	TSI0_GENCS |= TSI_GENCS_REFCHRG(2);	//set reference charge to 1uA

}

uint16_t read_tsi(void){
	uint16_t data;
	while((TSI0_GENCS & TSI_GENCS_SCNIP_MASK));
	TSI0_DATA |= TSI_DATA_TSICH(9);
	TSI0_DATA |= TSI_DATA_SWTS_MASK;	//start scanning
	while(!(TSI0_GENCS & TSI_GENCS_EOSF_MASK));
	data = (uint16_t)(TSI0_DATA & TSI_DATA_TSICNT_MASK);
	return data;
}

void start_scan(void){
	TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;	//enable TSI module
}

void stop_scan(void){
	TSI0_DATA &= ~TSI_DATA_SWTS_MASK;	//stop scanning
	TSI0_GENCS &= ~TSI_GENCS_TSIEN_MASK;	//disable TSI module
}

uint16_t scan_touch(void){
	uint8_t i;
	uint16_t result;
	start_scan();
	result=read_tsi();
	stop_scan();


	return result;
}
