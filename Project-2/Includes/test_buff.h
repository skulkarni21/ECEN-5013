#ifndef TEST_BUFF
#define TEST_BUFF

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"

state test_empty(CircBuff_t *buff);
state test_full(CircBuff_t *buff);
state test_warp(CircBuff_t *buff);
state test_all_param(CircBuff_t *buff);

#endif
