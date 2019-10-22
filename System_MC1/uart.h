/*
 * Module: uart.h
 * Description: Header file for UART Driver
 *  Created on: Oct 7, 2019
 *      Author: Amr Ramadan
 */



#ifndef UART_H_
#define UART_H_
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#define USART_BOUDRATE 9600


/*******************Functions Prototypes*************************/
void UART_init(void);
void UART_sendByte(uint8 Data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *Ptr);
void UART_receiveString(uint8 *Ptr);
#endif /* UART_H_ */
