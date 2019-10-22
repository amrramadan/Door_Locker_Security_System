/*
 * mc2.c
 * Description: Code for Second ECU called control ECU which is responsible for the
 system operations and control
 *  Created on: Oct 16, 2019
 *      Author: amr ramadan
 */

#include "external_eeprom.h"
#include "uart.h"
#include "lcd.h"

#define CORRECT_PASSWORD 0
#define WRONG_PASSWORD 1
#define WRITE_CONFIG 0
#define EEPROM_ADDRESS 0x0511
#define PASSCODE_SIZE 5
#define M1_READY 0x10
#define M2_READY 0x20

int main() {
	uint8 i = 0, write = 0, read = 0, compare;
	uint8 container[6], Data[6], buffer[6];

	UART_init();
	LCD_init();
	EEPROM_init();
	//_delay_ms(20);
	UART_sendByte(M2_READY);
#if WRITE_CONFIG
	UART_receiveString(Data);
	// receive the string
	while (i < PASSCODE_SIZE) {
		write = Data[i];
		EEPROM_writeByte(EEPROM_ADDRESS + i, write);
		_delay_ms(50);
		i++;
	}
	/*
	 while (i < PASSCODE_SIZE) {
	 LCD_integerToString(Data[i]);
	 i++;
	 }
	 */
#endif
	i = 0;
	while (i < PASSCODE_SIZE) {
		EEPROM_readByte(EEPROM_ADDRESS + i, &read);
		container[i] = read;
		_delay_ms(50);
		i++;
	}

	_delay_ms(100);
	UART_sendByte(M2_READY);
	UART_receiveString(buffer); // receive the string
	LCD_clearScreen();
	_delay_ms(100);

	i = 0;
	while (i < PASSCODE_SIZE) {
		LCD_integerToString(buffer[i]);
		i++;
	}
	_delay_ms(300);
	LCD_clearScreen();
	compare = strcmp(buffer, container);
	_delay_ms(100);


	if (compare == CORRECT_PASSWORD)
		UART_sendByte(CORRECT_PASSWORD);
	else
		UART_sendByte(WRONG_PASSWORD);
	//LCD_integerToString(compare);
	/*
	 * i = 0;
	 while (i < PASSCODE_SIZE) {
	 LCD_integerToString(container[i]);
	 i++;
	 }
	 i=0;
	 while(i<=5){
	 Feedback=EEPROM_writeByte(EEPROM_ADDRESS+i,Data[i]);
	 if(Feedback == ERROR)
	 break;
	 }
	 */
	while (1) {
	}
}

