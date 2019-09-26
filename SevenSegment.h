/******************************************************************************
 *
 * Module: Seven Segment
 *
 * File Name: seven_segment.c
 *
 * Description: Header file for Seven Segment
 *
 * Author: Mahmoud Rezk
 *
 *******************************************************************************/

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "DIO.h"


#define SEVEN_SEGMENT_PORT PORT_B
#define SEVEN_SEGMENT_PIN0 PIN0
#define SEVEN_SEGMENT_PIN1 PIN1
#define SEVEN_SEGMENT_PIN2 PIN2
#define SEVEN_SEGMENT_PIN3 PIN3

#define SEVEN_SEGMENT_ENABLE_PORT PORT_D
#define SEVEN_SEGMENT_ENABLE_PIN PIN2
/*
 * Function Prototypes for Seven Segment
 */
uint8 SEVEN_SEGMENT_displayDigit(uint8 digit);

#endif /* SEVEN_SEGMENT_H_ */
