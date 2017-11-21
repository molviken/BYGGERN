
#define F_CPU 16000000
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "bit_operations.h"
#include "motor.h"
#include "dac.h"



void motor_init(){
	//set_bit(TWCR, TWEN);
	DDRK = 0x00;		// Set PortK (ADCH) as input
	DDRH = 0xFF;		// Set PortH (MJ1) as output
	DDRD = 0x00;		// Set PortD (MJ2) as input
	set_bit(DDRD, PD0); //SCL port
	set_bit(DDRD, PD1); //SDA port
	set_bit(PORTH, EN); // Enable encoder
	set_bit(PORTH, RST); // Toggle !RST to set internal counter = 0
	set_bit(PORTH, RST);   // Toggle on to start counting
	//_delay_ms(200);
	//motor_set_ref(0);
	//sumError = 0;
	clear_bit(PORTH,PH1);

}
void motor_change_dir(int direction){
	if (direction == 1){
		set_bit(PORTH,DIR);
	}
	else if(direction == 0){
		clear_bit(PORTH, DIR);
	}
	else{
	
		//dac_write(0x00);
	}
}

int16_t motor_read(){
	int16_t bits = 0x00;
	clear_bit(PORTH, OE); // Toggle !OE low to enable output of encoder
	clear_bit(PORTH, SEL);  // Clears Sel
	_delay_us(100);
	bits = (PINK << 8);
	set_bit(PORTH, SEL); // Sets Sel
	_delay_us(100);
	bits |= PINK;

	set_bit(PORTH, RST); 
	set_bit(PORTH, OE); // sets !OE high to disable output of encoder
	if (-bits < 0x0000){
		bits = -0x0000;
	}
	//else if(-bits > 0x2134){
		//bits = -0x2134;
	//}
	return -bits;
}

void encoder_reset(){
	clear_bit(PORTH, RST); // Toggle !RST to set internal counter = 0
	_delay_us(20);
	set_bit(PORTH, RST); 
}

void test_program(){
	if(motor_read()>8000){

		Go_Left;
		dac_write(0x35);
		printf("Going left%d \n", motor_read());
	}
	else if (motor_read() <1000){

		Go_Right;
		dac_write(0x35);
		printf("Going right: %d \n", motor_read());
	}
}

void motor_cal(){
	Go_Left;
	dac_write(0x55);
	_delay_ms(2000);
	encoder_reset();
}

int16_t motor_set_enc_maxval(){		
	Go_Right;
	_delay_ms(1000);
	return motor_read();
}

void joystick_drive(uint8_t x_pos, uint8_t servo){
	uint8_t speed;
	PWM_control(servo);
	if(x_pos>137){
		speed = (x_pos- 137)*0x1.6p-1;
		Go_Right;
	}
	else if(x_pos<127){
		speed = (127 - x_pos)*0x1.6p-1;
		Go_Left;
	}
	else{
		speed = 0x00;
	}
	//printf("X: %d		speed: %d\n",x_pos,speed);
	dac_write(speed);
}