/*
 * motor.h
 *
 * Created: 13.11.2017 10:11:32
 *  Author: oystmol
 */ 
#define F_CPU 16000000UL
#define LEFT 1
#define RIGHT 0
#define STOP -1
#define DIR PH1
#define SEL PH3
#define EN PH4
#define OE PH5
#define RST PH6


#define Go_Left clear_bit(PORTH,DIR)
#define Go_Right set_bit(PORTH,DIR)
#define MOTOR_ENABLE PA4
#define MOTOR_DIR PA3
#include <avr/io.h>

void motor_init();
int16_t motor_read();
void encoder_reset();
void test_program();
void motor_cal();
struct PI_reg motor_reg_init();
struct PI_reg motor_reg_calc(uint8_t slider_right);
void motor_position_control(uint8_t slider_right, struct PI_reg reg);
int8_t motor_speed_control(int8_t speed);