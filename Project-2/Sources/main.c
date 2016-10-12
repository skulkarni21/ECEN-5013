/***************************************************************************
 *
 *	Filename: main.c
 *  Description:  This file is the main file for the project
 *
 *  Author: Sarang Kulkarni
 *
 *****************************************************************************/
#include "main.h"
uint8_t string[7]="sarang",sentence[200];
uint8_t value, color=0,mode=0,i;
uint16_t bright=100;

#define MALLINFO


void process(uint8_t value){
	uint8_t value_r;
	if(mode == 0){
		if(value == ':'){
				write_string("Enter the text file: \n");
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

	UART0_init();
	led_pwm_init();
	init_buff(&tx_buff,2000);//initialize TX buffer of 100 bytes
	init_buff(&rx_buff,2000);//initialize RX buffer of 100 bytes

	pit_init();
	__asm("cpsie i");		//Enable global interrupts

#ifdef MALLINFO
	struct mallinfo mi;
	write_string("Welcome\n");
	write_string("This Section shows the values of memory in the heap");
	mi=mallinfo();
	log3("\nTotal non-mmapped bytes (arena):", mi.arena);
	log3("\n# of free chunks (ordblks):", mi.ordblks);
	log3("\n# of free fastbin blocks (smblks):", mi.smblks);
	log3("\n# of mapped regions (hblks):", mi.hblks);
	log3("\nBytes in mapped regions (hblkhd):", mi.hblkhd);
	log3("\nMax. total allocated space (usmblks):", mi.usmblks);
	log3("\nFree bytes held in fastbins (fsmblks):", mi.fsmblks);
	log3("\nTotal allocated space (uordblks):", mi.uordblks);
	log3("\nTotal free space (fordblks):", mi.fordblks);
	log3("\nTopmost releasable block (keepcost):", mi.keepcost);
#endif

#ifdef UNIT_TEST
	CircBuff_t test_buff;
	uint8_t result;
	init_buff(&test_buff,10);
	result=test_all_param(&test_buff);
	if(result == SUCCESS)
		write_string("\nbuffer good");
	else
		write_string("\ntest fail");
#endif

#ifdef LOG_TEST
	uint8_t a=200;
	uint16_t b=4096;
	uint32_t c=123456;
	float f=1543.321;
	write_string("Testing123, Serial Print Test, no params");
	log3("\nThis is an integer number: ",a);
	log3("\nThis is an integer number:",b);
	log3("\nThis is an integer number:",c);
	log3("\nThis is floating point number:",f);
#endif

#ifdef PROFILE
	profile_test_2();
#endif

	while(1){
		if(!IfEmpty(&rx_buff)){
			remove_item(&rx_buff, &value);
			process(value);
			LED_select(color,bright);
		}
	}

    return 0;
}


