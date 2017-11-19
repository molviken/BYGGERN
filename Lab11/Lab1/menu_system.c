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
struct menu_element main_menu[5];
struct menu_element submain_menu1[5];
struct Hashtag hashtag;

void move_hashtag(int n, bool dir){
	if(n<5 && n!= 0 && dir) {
		
		oled_print_letter('#',main_menu[n].page, 0x00, 0x08);
		oled_print_letter(' ',main_menu[n-1].page, 0x00,0x08);
	}
	else if (dir){
		oled_print_letter('#',main_menu[0].page, 0x00, 0x08);
		oled_print_letter(' ',main_menu[n-1].page, 0x00,0x08);
		//printf("inni else\n");
		hashtag.chosen = 0;
	}
	printf("n: %i \n",n);
	if(n<5 && n !=-1 && !dir) {
		oled_print_letter('#',main_menu[n].page, 0x00, 0x08);
		oled_print_letter(' ',main_menu[n+1].page, 0x00,0x08);
	}
	else if (!dir){
		oled_print_letter('#',main_menu[4].page, 0x00, 0x08);
		oled_print_letter(' ',main_menu[0].page, 0x00,0x08);
		hashtag.chosen = 8;
	}
	//printf("n: %i		page: %d \n",n, main_menu[n].page);
	hashtag.moveY = true;
}
void menu_sub_folder(int *chosen){
	int temp = chosen;
	switch(temp){
		case 0:
			oled_print("sub11,sub12,sub13,sub14,sub15");
			break;
		case 2:
			oled_print("sub21,sub22,sub23,sub24,sub25");
			break;
		case 4:
			oled_print("sub31,sub32,sub33,sub34,sub35");
			break;
		case 6:
			oled_print("sub41,sub42,sub43,sub44,sub45");
			break;
		case 8:
			oled_print("sub51,sub52,sub53,sub54,sub55");
			break;
		default:
			printf("Invalid option\n");
			break;
	}
	hashtag.moveX = true;
	oled_reset();
	printf("hmmm\n");
	oled_print_letter('#',0x02, 0x00, 0x08);
	hashtag.chosen = 0;
	
}
void menu_navigate(){
	int temp;
	int y = read_joystick_position(channel1,channel2).y_pos;
	int x = read_joystick_position(channel1,channel2).x_pos;
	if (y<20 && !hashtag.moveY){
		hashtag.direction = true;
		hashtag.chosen+=1;
		temp = hashtag.chosen;
		move_hashtag(temp/2,hashtag.direction);
	}
	if(y>230 && !hashtag.moveY){
		hashtag.direction = false;
		hashtag.chosen-=1;
		temp = hashtag.chosen;
		move_hashtag(temp/2, hashtag.direction);
	}
	else if(y>100 && y<150 && hashtag.moveY){
		hashtag.moveY = false;
	}
	if (x > 200 && !hashtag.moveX){
		menu_sub_folder(hashtag.chosen);
	}
	else if (x<180 && hashtag.moveX){
		hashtag.moveX = false;
	}
}

void menu_system(){
	uint8_t page = 0x02;
	main_menu[0].word = "ain1";
	main_menu[1].word = "ain2 ";
	main_menu[2].word = "ain3 ";
	main_menu[3].word = "ain4 ";
	main_menu[4].word = "ain5 ";
	submain_menu1[0].word = "Main1 ";
	submain_menu1[1].word = "Main2 ";
	submain_menu1[2].word = "Main3 ";
	submain_menu1[3].word = "Main4 ";
	submain_menu1[4].word = "Main5 ";
	for(int i = 0;i<5;i++){
		main_menu[i].page = page;
		submain_menu1[i].page = page;
		page += 0x01;
	}
}

void menu_initialize(){
	//oled_pos(main_menu[0].page, 0x09,0x11);
	//uint8_t hjelp = 0x0a;
	//oled_print_letter("M",0x00,0x0a,0x12);
	//oled_print_letter("A",0x00, 0x13,0x1b);
	//oled_print_letter("I",0x00,0x1c,0x24);
	//oled_print_letter("N",0x00,0x25,0x2d);
	////oled_print_letter(" ",0x00,0x2e,36);
	//oled_print_letter("M",0x00,0x37,0x3f);
	//oled_print_letter("E",0x00,0x40,0x48);
	//oled_print_letter("N",0x00,0x49,0x51);
	//oled_print_letter("U",0x00,0x52,0x5a);
	oled_print("Play,Difficulty,Highscores,next page,Exit");
	oled_print_letter('#',0x02, 0x00, 0x08);
	
	hashtag.chosen = 0;
	hashtag.moveY = false;
	hashtag.moveX = false;
}
