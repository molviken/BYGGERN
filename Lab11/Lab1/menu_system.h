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

struct menu_element{
	char *word;
	uint8_t col;
	uint8_t page;
};
void menu_initialize();
void menu_system();
char create_string(struct menu_element liste[5]);
void menu_navigate();
void move_hashtag(int n, bool vert);
void menu_sub_folder(int *chosen);