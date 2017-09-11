#define set_bit( reg, bit ) (reg |= (1 << bit));
#define clear_bit( reg, bit ) (reg &= ~(1 << bit));
#define test_bit( reg, bit ) (reg & (1 << bit));
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) );
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) );

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

void EXT_MEM_Init(void);
void SRAM_test(void);