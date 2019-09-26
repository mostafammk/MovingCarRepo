/********************************************************************
 * File Name:			DIO Driver Configuration .h File			*
 *																	*
 * File Description:	This file is used to configure the state	*
 * 						of each pin and the initial value			*
 *																	*
 * Author: 				Mostafa Khalil &							*
 * 						Mahmoud Rezk								*
 ********************************************************************/


#ifndef DIO_CNFG_H_
#define DIO_CNFG_H_

#include "STD_TYPES.h"

typedef enum {SS1,SS2,SS3,SS4,SSEN,motorEN,motor1,motor2,NUM_OF_PINS}PINS_t;

#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define OUTPUT		1
#define INPUT		0

#define HIGH		1
#define LOW			0

#define PULLUP		1
#define EXTRES		0

#define INITIALIZED			1
#define NOT_INITIALIZED		0

#define NA 0xff

typedef struct
{
	uint8 PORT;
	uint8 PIN;
	uint8 DIR;
	uint8 OUT;
	uint8 RES;
	uint8 IS_init_arr;
}DIO_cnfg_t;

extern DIO_cnfg_t DIO_cnfg_arr [NUM_OF_PINS];



#endif /* DIO_CNFG_H_ */
