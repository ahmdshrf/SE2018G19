#include"MC1.h"
#include "avr/delay.h"

uint8 getPow(uint8 pow , uint8 num)
{
	uint8 result = 1;
	for( int i = 0; i<pow ; i++)
	{
		result *= num;
	}
	return result;
}

void main()
{
	uint8 counter = 0;
	uint8 passArr1[3];
	uint8 passArr2[3];
	uint8 passEntered[3];
	uint8 password1 = 0;
	uint8 password2 = 0;
	uint8 sentpassword=0;
	uint8 noOfPasswordSetting;
	uint8 noOfPasswordEntering;
	uint8 numPressed;
	uint8 M2_reply;
	uint8 passIsTrue=0;
	uint8 passFlag;
	uint8 respond_pass;
	DDRB = 0XFF;
	PORTB = 0;
	uint8 test;

	LCD_init();
	UART_init();
	EEPROM_init();

	//setting the original password
	do
	{
		//Here we're entering the password for the 1st time
		_delay_ms(100);
		//recieveFlag = 0;
		noOfPasswordSetting = 0;

		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Set Pass");
		LCD_displayStringRowColumn(1,0,"Pass:");
		LCD_goToRowColumn(1,6);

		//Enter password of 3 numbers
		for(counter = 0 ; counter < 3 ; counter++)
		{
			//_delay_ms(500);
			//get number preesed
			numPressed = KeyPad_getPressedKey();
			_delay_ms(500);
			LCD_intgerToString(numPressed);
			//store this number in an array
			passArr1[counter]=numPressed;
		}

		//Verifying the password
		do
		{
			//_delay_ms(500);
			passFlag=0;
			noOfPasswordSetting++;
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Set Pass again");
			LCD_displayStringRowColumn(1,0,"Pass:");
			LCD_goToRowColumn(1,6);

			for(counter = 0 ; counter < 3 ; counter++)
			{
				//_delay_ms(1000);
				//get number preesed
			    numPressed = KeyPad_getPressedKey();
				_delay_ms(500);
				LCD_intgerToString(numPressed);
				//store this number in an array
				passArr2[counter]=numPressed;
			}

			//Make sure the Re-entered password is matching the 1st one
			for ( counter = 0 ; counter<3 ; counter ++)
			{
				if (passArr1[counter] != passArr2[counter])
				{
					passFlag=1;
				}
			}
		}
		//Re-enter the same password if the he didnot verified the first password
		//and the number of password setting is < 3
		while (noOfPasswordSetting < 3 &&  passFlag==1);

	}
	while ( passFlag == 1); // if the two password aren't same after 4 times of entering the second one
	// the process will be repeated again


	/*
	//Hand Shaking
	while (UART_recieveByte() != START) {} //WAITINTG UNTILL THE 2ND MC BECOME AVAILABLE

	_delay_ms(1000);
	*/
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"OK");




	//making the password as 1-bytenumber not as an array
	for (counter = 0 ; counter <3 ; counter ++)
	{
		password1 += passArr1[counter] * getPow(counter , 10);
	}

	_delay_ms(500);

	/*
	//sending the password to the 2nd Uart to store it
	UART_sendByte(password1); //sending the original password to the second MC
	*/

	//Storing the origina; passwordd in the EEPROM
	while(! EEPROM_writeByte(0x0311, password1) ) {} //inserting the pass in the EEPROM--
													 //and make sure the process id done correctly


	_delay_ms(500);


	while(1)
	{
		/*test
		PORTB |= (1<<test);
		//PORTB |= 1<<PB1;*/


		noOfPasswordEntering = 0; // initialize the process


		do
		{

			_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Enter Pass");
			LCD_displayStringRowColumn(1,0,"Pass:");
			//LCD_clearScreen();

			LCD_goToRowColumn(1,6);
			passIsTrue=0;
			sentpassword=0;

			for(counter = 0 ; counter < 3 ; counter++)
			{
				//_delay_ms(1000);
				numPressed=KeyPad_getPressedKey();
				_delay_ms(500);
				LCD_intgerToString(numPressed);
				passEntered[counter]=numPressed;
			}

			for (counter = 0 ; counter <3 ; counter ++)
			{
				sentpassword += passEntered[counter] * getPow(counter , 10);
			}

			_delay_ms(10);


			/*
			//Hand Shaking
			UART_sendByte(NEWPASSWORD);
			_delay_ms(100);
			PORTB = 1<<noOfPasswordEntering;

			while (UART_recieveByte() != OK) {}


			UART_sendByte(sentpassword); //sending the password to the 2nd MC to open the door
			//_delay_ms(5);

			do
			{
				M2_reply = UART_recieveByte();
			}
			while( (M2_reply!=FALSE) && (M2_reply!=TRUE) );
			*/

			//while ((M2_reply != TRUE) || (M2_reply != FALSE)) {}

			//M2_reply = UART_recieveByte();

			//M2_reply = FALSE;

			do
			{
				M2_reply=EEPROM_readByte(0x0311, &respond_pass);
			}
			while (!M2_reply);


			//Testing if the entered password is right
			if (respond_pass == sentpassword)
			{
				passIsTrue=1;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Correct");
				_delay_ms(100);
			}
			else
			{
				passIsTrue=0;
				noOfPasswordEntering += 1;
			}

			/*
			if ( M2_reply == FALSE)
			{
				noOfPasswordEntering += 1;
				if(noOfPasswordEntering<3)
				{
					UART_sendByte(CONTINUE);
				}
				else
				{
					UART_sendByte(DANGER);
				}
			}
			else if (M2_reply == TRUE)
			{
				UART_sendByte(SAFE); //to operate the motor
				passIsTrue = 1 ;
				_delay_ms(1000);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Done !");
				_delay_ms(1000);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Enter Pass");
				LCD_displayStringRowColumn(1,0,"Pass:");
			}
			*/

		}while(noOfPasswordEntering < 3 && passIsTrue == 0 );

		LCD_clearScreen();

		if (noOfPasswordEntering >= 3 && passIsTrue == 0)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Theif");
			_delay_ms(1000); //lock the system for an hour
			LCD_clearScreen();
		}


		//Hand Shaking
		UART_sendByte(REQUEST); //REQUEST
		while (UART_recieveByte() != START) {} //WAITINTG UNTILL THE 2ND MC BECOME AVAILABLE
		_delay_ms(100);
		if (passIsTrue == 0)
		{
			UART_sendByte(DANGER); //to operate buzzer
		}
		else
		{
			UART_sendByte(SAFE); //to operate buzzer
		}

	}





}
