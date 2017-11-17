/*
 * dac.c
 *
 * Created: 13.11.2017 10:46:02
 *  Author: oystmol
 */ 
#include "dac.h"
#include "TWI_Master.h"
#define SLAVE_ADDRESS_WRITE 0x50;
// 


void dac_write(uint8_t value)
{
	
	unsigned char msgSize = 3;
	unsigned char i2c_write[3];
	
	i2c_write[0] = SLAVE_ADDRESS_WRITE;
	i2c_write[1] = 0x00;
	i2c_write[2] = (uint8_t) value;
	_delay_us(50);
	
	TWI_Start_Transceiver_With_Data(i2c_write, msgSize);
	//printf("slutten av dac_write\n");
}

