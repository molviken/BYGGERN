/*
 * MCPkontroll.h
 *
 * Created: 02.10.2017 11:43:42
 *  Author: arefv
 */ 

void MCP_init();
void MCP_write(uint8_t data, uint8_t address);
void MCP_read(uint8_t address);
void MCP_rts(uint8_t reg);
uint8_t MCP_read_status();
void MCP_bit_mod(uint8_t address, uint8_t m_byte, uint8_t d_byte);
void MCP_reset();