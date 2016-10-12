/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "circbuff.h"
#include "UART.h"
#include "LED.h"
#include "test_buff.h"
#include "conversion.h"
#include "timer.h"
#include "profile_test.h"
#include "log.h"

#define CLOCK_STATE 1 //set clock at 48Mhz and bus at 24Mhz

uint8_t string[7]="sarang",sentence[200];
uint8_t value, color=0,mode=0,i;
uint16_t bright=100;

void process(uint8_t value){
	uint8_t value_r;
	if(mode == 0){
		if(value == ':'){
				write_string("Enter the sentence \n");
				mode =1;
				i=0;
		}
		else if(value == 'a'){
			if(color == 0)
				color = 7;
			else
				color--;
		}
		else if(value == 'd'){
			if(color == 7)
				color = 0;
			else
				color++;
		}

		else if(value == 'w'){
			if(bright==1000)
				bright =1000;
			else
				bright += 100;
		}
		else if(value == 's'){
			if(bright == 0)
				bright = 0;
			else
				bright -= 100;
		}

	}
	else if(mode ==1){
		if(value == ':'){
			sentence[i]='\0';
			write_string(sentence);
			mode=0;
		}
		else{
			sentence[i] = value;
			i++;
		}
	}
}

int main(void)
{
	/*CircBuff_t test_buff;
	float result=10.45;
	uint8_t a[20];
	uint8_t b=12;*/
	UART0_init();
	led_pwm_init();
	init_buff(&tx_buff,2000);//initialize TX buffer of 100 bytes
	init_buff(&rx_buff,2000);//initialize RX buffer of 100 bytes

	//init_buff(&test_buff,10);
	pit_init();
	__asm("cpsie i");		//Enable global interrupts

	write_string("Welcome\n");

	//profile_tests();
	//my_ftoa(a, result);
	//write_string(a);

	//log1("result =", result);

	while(1){
		if(!IfEmpty(&rx_buff)){
			remove_item(&rx_buff, &value);
			process(value);
			LED_select(color,bright);
		}
	}

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
