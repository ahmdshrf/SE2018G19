#include "MC2.h"
#include <util/delay.h>

static volatile uint8 counter = 0;

void delay_Timer1(uint8 seconds)
{
	 counter++;
	 if ( counter == seconds)
	 {
		 counter = 0;
	 }
}

void main()
{
	/*delaring variables*/
	uint8 originalPass;
	uint8 sentPass;
	uint8 checkPass;
	uint8 reciveFlag;
	uint8 resumeFlag;

	/*PIN configrations*/
	DDRA |= (1<<PA0) |(1<<PA1) | (1<<PA5) | (1<<PA3); //PIN0,1 are for motor & 1 for buzzer
	//initially all pins are grounded except for the pin of the buzzer
	PORTA = 0b00000000;

	/*
	DDRB = 0XFF;
	PORTB = 1;
	*/

	/*Peripherals initialization*/
	UART_init();
	_delay_ms(100);

	//Hand shaking
	UART_sendByte(START);

	EEPROM_init();
	//while(!(UART_recieveByte() == 0)) {}

	//Setting CallBack Function
	setCallBackFunc(delay_Timer1);

	originalPass = UART_recieveByte();
	while(! EEPROM_writeByte(0x0311, originalPass) ) {} //inserting the pass in the EEPROM--
	//and make sure the process id done correctly


	while(1)
	{
		/*hand shaking*/
		PORTB = PORTB << 1;
		do
		{
			resumeFlag = UART_recieveByte();
		}
		while ( resumeFlag != NEWPASSWORD );
		UART_sendByte(OK);
		/****************************************************/
		_delay_ms(50);
		//recieve the entered password
		sentPass = UART_recieveByte(); // recieve password from the user

		//UART_sendByte(RESPONSE);
		//Checking if the entered password is right
		if ( sentPass == originalPass)
		{
			UART_sendByte(TRUE);
		}
		else
		{
			UART_sendByte(FALSE);
		}

		//_delay_ms(50);
		//Taking action according to the entered password
		do
		{
			reciveFlag = UART_recieveByte();

		}  while((reciveFlag != CONTINUE) && (reciveFlag != SAFE) && (reciveFlag != DANGER));

		if (reciveFlag == CONTINUE)
		{
			continue;
		}
		else if ( reciveFlag == SAFE)
		{
			PORTA |= 1<<PA0;
			PORTA &= ~(1<<PA5);
		}
		else if (reciveFlag == DANGER)
		{
			PORTA &= ~(1<<PA0);
			PORTA |= (1<<PA5);

			Timer_OF_init();
			while(counter <= 3) {}
			Timer_stop ();

			//_delay_ms(8000000);
			PORTA &= ~(1<<PA5);
		}
		/*
		do
		{
			reciveFlag = UART_recieveByte();
		}
		while( (reciveFlag != 11) && (reciveFlag != 10) );

		*/
		/*
		if((reciveFlag==SAFE) || (reciveFlag==DANGER))
		{

			if (reciveFlag==SAFE)
			{
				//rotating motor CW for 15 seconds
				PORTA |= 1<<PA0;
				PORTA &=~(1<<PA1);

				Timer_OF_init();
				while(counter != MOTOR_TIME) {}
				Timer_stop ();

				//waiting 3 seconds
				PORTA &=~(1<<PA0);
				PORTA &=~(1<<PA1);
				Timer_OF_init();
				while(counter != DELAY_TIME) {}
				Timer_stop ();

				//rotating motor CCW for 15 seconds
				PORTA |= (1<<PA1);
				PORTA &=~(1<<PA0);
				Timer_OF_init();
				while(counter != MOTOR_TIME) {}
				Timer_stop ();

				//stop the motor
				PORTA &=~(1<<PA0);
				PORTA &=~(1<<PA1);

			}

			else if (UART_recieveByte()==DANGER)
			{
				//operating buzzer for 30 seconds
				PORTA &= ~(1<<PA5);
				Timer_OF_init();
				while(counter != BUZZER_TIME) {}
				Timer_stop ();
				PORTA |=( 1<<PA5 );
			}


		}
		*/
		//UART_sendByte(100);

	}

}









