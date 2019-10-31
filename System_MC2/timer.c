/*
 * timer.c
 *
 *  Created on: Oct 23, 2019
 *      Author: amrra
 */
#include "timer.h"
void timer1_PWM_init(sint16 duty_cycle) {
	TCNT1 = 0;
	ICR1 = 2500;
	OCR1A = duty_cycle;
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	;

}

