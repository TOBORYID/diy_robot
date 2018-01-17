#include "main.h"

int main(void)
{
	Port_Init();
	ADC_Init();
	LED_Init();
	Pwm_Init();
	uart_init(9600);
	Init_Task();
	SysTime_Init();
	Task_Init(0,  -1,  1,  Com_Update);
	while(1)
	{
		Task_Running();
	}
}

extern uint16_t ChanPosition;
extern uint8_t ChanPower;
uint16_t ADC_Value;
float MotorOutput;

void LOOP(void)
{
	ADC_Value = ADC_Read(0);
	Servo_PID_Loop(ChanPosition, ADC_Value, &MotorOutput);
	if(ChanPower) Pwm_Output(MotorOutput);
	else Pwm_Output(0);
}

void Port_Init(void)
{
	cli();
	PORTB = 0x00;
	DDRB = 0x00;
	PORTC = 0x00;
	DDRC = 0x00;
	PORTD = 0x00;
	DDRD = 0x00;

	MCUCR = 0x00;
	GICR = 0x00;
	TIMSK = 0x00;
	sei();
}