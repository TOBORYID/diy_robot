#include "systime.h"
#include "main.h"

void SysTime_Init(void)
{
	TCNT0 = 25;
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1 << CS01) | (1 << CS00);
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 25;
	Task_Cnt();
	LOOP();
}