#ifndef data_main_h
#define data_main_h

//Integer-to-asciI needs to convert data from a standard integer type into an ascii string.
char *my_itoa(int val, char *buf, unsigned radix);

//AsciI-to-Integer needs to convert data back from an ASCII represented string into an integer type.
static int my_atoi(const char* str);

//do the little endian and big endian transfer through byteswap (for uint_32)
int endian_conveter(int data);

#endif
