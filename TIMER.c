/*
 * TIMER.c
 *
 *  Created on: Sep 20, 2019
 *      Author: alx
 */
#include "TIMER.h"



//void __vector__19(void )
ISR(TIMER0_COMP_vect)
{
	static uint8 x=0;
	x++;
	if(x == 4)
	{
		PORTB ^= 0xFF;
		x=0;
	}
}


static uint8 Init_check[NUM_OF_Timers] = {NOT_INITIALIZED,NOT_INITIALIZED};

uint8 TIMER_init(void)
{
	uint8 retval=OK;
	uint8 Loop_index=0;
	if(NUM_OF_Timers<=MAX_NUM_OF_TIMERS)
	{
		for(Loop_index=0;Loop_index<NUM_OF_Timers;Loop_index++)
		{
			Init_check[Loop_index]=INITIALIZED;
			switch(TIMER_cnfg_arr[Loop_index].TIMER_ID)
			{
			case TIMER0:
				PORTC |= 0x01;
				/*	uint8 TIMER_Mode  				done;
				 * 	uint8 OC_ChA_Mode				done;
					uint16 Normal_PreloadedValue  	done;
					uint8 Prescaler					done;
					uint8 Interrupt_ChA				done with Q;
					uint8 PWM_DUTYCYCLE;
					OCR chA							done*/


				switch(TIMER_cnfg_arr[Loop_index].TIMER_Mode)
				{
				/****************************************************************
				 * 						  Timer0 Normal Mode					*
				 ****************************************************************/
				case NORMAL_MODE:
					/*
					 * 1- FOC0 bit = 1 for non-PWM mode
					 * 2- WGM00 and WGM01 bits = 0 for Normal Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin as it's not used in Normal mode
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR0 = 0x80;

					/*
					 * Setting Timer Preloaded value
					 */
					if((TIMER_cnfg_arr[Loop_index].Normal_PreloadedValue >= 0)\
						&& (TIMER_cnfg_arr[Loop_index].Normal_PreloadedValue < 0xFF))
					{
						TCNT0 = TIMER_cnfg_arr[Loop_index].Normal_PreloadedValue;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}



					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x01;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x01;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR0 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					break;

				/****************************************************************
				 * 						  Timer0 CTC Mode						*
				 ****************************************************************/

				case CTC_MODE:
					/*
					 * 1- FOC0 bit = 1 for non-PWM mode
					 * 2- WGM00 bit = 0 and WGM01 bit = 1 for CTC Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin at the beginning of the initialization
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR0 = 0x88;
					PORTC |= 0x02;

					/*
					 * Setting the Compare value
					 */
					if(TIMER_cnfg_arr[Loop_index].OCR_ChA <= 0xFF)
					{
						OCR0 = TIMER_cnfg_arr[Loop_index].OCR_ChA;
						PORTC |= 0x04;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting the OC pin Mode
					 */
					switch(TIMER_cnfg_arr[Loop_index].OC_ChA_Mode)
					{
					case OC_DISABLED:
						break;

					case OC_TOGGLE:
						PORTC |= 0x08;
						TCCR0 |= (1<<TCCR0_COM00);
						break;

					case OC_CLEAR:
						TCCR0 |= (1<<TCCR0_COM01);
						break;

					case OC_SET:
						TCCR0 |= (3<<TCCR0_COM00);
						break;

					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						PORTC |= 0x10;
						TIMSK |= 0x02;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x02;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:
						PORTC |= 0x20;
						TCCR0 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					break;

				/****************************************************************
				 * 						  Timer0 FAST PWM Mode					*
				 ****************************************************************/

				case FAST_PWM_MODE:
					/*
					 * 1- FOC0 bit = 0 for PWM mode
					 * 2- WGM00 bit = 1 and WGM01 bit = 1 for Fast PWM Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin at the beginning of the initialization
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR0 = 0x48;

					/*
					 * Setting the Duty Cycle
					 */
					if(TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE <= 100)
					{

						OCR0 = (uint8)((255 * TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE)/100);
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting OC pin Mode
					 */
					switch(TIMER_cnfg_arr[Loop_index].OC_ChA_Mode)
					{
					case OC_DISABLED:
						break;

					case OC_NONINVERTING_PWM:
						TCCR0 |= (1<<TCCR0_COM01);
						break;

					case OC_INVERTING_PWM:
						TCCR0 |= (3<<TCCR0_COM00);
						break;

					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x02;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x02;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR0 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					break;

				/****************************************************************
				 * 					Timer0 PWM Phase Correct Mode				*
				 ****************************************************************/
				case PHASE_PWM_MODE:
					/*
					 * 1- FOC0 bit = 0 for PWM mode
					 * 2- WGM00 bit = 1 and WGM01 bit = 0 for PWM Phase Correct Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin at the beginning of the initialization
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR0 = 0x40;


					/*
					 * Setting the Duty Cycle
					 */
					if(TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE <= 100)
					{

						OCR0 = (uint8)((255 * TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE)/100);
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting the OC pin Mode
					 */
					switch(TIMER_cnfg_arr[Loop_index].OC_ChA_Mode)
					{
					case OC_DISABLED:
						break;

					case OC_NONINVERTING_PWM:
						TCCR0 |= (1<<TCCR0_COM01);
						break;

					case OC_INVERTING_PWM:
						TCCR0 |= (3<<TCCR0_COM00);
						break;

					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x02;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x02;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR0 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					break;


				default:
					Init_check[Loop_index]=NOT_INITIALIZED;
					retval = NOK;
				}

				break;

			case TIMER1:
				break;



			case TIMER2:

				switch(TIMER_cnfg_arr[Loop_index].TIMER_Mode)
				{
				/****************************************************************
				 * 						  Timer2 Normal Mode					*
				 ****************************************************************/
				case NORMAL_MODE:
					/*
					 * 1- FOC0 bit = 1 for non-PWM mode
					 * 2- WGM00 and WGM01 bits = 0 for Normal Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin as it's not used in Normal mode
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR2 = 0x80;

					/*
					 * Setting Timer Preloaded value
					 */
					if((TIMER_cnfg_arr[Loop_index].Normal_PreloadedValue >= 0)\
						&& (TIMER_cnfg_arr[Loop_index].Normal_PreloadedValue < 0xFF))
					{
						TCNT2 = TIMER_cnfg_arr[Loop_index].Normal_PreloadedValue;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}



					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x40;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x40;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR2 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					break;

				/****************************************************************
				 * 						  Timer2 CTC Mode						*
				 ****************************************************************/

				case CTC_MODE:
					/*
					 * 1- FOC0 bit = 1 for non-PWM mode
					 * 2- WGM00 bit = 0 and WGM01 bit = 1 for CTC Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin at the beginning of the initialization
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR2 = 0x88;

					/*
					 * Setting the Compare value
					 */
					if(TIMER_cnfg_arr[Loop_index].OCR_ChA <= 0xFF)
					{
						OCR2 = TIMER_cnfg_arr[Loop_index].OCR_ChA;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting the OC pin Mode
					 */
					switch(TIMER_cnfg_arr[Loop_index].OC_ChA_Mode)
					{
					case OC_DISABLED:
						break;

					case OC_TOGGLE:
						TCCR2 |= (1<<TCCR2_COM20);
						break;

					case OC_CLEAR:
						TCCR2 |= (1<<TCCR2_COM21);
						break;

					case OC_SET:
						TCCR2 |= (3<<TCCR2_COM20);
						break;

					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x80;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x80;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR2 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					break;

				/****************************************************************
				 * 						  Timer2 FAST PWM Mode					*
				 ****************************************************************/

				case FAST_PWM_MODE:
					/*
					 * 1- FOC0 bit = 0 for PWM mode
					 * 2- WGM00 bit = 1 and WGM01 bit = 1 for Fast PWM Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin at the beginning of the initialization
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR2 = 0x48;

					/*
					 * Setting the Duty Cycle
					 */
					if(TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE <= 100)
					{

						OCR2 = (uint8)((255 * TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE)/100);
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting OC pin Mode
					 */
					switch(TIMER_cnfg_arr[Loop_index].OC_ChA_Mode)
					{
					case OC_DISABLED:
						break;

					case OC_NONINVERTING_PWM:
						TCCR2 |= (1<<TCCR2_COM21);
						break;

					case OC_INVERTING_PWM:
						TCCR2 |= (3<<TCCR2_COM20);
						break;

					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x80;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x80;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR2 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					break;

				/****************************************************************
				 * 					Timer2 PWM Phase Correct Mode				*
				 ****************************************************************/
				case PHASE_PWM_MODE:
					/*
					 * 1- FOC0 bit = 0 for PWM mode
					 * 2- WGM00 bit = 1 and WGM01 bit = 0 for PWM Phase Correct Mode
					 * 3- COM00 and COM01 bits = 0 to disconnect the OC pin at the beginning of the initialization
					 * 4- CS00:1 bits = 0 for no clk source at the beginning of the initialization (it will be defined later with the prescaler)
					 */
					TCCR2 = 0x40;


					/*
					 * Setting the Duty Cycle
					 */
					if(TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE <= 100)
					{

						OCR2 = (uint8)((255 * TIMER_cnfg_arr[Loop_index].PWM_DUTYCYCLE)/100);
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting the OC pin Mode
					 */
					switch(TIMER_cnfg_arr[Loop_index].OC_ChA_Mode)
					{
					case OC_DISABLED:
						break;

					case OC_NONINVERTING_PWM:
						TCCR2 |= (1<<TCCR2_COM21);
						break;

					case OC_INVERTING_PWM:
						TCCR2 |= (3<<TCCR2_COM20);
						break;

					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting weather the timer operates in Interrupt or pooling mode
					 */
					if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == INTERRUPT)
					{
						TIMSK |= 0x80;
						SREG |= (1<<SREG_I);
					}
					else if(TIMER_cnfg_arr[Loop_index].Interrupt_ChA == POOLING)
					{
						TIMSK &= ~0x80;
					}
					else
					{
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}

					/*
					 * Setting Timer0 Prescaler
					 */
					switch(TIMER_cnfg_arr[Loop_index].Prescaler)
					{
					case NO_CLK_SRC:
					case F_CPU_1:
					case F_CPU_8:
					case F_CPU_64:
					case F_CPU_256:
					case F_CPU_1024:
					case EXT_CLK_FALLING:
					case EXT_CLK_RISING:

						TCCR2 |= TIMER_cnfg_arr[Loop_index].Prescaler;
						break;
					default:
						Init_check[Loop_index]=NOT_INITIALIZED;
						retval = NOK;
					}


					break;


				default:
					Init_check[Loop_index]=NOT_INITIALIZED;
					retval = NOK;
				}

				break;

				/*
				 * In case of wrong timer ID
				 * return not initialized timer and NOT OK
				 */
			default:
				Init_check[Loop_index]=NOT_INITIALIZED;
				retval = NOK;
			}

		}
	}

	/*
	 * In case that the number of timers to be configured more than 3
	 * return Not OK
	 */
	else{
		retval = NOK;
	}

















	return retval;
}



uint8 PWM_changeDutyC(uint8 Duty_Cycle,uint8 Timer_ID)
{
	uint8 retval=OK;


















	return retval;
}
