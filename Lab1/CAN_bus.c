/*
 * CAN_bus.c
 *
 * Created: 02.10.2017 13:38:20
 *  Author: arefv
 */ 
#include "CAN_bus.h"
#include "MCP2515.h"
#include "MCPkontroll.h"
void CAN_init(){
	MCP_init();
	MCP_CANCTRL = MODE_LOOPBACK;
}

void CAN_transmit(struct CAN_message message){
	if (CAN_completed_transmit()){
		MCP_write(message.id >> 6,MCP_TXB0SIDH);
		MCP_write(message.id << 5,MCP_TXB0SIDL);
		MCP_write(message.length, MCP_TXB0DLC);
		for (uint8_t i = 0x00; i< message.length; i++){
			MCP_write(message.data[i], MCP_TXB0D0+i);
		}
		MCP_rts(1);
	}

}

int CAN_completed_transmit(){
	if (test_bit(MCP_read(TXB0CTRL),3)){
		return 0;
	}
	else{
		return 1;
	}
}