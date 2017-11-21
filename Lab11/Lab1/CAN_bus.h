/*
 * CAN_bus.h
 *
 * Created: 02.10.2017 13:38:30
 *  Author: arefv
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

struct CAN_message{
	uint8_t id;
	uint8_t length;
	uint8_t data[8]; 
	};

void CAN_init(void);
int CAN_transmit(struct CAN_message message);
int CAN_check_error(void);
int CAN_completed_transmit(void);
void CAN_int_vect(void);
struct CAN_message CAN_receive(void);
int start_game(int mode, int opt);
