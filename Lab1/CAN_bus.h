/*
 * CAN_bus.h
 *
 * Created: 02.10.2017 13:38:30
 *  Author: arefv
 */ 

struct CAN_message{
	int id;
	uint8_t length;
	int8_t data[8]; 
	};

void CAN_init();
void CAN_transmit(struct CAN_message message);