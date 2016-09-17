#include <stdio.h>
#include "memory.h"

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
    
    return 0;
}
