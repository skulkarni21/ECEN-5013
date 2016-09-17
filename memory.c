#include <stdio.h>
#include "memory.h"

#define MAXSIZE 100000

int main(int argc, const char * argv[]) {
    
    //Test for memmove
    char dest[] = "newstring";
    char src[]  = "oldstring";
    memmove(src, dest, 9);
    printf("(memmove) dest = %s, src = %s\n", dest, src);
    
    
    //Test for my_reverse
    char string[] = "foobar";
    my_reverse(string);
    printf("(my_reverse) %s\n", string);
    
    
    //Test for my_memzero
    char arr[MAXSIZE];
    for(int i=0;i<3;i++)
    {
        my_memzero(arr,'0',sizeof(arr));
    }

    return 0;
}
