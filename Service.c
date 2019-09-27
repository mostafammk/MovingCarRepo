/*
 * Service.c
 *
 *  Created on: Sep 25, 2019
 *      Author: alx
 */
#include "Service.h"



uint32 g_TimeCount=0;

void Counting_Time(void)
{
	g_TimeCount++;

}

uint8 SERVICE_init (void)
{
	uint8 funcStatus = OK;

	if(DIO_init())
	{

	}
	else
	{
		funcStatus = NOK;
	}

	if(TIMER_init())
	{

	}
	else
	{
		funcStatus = NOK;
	}

	return funcStatus;
}

uint8 Delay(uint8 TIMER_ID,uint32 Delay_ms)
{
	uint8 retval=NOK;
	uint8 Loop_index=0;
	uint16 LOC_TimeCount=0;
	float128 Tick_Time=0;
	for(Loop_index=0;Loop_index<NUM_OF_Timers;Loop_index++)
	{
		if(TIMER_cnfg_arr[Loop_index].TIMER_ID==TIMER_ID)
		{
			retval=OK;
			switch(TIMER_cnfg_arr[Loop_index].Prescaler)
			{
			case F_CPU_1:
				Tick_Time= (1.0/ F_CPU)*1000;
				break;
			case F_CPU_8:
				Tick_Time= (8.0/ F_CPU)*1000;
				break;
			case F_CPU_32:
				Tick_Time= (32.0/ F_CPU)*1000;
				break;
			case F_CPU_64:
				Tick_Time= (64.0/ F_CPU)*1000;
				break;
			case F_CPU_128:
				Tick_Time= (128.0/ F_CPU)*1000;
				break;
			case F_CPU_256:
				Tick_Time= (256.0/ F_CPU)*1000;
				break;
			case F_CPU_1024:
				Tick_Time= (1024.0/ F_CPU)*1000;
				break;
			default:
				retval=NOK;
				break;
			}
			switch(TIMER_ID)
				{
				case TIMER0:
					if(TIMER_cnfg_arr[Loop_index].TIMER_Mode==NORMAL_MODE)
					{
						LOC_TimeCount= (Delay_ms)/(Tick_Time*256);
						TIMSK |= 0x01;
						SREG |= (1u<<SREG_I);
						TIMER0_OVF_setCallBack(Counting_Time);
					}
					else if(TIMER_cnfg_arr[Loop_index].TIMER_Mode==CTC_MODE)
					{
						LOC_TimeCount= (Delay_ms*1000.0)/(Tick_Time*(TIMER_cnfg_arr[Loop_index].OCR_ChA));
						TIMSK |= 0x02;
						SREG |= (1u<<SREG_I);
						TIMER0_CMP_setCallBack(Counting_Time);
					}
					else
					{
					retval=NOK;
					}

				break;
				case TIMER1:
					if(TIMER_cnfg_arr[Loop_index].TIMER_Mode==NORMAL_MODE)
					{
						LOC_TimeCount= (Delay_ms*1000.0)/(Tick_Time*(0xffff));
						TIMSK |= 0x04;
						SREG |= (1u<<SREG_I);
						TIMER1_OVF_setCallBack(Counting_Time);

					}
					else if(TIMER_cnfg_arr[Loop_index].TIMER_Mode==CTC_MODE)
					{
						LOC_TimeCount= (Delay_ms*1000.0)/(Tick_Time*(TIMER_cnfg_arr[Loop_index].OCR_ChA));
						TIMSK |= 0x08;
						SREG |= (1u<<SREG_I);
						TIMER1_CMPA_setCallBack(Counting_Time);
					}
					else
					{
						retval=NOK;
					}
				break;
				case TIMER2:
					if(TIMER_cnfg_arr[Loop_index].TIMER_Mode==NORMAL_MODE)
					{
						LOC_TimeCount= (Delay_ms*1000.0)/(Tick_Time*256);
						TIMSK |= 0x40;
						SREG |= (1<<SREG_I);
						TIMER2_OVF_setCallBack(Counting_Time);
					}
					else if(TIMER_cnfg_arr[Loop_index].TIMER_Mode==CTC_MODE)
					{
						LOC_TimeCount= (Delay_ms*1000.0)/(Tick_Time*(TIMER_cnfg_arr[Loop_index].OCR_ChA));
						TIMSK |= 0x80;
						SREG |= (1<<SREG_I);
						TIMER2_CMP_setCallBack(Counting_Time);
					}
					else
					{
						retval=NOK;
					}

				break;
				default:
					retval = NOK;
				break;

				}
			TIMER_start(TIMER_ID);
			while(LOC_TimeCount != g_TimeCount);
			TIMER_stop(TIMER_ID);
			g_TimeCount=0;
			Loop_index=MAX_NUM_OF_TIMERS+1;
		}
		else
		{
			retval=NOK;
		}
	}

	return retval;

}
