/*
 * Module: lcd.c
 * Description: Source file for LCD Driver
 *  Created on: Oct 5, 2019
 *      Author: Amr Ramadan
 */

#include "lcd.h"

void LCD_sendCommand(uint8 command) {
	CLEAR_BIT(LCD_CTRL_PORT, RS); //instruction select
	CLEAR_BIT(LCD_CTRL_PORT, RW); //Write on LCD
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E); // Enable LCD
	_delay_ms(1);
	LCD_DATA_PORT = command; //send CMD to DATA BUS
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E); //disable LCD
	_delay_ms(1);
}
void LCD_displayChar(uint8 data) {
	SET_BIT(LCD_CTRL_PORT, RS); //Data select
	CLEAR_BIT(LCD_CTRL_PORT, RW); //Write on LCD
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E); // Enable LCD
	_delay_ms(1);
	LCD_DATA_PORT = data; //send DATA to DATA BUS
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E); //Disable LCD
	_delay_ms(1);
}

void LCD_init(void){
	LCD_DATA_PORT_DIR = 0xFF; // configure data port as output port
	LCD_CTRL_PORT_DIR |= (1 << RS) | (1 << RW) | (1 << E); // configure Control pins
	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE); //use 2-line lcd, 8-bit mode, 5*7 dots
	LCD_sendCommand(CURSOR_OFF); // cursor off
	LCD_sendCommand(CLEAR_CMD); // clear LCD
}
//Display String in LCD
void LCD_displayString(uint8 *Str) {
	while ((*Str) != '\0') {
		LCD_displayChar(*Str);
		Str++;
	}
}

void LCD_goToRowCol(uint8 row, uint8 col) {
	// calculate the required address location
	uint8 address;
	switch (row) {
	case 0:
		address = col; //first row
		break;
	case 1:
		address = col + 0x40; //second row
		break;
	case 2:
		address = col + 0x10; //third row
		break;
	case 3:
		address = col + 0x50; // fourth row
		break;
	//write in a specific address in LCD
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}
// display a string in a specific address
void LCD_displayStringRowCol(uint8 *Str , uint8 row, uint8 col){
	LCD_goToRowCol(row,col);
	LCD_displayString(Str);
}
//display integer
void LCD_integerToString(int data){
	char buff[16]; // string holds ASCII result
	itoa(data,buff,10);
	LCD_displayString(buff);
}
//clear screen
void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_CMD);
}
