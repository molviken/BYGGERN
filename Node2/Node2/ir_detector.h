/*
 * ir_detector.h
 *
 * Created: 06.11.2017 15:31:11
 *  Author: oystmol
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
uint16_t ir_threshold(uint16_t filterTrigger);
int ir_detection(uint16_t filterTrigger, uint16_t threshold);
struct Score ir_score_update(uint16_t threshold, struct Score poeng);


struct Score {
	int score;
	int flag;
	};