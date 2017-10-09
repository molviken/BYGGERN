/*
 * MCPkontroll.c
 *
 * Created: 02.10.2017 11:43:29
 *  Author: arefv
 */ 
#include "MCPkontroll.h"
#include "MCP2515.h"

void MCP_init(){
	SPI_MasterInit();
	MCP_reset();
}

void MCP_write(uint8_t data, uint8_t address){
	clear_bit(PORTB, PB4);
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	set_bit(PORTB,PB4);
}

uint8_t MCP_read(uint8_t address){
	clear_bit(PORTB, PB4);
	SPI_MasterTransmit(MCP_READ);
	SPI_MasterTransmit(address);
	set_bit(PORTB,PB4);
	return SPI_MasterReceive();
}

void MCP_rts(uint8_t reg){
	clear_bit(PORTB, PB4);
	SPI_MasterTransmit(MCP_RTS + reg);
	set_bit(PORTB,PB4);	
}

uint8_t MCP_read_status(){
	clear_bit(PORTB, PB4);
	SPI_MasterTransmit(MCP_READ_STATUS);
	set_bit(PORTB,PB4);	
	return SPI_MasterReceive();
}

void MCP_bit_mod(uint8_t address, uint8_t m_byte, uint8_t d_byte){
	clear_bit(PORTB, PB4);
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(m_byte);
	SPI_MasterTransmit(d_byte);
	set_bit(PORTB,PB4);	
}

void MCP_reset(){
	clear_bit(PORTB, PB4);
	SPI_MasterTransmit(MCP_RESET);
}