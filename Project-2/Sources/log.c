#include "log.h"


void write_string(uint8_t *str){
	while(*str !='\0'){
		add_item(&tx_buff, *str++);
	}

	if(!(IfEmpty(&tx_buff)) && !(UART0_C2_REG(UART0) & UART0_C2_TIE_MASK ))
			UART0_C2 |= UART_C2_TIE_MASK;
}

void log1(uint8_t * str, uint32_t param){
	uint8_t a[20], i=0, str_final[100];
	my_itoa(a, param,10);
	while(*(str+i) !='\0'){
		*(str_final+i) = *(str+i);
		i++;
	}
	*(str_final+i)= '\0';
	strcat(str_final, a);
	write_string(str_final);
}

