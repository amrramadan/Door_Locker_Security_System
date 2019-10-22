/*
 * mc1.c
 * Description: Code for first ECU called HMI(Human Machine Interface)
 * 				responsible for interfacing with the user
 *  Created on: Oct 16, 2019
 *      Author: amr ramadan
 */

#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#define WRITE_CONFIG 0
#define OPEN_DOOR 1
#define CHANGE_PASSCODE 0
#define PASSCODE_SIZE 5
#define M1_READY 0x10
#define M2_READY 0x20
int main() {

	uint8 i = 0; //EEPROM PASSCODE WRITE FLAG
	uint8 Data[20], buffer_1[6], buffer_2[6], key, receive;
	UART_init();
	LCD_init();

#if WRITE_CONFIG
	LCD_displayStringRowCol("  Enter New  ", 0, 0);
	LCD_displayStringRowCol("Passcode : ", 1, 0);
	while (i < PASSCODE_SIZE) {
		_delay_ms(200);
		key = Keypad_getPressedKey();
		if (key >= 0 && key <= 9) {
			_delay_ms(50);
			LCD_integerToString(key);
			buffer_1[i] = (uint8) (key);
			i++;
		}
	}
	buffer_1[5] = '+';
	_delay_ms(100);

	while (UART_receiveByte() != M2_READY) {
	}
	UART_sendString(buffer_1);
	_delay_ms(100);
	LCD_clearScreen();
#endif

	LCD_displayStringRowCol("'+' : Open Door ", 0, 0);
	LCD_displayStringRowCol("'-' : Change password ", 1, 0);
	key = Keypad_getPressedKey();
	if (key == '+') {
		LCD_clearScreen();
		_delay_ms(100);
		LCD_displayStringRowCol("Please Enter  ", 0, 0);
		LCD_displayStringRowCol("Passcode  ", 1, 0);
		i = 0;
		while (i < PASSCODE_SIZE) {
			_delay_ms(200);
			key = Keypad_getPressedKey();
			if (key >= 0 && key <= 9) {
				_delay_ms(50);
				LCD_integerToString(key);
				buffer_2[i] = (uint8) (key);
				i++;
			}
		}
		buffer_2[5] = '+';
		_delay_ms(100);

		while (UART_receiveByte() != M2_READY) {
		}
		UART_sendString(buffer_2);
		LCD_clearScreen();


		receive = UART_receiveByte();
		if (receive == 0)
		LCD_displayString("Door Opening");
		else
			LCD_displayString("Incorrect Passcode");
		//	LCD_clearScreen();
	}

	/*********************************
	 i=0;
	 _delay_ms(500);
	 LCD_clearScreen();
	 _delay_ms(50);
	 UART_sendByte(M1_READY);
	 UART_receiveString(Data);
	 LCD_displayString(Data);
	 *****************************************/

	while (1) {

	}
}
