#ifndef __LED_H__
#define __LED_H__

#include "inc.h"

#define RED_LED_ON PORTB &= (1 << PORT3)
#define RED_LED_OFF PORTB &= ~(1 << PORT3)
#define RED_LED_TOG PORTB ^= (1 << PORT3)

#define GREEN_LED_ON PORTB &= (1 << PORT4)
#define GREEN_LED_OFF PORTB &= ~(1 << PORT4)
#define GREEN_LED_TOG PORTB ^= (1 << PORT4)

#define BLUE_LED_ON PORTB &= (1 << PORT5)
#define BLUE_LED_OFF PORTB &= ~(1 << PORT5)
#define BLUE_LED_TOG PORTB ^= (1 << PORT5)

void LED_Init(void);

#endif
