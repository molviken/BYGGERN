/*
 * tests.c
 *
 * Created: 16.10.2017 15:43:54
 *  Author: arefv
 */ 
#include "tests.h"

void test_MCP(void){
		// MCP Test
		
	uint8_t data = 0x55;		
	MCP_write(data, 0b00110110);
	uint8_t test = MCP_read(0b00110110);
	printf("data = %x, data lest = %x \n\n",data, test);
		
}

void test_CAN_bus(void){
	struct CAN_message first_message;
	first_message.id = 3;
	first_message.length = 1;
	first_message.data[0] = 0xff;
	int status = CAN_transmit(first_message);

	struct CAN_message copy_message;
	copy_message = CAN_receive();
	printf("first message id = %x, ", first_message.id);
	printf("copy message id = %x \n", copy_message.id);
	printf("first message data[0] = %x, ", first_message.data[0]);
	printf("copy message data[0} = %x \n", copy_message.data[0]);	
}

