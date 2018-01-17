#ifndef __SERVO_H__
#define __SERVO_H__

#include "stdint.h"

void Write_Position(uint8_t *data);
void Read_Position(void);
void Servo_PID_Loop(float EurDesir, float measure, float *Output);
float constrain(float amt, float low, float high);

#endif
