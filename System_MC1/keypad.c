/*
 * Module: keypad.c
 * Description: Source file for Keypad Driver
 *  Created on: Oct 4, 2019
 *      Author: Amr Ramadan
 */

#include "keypad.h"

#if(N_Col == 3)
//note: this function designed for proteus 4x3 keypad
static uint8 Keypad_4x3_adjust(uint8 button_number)
{
	switch(button_number) {
		case 10 : return '*';
		break;
		case 11 : return 0;
		break;
		case 12 : return '#';
		break;
		default: return button_number;

	}
}

#elif(N_Col == 4)
//note: this function designed for proteus 4x4 keypad
static uint8 Keypad_4x4_adjust(uint8 button_number) {
	switch (button_number) {
	case 1:
		return 7;
		break;
	case 2:
		return 8;
		break;
	case 3:
		return 9;
		break;
	case 4:
		return '%';
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 5;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return '*';
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 2;
		break;
	case 11:
		return 3;
		break;
	case 12:
		return '-';
		break;
	case 13:
		return 13;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return '=';
		break;
	case 16:
		return '+';
		break;

	default:
		return button_number;

	}
}
#endif

uint8 Keypad_getPressedKey(void) {
	uint8 col, row;
	while (1) {
		for (col = 0; col < N_Col; col++) {
			KEYPAD_PORT_DIR = (0b00010000 << col); // each time one of col pins will be output pin
			KEYPAD_PORT_OUT = (~(0b00010000) << col); // each time enable internal pullup for one pin
			for (row = 0; row < N_Row; row++) {
				if (!(KEYPAD_PORT_IN & (1 << row))) { // check if switch pressed
					#if(N_Col==3)
						return Keypad_4x3_adjust((row*N_Col)+col+1);
					#elif(N_Col==4)
						return Keypad_4x4_adjust((row * N_Col) + col + 1);
					#endif
				}
			}
		}
	}
}
