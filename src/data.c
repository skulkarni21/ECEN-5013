#include <stdio.h>
#include "data.h"

char *my_itoa(int val, char *buf, unsigned radix)
{
    char   *p;
    char   *firstdig;
    char   temp;
    unsigned   digval;
    p = buf;

    if(val <0)
    {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }

    firstdig = p;

    do{
        digval = (unsigned)(val % radix);
        val /= radix;

        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a');
        else
            *p++ = (char)(digval + '0');
    }while(val > 0);

    *p-- = '\0';
    do{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;
    }while(firstdig < p);
    return buf;
}



static int my_atoi(const char* str)
{
    int result = 0;
    int sign = 0;

    // whitespace characters
    while (*str==' ' || *str=='\t' || *str=='\n')
        ++str;

    //sign character
    if (*str=='-')
    {
        sign = 1;
        ++str;
    }
    else if (*str=='+')
    {
        ++str;
    }

    //numbers
    while (*str>='0' && *str<='9')
    {
        result = result*10 + *str - '0';
        ++str;
    }

    // return result
    if (sign==1)
        return -result;
    else
        return result;
}

void dump_memory (void *start, int length) {
    int i;
    unsigned char *pc = (unsigned char*)start;
    unsigned char buff[17];

    // Process every byte in the data.
    for (i = 0; i < length; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

}


int endian_conveter(int data)
{
    data = ((data & 0x000000FF) << 24) |
    ((data & 0x0000FF00) <<  8) |
    ((data & 0x00FF0000) >>  8) |
    ((data & 0xFF000000) >> 24);
    return data;
}

