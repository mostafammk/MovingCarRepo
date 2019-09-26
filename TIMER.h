/*
 * TIMER.h
 *
 *  Created on: Sep 20, 2019
 *      Author: alx
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "REG_Lib.h"
#include "STD_TYPES.h"
#include "TIMER_cnfg.h"
#include "Interrupts.h"
//#include <avr/Interrupt.h>
//#include <avr/io.h>



#define MAX_NUM_OF_TIMERS		(uint8)3
#define OK 0
#define NOK 1

uint8 TIMER_init(void);
uint8 CHANGE_PWM(uint8 TIMER_ID,uint8 PWM_DUTYCYCLE_chA)

#endif /* TIMER_H_ */
