#include "task.h"

static volatile unsigned char TaskTick;

TASK tasks[MAXTASKS];

void Init_Task(void)
{
	for(uint8_t i = 0; i < MAXTASKS; i++)
	{
		tasks[i].times = 0;
		tasks[i].period = 0;
		tasks[i].cnt = 0;
		tasks[i].task = (Task_Function)0x00;
	}
}

void Task_Init(uint8_t id, uint16_t time, uint16_t period, Task_Function task)
{
	tasks[id].times = time;
	tasks[id].period = period;
	tasks[id].cnt = period;
	tasks[id].task = task;
}

void Task_DeInit(uint8_t id)
{
	tasks[id].task = (Task_Function)0x00;
}

void Task_Running(void)
{
	uint8_t i;
	for(i = 0; i < MAXTASKS; i++)
	{
		if(tasks[i].task != 0)
		{
			if(tasks[i].cnt == tasks[i].period)
			{
				if(tasks[i].times != 0)
				{
					tasks[i].cnt = 0;
					(*tasks[i].task)();
				}
				if(tasks[i].times > 0)
				{
					tasks[i].times--;
					if(tasks[i].times == 0)
					{
						tasks[i].task = (Task_Function)0x00;
					}
				}
			}
		}
	}
}

void Task_Cnt(void)
{
	uint8_t i;
	for(i = 0; i < MAXTASKS; i++)
	{
		if(tasks[i].cnt < tasks[i].period)
		{
			tasks[i].cnt++;
		}
	}
}
