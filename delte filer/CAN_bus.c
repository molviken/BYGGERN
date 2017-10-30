/*
 * CAN_bus.c
 *
 * Created: 02.10.2017 13:38:20
 *  Author: arefv
 */ 
#include "CAN_bus.h"
#include "MCP2515.h"
#include "MCPkontroll.h"

uint8_t rx_flag = 0;

void CAN_init(){
	MCP_init();
	// Turn mask/filters off
	MCP_bit_mod(MCP_RXB0CTRL, 0b01100100, 0xFF);
	
	// Set LoopBack mode on
	MCP_bit_mod(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK); // MCP_CANCTRL = MODE_LOOPBACK;
	
	// Enable interrupt when a valid message has been received
	MCP_bit_mod(MCP_CANINTE, MCP_RX0IF, 1);
	if ((MCP_read(MCP_CANSTAT) & MODE_MASK) != MODE_LOOPBACK)
	{
		printf("NOT in loopback mode!\n");
	}
	
	char temp = MCP_read(MCP_CANCTRL);
	
}

int CAN_transmit(struct CAN_message message){
	if (CAN_completed_transmit()){
		
		// Setting the standard identifier
		MCP_write(message.id >> 3, MCP_TXB0SIDH);
		MCP_write(message.id << 5, MCP_TXB0SIDL);
		
		// setting data length
		MCP_write((0x0F) & message.length, MCP_TXB0DLC);
		
		// setting data bytes
		for (uint8_t i = 0x00; i< message.length; i++){
			MCP_write(message.data[i], MCP_TXB0D0+i);
		}
		MCP_rts(1);
	}
	else{
		if(CAN_check_error()<0){return -1;}
	}
	return 0;
}

int CAN_check_error(void){
	uint8_t error = MCP_read(MCP_TXB0CTRL);
	// Checking transmission error
	if(test_bit(error,4)){return -1;}
		
	// checking for message lost arbitration
	if(test_bit(error,5)){return -2;}
	else{return 1;}
}

int CAN_completed_transmit(void){
	if (test_bit(MCP_read(MCP_TXB0CTRL),3)){
		return 0;
	}
	else{
		return 1;
	}
}

void CAN_int_vect(void){
	// clear interrupt flag in buffer 0
	MCP_bit_mod(MCP_CANINTF, 0x01, 0);
	rx_flag = 1;
}

struct CAN_message CAN_receive(void){
	struct CAN_message new_message;
	MCP_read(MCP_RXB0SIDL) >> 5;
	MCP_read(MCP_RXB0SIDH) << 3;
	if(MCP_RX0IF == 1){
		// writing the 8 bits we want from IDH and IDL
		new_message.id = MCP_read(MCP_RXB0SIDL) >> 5;
		new_message.id |= MCP_read(MCP_RXB0SIDH) << 3;
		// Get the length (only last 4 bits)
		new_message.length = MCP_read(0x65);
		
		// Get the required data from RXB0DM
		for(uint8_t i = 0; i < new_message.length; i++){
			new_message.data[i] = MCP_read(MCP_RXB0D0 + i);
		}

	}
	else{
		// message not received
		new_message.id = -1;
	}
	return new_message;
}

// Interrupt service
ISR(INT0_vect){
	_delay_ms(10);
	CAN_int_vect();
}