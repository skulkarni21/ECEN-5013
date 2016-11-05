#ifndef MAIN_H
#define MAIN_H

#include "MKL25Z4.h"
//#include <malloc.h>
#include "circbuff.h"
#include "UART.h"
#include "LED.h"
//#include "test_buff.h"
#include "conversion.h"
#include "timer.h"
#include "profile_test.h"
#include "log.h"
#include "DMA.h"


#define FRDM
#define CLOCK_STATE 1 //set clock at 48Mhz and bus at 24Mhz

//Compile time flag for different boards
#ifdef FRDM

#define write_string(x) log0(x)
#define log3(x,y) log3(x,y)

#endif

#ifdef BBB

#define write_string(x) printf(x)
#define log3(x,y) printf(x,y)

#endif

#endif
