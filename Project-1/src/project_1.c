#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memory.h"

uint8_t array[32];
uint8_t *aptr_1=NULL;
uint8_t *aptr_2=NULL;
uint8_t *aptr_3=NULL;

void project_1_report(){
	uint8_t i=0,data=31;
    aptr_1 = array;
    aptr_2 = (array+8);
    aptr_3 = (array+16);

	for (i=0; i<16; i++){
		*(aptr_1+i) = data;
		data++;
	}

	my_memzero(aptr_3, 16);

	my_memmove(aptr_1, aptr_3,8);

	my_memmove(aptr_2,aptr_1,16);

	my_reverse(aptr_1,32);

	for(i=0;i<32;i++)
		printf("%d  ",array[i]);
	printf("\n");
}

