#include "led.h"

void LED_Init(void)
{
	DDRB |= (1 << DDB3) | (1 << DDB4) | (1 << DDB5);
	PORTB &= ~((1 << PORT3) | (1 << PORT4) | (1 << PORT5));
}
