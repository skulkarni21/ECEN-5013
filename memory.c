#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    char dest[] = "abc";
    char src[]  = "def";
    memmove(src, dest, 3);
    printf("After memmove, dest = %s, src = %sn", dest, src);
    
    return 0;
}

