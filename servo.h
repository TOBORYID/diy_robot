#ifndef __SERVO_H__
#define __SERVO_H__

#include "stdint.h"

typedef struct
{
	uint16_t CH0: 12;
	uint16_t CH1: 12;
	uint16_t CH2: 12;
	uint16_t CH3: 12;
	uint16_t CH4: 12;
	uint16_t CH5: 12;
	uint16_t CH6: 12;
	uint16_t CH7: 12;
	uint16_t CH8: 12;
	uint16_t CH9: 12;
	uint16_t CH10: 12;
	uint16_t CH11: 12;
	uint16_t CH12: 12;
	uint16_t CH13: 12;
	uint16_t CH14: 12;
	uint16_t CH15: 12;
	uint16_t CH16: 12;
	uint16_t CH17: 12;
	uint16_t CH18: 12;
	uint16_t CH19: 12;
	uint16_t CH20: 12;
	uint16_t CH21: 12;
	uint16_t CH22: 12;
	uint16_t CH23: 12;
} w_position;

typedef struct
{
	uint8_t id;
	uint16_t position;
} r_position;

void Servo_PID_Loop(float EurDesir, float measure, float* Output);
float constrain(float amt, float low, float high);

#endif
