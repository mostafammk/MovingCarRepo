/*
 * Motor.h
 *
 *  Created on: Sep 26, 2019
 *      Author: Mahmoud Rezk Mahmoud , Mustafa Khalil
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "MOTOR_confg.h"

#define MOTOR_CTRL_REG PORT_D
#define MOTOR_ENA_PIN PIN5
#define MOTOR_DIR_PIN1 PIN6
#define MOTOR_DIR_PIN2 PIN7

uint8 MOTOR_init(void);
uint8 MOTOR_Forward(uint8 Motor_Num);
uint8 MOTOR_Reverse(uint8 Motor_Num);
uint8 MOTOR_Stop(uint8 Motor_Num);


#endif /* MOTOR_H_ */
