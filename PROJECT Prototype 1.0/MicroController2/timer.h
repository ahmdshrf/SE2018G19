/*
 * timer.h
 *
 *  Created on: ١٢‏/١٠‏/٢٠١٨
 *      Author: Ahmed
 */

#ifndef TIMER_H_
#define TIMER_H_

/*included files*/
#include "micro_config.h"
#include "std_types.h"
/************************************************************************************/

/*Macros*/
#define NUMBER_OF_OVERFLOWS_PER_SECOND 31
/************************************************************************************/

/*Function prototypes*/
void Timer_OF_init();
//void Timer_Comp_init(int value);
//void Timer_pwm_init(int duty);
void setCallBackFunc(void(*ptr2func)(uint8));
void Timer_stop ();
/*************************************************************************************/




#endif /* TIMER_H_ */
