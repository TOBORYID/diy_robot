#include "servo.h"
#include "eeprom.h"
#include "adc.h"
#include "communication.h"

uint16_t Position[24] = {2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
                         2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
                         2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048
                        };

void Write_Position(uint8_t *data)
{
	w_position W_Position;
	memcpy(&W_Position, data, 36);
	Position[0] = W_Position.CH0;
	Position[1] = W_Position.CH1;
	Position[2] = W_Position.CH2;
	Position[3] = W_Position.CH3;
	Position[4] = W_Position.CH4;
	Position[5] = W_Position.CH5;
	Position[6] = W_Position.CH6;
	Position[7] = W_Position.CH7;
	Position[8] = W_Position.CH8;
	Position[9] = W_Position.CH9;
	Position[10] = W_Position.CH10;
	Position[11] = W_Position.CH11;
	Position[12] = W_Position.CH12;
	Position[13] = W_Position.CH13;
	Position[14] = W_Position.CH14;
	Position[15] = W_Position.CH15;
	Position[16] = W_Position.CH16;
	Position[17] = W_Position.CH17;
	Position[18] = W_Position.CH18;
	Position[19] = W_Position.CH19;
	Position[20] = W_Position.CH20;
	Position[21] = W_Position.CH21;
	Position[22] = W_Position.CH22;
	Position[23] = W_Position.CH23;
}

void Read_Position(void)
{
	uint8_t data[3];
	uint16_t position;

	position = ADC_Read(1);
	data[0] = Servo.Id;
	data[1] = position >> 8;
	data[2] = position & 0xff;
	ComCode(MyID,  MainID,  SetParameter,  &data,  3);
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
