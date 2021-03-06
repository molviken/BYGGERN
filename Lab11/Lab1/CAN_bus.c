/*
 * CAN_bus.c
 *
 * Created: 02.10.2017 13:38:20
 *  Author: arefv
 */ 
#include <avr/io.h>
#include "bit_operations.h"
#include "CAN_bus.h"
#include "MCP2515.h"
#include "MCPkontroll.h"
#include "usb_board_inputs.h"
#include "adc.h"


uint8_t rx_flag = 0;

void CAN_init(){
	MCP_init();
	// Turn mask/filters off
	MCP_bit_mod(MCP_RXB0CTRL, 0b01100100, 0xFF);
	
	// Set LoopBack mode on
	MCP_bit_mod(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); // MCP_CANCTRL = MODE_LOOPBACK;
	
	// Enable interrupt when a valid message has been received
	MCP_bit_mod(MCP_CANINTE, MCP_RX0IF, 1);
	MCP_bit_mod(MCP_CANINTE, MCP_TX0IF, 1);
	if ((MCP_read(MCP_CANSTAT) & MODE_MASK) != MODE_NORMAL)
	{
		//printf("NOT in NORMAL mode!\n");
	}
	
	MCP_read(MCP_CANCTRL);
	
}

int CAN_transmit(struct CAN_message message){
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
	_delay_ms(1);
	
	if(!CAN_completed_transmit()){
		//printf("Transmit not completed, bit = %i \n",test_bit(MCP_TXB0CTRL,3));
		return CAN_check_error();
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
	if(test_bit(MCP_RX0IF,0) == 1){
		// writing the 8 bits we want from IDH and IDL
		new_message.id = MCP_read(MCP_RXB0SIDL) >> 5;
		new_message.id |= MCP_read(MCP_RXB0SIDH) << 3;
		// Get the length (only last 4 bits)
		new_message.length = MCP_read(0x65);
		
		// Get the required data from RXB0DM
		for(uint8_t i = 0; i < new_message.length; i++){
			new_message.data[i] = MCP_read(MCP_RXB0D0 + i);
		}
		MCP_bit_mod(MCP_CANINTF, 0xff, 0);

	}
	else{
		// message not received
		new_message.id = -1;
	}
	return new_message;
}

// Interrupt service
//ISR(INT0_vect){
	//CAN_int_vect();
//}
int start_game(int mode, int opt){
	struct CAN_message chosen_game;
	chosen_game.id = 10;
	chosen_game.length = 8;
	struct CAN_message game_over_check;
	int8_t game_mode = mode;
	int8_t controller_mode = opt;
	struct Joystick joy;
	struct Slider sli;
	
	if(game_mode == 1){
		switch(controller_mode){
			case 1:
			chosen_game.id = 10;
			break;
			
			case 2:
			chosen_game.id = 11;
			break;
		}
	}
	else if(game_mode == 2){
		switch(controller_mode){
			case 1:
			chosen_game.id = 14;
			break;

			case 2:
			chosen_game.id = 15;
			break;
		}
	}
	while(game_over_check.id != 1){
		game_over_check = CAN_receive();
		joy = read_joystick_position(channel1, channel2);
		sli = read_slider_position(channel3, channel4);
		chosen_game.data[0] = (uint8_t)joy.x_pos;
		chosen_game.data[3] = (uint8_t)sli.slider2;
		//printf("trans id: %d rec id: %d  \n",chosen_game.id, game_over_check.id);
		CAN_transmit(chosen_game);
		_delay_ms(10);
	}
	printf("%d\n", game_over_check.data[6]);
	save_highscore(game_over_check.data[6]);
}