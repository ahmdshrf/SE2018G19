/*
 * MC1.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */

#ifndef MC2_H_
#define MC2_H_

/*definitions*/
#define TRUE 11
#define FALSE 10
#define DANGER 12
#define SAFE 13
#define NEWPASSWORD 14
#define OK 15
#define RESPONSE 16
#define CONTINUE 20
#define START 1
#define MOTOR_TIME 15
#define BUZZER_TIME 30
#define DELAY_TIME 3
#define REQUEST 45
/****************************************************************************************/

/*included files*/
#include "lcd.h"
#include "adc.h"
#include "external_eeprom.h"
#include "i2c.h"
#include "uart.h"
#include "micro_config.h"
#include "std_types.h"
/*****************************************************************************************/

/*Function Decleration*/
void adjust_temp(int current_temp , int desired_temp);
void Timer0_PWM_Init(unsigned char set_duty_cycle);


#endif /* MC2_H_ */
