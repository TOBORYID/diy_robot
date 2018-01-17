#include "servo.h"
#include "eeprom.h"
#include "led.h"
#include "adc.h"
#include "communication.h"

uint16_t ChanPosition = 2048;
uint8_t ChanPower = 1;

void Write_Position(uint8_t *data)
{
	if(data[2 * MyID] & 0x80) RED_LED_ON;
	else RED_LED_OFF;
	if(data[2 * MyID] & 0x40) GREEN_LED_ON;
	else GREEN_LED_OFF;
	if(data[2 * MyID] & 0x20) BLUE_LED_ON;
	else BLUE_LED_OFF;
	ChanPower = (data[2 * MyID] >> 4) & 0x01 ;
	ChanPosition = (((uint16_t)data[2 * MyID] & 0x0f) << 4) | data[2 * MyID + 1];
}

void Read_Position(void)
{
	uint8_t data[3];
	uint16_t position;

	position = ADC_Read(1);
	data[0] = Servo.Id;
	data[1] = position >> 8;
	data[2] = position & 0xff;
	ComCode(MyID,  MainID,  SetParameter, (uint8_t *)data,  3);
}

void Servo_PID_Loop(float EurDesir, float measure, float *Output)
{
	static float Err = 0, ErrSum = 0, DErr = 0, LastErr = 0;
	float Pout, Iout, Dout;
	Err = EurDesir - measure;
	ErrSum += Err;
	DErr = Err - LastErr;
	LastErr = Err;

	Pout = Servo.Kp * Err;
	Pout = constrain(Pout, -1, 1);

	Iout = Servo.Ki * ErrSum;
	Iout = constrain(Pout, -1, 1);

	Dout = Servo.Kd * DErr;
	Dout = constrain(Dout, -0.2, 0.2);

	*Output = Pout + Iout + Dout;
	*Output = constrain(*Output, -1, 1);
}

float constrain(float amt, float low, float high)
{
	if(amt < low)
	{
		return low;
	}
	else if(amt > high)
	{
		return high;
	}
	else
	{
		return amt;
	}
}
