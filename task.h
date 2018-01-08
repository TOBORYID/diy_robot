#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>

#define MAXTASKS 10

typedef void (*Task_Function)(void);

typedef struct
{
	uint8_t id;
	int16_t times;
	uint16_t period;
	uint16_t cnt;
	Task_Function task;
} TASK;

void Init_Task(void);
void Task_Init(uint8_t id, uint16_t time, uint16_t period, Task_Function task);
void Task_DeInit(uint8_t id);
void runtasks(void);
void TaskCount(void);

#endif
