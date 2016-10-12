#include<stdio.h>
#include<stdint.h>
#include"memory.h"


int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length) //Function definition to move data from one location to other location
{
    uint32_t i=0;
    uint8_t temp[5000];

    if(src)
    {
        while(i<length)   //Copies data from source  to temp array
        {
             *(temp+i)=*(src+i);
             i++;
        }
        i=0;

        while(i<length)   //Copies data from temp to destination array
        {
             *(dst+i)=*(temp+i);
             i++;
        }
        return 0;
    }
    else
    {
    //Displays an error if move failed
        return 1;
    }
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


