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
	while(1)
	{
		Task_Running();
	}
}
uint16_t ADC_Value;
uint16_t Input = 1000;
float MotorOutput;

void LOOP(void)
{
	ADC_Value = ADC_Read(0);
	Servo_PID_Loop(Input, ADC_Value, &MotorOutput);
	Pwm_Output(MotorOutput);
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