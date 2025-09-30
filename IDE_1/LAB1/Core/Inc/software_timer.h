/*
 * software_timer.h
 *
 *  Created on: Sep 28, 2025
 *      Author: User
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;


void setTimer1(int duration);
void setTimer2(int duration);
void timerRun();
void display7SEG (int num);
#endif /* INC_SOFTWARE_TIMER_H_ */
