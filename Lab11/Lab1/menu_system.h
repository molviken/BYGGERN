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
	bool parent;
	bool direction;
	int *chosen;
	bool moveY;
	bool moveX;
};
typedef struct{
	char* text;
	char* line1;
	char* line2;
	char* line3;
	char* line4;
	
	unsigned int sub_menus;
	void (*goto_func)();
	struct MENU *over;
	struct MENU *under;
	struct MENU *parent;
	struct MENU *sub;
}MENU;

	
MENU* init_menu(char *title);
MENU* menu_add_submenu(MENU *parent, void (*goto_func)(), char*name);
MENU* menu_add_node(MENU *over, MENU *under, void (*goto_func)(), char*name);
MENU* menu_change_sub(MENU *sub, int n);
MENU* menu_create();
void menu_nav();


void menu_initialize();
//void menu_system();
////char create_string(struct menu_element liste[5]);
//void menu_navigate();
//void move_hashtag(int n, bool vert);
//void menu_sub_folder(int *chosen);
//

