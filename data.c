#include <stdio.h>
#include "data.h"

int main()
{
    
    //Test code for my_atoi
    char test_atoi[10] = "100";
    int value = my_atoi(test_atoi);
    printf("(atoi) Value = %d\n", value);
    
    //Test code for my_itoa
    int test_itoa = 10;
    char buffer[20];
    my_itoa(test_itoa,buffer,2);   // here 2 means binary
    printf("(itoa) Binary Value = %s\n", buffer);
    
    my_itoa(test_itoa,buffer,10);   // here 10 means decimal
    printf("(itoa) Decimal Value = %s\n", buffer);
    
    my_itoa(test_itoa,buffer,16);   // here 16 means Hexadecimal
    printf("(itoa) Hexadecimal Value = %s\n", buffer);
    return 0;
    
    
}
