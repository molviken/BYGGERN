/*
 * timerModule.h
 *
 * Created: 06.11.2017 08:49:31
 *  Author: oystmol
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
void pwm_setup(void);
int PWM_set_puls_width(double ms);
double PWM_control(uint8_t x_pos);