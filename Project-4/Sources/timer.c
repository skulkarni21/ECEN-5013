#include "timer.h"

void delay_init(void){
	// Enable PIT clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	// Turn on PIT
	PIT_MCR = 0;

}

/*uint32_t start_timer(void){
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //enable the timer
	return timer_val;
}*/

/*uint32_t stop_timer(void){
	PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);
	return timer_val;
}*/

void delay_ms(uint32_t delay){
	uint32_t i;
	//__asm("cpsid i");
	for(i=0;i<delay;i++){
		PIT_LDVAL1 = 0x0005DBF;	// 1/24Mhz = 41.67ns   (1ms/41.67ns)-1= 23999 cycles or 0x00005DBF
		PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //enable the timer
		while(!(PIT_TFLG1 & PIT_TFLG_TIF_MASK));  //waiting for 1ms
		PIT_TFLG1 = PIT_TFLG_TIF_MASK;
		PIT_TCTRL1 &= ~(PIT_TCTRL_TEN_MASK);
	}
	//__asm("cpsie i");
}

void delay_us(uint32_t delay){
	uint32_t i;
	__asm("cpsid i");
	for(i=0;i<delay;i++){
		PIT_LDVAL1 = 0x0000017;	// 1/24Mhz = 41.67ns   (1us/41.67ns)-1= 23 cycles or 0x00000017
		PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; //enable the timer
		while(!(PIT_TFLG1 & PIT_TFLG_TIF_MASK));  //waiting for 1us
		PIT_TFLG1 = PIT_TFLG_TIF_MASK;
		PIT_TCTRL1 &= ~(PIT_TCTRL_TEN_MASK);
	}
	__asm("cpsie i");
}

/*void PIT_IRQHandler(void)
{
	// Clear interrupt
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
	timer_val++;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
}*/
