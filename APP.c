/********************************************************************
 * Project Name:		MovingCar									*
 *																	*
 * Project Description:	A car moving forward for 10seconds then		*
 * 						reverse for 10seconds						*
 *																	*
 * Project Author: 		Mostafa Khalil &							*
 * 						Mahmoud Rezk								*
 ********************************************************************/

#include "SevenSegment.h"
#include "Motor.h"
#include "Service.h"


void main(void)
{
	uint8 sevenSegmentValue = 0;
	uint8 motorDirectionFlag = FORWARD;

	SERVICE_init();
	//MOTOR_init();
	MOTOR_Forward(MOTOR1);

	while(1)
	{
		SEVEN_SEGMENT_displayDigit(sevenSegmentValue);
		Delay(TIMER0,10000);

		if(motorDirectionFlag == FORWARD)
		{
			sevenSegmentValue++;
			if(sevenSegmentValue == 9)
			{
				motorDirectionFlag = REVERSE;
				MOTOR_Reverse(MOTOR1);
			}
		}

		else if(motorDirectionFlag == REVERSE)
		{
			sevenSegmentValue--;
			if(sevenSegmentValue == 0)
			{
				motorDirectionFlag = FORWARD;
				MOTOR_Forward(MOTOR1);
			}
		}

	}

}
