/***************************************************************************
 *
 *  	Filename: test_buff.c
 *      Description:	This file contains the code for all the unit tests of
 *      				circular buffer
 *
 *      Author: Sarang Kulkarni
 *
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"
#include "UART.h"

state test_empty(CircBuff_t *buff){
	uint8_t value,status;

	empty_buff(buff);

	status = remove_item(buff,&value);
	if(status == EMPTY){
		return SUCCESS;
	}
	else
		return FAIL;
}

state test_full(CircBuff_t *buff){
	uint8_t result, i=1;
	fill_buff(buff);
	result = add_item(buff, i);
	if(result == FULL)
		return SUCCESS;
	else
		return FAIL;
}

state test_warp(CircBuff_t *buff){
	uint8_t result;

	fill_buff(buff);
	if(buff ->tail != buff->head)
		return FAIL;

	empty_buff(buff);

	if(buff ->tail != buff->head)
		return FAIL;

	return SUCCESS;
}

state test_all_param(CircBuff_t *buff){
	if((test_empty(buff)== SUCCESS))
			write_string("Write test pass(1/5) \n Read test pass(2/5)\n Empty test pass(3/5)");
	else
		write_string("Write test fail \n Read test fail \n Empty test fail");
	if((test_full(buff)== SUCCESS))
		write_string("\nfull test pass(4/5)");
	else
		write_string("\nfull test fail");
	if((test_warp(buff)) == SUCCESS){
		write_string("\nWarp test pass(5/5)");
		return SUCCESS;
	}
	return FAIL;
}
