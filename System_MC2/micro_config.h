/*
 * micro_config.h
 *  Module: Microcontroller Configuration file
 *  Created on: Oct 4, 2019
 *  Description: include all Microcontroller libraries
 *      Author: Amr Ramadan
 *
 */

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_
#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <string.h>
#endif /* MICRO_CONFIG_H_ */
