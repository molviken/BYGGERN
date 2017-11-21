/*
 * test_menu.c
 *
 * Created: 20.11.2017 13:06:12
 *  Author: arefv
 */ 
#define F_CPU 16000000
#include "menu_functions.h"
#include "menu_system.h"
#include "CAN_bus.h"
#include "joystick.h"
#include <util/delay.h>
int menu_start_game(int mode, int opt){
	start_game(mode, opt);
}

int menu_print_HS(int mode, int opt){
	 uint8_t array[5];
	 array[0] = EEPROM_read(0x01);
	 array[1] = EEPROM_read(0x02);
	 array[2] = EEPROM_read(0x03);
	 array[3] = EEPROM_read(0x04);
	 array[4] = EEPROM_read(0x05);
	 int n = 5;
	 uint8_t swap;
	 for (int c = 0 ; c < ( n - 1 ); c++)
	 {
		 for (int d = 0 ; d < n - c - 1; d++)
		 {
			 if (array[d] < array[d+1]) /* For decreasing order use < */
			 {
				 swap       = array[d];
				 array[d]   = array[d+1];
				 array[d+1] = swap;
			 }
		 }
	 }
		//oled_print_letter(array[0],0x01, 0x1c,0x25);
		//oled_print_letter(array[1],0x02, 0x1c,0x25);
		//oled_print_letter(array[2],0x03, 0x1c,0x25);
		//oled_print_letter(array[3],0x04, 0x1c,0x25);
		//oled_print_letter(array[4],0x05, 0x1c,0x25);
		//oled_print("ANYTHING",0x03,0x1c,0x25);
	// printf("test: %s \n",d);
	 for (int i = 0; i < 6; i++ )
	 { 
		//// oled_print_letter(i,i,0x09,0x11);
		 //oled_print_letter(array[i],i, 0x1c,0x25);
		printf("%i	 %d\n", i+1, array[i]);
	 }
	 int x = read_joystick_position(channel1,channel2).x_pos;
	 while (x>40){
		 //printf("WHY\n");
	 }
}

int menu_reset_HS(int mode, int opt){
	
}

int menu_choose_goalie_mode(int mode, int opt){
	return 2;
}

int menu_choose_survival_mode(int mode, int opt){
	return 1;
}

int menu_controller_joystick(int mode, int opt){
	return 2;
}

int menu_controller_slider(int mode, int opt){
	return 1;
}

int program_exit(int mode, int opt){
	exit(1);
}
