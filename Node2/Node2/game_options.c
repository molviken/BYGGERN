/*
 * game_options.c
 *
 * Created: 21.11.2017 14:37:24
 *  Author: arefv
 */ 
#include <avr/io.h>
#include "game_options.h"
#include "bit_operations.h"
#include "ir_detector.h"
#include "CAN_bus.h"
#include "sonoid.h"
#include "PID.h"
#include "pwm.h"


int choose_game_options(){
	// Necessary Initializing
	int seconds = 0;
	int second_check = 0;   // second updater

	int channel_change = 0; // change which ir we check
	uint16_t threshold = ir_threshold(0xa);

	struct Score scorecount; // initializing the IRs
	struct Score ir_bottom;
	
	scorecount.score = 0;
	scorecount.flag = 1;
	ir_bottom.score = 0;
	ir_bottom.flag = 1;
		
	motor_cal();
	int16_t max_encoder_value = motor_set_enc_maxval();
	struct CAN_message game;
	
	while(1){
		if(TIFR3 & (1 << OCF3B)){
			game = CAN_receive();
			adc_node2_switch(channel_change);
			channel_change = !channel_change;
			// updating second checker
			second_check += 1;
			if(second_check == 10){
				seconds += 1;
				//printf("second check: %d \n", seconds);
				second_check = 0;
			}
			// Clear interrupt and reset counter
			TCNT3 = 0;
			TIFR3 |= (1 << OCF3B);
		}
		if(game.id != 1){
			switch(game.id){
				case 10:
				PWM_control(game.data[0]);
				PID_regulator(game.data[3], max_encoder_value);
				scorecount.score = seconds;
				//printf("score (seconds): %d \n", seconds);
				break;
				
				case 11:
				joystick_drive(game.data[0],game.data[3]);
				scorecount.score = seconds;
				break;

				case 14:
				PWM_control(game.data[0]);
				PID_regulator(game.data[3], max_encoder_value);
				if(!channel_change){scorecount = ir_score_update(threshold,scorecount);}
				break;
				
				case 15:
				joystick_drive(game.data[0],game.data[3]);
				if(!channel_change){scorecount = ir_score_update(threshold,scorecount);}
				break;
			}
			if(channel_change){
				ir_bottom = ir_score_update(threshold, ir_bottom);
				//printf("ir_bottom = %d	channel_change = %d\n", ir_bottom.score, channel_change);
			}
			if(ir_bottom.score > 0){
				game.data[7] = scorecount.score;
				printf("score: %d\n", scorecount.score);
				game.data[6] = seconds;
				seconds = 0;
				ir_bottom.score = 0;
				game.id = 0x01;
			}
			//printf("id: %d		ir: %d		flag: %i\n", game.id, ir_bottom.score, ir_bottom.flag);
			//printf("score%d\n",scorecount.score);
			CAN_transmit(game);
		}
		else{
			scorecount.score = 0;
		}
		_delay_ms(100);	//printf("ir%d\n",ir_bottom.score);
	}		

}