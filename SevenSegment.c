/******************************************************************************
 *
 * Module: Seven Segment
 *
 * File Name: seven_segment.c
 *
 * Description: Source file for Seven Segment
 *
 * Author: Mahmoud Rezk Mahmoud
 *
 *******************************************************************************/

#include "SevenSegment.h"

uint8 SEVEN_SEGMENT_displayDigit(uint8 digit){

	uint8 func_status = OK;
	DIO_write(SEVEN_SEGMENT_ENABLE_PORT,SEVEN_SEGMENT_ENABLE_PIN,HIGH);
	if((digit>=0) && (digit<=9))
	{
		DIO_write(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN0,(1u&(digit>>0)));
		DIO_write(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN1,(1u&(digit>>1)));
		DIO_write(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN2,(1u&(digit>>2)));
		DIO_write(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN3,(1u&(digit>>3)));
	}
	else
	{
		func_status = NOK;
	}

	return func_status;
}
