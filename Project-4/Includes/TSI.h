#ifndef TSI
#define TSI
#include "MKL25Z4.h"

void tsi_init(void);
uint16_t read_tsi(void);
void start_scan(void);
void stop_scan(void);
uint16_t scan_touch(void);

#endif
