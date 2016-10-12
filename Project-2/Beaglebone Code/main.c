#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memory.c"
#include "conversion.c"

//BBB's default clock rate (clock frequency) is 100KHz

#include<sys/time.h>
#include<unistd.h>

int main( void )
{
    struct timeval start_memmove,  start_my_memmove, start_memset, start_my_memzero, start_my_reverse, start_my_itoa, start_my_ftoa, start_my_atoi, finish_memmove, finish_my_memmove, finish_memset, finish_my_memzero, finish_my_reverse, finish_my_itoa, finish_my_ftoa, finish_my_atoi;

    //Define the test size for memory file
    uint8_t dest[5000] ;
    uint8_t src[5000] ;
    
    //Define the size for itoa function
    int32_t base=10;
    uint8_t oput[5000];
    uint32_t itoa_test = 1234567;
    
    //Define the test for ftoa function
    uint8_t a[5000]={};
    uint8_t *p=&a;
    float ftoa_test = 123456.54321;

    //execution times of memmove
    gettimeofday(&start_memmove, NULL);
    my_memmove(&dest[10],&src[500],1000);
    gettimeofday(&finish_memmove, NULL);
    uint16_t duration_memmove = finish_memmove.tv_usec - start_memmove.tv_usec;
    
    //execution times of my_memmove
    gettimeofday(&start_my_memmove, NULL);
    my_memmove(&dest[10],&src[500],1000);
    gettimeofday(&finish_my_memmove, NULL);
    uint16_t duration_my_memmove = finish_my_memmove.tv_usec - start_my_memmove.tv_usec;
    
    //execution times of memset
    gettimeofday(&start_memset, NULL);
    memset(src,'0',1000);
    gettimeofday(&finish_memset, NULL);
    uint16_t duration_memset = finish_memset.tv_usec - start_memset.tv_usec;
    
    //execution times of my_memzero
    gettimeofday(&start_my_memzero, NULL);
    my_memzero(&src[0],1000);
    gettimeofday(&finish_my_memzero, NULL);
    uint16_t duration_my_memzero = finish_my_memzero.tv_usec - start_my_memzero.tv_usec;
    
    //execution times of my_reverse
    gettimeofday(&start_my_reverse, NULL);
    my_reverse(&src[0],1000);
    gettimeofday(&finish_my_reverse, NULL);
    uint16_t duration_my_reverse = finish_my_reverse.tv_usec - start_my_reverse.tv_usec;
    
    //execution times of my_itoa
    gettimeofday(&start_my_itoa, NULL);
    my_itoa(oput,itoa_test,base);
    gettimeofday(&finish_my_itoa, NULL);
    uint16_t duration_my_itoa = finish_my_itoa.tv_usec - start_my_itoa.tv_usec;
    
    //execution times of my_ftoa
    gettimeofday(&start_my_ftoa, NULL);
    my_ftoa (p,ftoa_test);
    gettimeofday(&finish_my_ftoa, NULL);
    uint16_t duration_my_ftoa = finish_my_ftoa.tv_usec - start_my_ftoa.tv_usec;
    
    //execution times of my_atoi
    gettimeofday(&start_my_atoi, NULL);
    my_atoi(oput);
    gettimeofday(&finish_my_atoi, NULL);
    uint16_t duration_my_atoi = finish_my_atoi.tv_usec - start_my_atoi.tv_usec;
    
    //print result
    printf( "--------Exectution time for memory file--------\n");
    printf( "The execution time for memmove is : %f seconds\n", (double)duration_memmove/ CLOCKS_PER_SEC);
    printf( "The execution time for my_memmove is : %f seconds\n", (double)duration_my_memmove/ CLOCKS_PER_SEC);
    printf( "The execution time for memset is : %f seconds\n", (double)duration_memset/ CLOCKS_PER_SEC);
    printf( "The execution time for my_memzero is : %f seconds\n", (double)duration_my_memzero/ CLOCKS_PER_SEC);
    printf( "The execution time for my_reverse is : %f seconds\n\n", (double)duration_my_reverse/ CLOCKS_PER_SEC);
    
    printf( "--------Exectution time for data file--------\n");
    printf( "The execution time for my_itoa is : %f seconds\n", (double)duration_my_itoa/ CLOCKS_PER_SEC);
    printf( "The execution time for my_ftoa is : %f seconds\n", (double)duration_my_ftoa/ CLOCKS_PER_SEC);
    printf( "The execution time for my_atoi is : %f seconds\n", (double)duration_my_atoi/ CLOCKS_PER_SEC);
  
    return (0);
    
}

/* below can't run on BBB
int main( void )
{
    //Define the clock start time
    clock_t start_memmove,  start_my_memmove, start_memset, start_my_memzero, start_my_reverse ;
    clock_t start_my_itoa, start_my_ftoa, start_my_atoi;
    
    //Define the clock finish time
    clock_t finish_memmove, finish_my_memmove, finish_memset, finish_my_memzero, finish_my_reverse;
    clock_t finish_my_itoa, finish_my_ftoa, finish_my_atoi;
    
    //Define the duration
    double   duration_memmove, duration_my_memmove, duration_memset, duration_my_memzero, duration_my_reverse;
    double duration_my_itoa, duration_my_ftoa, duration_my_atoi;
    
    //Define the test size for memory file
    uint8_t dest[5000] ;
    uint8_t src[5000] ;
    
    //Define the size for itoa function
    int32_t base=10;
    uint8_t oput[5000];
    uint32_t itoa_test = 1234567;

    //Define the test for ftoa function
    uint8_t a[5000]={};
    uint8_t *p=&a;
    float ftoa_test = 123456.54321;

    //Define the test for atoi function
    uint8_t str[5000];
    
    //execution times of memmove
    start_memmove = clock();
    memmove(dest, src, 1000);
    finish_memmove = clock();
    duration_memmove = (double)(finish_memmove - start_memmove) / CLOCKS_PER_SEC;

    //execution times of my_memmove
    start_my_memmove = clock();
    my_memmove(&dest[10],&src[500],1000);
    finish_my_memmove = clock();
    duration_my_memmove = (double)(finish_my_memmove - start_my_memmove) / CLOCKS_PER_SEC;

    //execution times of memset
    start_memset = clock();
    memset(src,'0',1000);
    finish_memset = clock();
    duration_memset = (double)(finish_memset - start_memset) / CLOCKS_PER_SEC;

    //execution times of my_memzero
    start_my_memzero = clock();
    my_memzero(&src[0],1000);
    finish_my_memzero = clock();
    duration_my_memzero = (double)(finish_my_memzero - start_my_memzero) / CLOCKS_PER_SEC;

    //execution times of my_reverse
    start_my_reverse = clock();
    my_reverse(&src[0],1000);
    finish_my_reverse = clock();
    duration_my_reverse = (double)(finish_my_reverse - start_my_reverse) / CLOCKS_PER_SEC;
    
    //execution times of my_itoa
    start_my_itoa = clock();
    my_itoa(oput,itoa_test,base);
    finish_my_itoa = clock();
    duration_my_itoa = (double)(finish_my_itoa - start_my_itoa) / CLOCKS_PER_SEC;
    
    //execution times of my_ftoa
    start_my_ftoa = clock();
    my_ftoa (p,ftoa_test);
    finish_my_ftoa = clock();
    duration_my_ftoa = (double)(finish_my_ftoa - start_my_ftoa) / CLOCKS_PER_SEC;
    
    //execution times of my_atoi
    start_my_atoi = clock();
    my_atoi(oput);
    finish_my_atoi = clock();
    duration_my_atoi = (double)(finish_my_atoi - start_my_atoi) / CLOCKS_PER_SEC;

    //print result
    printf( "--------Exectution time for memory file--------\n");
    printf( "The execution time for memmove is : %f seconds\n", duration_memmove);
    printf( "The execution time for my_memmove is : %f seconds\n", duration_my_memmove);
    printf( "The execution time for memset is : %f seconds\n", duration_memset);
    printf( "The execution time for my_memzero is : %f seconds\n", duration_my_memzero);
    printf( "The execution time for my_reverse is : %f seconds\n\n", duration_my_reverse);
    
    printf( "--------Exectution time for data file--------\n");
    printf( "The execution time for my_itoa is : %f seconds\n", duration_my_itoa);
    printf( "The execution time for my_ftoa is : %f seconds\n", duration_my_ftoa);
    printf( "The execution time for my_atoi is : %f seconds\n", duration_my_atoi);
 
    return(0);
    
}*/