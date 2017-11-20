// chose
int main(){
    // Lager spillet i denne CAN_messagen
    CAN_message chosen_game;
    // Velger at hele data arrayet skal kunne brukes.
    chosen_game.length = 8;
    // Setter spillet i default -> survival med slider control
    chosen_game.id = 10;
    chosen_game.data[5] = 1;
    chosen_game.data[6] = 1;
    // Hvis survival blir valgt -> chosen_game.data[5] = 1
    // Hvis goalie blir valgt -> chosen_game.data[5] = 2

    // slider controls -> chosen_game.data[6] = 1
    // joystick controls -> chosen_game.data[6] = 2
}

start_game(struct CAN_message chose_game){
    int8_t game_mode = data[5];
    int8_t controller_mode = data[6];
    if(game_mode == 1){
        switch(controller_mode){
            case 1:
            chosen_game.id = 10;
            break;
            
            case 2:
            chosen_game.id = 11;
            break;
        }
     }
     else if(game_mode == 2){
         case 1:
         chosen_game.id = 14;
         break;

         case 2:
         chosen_game.id = 15;
         break;
     }
     // receiving data from bus every 10 ms.
     if(TIFR1 & (1 << OCF1B)){ // if counter has reached OCR1B
        CAN_message game_over_check = CAN_receive();
        TCNT1 = 0;
        TIFR1 |= (1 << OCF1B);
    }
    while(game_over_check.id != 1){
        chosen_game.data[0] = (uint8_t)read_joystick_position(channel1, channel2).xpos;
        chosen_game.data[3] = (uint8_t)read_slider_position(channel3, channel4).slider2;
        CAN_transmit(chosen_game);
        
        // receiving data from bus every 10 ms.
        if(TIFR1 & (1 << OCF1B)){ // if counter has reached OCR1B
            CAN_message game_over_check = CAN_receive();
            TCNT1 = 0;
            TIFR1 |= (1 << OCF1B);
    }
}
