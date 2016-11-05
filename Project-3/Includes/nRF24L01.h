#include "MKL25Z4.h"

/* Memory Map */
#define NRF_CONFIG      0x00
#define NRF_EN_AA       0x01
#define NRF_EN_RXADDR   0x02
#define NRF_SETUP_AW    0x03
#define NRF_SETUP_RETR  0x04
#define NRF_RF_CH       0x05
#define NRF_RF_SETUP    0x06
#define NRF_STATUS      0x07
#define NRF_OBSERVE_TX  0x08
#define NRF_CD          0x09
#define NRF_RX_ADDR_P0  0x0A
#define NRF_RX_ADDR_P1  0x0B
#define NRF_RX_ADDR_P2  0x0C
#define NRF_RX_ADDR_P3  0x0D
#define NRF_RX_ADDR_P4  0x0E
#define NRF_RX_ADDR_P5  0x0F
#define NRF_TX_ADDR     0x10
#define NRF_RX_PW_P0    0x11
#define NRF_RX_PW_P1    0x12
#define NRF_RX_PW_P2    0x13
#define NRF_RX_PW_P3    0x14
#define NRF_RX_PW_P4    0x15
#define NRF_RX_PW_P5    0x16
#define NRF_FIFO_STATUS 0x17
#define NRF_DYNPD	      0x1C
#define NRF_FEATURE	    0x1D

/* Bit Mnemonics */
#define NRF_MASK_RX_DR  6
#define NRF_MASK_TX_DS  5
#define NRF_MASK_MAX_RT 4
#define NRF_EN_CRC      3
#define NRF_CRCO        2
#define NRF_PWR_UP      1
#define NRF_PRIM_RX     0
#define NRF_ENAA_P5     5
#define NRF_ENAA_P4     4
#define NRF_ENAA_P3     3
#define NRF_ENAA_P2     2
#define NRF_ENAA_P1     1
#define NRF_ENAA_P0     0
#define NRF_ERX_P5      5
#define NRF_ERX_P4      4
#define NRF_ERX_P3      3
#define NRF_ERX_P2      2
#define NRF_ERX_P1      1
#define NRF_ERX_P0      0
#define NRF_AW          0
#define NRF_ARD         4
#define NRF_ARC         0
#define NRF_PLL_LOCK    4
#define NRF_RF_DR       3
#define NRF_RF_PWR      6
#define NRF_RX_DR       6
#define NRF_TX_DS       5
#define NRF_MAX_RT      4
#define NRF_RX_P_NO     1
#define NRF_TX_FULL     0
#define NRF_PLOS_CNT    4
#define NRF_ARC_CNT     0
#define NRF_TX_REUSE    6
#define NRF_FIFO_FULL   5
#define NRF_TX_EMPTY    4
#define NRF_RX_FULL     1
#define NRF_RX_EMPTY    0
#define NRF_DPL_P5	    5
#define NRF_DPL_P4	    4
#define NRF_DPL_P3	    3
#define NRF_DPL_P2	    2
#define NRF_DPL_P1	    1
#define NRF_DPL_P0	    0
#define NRF_EN_DPL	    2
#define NRF_EN_ACK_PAY  1
#define NRF_EN_DYN_ACK  0

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

/* Non-P omissions */
#define LNA_HCURR   0

/* P model memory Map */
#define RPD         0x09

/* P model bit Mnemonics */
#define RF_DR_LOW   5
#define RF_DR_HIGH  3
#define RF_PWR_LOW  1
#define RF_PWR_HIGH 2

/*Function Prototypes*/

void ce_low(void);
void ce_high(void);
uint8_t write_register(uint8_t reg,uint8_t value );
uint8_t read_register(uint8_t reg);
