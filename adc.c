#include "adc.h"

void ADC_Init(void)
{
	DDRC = DDRC & 0xf8;
	ADCSRA = 0x00;
	PORTC = PORTC & 0xf8;
	ADMUX = 0x44;
	ACSR = 1 << ACD;
	ADCSRA = 0x84;
}

uint16_t ADC_Read(uint8_t ADCChannel)
{
	uint16_t data;
	ADMUX = (ADMUX & 0xf0) + (ADCChannel & 0x0f);
	data = 0;
	for(uint8_t i = 0; i < 4; i++)
	{
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) == 0);
		ADCSRA |= 0x10;
		data += (ADCH << 8) | ADCL;
	}
	data /= 4;
	return data;
}
