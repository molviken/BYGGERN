
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "uart.h"
#include "menu_system.h"
#include "Eeprom.h"

volatile char* oled_adresse = 0x1200;
volatile char* adc_adresse = 0x1400;
volatile char* ram_adresse = 0x1800;



int main(void)
{
	DDRB = 0b00000000;

	EXT_MEM_Init();
	USART_Init(31);				
	oled_init();
	oled_reset();
	adc_init();
	CAN_init();
	printf("Init er good\n");
	
	oled_reset();
	
	MENU *main_menu = menu_create();
	printf("reseted\n");
	
	while(1)
    {
		main_menu = menu_nav(main_menu);	
	}
}