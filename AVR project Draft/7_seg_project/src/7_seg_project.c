#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define NUMBER_OF_OVERFLOWS_PER_SECOND 123

unsigned char num[6]={0,0,0,0,0,0};
char flag =0;
void display();


unsigned char tick=0;

void Timer0_init_Normal_Mode(void)
{
	TCNT0 = 0;
	TIMSK = (1<<TOIE0);
	TCCR0 = (1<<FOC0) | (1<<CS02);
	SREG |= (1<<7);
}
void int0_reset(void)
{
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);
	MCUCR |= (1<<ISC00) | (1<<ISC01);
	GICR |= (1<<INT0);
	SREG |= (1<<7);
}



ISR(INT0_vect)
{
	for(int i = 0 ; i<6 ;i++ )
	{
		num[i] = 0;
	}
}

ISR(TIMER0_OVF_vect)
{
	tick++;
	if(tick == NUMBER_OF_OVERFLOWS_PER_SECOND){
		tick=0;
		if(num[5]== 9)
		{
			num[5]= 0;
			num[4]++;
		}
		else
			num[5]++;
		if(num[4]== 6 ){
			num[4]=0;
			num[3]++;
		}
		if(num[3]== 10){
			num[3]=0;
			num[2]++;
		}
		if(num[2]== 6 ){
			num[2]=0;
			num[1]++;
		}
		if(num[1]==9)
			num[0]++;
	}

}

void display(void)
{
	for(int j=5;j>=0;j--)
	{
		PORTB |=(1<<j);
		PORTA = num[j];
		_delay_ms(5);
		PORTB &=~(1<<j);
	}
}


int main(void)
{
	unsigned char button = 0;
	DDRB = 0xFF;
	DDRD &= ~(1<<PD3);
	PORTD |= (1<<PD3);
	DDRA  = 0xFF;
	PORTA = 0x00;
	int0_reset();
	Timer0_init_Normal_Mode();
    while(1)
    {
    	display();
    	if(PIND & (1<<PD3))
    	{
    		if(button == 0)
    		{
    			SREG = SREG ^ (1<<7);
    			button = 1;
    		}
    	}
    	else
    		button = 0;
    }
}
