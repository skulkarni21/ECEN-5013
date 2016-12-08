#include "I2C.h"

void i2c_init(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;	//Set clock for portb
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;	//set clock for I2c module

	PORTC_PCR8 |= PORT_PCR_MUX(2);		//Select alternate function for portb pin 0
	PORTC_PCR9 |= PORT_PCR_MUX(2);		//select alternate funtion for portb pin 1

	I2C0_C1 = 0;						//Turn off I2C
	I2C0_S |= I2C_S_IICIF_MASK;			//clear interrupt flag
	I2C0_F |= I2C_F_ICR(0x14);			//Divide bus clock of 24Mhz with 64 to get 375Khz
	I2C0_C1 |= I2C_C1_IICEN_MASK;		//enable I2C
}

void i2c_writeByte(uint8_t slave_addr,uint8_t mem_addr,uint8_t data){
	//while(I2C0_S & I2C_S_BUSY_MASK);//wait until bus is busy

	I2C0_C1 |= I2C_C1_TX_MASK;	//Set the direction of tranfer
	I2C0_C1 |= I2C_C1_MST_MASK;	//start I2C in master mode

	I2C0_D = slave_addr << 1;		//Start I2C data transfer for address
	while((I2C0_S & I2C_S_TCF_MASK)==0);
	while(!(I2C0_S & I2C_S_RXAK_MASK)==0);
	while((I2C0_S & I2C_S_IICIF_MASK)==0); //wait for transfer to complete
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_D = mem_addr;		//Start I2C data transfer for address
	while((I2C0_S & I2C_S_TCF_MASK)==0);
	while(!(I2C0_S & I2C_S_RXAK_MASK)==0);
	while((I2C0_S & I2C_S_IICIF_MASK)==0); //wait for transfer to complete
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_D = data;		//Start I2C data transfer for address
	while((I2C0_S & I2C_S_TCF_MASK)==0);
	while(!(I2C0_S & I2C_S_RXAK_MASK)==0);
	while((I2C0_S & I2C_S_IICIF_MASK)==0); //wait for transfer to complete
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_C1 &= ~I2C_C1_MST_MASK;
	I2C0_C1 &= ~I2C_C1_TX_MASK; 	//stop the I2C transfer

	i2c_delay(50);
}

uint8_t i2c_readByte(uint8_t slave_addr,uint8_t mem_addr){
	unsigned char dummy;
	uint8_t data;
	//while(I2C0_S & I2C_S_BUSY_MASK);//wait until bus is busy

	I2C0_C1 |= I2C_C1_TX_MASK;	//Set the direction of transfer
	I2C0_C1 |= I2C_C1_MST_MASK;	//start I2C in master mode

	I2C0_D = slave_addr << 1;		//Start I2C data transfer for address
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_D = mem_addr;		//send memory address
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_C1 |= I2C_C1_RSTA_MASK;	//send repeat start

	I2C0_D = (slave_addr<<1)|0x01;		//Start I2C data transfer for address in read mode
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_C1 &= ~(I2C_C1_TX_MASK);	//enter reciever mode
	I2C0_C1 |= I2C_C1_TXAK_MASK;		//disable ack

	dummy = I2C0_D;			//read dummy byte to initiate transfer
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_C1 &= ~I2C_C1_MST_MASK;
	I2C0_C1 &= ~I2C_C1_TX_MASK;		//i2c stop condition

	data = I2C0_D;				//read the data
	i2c_delay(50);
	return data;
}

void i2c_read_multi(uint8_t slave_addr,uint8_t cmd,uint8_t* var, uint8_t number){
	unsigned char dummy;
	uint32_t i;

	I2C0_C1 |= I2C_C1_TX_MASK;	//Set the direction of transfer
	I2C0_C1 |= I2C_C1_MST_MASK;	//start I2C in master mode

	I2C0_D = slave_addr << 1;		//Start I2C data transfer for address
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_D = cmd;		//send memory address
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	for(i=0;i<10000000;i++);			//wait for some time
	I2C0_C1 |= I2C_C1_RSTA_MASK;	//send repeat start

	I2C0_D = (slave_addr<<1)|0x01;		//Start I2C data transfer for address in read mode
	while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
	while((I2C0_S & I2C_S_IICIF_MASK)==0);
	I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

	I2C0_C1 &= ~(I2C_C1_TX_MASK);	//enter reciever mode
	if(number == 1)
		I2C0_C1 |= I2C_C1_TXAK_MASK;		//disable ack
	dummy = I2C0_D;			//read dummy byte to initiate transfer

	while(number > 0){
		if(number == 1)
			I2C0_C1 |= I2C_C1_TXAK_MASK;		//disable ack
		while((I2C0_S & I2C_S_TCF_MASK)==0); //wait for transfer to complete
		while((I2C0_S & I2C_S_IICIF_MASK)==0);
		I2C0_S |= I2C_S_IICIF_MASK;		//clear interrupt flag

		if(number ==1){
			I2C0_C1 &= ~I2C_C1_MST_MASK;
			I2C0_C1 &= ~I2C_C1_TX_MASK; 	//stop the I2C transfer
		}
		*var++=I2C0_D;
		number --;

	}
}

void i2c_delay(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		__asm("nop");
	};
}
