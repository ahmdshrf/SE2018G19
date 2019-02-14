#include "MC2.h"
#include <util/delay.h>

static volatile uint8 counter = 0;


void main()
{

	//delaring variables

	uint8 reciveFlag;
	uint32 temp;

	//PIN configrations
	DDRA |= (1<<PA0) |(1<<PA1) | (1<<PA5) | (1<<PA3); //PIN0,1 are for motor & 1 for buzzer
	//initially all pins are grounded except for the pin of the buzzer

	DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB3);

	PORTA = 0b00000000;
	//PORTB = 0b00000000;





	/*Peripherals initialization*/
	ADC_init(); //initialize ADC driver
	UART_init();
	_delay_ms(100);



	while(1)
	{

		//Read temp
		temp = ADC_readChannel(3); // read channel 3 where the temp sensor is connect
		temp = (temp*150*5)/(1023*1.5); //calculate the temp from the ADC value
		//temp =20;

		//temperature control
		adjust_temp(temp,25);
		//_delay_ms(10000);

		//Hand shaking
		if (UART_recieveByte() == REQUEST)
		{
			UART_sendByte(START);
			/*
			do
			{
				reciveFlag = UART_recieveByte();

			}  while((reciveFlag != SAFE) && (reciveFlag != DANGER)); */

			reciveFlag = UART_recieveByte();

			if ( reciveFlag == SAFE)
			{
				PORTB= 1<<PB0;
				PORTA |= 1<<PA0;
				PORTA &= ~(1<<PA1);
				_delay_ms(5000);
				PORTA |= 1<<PA1;
				PORTA &= ~(1<<PA0);
				_delay_ms(5000);
				PORTA=0;

			}
			if ( reciveFlag == DANGER)
			{
				PORTB= 1<<PB1;
			}

		}
	}

}



void adjust_temp(int current_temp , int desired_temp)
{


	if ( (current_temp-2) > desired_temp)
	{
		//Output voltage is 0 and delay 1 minute
		Timer0_PWM_Init (255);

	}
	else if ( (current_temp+2) < desired_temp)
	{
		//Output voltage is 128 and delay 1 minute
		Timer0_PWM_Init (128);
	}

}




void Timer0_PWM_Init(unsigned char set_duty_cycle){

	TCNT0 = 0; // Timer initial value

	OCR0  = set_duty_cycle; //compare value

	//DDRB  = DDRB | (1<<PB3); //set OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

/*int main(void)
{
	unsigned char duty;
	while(1)
	{
		for(duty = 0 ; duty < 255 ; duty++)
		{
			/*increase the LED light intensity
			Timer0_PWM_Init(duty);
			_delay_ms(10);
		}
		_delay_ms(100);
		for(duty = 255 ; duty > 0 ; duty--)
		{
			/*decrease the LED light intensity
			Timer0_PWM_Init(duty);
			_delay_ms(10);
		}
	}
}
*/
