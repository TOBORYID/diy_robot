#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "inc.h"

typedef struct
{
	uint8_t Id;
	float Kp;
	float Ki;
	float Kd;
} parameter;

extern parameter Servo;

void Write_eeprom(uint16_t address, uint8_t data);
uint8_t Read_eeprom(uint16_t address);
void Write_Parameter(uint8_t *data);
void Read_Parameter(void);
void Init_Parameter(void);

#endif
