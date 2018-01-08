#include "pwm.h"

void Pwm_Output(float pulse)
{
	OCR1A = ICR1 * pulse;
	if(pulse > 0)
	{
	}
	else
	{
	}
}

void Pwm_Init(void)
{
	DDRB |= (1 << DDB1) | (1 << DDB2);
	TCNT1 = 0;
	ICR1 = 737;
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
	OCR1A = 0;
	OCR1B = 0;
}
