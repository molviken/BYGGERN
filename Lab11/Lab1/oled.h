/*
 * oled.h
 *
 * Created: 25.09.2017 08:26:15
 *  Author: oystmol
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void oled_goto_coloumn(uint8_t coloumn_start, uint8_t coloumn_end);
void oled_print_letter(char letter,uint8_t page, uint8_t coloumn_start,uint8_t coloumn_end);
void oled_pos(uint8_t page,uint8_t coloumn_start,uint8_t coloumn_end);
void oled_init();
void oled_reset(void);
void oled_draw();
void oled_clear_page(uint8_t page);
void oled_home(void);
void oled_pos(uint8_t page,uint8_t coloumn_start,uint8_t coloumn_end);
void oled_print(char* word );
void oled_navigate_vertical();
