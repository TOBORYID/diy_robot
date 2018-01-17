#ifndef __MAIN_H__
#define __MAIN_H__

#include "adc.h"
#include "eeprom.h"
#include "led.h"
#include "pwm.h"
#include "servo.h"
#include "systime.h"
#include "task.h"
#include "uart.h"
#include "inc.h"
#include "communication.h"

typedef struct self_para
{
	float PID_Kp;
	float PID_Ki;
	float PID_Kd;
	uint8_t Id;
	uint16_t position;
	float vot;
	float cur;
} self_para_t;

void LOOP(void);
void Port_Init(void);
#endif
