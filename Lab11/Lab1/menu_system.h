/*
 * menu_system.h
 *
 * Created: 18.11.2017 17:01:02
 *  Author: arefv
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
	
struct Hashtag{
	int * moveY;
	int * moveX;	
};

typedef struct{
	char* text;
	char* line1;
	char* line2;
	char* line3;
	char* line4;
	int game_mode;
	int controller_option;
	uint8_t page;
	unsigned int sub_menus;
	int (*goto_func)();
	struct MENU *over;
	struct MENU *under;
	struct MENU *parent;
	struct MENU *sub;
}MENU;

void save_highscore(uint8_t highscore);	
MENU* init_menu(char *title);
MENU* menu_add_submenu(MENU *parent, void (*goto_func)(), char*name);
MENU* menu_add_node(MENU *over, MENU *under, void (*goto_func)(), char*name);
MENU* menu_create();
MENU* menu_nav();
MENU* menu_display(MENU* current_menu, int x);

