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

MENU* menu_change_sub(MENU *sub, int n){
	MENU *current = (MENU*)malloc(sizeof(MENU));
	
	current = sub->sub;
	
	for(int i = 0; i<n; i++){
		current = current->under;
	}
	return current;
}
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
	
	MENU *start_game = menu_add_node(main_menu,main_menu,menu_start_game,"Play");
	menu_add_description(start_game,"Joy mode!",1) ;
	menu_add_description(start_game,"Green = fire",1) ;
	start_game->page = 0x02;

	// highscore nodes	
	MENU *highscore = menu_add_node(start_game,main_menu,NULL,"Highscores");
	MENU *hs_print = menu_add_submenu(highscore,menu_print_HS,"Highscores");
	MENU *hs_reset = menu_add_node(hs_print,hs_print,menu_reset_HS, "Reset");
	
	// all option nodes		
	MENU *options = menu_add_node(highscore,main_menu,NULL,"Options");
	MENU *option_modes = menu_add_submenu(options,NULL,"Modes");
	MENU *option_modes_goalie = menu_add_submenu(option_modes,menu_choose_goalie_mode,"Goalie");
	MENU *option_modes_survival = menu_add_node(option_modes_goalie,option_modes_goalie,menu_choose_survival_mode, "Surivival");
	MENU *option_controller = menu_add_node(option_modes,option_modes,NULL,"Controller");
	MENU *option_controller_joystick = menu_add_submenu(option_controller,menu_controller_joystick,"Joystick");
	MENU *option_controller_slider = menu_add_node(option_controller_joystick,option_controller_joystick, menu_controller_slider,"Slider");
	MENU *exit_program = menu_add_node(options,start_game,program_exit,"Exit");
	
	//Creating loopover for first element to last, skipping main menu
	start_game->over = exit_program;
	exit_program->page = 0x06;
	main_menu->over = exit_program;
	
	//printf("sg:%d	hs:%d	hsp:%d	hsr:%d	opt:%d	optm:%d	 optmg:%d	optms:%d\n",
	//start_game->page,highscore->page,hs_print->page,hs_reset->page,options->page,option_modes->page,option_modes_goalie->page,option_modes_survival->page);
	// Print starting menu
	MENU *temp = main_menu;

	oled_print(main_menu->text,0x00,0x1c,0x25);
	oled_print(start_game->text,0x02,0x1c,0x25);
	oled_print(highscore->text,0x03,0x1c,0x25);
	oled_print(options->text,0x04,0x1c,0x25);
	oled_print(exit_program->text,0x06,0x1c,0x25);
	oled_print_letter("#",0x02,0x00,0x08);
	hashtag.moveY = 0;
	hashtag.moveX = 0;
	return main_menu;
}

void menu_display(MENU* element, int x){
	MENU *curr;
	MENU *temp;
	if(x<50){
		printf("mindre enn 50\n");
		curr = element->parent;
		temp = element->parent;
	}
	else{
		printf("større enn 50\n");
		curr = element->sub;
		temp = element->sub;
	}

	if (element->goto_func == NULL){
		oled_print(element->text,0x00,0x1c,0x25);
		printf("elemen text: %s\n",element->text);
		//while (curr->under != temp){
			//oled_print(curr->text,curr->page,0x1c,0x25);
			//curr = curr->under;
		//}
		oled_print_letter("#",0x02,0x00,0x08);
		oled_print_letter(" ",element->page,0x00,0x08);
	}
}
MENU* menu_nav(MENU* current_menu){
	MENU *hashtag = current_menu;
	int y = read_joystick_position(channel1,channel2).y_pos;
	int x = read_joystick_position(channel1,channel2).x_pos;
	//printf("x:%d	y:%d \n",x,y);
	// MOVING UP AND DOWN
	if(y < 20 && !navy){
		//hashtag = current_menu->under;
		hashtag = current_menu->under;
		navy = true;

		oled_print(" ",current_menu,0x00,0x08);
		oled_print("#",hashtag->page,0x00,0x08);

		printf("cm: %d, hashtag: %d	 %s\n ",current_menu->page, hashtag->page,current_menu->text);
		current_menu = current_menu->under;
	}
	else if(y > 220 && !navy){
		navy = true;
		hashtag = current_menu->over;
		oled_print(" ",current_menu->page,0x00,0x08);
		oled_print("#",hashtag->page,0x00,0x08);
		//printf("cm: %d, hashtag: %d	 %s\n ",current_menu->page, hashtag->page,current_menu->text);
		current_menu = current_menu->over;
		
		
	}
	else if(y > 120 && y<150){navy = false;}
		
	 //CHANGING SUB MENU
	 if(((x < 20  && current_menu->parent != NULL) || x > 220) && !navx){
		navx = true;
		 oled_reset();
		 //menu_display(current_menu,x);
	 }
	 else if(x < 150 && x > 120){navx = false;}
	 
	return current_menu;
}

void menu_initialize(){
	//current_menu = menu_create();
}











//void move_hashtag(int n, bool dir){
	//if(n<5 && n!= 0 && dir) {
		//
		//oled_print_letter('#',(uint8_t)n, 0x00, 0x08);
		//oled_print_letter(' ',(uint8_t)(n-1), 0x00,0x08);
	//}
	//else if (dir){
		//oled_print_letter('#',(uint8_t)n, 0x00, 0x08);
		//oled_print_letter(' ',(uint8_t)(n-1), 0x00,0x08);
		////printf("inni else\n");
		//hashtag.chosen = 0;
	//}
	////printf("n: %i \n",n);
	//if(n<5 && n !=-1 && !dir) {
		//oled_print_letter('#',(uint8_t)n, 0x00, 0x08);
		//oled_print_letter(' ',(uint8_t)(n-1), 0x00,0x08);
	//}
	//else if (!dir){
		//oled_print_letter('#',0x04, 0x00, 0x08);
		//oled_print_letter(' ',0x01, 0x00,0x08);
		//hashtag.chosen = 8;
	//}
	////printf("n: %i		page: %d \n",n, main_menu[n].page);
	//hashtag.moveY = true;
//}
//void menu_sub_folder(int *chosen){
//int temp = chosen;
//if (temp < 13 && hashtag.parent){
//hashtag.parent = false;
//
//oled_print_letter('#',0x02, 0x00, 0x08);
//
//}
//else if(!hashtag.parent){
//oled_reset();
//oled_print_letter("#",0x02,0x00,0x08);
//oled_print("Play,high,diff,mode,exit");
//hashtag.parent = true;
//}
//hashtag.moveX = true;
//
//hashtag.chosen = 0;
//
//}

//void menu_navigate(){
	//int temp;
	//int y = read_joystick_position(channel1,channel2).y_pos;
	//int x = read_joystick_position(channel1,channel2).x_pos;
	////printf("x: %d	y: %d \n",x,y);
	//if (y<20 && !hashtag.moveY){
		//printf("why are you in here	%d		%i\n",y,hashtag.moveY);
		//hashtag.direction = true;
		//hashtag.chosen+=1;
		//temp = hashtag.chosen;
		//move_hashtag(temp/2,hashtag.direction);
	//}
	//if(y>230 && !hashtag.moveY){
		//hashtag.direction = false;
		//hashtag.chosen-=1;
		//temp = hashtag.chosen;
		//move_hashtag(temp/2, hashtag.direction);
	//}
	//else if(y>100 && y<150 && hashtag.moveY){
		//hashtag.moveY = false;
	//}
	//if (x > 200 && !hashtag.moveX){
	//menu_sub_folder(hashtag.chosen);
	//}
	//else if (x<180 && hashtag.moveX){
	//hashtag.moveX = false;
	//}
	//if(x < 40 && !hashtag.moveX){
	//menu_sub_folder(15);
	//}
//}