/*
 * Motor.c
 *
 *  Created on: Sep 26, 2019
 *      Author: Mahmoud Rezk Mahmoud , Mustafa Khalil
 */
#include "Motor.h"



uint8 MOTOR_init(void)
{
	uint8 retval=OK;
	uint8 LOOP_index=0;

	for(LOOP_index=0;LOOP_index<NUM_OF_Motors;LOOP_index++)
	{
		switch(MOTOR_cnfg_arr[LOOP_index].MOTOR_ID)
		{
		case MOTOR1:
			switch(MOTOR_cnfg_arr[LOOP_index].MOTOR_STATUS)
			{
			case STOP:
				DIO_write(MOTOR_CTRL_REG,MOTOR_ENA_PIN,LOW);
				DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN1,LOW);
				DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN2,LOW);
				break;
			case FORWARD:
				DIO_write(MOTOR_CTRL_REG,MOTOR_ENA_PIN,HIGH);
				DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN1,HIGH);
				DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN2,LOW);
				break;
			case REVERSE:
				DIO_write(MOTOR_CTRL_REG,MOTOR_ENA_PIN,HIGH);
				DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN1,LOW);
				DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN2,HIGH);
				break;
			default:
				retval=NOK;
				break;
			}
			break;
		case MOTOR2:
			break;
		default:
			retval=NOK;
			break;
		}
	}


	return retval;
}

uint8 MOTOR_Forward(uint8 Motor_Num)
{
	uint8 retval=OK;
	if(Motor_Num<NUM_OF_Motors)
	{
		DIO_write(MOTOR_CTRL_REG,MOTOR_ENA_PIN,HIGH);
		DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN1,HIGH);
		DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN2,LOW);
	}
	else
	{
		retval=NOK;
	}

	return retval;

}

uint8 MOTOR_Reverse(uint8 Motor_Num)
{
	uint8 retval=OK;
		if(Motor_Num<NUM_OF_Motors)
		{
			DIO_write(MOTOR_CTRL_REG,MOTOR_ENA_PIN,HIGH);
			DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN1,LOW);
			DIO_write(MOTOR_CTRL_REG,MOTOR_DIR_PIN2,HIGH);
		}
		else
		{
			retval=NOK;
		}


	return retval;

}


uint8 MOTOR_Stop(uint8 Motor_Num)
{
	uint8 retval=OK;
	if(Motor_Num<NUM_OF_Motors)
	{
		DIO_write(MOTOR_CTRL_REG,MOTOR_ENA_PIN,LOW);
	}
	else
	{
		retval= NOK;
	}


	return retval;

}


