/***************************************************************************
 *
 *  	Filename: log.c
 *      Description:	This file contains the code for log functions write_string
 *      				and log3()
 *
 *      Author: Sarang Kulkarni
 *
 ****************************************************************************/
#include "log.h"


void log0(uint8_t *str){
	while(*str !='\0'){
		add_item(&tx_buff, *str++);
	}

	if(!(IfEmpty(&tx_buff)) && !(UART0_C2_REG(UART0) & UART0_C2_TIE_MASK ))
			UART0_C2 |= UART_C2_TIE_MASK;
}

void log3(uint8_t *str, float param){
	uint8_t a[20], i=0, str_final[100];
		my_ftoa(param, a,3);
	while(*(str+i) !='\0'){
		*(str_final+i) = *(str+i);
		i++;
	}
	*(str_final+i)= '\0';
	strcat(str_final, a);
	write_string(str_final);
}

