#include "uart.h"

USARTCBUF uart_putbuf, uart_getbuf;

void uart_init(uint16_t BAUD_RATE)
{
	UBRRH = (((F_CPU / BAUD_RATE) / 16) - 1) >> 8;
	UBRRL = (((F_CPU / BAUD_RATE) / 16) - 1);
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	uart_putbuf.putIdx = uart_putbuf.getIdx = 0;
	uart_getbuf.putIdx = uart_getbuf.getIdx = 0;
}

uint8_t Get_Length(void)
{
	return (uart_getbuf.putIdx - uart_getbuf.getIdx);
}

uint8_t Get_Byte(void)
{
	return ((Get_Length() == 0) ? EOF : uart_getbuf.buffer[uart_getbuf.getIdx++ & (USARTBUFSIZE - 1)]);
}

void Put_Byte(uint8_t c)
{
	uart_putbuf.buffer[uart_putbuf.putIdx++ & (USARTBUFSIZE - 1)] = c;
	UCSRB |= (1 << TXCIE);
}

void Put_Str(const uint8_t* data, uint8_t size)
{
	while(size--)
	{
		uart_putbuf.buffer[uart_putbuf.putIdx++ & (USARTBUFSIZE - 1)] = *data++;
	}
	UCSRB |= (1 << TXCIE);
}

ISR(USART_RXC_vect)
{
	uint8_t data = UDR;
	if((UCSRA & ((1 << FE) | (1 << PE) | (1 << DOR))) == 0)
	{
		uart_getbuf.buffer[uart_getbuf.putIdx++ & (USARTBUFSIZE - 1)] = data;
	}
}

ISR(USART_TXC_vect)
{
	if(uart_putbuf.putIdx - uart_putbuf.getIdx != 0)
	{
		UDR = uart_putbuf.buffer[uart_putbuf.getIdx++ & (USARTBUFSIZE - 1)];
	}
	else
	{
		UCSRB &= ~(1 << TXCIE);
	}
}