/*
 * Module: lcd.h
 * Description: Header file for LCD Driver
 *  Created on: Oct 5, 2019
 *      Author: Amr Ramadan
 */

#ifndef LCD_H_
#define LCD_H_
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"
#include <stdlib.h>
#include <stdio.h>
/*Macros*/
//LCD HW Configuration Pins
#define RS PD4 //LCD Register Select Pin
#define RW PD5 //LCD R/W Pin
#define E  PD6 //LCD Enable Pin
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR PORTC

//LCD Commands
#define CLEAR_CMD 0x01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

// Functions Prototypes
void LCD_sendCommand(uint8 command);
void LCD_displayChar(uint8 data);
void LCD_init(void);
void LCD_displayString(uint8 *Str);
void LCD_goToRowCol(uint8 row, uint8 col);
void LCD_displayStringRowCol(uint8 *Str , uint8 row, uint8 col);
void LCD_integerToString(int data);
void LCD_clearScreen(void);
#endif /* LCD_H_ */
