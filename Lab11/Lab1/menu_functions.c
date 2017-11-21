/*
 * test_menu.c
 *
 * Created: 20.11.2017 13:06:12
 *  Author: arefv
 */ 
#include "menu_functions.h"
#include "menu_system.h"
#include "CAN_bus.h"
int menu_start_game(int mode, int opt){
	start_game(mode, opt);
}

int menu_print_HS(int mode, int opt){
	
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
