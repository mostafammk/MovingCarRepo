/*
 * Motor.h
 *
 *  Created on: Sep 26, 2019
 *      Author: Mahmoud Rezk Mahmoud , Mustafa Khalil
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "DIO.h"
#include "MOTOR_confg.h"
#define MOTOR_CTRL_REG PORTD
#define MOTOR_ENA_PIN PIN5
#define MOTOR_DIR_PIN1 PIN6
#define MOTOR_DIR_PIN2 PIN7
uint8 Motor_Forward(void);
uint8 Motor_Reverse(void);
uint8 Motor_Stop(void);


#endif /* MOTOR_H_ */
