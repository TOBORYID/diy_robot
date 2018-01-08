#include "eeprom.h"
#include "communication.h"


parameter Servo;

void Write_eeprom(uint16_t address, uint8_t data)
{
	while(EECR & (1 << EEWE));
	EEAR = address;
	EEDR = data;
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
}

uint8_t Read_eeprom(uint16_t address)
{
	while(EECR & (1 << EEWE));
	EEAR = address;
	EECR |= (1 << EERE);
	return EEDR;
}

void Write_Parameter(uint8_t *data)
{
	parameter Parameter;
	memcpy(&Parameter, data, 13);
	Servo.Id = Parameter.Id;
	Servo.Kp = Parameter.Kp;
	Servo.Ki = Parameter.Ki;
	Servo.Kd = Parameter.Kd;
	for(uint8_t i = 0; i < 13; i++)
	{
		Write_eeprom(i + 1, data[i]);
	}
	Write_eeprom(0, 0xAA);
	SendData("Set Para Success！");
}

void Read_Parameter(void)
{
	uint8_t data[13];

	memcpy(data, &Servo, 13);
}

void Init_Parameter(void)
{
	if(Read_eeprom(0) == 0xAA)
	{
		uint8_t data[13];
		parameter Parameter;

		for(uint8_t i = 0; i < 13; i++)
		{
			data[i] = Read_eeprom(i);
		}
		memcpy(&Parameter, data, 13);
		Servo.Id = Parameter.Id;
		Servo.Kp = Parameter.Kp;
		Servo.Ki = Parameter.Ki;
		Servo.Kd = Parameter.Kd;
	}
	else
	{
		Servo.Id = 0x00;
		Servo.Kp = 0.1f;
		Servo.Ki = 0.1f;
		Servo.Kd = 0.1f;
	}
}