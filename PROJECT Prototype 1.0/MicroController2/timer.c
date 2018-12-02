#include "timer.h"

unsigned int g_tick = 0;
static volatile void (*g_Timer0_Call_Back_Ptr)(void);

void Timer_OF_init()
{
	TCCR0 = (1<<FOC0) | (1<<CS00) | (CS02);
	TCNT0 = 0;
	TIMSK = (1<<TOIE0);
}

/*void Timer_pwm_init(int duty)
{
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<CS00) | (CS02);
}
*/
void setCallBackFunc(void(*ptr2func)(uint8))
{
	g_Timer0_Call_Back_Ptr = ptr2func;
}

void Timer_stop ()
{
	TCCR0 = 0;
}

ISR (TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		g_Timer0_Call_Back_Ptr();
		g_tick = 0;
	}
}




