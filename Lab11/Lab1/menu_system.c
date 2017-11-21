/*
 * menu_system.c
 *
 * Created: 18.11.2017 17:00:49
 *  Author: arefv
 */ 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include "menu.h"
#include "menu_system.h"
#include "oled.h"
#include "joystick.h"
#include "menu_functions.h"
#include "CAN_bus.h"
//static MENU *current_menu;
struct Hashtag hashtag;
bool navy = false;
bool navx = false;
MENU* init_menu(char*title){
	MENU *main_menu = (MENU*)malloc(sizeof(MENU));
	
	if (main_menu == NULL){
		printf("Cant continue, memory full\n");
		exit(1);
	}
	
	main_menu->text = title;
	main_menu->parent = NULL;
	main_menu->sub = NULL;
	main_menu->over = NULL;
	main_menu->under = NULL;
	main_menu->sub_menus = 0;
	main_menu->goto_func = NULL;
	main_menu->page = 0x00;
	return main_menu;
	
}

MENU* menu_add_submenu(MENU *parent, void (*goto_func)(), char*text){
	MENU *menu = (MENU*)malloc(sizeof(MENU));
	
	menu->text = text;
	menu->parent = parent;
	menu->sub = NULL;
	menu->over = NULL;
	menu->under = NULL;
	menu->sub_menus = 0;
	menu->goto_func = goto_func;
	menu->page = 0x02;
	parent->sub = menu;
	parent->sub_menus +=1;
	return menu;
}

MENU* menu_add_node(MENU *over, MENU *under, void (*goto_func)(), char*text){
	MENU *node = (MENU*)malloc(sizeof(MENU));
	
	node->parent = over->parent;
	node->sub = NULL;
	node->over = over;
	over->under = node;
	node->under = under;
	node->text = text;
	node->page = over->page + 0x01;
	node->sub_menus = 0;
	node->goto_func = goto_func;
	return node;
}

//MENU* menu_change_sub(MENU *sub, int n){
	//MENU *current = (MENU*)malloc(sizeof(MENU));
	//
	//current = sub->sub;
	//
	//for(int i = 0; i<n; i++){
		//current = current->under;
	//}
	//return current;
//}
void menu_add_description(MENU* node, char* description, int line){
	switch(line){
		case 1:
			node->line1 = description;
			break;
		case 2:
			node->line2 = description;
			break;
		case 3:
			node->line3 = description;
			break;
		case 4:
			node->line4 = description;
			break;
		default:
			break;
	}
}

MENU* menu_create(){
	MENU *main_menu = init_menu("Main Menu");
	
	MENU *start_game = menu_add_node(NULL,NULL,menu_start_game,"Play");
	menu_add_description(start_game,"Joy mode!",1) ;
	menu_add_description(start_game,"Green",1) ;
	start_game->page = 0x02;

	// highscore nodes	
	MENU *highscore = menu_add_node(start_game,start_game,NULL,"Highscores");
	MENU *hs_print = menu_add_submenu(highscore,menu_print_HS,"Print");
	MENU *hs_reset = menu_add_node(hs_print,hs_print,menu_reset_HS, "Reset");
	
	// all option nodes		
	MENU *options = menu_add_node(highscore,highscore,NULL,"Options");
	MENU *option_modes = menu_add_submenu(options,NULL,"Modes");
	MENU *option_modes_goalie = menu_add_submenu(option_modes,menu_choose_goalie_mode,"Goalie");
	MENU *option_modes_survival = menu_add_node(option_modes_goalie,option_modes_goalie,menu_choose_survival_mode, "Survival");
	MENU *option_controller = menu_add_node(option_modes,option_modes,NULL,"Controller");
	MENU *option_controller_joystick = menu_add_submenu(option_controller,menu_controller_joystick,"Joystick");
	MENU *option_controller_slider = menu_add_node(option_controller_joystick,option_controller_joystick, menu_controller_slider,"Slider");
	MENU *exit_program = menu_add_node(options,NULL,program_exit,"Exit");
	options->parent = NULL;
	start_game->parent = NULL;
	highscore->parent = NULL;
	exit_program->parent = NULL;
	start_game->under = highscore;
	hs_reset->under = NULL;
	option_controller->under = NULL;
	main_menu->under = start_game;
	option_modes_survival->under = NULL;
	option_controller_slider->under = NULL;
	//Creating loopover for first element to last, skipping main menu
	//start_game->over = exit_program;
	exit_program->page = 0x06;
	//main_menu->over = exit_program;
	//option_modes->over = option_controller;
	//option_modes_goalie->over = option_modes_survival;
	//hs_print->over = hs_reset;
	//printf("sg:%d	hs:%d	hsp:%d	hsr:%d	opt:%d	optm:%d	 optmg:%d	optms:%d\n",
	//start_game->page,highscore->page,hs_print->page,hs_reset->page,options->page,option_modes->page,option_modes_goalie->page,option_modes_survival->page);
	// Print starting menu
	MENU *temp = main_menu;

	oled_print(main_menu->text,0x00,0x1c,0x25);
	oled_print(start_game->text,0x02,0x1c,0x25);
	oled_print(highscore->text,0x03,0x1c,0x25);
	oled_print(options->text,0x04,0x1c,0x25);
	oled_print(exit_program->text,0x06,0x1c,0x25);
	oled_print_letter('#',0x02,0x00,0x08);
	hashtag.moveY = 0;
	hashtag.moveX = 0;
	return main_menu;
}
// INN I HIGHSCORE / OPTIONS
MENU* menu_display(MENU* element, int x){
	printf("før.text    %s\n",element->text);
	if(x>200 && (element->text == "Highscores" || element->text == "Options")){
		switch(element->page){
			case 3:
				oled_print("Highscores",0x00,0x1c,0x25);
				oled_print("Print",0x02,0x1c,0x25);
				oled_print("Reset",0x03,0x1c,0x25);
				oled_print_letter(' ',element->page,0x00,0x08);
				oled_print_letter('#',0x02,0x00,0x08);

				break;
			case 4:
				oled_print("Modes",0x02,0x1c,0x25);
				oled_print("Controller",0x03,0x1c,0x25);
				oled_print_letter(' ',element->page,0x00,0x08);
				oled_print_letter('#',0x02,0x00,0x08);
				break;
			default:
				break;
		}
		element = element->sub;
	}
	// INN I MODES / CONTROLLER
	else if(x>200 && (element->text == "Modes" || element->text == "Controller")){
		switch(element->page){
			case 2:
				oled_print("Modes",0x00,0x1c,0x25);

				oled_print("Goalie",0x02,0x1c,0x25);
				oled_print("Survival",0x03,0x1c,0x25);
				oled_print_letter(' ',element->page,0x00,0x08);
				oled_print_letter('#',0x02,0x00,0x08);
				break;
			case 3:
				oled_print("Controller",0x00,0x1c,0x25);
				oled_print("Joystick",0x02,0x1c,0x25);
				oled_print("Slider",0x03,0x1c,0x25);
				oled_print_letter(' ',element->page,0x00,0x08);
				oled_print_letter('#',0x02,0x00,0x08);
				break;
			default:
				break;
		}
		element = element->sub;
	}
	// UT FRA MODES
	else if(x<50 && (element->text == "Goalie" || element->text == "Survival")){
			element = element->parent;
			oled_print("Options",0x00,0x1c,0x25);
			oled_print("Modes",0x02,0x1c,0x25);
			oled_print("Controller",0x03,0x1c,0x25);

			oled_print_letter(' ',0x02,0x00,0x08);
			oled_print_letter(' ',0x03,0x00,0x08);
			oled_print_letter('#',element->page,0x00,0x08);
	}
		// UT FRA CONTROLLER
		else if(x<50 && (element->text == "Joystick" || element->text == "Slider")){
			element = element->parent;
			oled_print("Options",0x00,0x1c,0x25);
			oled_print("Modes",0x02,0x1c,0x25);
			oled_print("Controller",0x03,0x1c,0x25);

			oled_print_letter(' ',0x02,0x00,0x08);
			oled_print_letter(' ',0x03,0x00,0x08);
			oled_print_letter('#',element->page,0x00,0x08);
		}
	// UT FRA OPTIONS
	else if(x<50 && (element->text == "Modes" || element->text == "Controller")){
			element = element->parent;
			oled_print("Main Menu",0x00,0x1c,0x25);
			oled_print("Play",0x02,0x1c,0x25);
			oled_print("Highscores",0x03,0x1c,0x25);
			oled_print("Options",0x04,0x1c,0x25);
			oled_print("Exit",0x06,0x1c,0x25);

			oled_print_letter(' ',0x02,0x00,0x08);
			oled_print_letter(' ',0x03,0x00,0x08);
			oled_print_letter('#',element->page,0x00,0x08);
	}
	// UT FRA HIGHSCORES
	else if(x<50 && (element->text == "Print" || element->text == "Reset")){
			element = element->parent;
			oled_print("Main Menu",0x00,0x1c,0x25);
			oled_print("Play",0x02,0x1c,0x25);
			oled_print("Highscores",0x03,0x1c,0x25);
			oled_print("Options",0x04,0x1c,0x25);
			oled_print("Exit",0x06,0x1c,0x25);

			oled_print_letter(' ',0x02,0x00,0x08);
			oled_print_letter(' ',0x03,0x00,0x08);
			oled_print_letter('#',element->page,0x00,0x08);
	}
	
	//if(x<50){
		//printf("mindre enn 50\n");
		//curr = element->parent;
		//temp = element->parent;
	//}
	//else{
		////printf("større enn 50\n");
		//curr = element->sub;
		//temp = curr;
	//}
	//printf("Element.parent: %s \n",element->text);
	//if (element->goto_func == NULL){
		//oled_print(element->text,0x00,0x1c,0x25);
		//oled_print(curr->text,curr->page,0x1c,0x25);
		//curr = curr->under;
		//while (curr != NULL){
			//printf("elemen text: %s\n",curr->text);
			//oled_print(curr->text,curr->page,0x1c,0x25);
			//curr = curr->under;
//
		//}
		//oled_print_letter(' ',element->page,0x00,0x08);
		//oled_print_letter('#',0x02,0x00,0x08);
	////else if(element)
		////
	printf("etter.text %s \n",element->text);
	
	return element;
}
MENU* menu_nav(MENU* current_menu){
	MENU *hashtag = current_menu;
	int y = read_joystick_position(channel1,channel2).y_pos;
	int x = read_joystick_position(channel1,channel2).x_pos;
	//printf("x:%d	y:%d \n",x,y);
	// MOVING UP AND DOWN
	//printf("current text  %s\n",current_menu->text);
	if(y < 20 && !navy && (current_menu->under != NULL)){
		hashtag = current_menu->under;
		navy = true;

		oled_print_letter(' ',current_menu->page,0x00,0x08);
		oled_print_letter('#',hashtag->page,0x00,0x08);
		current_menu = current_menu->under;
		printf("UNDER		cm: %d, hashtag: %d	 %s\n ",current_menu->page, hashtag->page,current_menu->text);

	}

	else if(y > 220 && !navy && current_menu->over != NULL){
		navy = true;
		hashtag = current_menu->over;
		oled_print_letter(' ',current_menu->page,0x00,0x08);
		oled_print_letter('#',hashtag->page,0x00,0x08);
		printf("OVER:		cm: %d, hashtag: %d	 %s\n ",current_menu->page, hashtag->page,current_menu->text);
		current_menu = current_menu->over;
		
		
	}
	else if(y > 120 && y<150){navy = false;}
		
	 //CHANGING SUB MENU
	 if(((x < 20  && current_menu->parent != NULL) || x > 200) && !navx){
		 navx = true;
		 oled_reset();
		 if(current_menu->sub == NULL){

			int a = current_menu->goto_func(current_menu->game_mode,current_menu->controller_option);
			if(current_menu->text == "Goalie" || current_menu->text == "Survival"){
				current_menu = current_menu->parent;
				current_menu = current_menu->parent;
				current_menu = current_menu->over;
				current_menu = current_menu->over;
				current_menu->game_mode = a;
				
			}
			else if(current_menu->text == "Joystick" || current_menu->text == "Slider"){
				current_menu = current_menu->parent;
				current_menu = current_menu->parent;
				current_menu = current_menu->over;
				current_menu = current_menu->over;
				current_menu->controller_option = a;
			}

			 printf("Mode: %i\n",current_menu->game_mode);
			 oled_print("Main Menu",0x00,0x1c,0x25);
			 oled_print("Start game",0x02,0x1c,0x25);
			 oled_print("High Scores",0x03,0x1c,0x25);
			 oled_print("Options",0x04,0x1c,0x25);
			 oled_print("Exit",0x06,0x1c,0x25);
			 oled_print_letter('#',0x02,0x00,0x08);
		 }
		 current_menu = menu_display(current_menu,x);

		
	 }
	 else if(x < 150 && x > 120){navx = false;}
	//printf("Game mode: %i		Controller: %i \n",current_menu->game_mode,current_menu->controller_option);
	return current_menu;
}

void save_highscore(uint8_t highscore){

	uint8_t min = highscore;
	uint8_t adr = 0x00;
	
	for (uint8_t i = 0x01; i<0x06; i++){
		uint8_t temp = EEPROM_read(i);
		if (temp >= 0xff)
		{temp = 0;
		}
		if (min > temp)
		{min = temp;
			printf("min: %x\n",min);
		adr = i;
		}
	}
	
	if (adr != 0x00)
	{printf("Adr: %x\n", adr);
		EEPROM_write( adr, highscore);
	}
}	
