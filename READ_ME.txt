Our game is played through the start_game() function which is in the CAN_bus.c and CAN_bus.h files.
This is because the function needs to use a CAN_message, which caused us many problems when this file
was (as originally intended) implementet in the menu_function files.

