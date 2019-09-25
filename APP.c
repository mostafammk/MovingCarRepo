
#include "DIO.h"
#include "TIMER.h"

void main(void)
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	DIO_init();
	uint8 value = TIMER_init();
	DIO_write(PORT_A,PIN5,value);
	while(1)
	{

	}

}
