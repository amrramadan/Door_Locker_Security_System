/*
 * Module: i2c.h
 * Description: Header file for I2C Driver
 *  Created on: Oct 10, 2019
 *      Author: Amr Ramadan
 */

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#ifndef I2C_H_
#define I2C_H_

/*******************Preprocessor Macros*************************/

/*TWSR status Register BITS*/
#define TW_START 		 0x08 //Start condition has been transmitted
#define TW_REP_START	 0x10 //Repeated start condition has been transmitted
#define TW_MT_SLA_W_ACK	 0x18 //Master transmit (slave address + write request) to slave and Ack received from slave
#define TW_MT_SLA_R_ACK	 0x40 //Master transmit (slave address + read request) to slave and Ack received from slave
#define TW_MT_DATA_ACK   0x28 //Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 //Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 //Master received data but doesn't send ACK to slave
/*******************Functions Prototypes*************************/
void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 Data);
uint8 TWI_readWithACK(void);
uint8 TWI_readWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */
