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

struct Hashtag hashtag;

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
	
	parent->sub = menu;
	parent->sub_menus +=1;
	return menu;
}

MENU* menu_add_node(MENU *over, MENU *under, void (*goto_func)(), char*text){
	MENU *node = (MENU*)malloc(sizeof(MENU));
	
	node->parent = over->parent;
	node->sub = NULL;
	node->over = over;
	//node->over->under = node;
	//node->under->over = node;
	node->under = under;
	node->text = text;
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
	oled_print(main_menu->text);

	//MENU *start_game = menu_add_submenu(main_menu,menu_start_game(),"Pong starts now!");
	//menu_add_description(start_game,"Joystick mode!",1) ;
	return main_menu;
}









void menu_nav(){
	//oled_print("Main1,main2,main3,main4");
	static uint8_t page = 0x00;
	int y = read_joystick_position(channel1,channel2).y_pos;
	if (y<20 && !hashtag.moveY){
	//printf("why are you in here	%d		%i\n",y,hashtag.moveY);
		//oled_print_letter(" ",page,0x09,0x11);
		page +=0x01;
		oled_print_letter('a',page,0x09,0x11);
		hashtag.moveY = true;
	}
	else if(y>120){
		hashtag.moveY = false;
	}
}















void menu_initialize(){

	//oled_print("Main1a,Main2b,Main3c,Main4d");
	//oled_print(sub_menu_start_game->text);
 	////printf("%s\n",main_menu->text);
 	//printf("%s\n",sub_menu_start_game->text);
	//hashtag.chosen = 2;
	//hashtag.moveY = false;
	//hashtag.moveX = false;
	//hashtag.parent = true;
	//uint8_t page = 0x02;
	//for (int i=0;i<5;i++){
		//main_menu[i].page = page;
		//sub_menu_play[i].page = page;
		//sub_menu_options[i].page = page;
		//sub_menu_highscores[i].page = page;
		//sub_menu_nextpage[i].page = page;
		//sub_menu_exit[i].page = page;
		//page+=0x01;	
	//}
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