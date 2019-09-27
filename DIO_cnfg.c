/********************************************************************
 * File Name:			DIO Driver Configuration C File				*
 *																	*
 * File Description:	This file is used to configure the state	*
 * 						of each pin and the initial value			*
 *																	*
 * Author: 				Mostafa Khalil &							*
 * 						Mahmoud Rezk								*
 ********************************************************************/

#include "DIO_cnfg.h"

DIO_cnfg_t DIO_cnfg_arr [NUM_OF_PINS] =
{
	{PORT_B,PIN0,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_B,PIN1,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_B,PIN2,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_B,PIN3,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_D,PIN2,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_D,PIN5,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_D,PIN6,OUTPUT,LOW,NA,INITIALIZED},
	{PORT_D,PIN7,OUTPUT,LOW,NA,INITIALIZED}

};
