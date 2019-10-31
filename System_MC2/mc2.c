/*
 * mc2.c
 * Description: Code for Second ECU called control ECU which is responsible for the
 system operations and control
 *  Created on: Oct 16, 2019
 *      Author: amr ramadan
 */

#include "external_eeprom.h"
#include "uart.h"
#include "timer.h"
#include "config2.h"

#define WRITE_CONFIG 1
#define CORRECT_PASSWORD 0
#define WRONG_PASSWORD 1
#define EEPROM_ADDRESS 0x0511
#define PASSCODE_SIZE 5
#define M1_READY 0x10
#define M2_READY 0x20

uint8 i = 0, write = 0, read = 0, compare;
uint8 container[6], Data[6], buffer[6];
int main() {

	//DDRA |= (1 << PA0);
	DDRD |= (1 << PD5);
	UART_init();
	EEPROM_init();

	UART_sendByte(M2_READY);
	UART_receiveString(Data);
	// receive the string
	while (i < PASSCODE_SIZE) {
		write = Data[i];
		EEPROM_writeByte(EEPROM_ADDRESS + i, write);
		_delay_ms(50);
		i++;
	}

	while (1) {
		i = 0;
		while (i < PASSCODE_SIZE) {
			EEPROM_readByte(EEPROM_ADDRESS + i, &read);
			container[i] = read;
			_delay_ms(50);
			i++;
		}

		UART_sendByte(M2_READY);
		UART_receiveString(buffer); // receive the string
		compare = strcmp(buffer, container);
		_delay_ms(100);
		if (compare == CORRECT_PASSWORD) {
			UART_sendByte(CORRECT_PASSWORD);
			timer1_PWM_init(124);
			_delay_ms(1500);
			timer1_PWM_init(187);

		}

		else {

			PORTA |= (1 << PA0);
			_delay_ms(1500);
			PORTA &= (~(1 << PA0));
			UART_sendByte(WRONG_PASSWORD);
		}

	}
}

