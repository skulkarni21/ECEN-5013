#ifndef memove_memove_h
#define memove_memove_h

#include <string.h>

//This would take two pointers (one source and one destination) and a length of bytes to move from one location to the other.
void memmov(int *src, int *dst, int length);

//This would take a pointer to a memory location and a length in bytes and zero out all of the memory.
void *(my_memzero) (void *src,int c,size_t length);

//This would take a pointer to a memory location and a length in bytes and reverse the order of all of the bytes.
void my_reverse(char* str);

#endif

