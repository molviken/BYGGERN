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

struct CAN_message game;

if(TIFR5 & (1 << OCF5B)){
    game = CAN_receive();
    // Clear interrupt and reset counter
    TCNT5 = 0;
    TIFR5 |= (1 << OCF5B);
}
while(game.id != 1){
    if(TIFR5 & (1 << OCF5B)){ // if counter has reached OCR5B
        // changes which ir detector we're checking
        adc_node2_switch(channel_change); 
        channel_change = !channel_change;
        // updating second checker
        second_check += 1;
        if(second_check == 250){
            seconds += 1;
            second_check = 0;
        }

        // Clear interrupt and reset counter
        TCNT5 = 0;
        TIFR5 |= (1 << OCF5B);
    }
    switch(game.id){
        case 10:
        pwm_control(game.data[0]);
        PID_reg(game.data[3]);
        scorecount.score = seconds;
        break;
        case 11:
        joystick_drive(game.data[0],game.data[3]);
        scorecount.score = seconds;
        break;

        case 14:
        pwm_control(game.data[0]);
        PID_reg(game.data[3]);
        if(channel_change){scorecount = ir_score_update(threshold,score);}
        break;
        case 15:
        joystick_drive(game.data[0],game.data[3]);
        if(channel_change){scorecount = ir_score_update(threshold,score);}
        break;
    }
    if(!channel_change){ir_bottom = ir_score_update(threshold, ir_bottom);}
    if{ir_bottom.score > 0}{
        game.data[7] = scorecount.score;
        game.id = 1;
    }
    CAN_transmit(game);
}
