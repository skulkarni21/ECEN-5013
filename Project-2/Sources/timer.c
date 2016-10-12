#include "timer.h"

volatile uint32_t timer_val =0;

void pit_init(void){
	// Enable PIT clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	// Turn on PIT
	PIT_MCR = 0;

	// Configure PIT to produce an interrupt every 1 uSec
	PIT_LDVAL0 = 0x00000017;	// 1/24Mhz = 41.67ns   (1us/41.67ns)-1= 23 cycles or 0x00000017
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK; // Enable interrupt and enable timer

	// Enable interrupt registers in NVIC
	//NVIC->ISER[0] = (uint32_t)(1UL << (((uint32_t)(int32_t)PIT_IRQn) & 0x1FUL));
	NVIC_EnableIRQ(PIT_IRQn);
}

void start_timer(void){
	timer_val =0;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; //enable the timer
}

uint32_t stop_timer(void){
	PIT_TCTRL0 &= ~(PIT_TCTRL_TEN_MASK);
	return timer_val;
}

void PIT_IRQHandler(void)
{
	// Clear interrupt
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
	timer_val++;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
}
