/*
 * Module: i2c.c
 * Description: source file for I2C Driver
 *  Created on: Oct 10, 2019
 *      Author: Amr Ramadan
 */

#include "i2c.h"

void TWI_init(void)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
    TWBR = 0x02;
	TWSR = 0x00;

    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = 0b00000010; // my address = 0x01 :)

    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void) {
/*
 * TWEN  = 1 : Enable TWI Protocol
 * TWINT = 1 : Clear Interrupt Flag
 * TWSTA = 1 : Send Start Bit
 */
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
	/*wait until Start bit send successfully*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
	/*
	 * TWEN  = 1 : Enable TWI Protocol
	 * TWINT = 1 : Clear Interrupt Flag
	 * TWSTA = 1 : Send Stop Bit
	 */
		TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTO);
}

void TWI_write(uint8 Data){
	// initiate Data Register With Data
	TWDR = Data;
	/*
	 * TWEN  = 1 : Enable TWI Protocol
	 * TWINT = 1 : Clear Interrupt Flag
	 */

	TWCR = (1<<TWEN) | (1<<TWINT);
	/*wait until data is send successfully*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void){
	/*
	 * TWEN  = 1 : Enable TWI Protocol
	 * TWINT = 1 : Clear Interrupt Flag
	 * TWEA  = 1 : Enable Acknowledge Bit
	 */
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
	/*wait until Ack is received successfully*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR; //Read Data

}
uint8 TWI_readWithNACK(void){
	/*
	 * TWEN  = 1 : Enable TWI Protocol
	 * TWINT = 1 : Clear Interrupt Flag
	 */
	TWCR = (1<<TWEN) | (1<<TWINT);
	/*wait until data is received successfully*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR; //Read Data
}

uint8 TWI_getStatus(void){
	uint8 status;
	status = TWSR & 0xF8;
	return status;
}

