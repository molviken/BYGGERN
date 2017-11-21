/*
 * DEFINITIONS.h
 *
 * Created: 21.11.2017 14:54:13
 *  Author: arefv
 */ 

//#define	NAVIGATE_DOWN(){\
		////hashtag = current_menu->under;
		////navy = true;
		////oled_print_letter(' ',current_menu->page,0x00,0x08);
		////oled_print_letter('#',hashtag->page,0x00,0x08);
		////current_menu = current_menu->under;
//
//} while(0)

#define	NAVIGATE_DOWN(hashtag, current_menu,navy){\
	hashtag = current_menu->under;\
	navy = true; \
	oled_print_letter(' ',current_menu->page,0x00,0x08);\
	oled_print_letter('#',hashtag->page,0x00,0x08);\
	current_menu = current_menu->under;\
} while(0)

#define	NAVIGATE_UP(hashtag, current_menu,navy){\
		hashtag = current_menu->over;\
		navy = true; \
		oled_print_letter(' ',current_menu->page,0x00,0x08);\
		oled_print_letter('#',hashtag->page,0x00,0x08);\
		current_menu = current_menu->over;\
} while(0)


#define GOTO_OPTIONS(){\
		oled_print("OPTIONS",0x00,0x1c,0x25);\
		oled_print("Modes",0x02,0x1c,0x25);\
		oled_print("Controller",0x03,0x1c,0x25);\
		oled_print_letter('#',0x02,0x00,0x08);\
}while(0)

#define GOTO_MAIN_MENU(){\
		oled_print("MAIN MENU",0x00,0x1c,0x25);\
		oled_print("Play",0x02,0x1c,0x25);\
		oled_print("Highscores",0x03,0x1c,0x25);\
		oled_print("Options",0x04,0x1c,0x25);\
		oled_print("Exit",0x06,0x1c,0x25);\
		oled_print_letter('#',0x02,0x00,0x08);\
}while(0)

#define EXTRA_MENU_INIT(){\
		options->parent = NULL;\
		start_game->parent = NULL;\
		highscore->parent = NULL;\
		exit_program->parent = NULL;\
		start_game->under = highscore;\
		hs_reset->under = NULL;\
		option_controller->under = NULL;\
		main_menu->under = start_game;\
		option_modes_survival->under = NULL;\
		option_controller_slider->under = NULL;\
		start_game->page = 0x02;\
		exit_program->page = 0x06;\
}while(0)