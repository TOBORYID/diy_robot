#ifndef __UART_H__
#define __UART_H__

#include "inc.h"

#define USARTBUFSIZE 255

typedef struct
{
	volatile uint8_t getIdx;
	volatile uint8_t putIdx;
	volatile uint8_t buffer[USARTBUFSIZE];
} USARTCBUF;

extern USARTCBUF uart_putbuf, uart_getbuf;

void uart_init(uint16_t BAUD_RATE);
uint8_t Get_Length(void);
uint8_t Get_Byte(void);
void Put_Byte(uint8_t c);
void Put_Str(const uint8_t* data, uint8_t size);

#endif
