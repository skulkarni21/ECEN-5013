/***************************************************************************
 *
 *  	Filename: LED.c
 *      Description:  This file contains the drivers for TPM PWM Module
 *
 *      Author: Sarang Kulkarni
 *
 ****************************************************************************/
#include "MKL25Z4.h"
#include "circbuff.h"
#include "UART.h"
#include "LED.h"

void led_gpio_init(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;//setup clock for port B and port D

	PORTB_PCR18 = PORT_PCR_MUX(1);
	GPIOB_PDDR |= (1<<18);//Set pin 18(Red led) as output.

	PORTB_PCR19 = PORT_PCR_MUX(1);//set MUX to GPIO for pin 19(GREEN LED)
	GPIOB_PDDR |= (1<<19); // Set pin 19 as output

	PORTD_PCR1 = PORT_PCR_MUX(1);// Set MUX to GPIO for pin 1 port D
	GPIOD_PDDR |= (1<<1);// Set pin 1 port d as output

	GPIOB_PSOR = (1<<18);
	GPIOB_PSOR = (1<<19);
	GPIOD_PSOR = (1<<1);
}

void led_pwm_init(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;//setup clock for port B and port D
	SIM_SCGC6	|= SIM_SCGC6_TPM2_MASK; // enable clock for TPM2 module
	SIM_SOPT2	|= SIM_SOPT2_TPMSRC(1); //select PLL as clock source for TPM2

	/*-----------------for Red LED-----------------------------*/
	PORTB_PCR18 = PORT_PCR_MUX(3);//set MUX to PWM for pin 18
	TPM_MOD_REG(TPM2_BASE_PTR) = 1875;//reset 100 times in a second
	TPM_SC_REG(TPM2_BASE_PTR)|= TPM_SC_CMOD(1) | TPM_SC_PS(7); //select prescaler of 8 and increament every clock cycle

	TPM_CnSC_REG(TPM2_BASE_PTR, 0) |= TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK;//Sets the mode in which output clears on match and sets on low
	TPM_CnV_REG(TPM2_BASE_PTR,0) = 100;

	/*-----------------for Green LED----------------------------*/
	PORTB_PCR19 = PORT_PCR_MUX(3);
	TPM_CnSC_REG(TPM2_BASE_PTR, 1) |= TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK;
	TPM_CnV_REG (TPM2_BASE_PTR, 1) |= 100;

	/*------------------for Blue LED----------------------------*/

	SIM_SCGC6	|= SIM_SCGC6_TPM0_MASK; // enable clock for TPM2 module
	SIM_SOPT2	|= SIM_SOPT2_TPMSRC(1); //select PLL as clock source for TPM2
	PORTD_PCR1 = PORT_PCR_MUX(4);
	TPM_MOD_REG(TPM0_BASE_PTR) = 1875;//reset 100 times in a second
	TPM_SC_REG(TPM0_BASE_PTR)|= TPM_SC_CMOD(1) | TPM_SC_PS(7); //select prescaler of 8 and increament every clock cycle

	TPM_CnSC_REG(TPM0_BASE_PTR, 1) |= TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK;
	TPM_CnV_REG (TPM0_BASE_PTR, 1) |= 100;
}

void LED_select(uint8_t choice, uint16_t bright){
	if(choice == OFF){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = 00;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = 00;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = 00;
	}
	else if(choice == RED){
		//write_string('s');
		TPM_CnV_REG(TPM2_BASE_PTR,0) = bright;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = 00;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = 00;
	}
	else if(choice == YELLOW){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = bright;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = bright;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = 00;
	}
	else if(choice == MAGENTA){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = bright;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = 00;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = bright;
	}
	else if(choice == GREEN){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = 00;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = bright;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = 00;
	}
	else if(choice == CYAN){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = 00;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = bright;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = bright;
	}
	else if(choice == BLUE){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = 00;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = 00;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = bright;
	}
	else if(choice == WHITE){
		TPM_CnV_REG(TPM2_BASE_PTR,0) = bright;
		TPM_CnV_REG(TPM2_BASE_PTR,1) = bright;
		TPM_CnV_REG(TPM0_BASE_PTR,1) = bright;
	}
}

