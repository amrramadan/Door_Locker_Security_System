/*
 * Module: uart.h
 * Description: Header file for UART Driver
 *  Created on: Oct 7, 2019
 *      Author: Amr Ramadan
 */
#include "uart.h"
#define BOUD_PRESCALE (((F_CPU /(USART_BOUDRATE*8UL)))-1)

void UART_init(void) {
	/*/*USART Control and Status Register A >> UCSRA
	 * 		U2X=1 : Enable Double USART Transmission speed
	 */
	UCSRA = (1 << U2X);

	/*USART Control and Status Register B >> UCSRB
	 * 		RXC=1 :to able to
	 */
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/* USART Control and Status Register C >> UCSRC
	 * 		URSEL = 1 : To able to write in this register
	 * 		UCSZ1:UCSZ0 = 11 : 8-bit mode
	 */
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

	//The URSEL must be zero when writing the UBRRH.
	UBRRH = 0;
	UBRRL = BOUD_PRESCALE;

}
/*
 * Note:
 * 		The USART Transmit Data Buffer Register
 * 		and USART Receive Data Buffer Registers share the
 * 		same I/O address referred to as USART Data Register or UDR.
 */
void UART_sendByte(uint8 Data) {
	UDR = Data;   // copy char into UDR register
	while (BIT_IS_CLEAR(UCSRA, TXC))
		; // wait until transmission complete ( flag is set )
	SET_BIT(UCSRA, TXC); // Clear the TXC flag
}

uint8 UART_receiveByte(void) {
	/*
	 * RXC flag is set when the UART Receive data
	 * Read the received data from RX buffer (UDR)
	 * wait until the RXC flag is cleared after read the data
	 */
	while (BIT_IS_CLEAR(UCSRA, RXC))
		; // Receive Buffer is Empty ( no pending data )
	return UDR;
}

void UART_sendString(const uint8 *Ptr) {
	uint8 i = 0;
	while(Ptr[i] != '\0')
	{
		UART_sendByte(Ptr[i]);
		i++;
	}
}

void UART_receiveString( uint8 *Ptr) {
	uint8 i = 0;
	Ptr[i] = UART_receiveByte();
	while(Ptr[i] != '+')
	{
		i++;
		Ptr[i] = UART_receiveByte();
	}
	Ptr[i] = '\0';
}
