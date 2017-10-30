/*
 * MCPkontroll.c
 *
 * Created: 02.10.2017 11:43:29
 *  Author: arefv
 */ 
#include "MCPkontroll.h"
#include "MCP2515.h"
#define DD_SS PB7

void select_CAN(void){
	clear_bit(PORTB, DD_SS);
}

void deselect_CAN(void){
	set_bit(PORTB, DD_SS);
}

void MCP_init(){
	SPI_MasterInit();
	MCP_reset();
}

void MCP_write(uint8_t data, uint8_t address){
	// printf("MCP_write data = %x, address = %x \n", data, address);
	select_CAN();
	
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	deselect_CAN();
}

uint8_t MCP_read(uint8_t address){
	uint8_t temp;
	
	select_CAN();
	
	SPI_MasterTransmit(MCP_READ);
	SPI_MasterTransmit(address);
	temp = SPI_MasterReceive();
	deselect_CAN();
	// printf("I MCP_read, temp = %x, address = %x \n", temp, address);
	return temp;
}

void MCP_rts(uint8_t reg){
	if (reg <= 7)
	{reg = MCP_RTS | reg;
	}
	else{
		reg = MCP_RTS;
	}
	
	select_CAN();
	SPI_MasterTransmit(reg);
	deselect_CAN();	
}

uint8_t MCP_read_status(){
	select_CAN();
	SPI_MasterTransmit(MCP_READ_STATUS);
	deselect_CAN();
	return SPI_MasterReceive();
}

void MCP_bit_mod(uint8_t address, uint8_t m_byte, uint8_t d_byte){
	select_CAN();
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(m_byte);
	SPI_MasterTransmit(d_byte);
	deselect_CAN();
}

void MCP_reset(){
	select_CAN();
	SPI_MasterTransmit(MCP_RESET);
	deselect_CAN();
	uint8_t mode = MCP_read(MCP_CANSTAT);
	if ((mode&MODE_MASK)!=MODE_CONFIG)
	{
		printf("Not in config after reset\n");
	}
	
}