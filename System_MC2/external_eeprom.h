/*
 * Module: External EEPROM
 * Description: Header file for EEPROM Driver
 *  Created on: Oct 12, 2019
 *      Author: Amr Ramadan
 */
#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"
/*************************Preprocessor Macros***********************/
#define ERROR 0
#define SUCCESS 1

/*************************Functions Prototypes***********************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 Address, uint8 Data);
uint8 EEPROM_readByte(uint16 Address, uint8 *Data);

#endif /* EXTERNAL_EEPROM_H_ */
