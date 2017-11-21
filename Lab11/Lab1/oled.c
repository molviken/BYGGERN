/*
 * oled.c
 *
 * Created: 25.09.2017 08:26:04
 *  Author: oystmol
 */ 
#include <stdbool.h>
#include "oled.h"
#include "joystick.h"
#include "fonts.h"
#include "menu_system.h"

struct Menu_position pos;

int coloumn_counter = 0;
int tall = 0;
void write_c(uint8_t command){
	volatile char *oled_c = (char *) 0x1000;
	oled_c[0] = command;
}
void write_d(uint8_t data){
	volatile char *oled_d = (char *) 0x1200;
	oled_d[0] = data;
}
void oled_init(void){
	write_c(0xae);        //  display  off
	write_c(0xa1);        //segment  remap
	write_c(0xda);        //common  pads  hardware:  alternative
	write_c(0x12);
	write_c(0xc8);        //common	output scan direction:com63~com0
	write_c(0xa8);        //multiplex  ration  mode:63
	write_c(0x3f);
	write_c(0xd5);        //display	divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);        //contrast  control
	write_c(0x50);
	write_c(0xd9);        //set  pre-charge  period
	write_c(0x21);
	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x02);
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        //out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
}

void oled_reset(void){
	for (uint8_t i=0x00; i<0x08;i++){
		oled_clear_page(i);
	}
	//oled_init();
}
void oled_goto_page(uint8_t page){
	uint8_t goto2 = 0xb0+page;
	write_c(goto2);
}
void oled_goto_coloumn(uint8_t coloumn_start, uint8_t coloumn_end){
	write_c(0x21);
	write_c(coloumn_start);
	write_c(coloumn_end);
}
void oled_clear_page(uint8_t page){
	oled_goto_page(page);
	oled_goto_coloumn(0x00,0x7f);
		for (uint8_t i = 0;i<0x7f;i++){
			oled_goto_coloumn(i,0x7f);
			write_d(0x00);
		}
}

void oled_print_letter(char letter,uint8_t page, uint8_t coloumn_start,uint8_t coloumn_end){
	
	//uint8_t char_alfa[8] = font8[34];
	oled_pos(page, coloumn_start, coloumn_end);
	int ltr;
	for (int i = 0;i<8;i++){
		ltr = pgm_read_byte(&(font8[letter-32][i]));
		write_d(ltr);
	}
	//printf("printet letter\n");
}
void oled_pos(uint8_t page,uint8_t coloumn_start,uint8_t coloumn_end){
	oled_goto_page(page);
	oled_goto_coloumn(coloumn_start,coloumn_end);
}


void oled_print(char* word,uint8_t page,uint8_t coloumn_start,uint8_t coloumn_end){
	
	//uint8_t coloumn_start = 0x09;
	//uint8_t coloumn_end = 0x11;
	//uint8_t page = 0x02;	
	for (int i = 0; word[i] != '\0'; i++){
		if(word[i] == 44){
			page +=0x01;
			//coloumn_start = 0x09;
			//coloumn_end = 0x11;
			i++;
		}			
		oled_print_letter(word[i], page, coloumn_start,coloumn_end);
		coloumn_start += 0x09;
		coloumn_end += 0x09;


	}
	
}

void oled_home(void){
	oled_goto_page(0x00);
	oled_goto_coloumn(0x00,0x00);
}
