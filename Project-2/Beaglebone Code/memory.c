#include<stdio.h>
#include<stdint.h>
#include"memory.h"


int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{
	uint32_t i=0;
	uint8_t tmp[1000];
    if(src != NULL){

		for(i=0;i<length;i++){
             *(tmp+i)=*(src+i);
        }

        for(i=0;i<length;i++){
             *(dst+i)=*(tmp+i);
        }
         return 0;
    }
    else
		return 1;

}

int8_t my_memzero (uint8_t *src,uint32_t length){
	if(src != NULL){
		unsigned char *ptr;
		for(ptr = src; 0 < length ; ++ptr, --length)
			*ptr = 0;
		return 0;
	}
	else
		return 1;
}

int8_t my_reverse(uint8_t *src, int length)
{
    uint16_t j;

    if(src != NULL)
    {
        int8_t tmp;
        for (j=0;j<(length/2);j++)
        {
           tmp=*(src+j);
           *(src+j)=*(src+length-j-1);
           *(src+length-j-1)=tmp;
        }
		return 0;
    }

    else
        return 1;

}


