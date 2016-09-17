#include <stdio.h>
#include "memory.h"
#include <string.h>

void memmov(int *src, int *dst, int length)
{
    if (src <= dst)
    {
        int *se = src + length - 1;
        int *te = dst + length - 1;
        
        while(se >= src)
            *te-- = *se--;
    }
    else
    {
        int *sb = src;
        int *tb = dst;
        while(sb < src+length)
            *tb++ = *sb++;
    }
}


void *(my_memzero) (void *src,int c,size_t length)
{
    const unsigned char uc = c;
    unsigned char *ptr;
    for(ptr = src; 0 < length ; ++ptr, --length)
        *ptr = uc;
        return src;
}


void my_reverse(char* str){
    char temp;
    char* end;
    end = str + strlen(str)-1;
    
    while(end>str){
        temp = *end;
        *end = *str;
        *str = temp;
        end--;
        str++;
    }
}
