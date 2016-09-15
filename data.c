#include <stdio.h>
#include "data.h"


int main()
{
    char a[10] = "100";
    int value = my_atoi(a);
    printf("Value = %d\n", value);
    return 0;
}
