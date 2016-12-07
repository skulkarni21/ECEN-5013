#include "ADC.h"

void ADC_temperature_test(void){
	 float result,m,temp;

	 ADC_Init();                    /* Configure ADC0 */

	 ADC0->SC1[0] = 0;           /* start conversion on channel 0 */
	 while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO (Conversion Complete Flag) */
	 result = ADC0->R[0];        /* read conversion result and clear COCO flag */

	 result *= (3.3);
	 if(result > 0.7012)
		 m=0.003125;
	 else
		 m=0.001749;
	temp= 25-((result-0.7012)/m);
	log3("The temp is",temp);

	 delayMs(1000);
}

uint16_t read_channel(uint8_t channel){
	ADC0_SC1A = channel & ADC_SC1_ADCH_MASK;
	while(!(ADC0->SC1[0] & 0x80));
	return ADC0_RA;
}
void ADC_Init(void)
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK; //Turn on ADC clock gate
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;//Turn on clock for port b
	PORTB_PCR0 |= PORT_PCR_MUX(0);

	ADC0_CFG1 |= (ADC_CFG1_MODE(3) |  //16-bit conversion
			      ADC_CFG1_ADIV(2));  //The divide ratio is 4 and the clock rate is (input clock)/4.
	ADC0_SC1A  = ADC_SC1_ADCH(31);    //Disable ADC module
}


void delayMs(int32_t n) {
    int32_t i;
    int32_t j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 3000; j++) {}
}

