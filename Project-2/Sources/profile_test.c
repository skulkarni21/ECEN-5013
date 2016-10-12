/***************************************************************************
 *
 *  	Filename: profile_test.c
 *      Description:  This file is for profiling of the code using timers.
 *
 *      Author: Sarang Kulkarni
 *
 ****************************************************************************/

#include "profile_test.h"

#define MEM1000

void profile_tests(void){
	uint32_t stop_time;
	uint8_t source[10]="0123456789", dest[10],i;
	uint8_t source1[100], dest1[100];
	uint8_t source2[1000]="1", dest2[1000];
	uint8_t source3[5000]="1", dest3[5000];
/*-----------------------------------For 10 bytes-------------------------------------------*/
#ifdef MEM10
	start_timer();
	my_memmove(source,dest,10);
	stop_time =stop_timer();
	log3("\nTime for my_memmove(10 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memmove(source,dest,10);
	stop_time =stop_timer();
	log3("\nTime for memmove(10 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_memzero(dest,10);
	stop_time =stop_timer();
	log3("\n\nTime for my_memzero(10 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memset(dest,0,10);
	stop_time =stop_timer();
	log3("\nTime for memset(10 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_reverse(source,10);
	stop_time =stop_timer();
	log3("\n\nTime for my_reverse(10 chars) = ",stop_time);
	write_string("uSec");
#endif

/*----------------------------------For 100 bytes ------------------------------------------*/

#ifdef MEM100
	for(i=0; i<100; i++)
		*(source1+i)=i;

	start_timer();
	my_memmove(source1,dest1,100);
	stop_time =stop_timer();
	log3("\n\nTime for my_memmove(100 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memmove(source1,dest1,100);
	stop_time =stop_timer();
	log3("\nTime for my_memmove(100 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_memzero(dest1,100);
	stop_time =stop_timer();
	log3("\n\nTime for my_memzero(100 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memset(dest1,0,100);
	stop_time =stop_timer();
	log3("\nTime for memset(100 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_reverse(source1,100);
	stop_time =stop_timer();
	log3("\nTime for my_reverse(100 chars) = ",stop_time);
	write_string("uSec");
#endif
/*----------------------------------For 1000 bytes ------------------------------------------*/

#ifdef MEM1000

	start_timer();
	memmove(source2,dest2,1000);
	stop_time =stop_timer();
	log3("\nTime for memmove(1000 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_memzero(dest2,1000);
	stop_time =stop_timer();
	log3("\n\nTime for my_memzero(1000 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memset(dest2,0,1000);
	stop_time =stop_timer();
	log3("\nTime for memset(1000 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_reverse(source2,1000);
	stop_time =stop_timer();
	log3("\n\nTime for my_reverse(1000 chars) = ",stop_time);
	write_string("uSec");
#endif

/*----------------------------------For 5000 bytes ------------------------------------------*/
#ifdef MEM5000

	start_timer();
	my_memmove(source3,dest3,5000);
	stop_time =stop_timer();
	log3("\n\nTime for my_memmove(100 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memmove(source3,dest3,5000);
	stop_time =stop_timer();
	log3("\nTime for memmove(5000 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_memzero(dest3,5000);
	stop_time =stop_timer();
	log3("\n\nTime for my_memzero(1000 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	memset(dest3,0,5000);
	stop_time =stop_timer();
	log3("\nTime for memset(5000 chars) = ",stop_time);
	write_string("uSec");

	start_timer();
	my_reverse(source3,5000);
	stop_time =stop_timer();
	log3("\n\nTime for my_reverse(5000 chars) = ",stop_time);
	write_string("uSec");
#endif

}

void profile_test_2(void){
	uint8_t* ptr;
	uint8_t a=20;
	uint32_t stop_time;
	CircBuff_t test_buff;

#ifdef MALLOC_TEST
	start_timer();
	ptr= (uint8_t*)malloc(10);
	stop_time =stop_timer();
	log3("\nTime for malloc(10 chars)",stop_time);
	write_string("uSec");

	start_timer();
	free(ptr);
	stop_time =stop_timer();
	log3("\nTime for free(10 chars)",stop_time);
	write_string("uSec");

	start_timer();
	ptr= (uint8_t*)malloc(100);
	stop_time =stop_timer();
	log3("\nTime for malloc(100 chars)",stop_time);
	write_string("uSec");

	start_timer();
	free(ptr);
	stop_time =stop_timer();
	log3("\nTime for free(100 chars)",stop_time);
	write_string("uSec");

	start_timer();
	ptr= (uint8_t*)malloc(500);
	stop_time =stop_timer();
	log3("\nTime for malloc(500 chars)",stop_time);
	write_string("uSec");

	start_timer();
	free(ptr);
	stop_time =stop_timer();
	log3("\nTime for free(500 chars)",stop_time);
	write_string("uSec");

	start_timer();
	ptr= (uint8_t*)malloc(1000);
	stop_time =stop_timer();
	log3("\nTime for malloc(1000 chars)",stop_time);
	write_string("uSec");

	start_timer();
	free(ptr);
	stop_time =stop_timer();
	log3("\nTime for free(1000 chars)",stop_time);
	write_string("uSec");
#endif


	init_buff(&test_buff,10);

	start_timer();
	add_item(&test_buff,'s');
	stop_time =stop_timer();
	log3("\nTime for adding item to buffer",stop_time);
	write_string("uSec");

	start_timer();
	remove_item(&test_buff,ptr);
	stop_time =stop_timer();
	log3("\nTime for removing item from buffer",stop_time);
	write_string("uSec");

	start_timer();
	write_string("\nThis is test for log function\n");
	stop_time =stop_timer();
	log3("\nTime for log is",stop_time);
	write_string("uSec");

	start_timer();
	my_itoa(ptr,a,10);
	stop_time =stop_timer();
	log3("\nTime for itoa is ",stop_time);
	write_string("uSec");

	start_timer();
	my_atoi(ptr);
	stop_time =stop_timer();
	log3("\nTime for adding item to buffer",stop_time);
	write_string("uSec");

}
