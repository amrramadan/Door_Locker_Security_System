/*
 *  Module: keypad.h
 *  Description: Header file for keypad driver
 *  Created on: Oct 4, 2019
 *      Author: Amr Ramadan
 */

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

/* keypad number of rows and columns configurations */
#define N_Col 4
#define N_Row 4
/* keypad port configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN PINA
#define KEYPAD_PORT_DIR DDRA

/*functions Prototypes*/
uint8 Keypad_getPressedKey(void);

#endif /* KEYPAD_H_ */
