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
extern int currentDigit;
extern const int MAX_LED;
extern int index_led;
extern int led_buffer[4];
extern int hour;
extern int minute;
extern int second;

void setTimer1(int duration);
void setTimer2(int duration);
void timerRun();
void display7SEG (int num);
void update7SEG(int index);
void updateClockBuffer();

/*extern const int MAX_LED_MATRIX;
extern int index_led_matrix;
extern int matrix_buffer[8];
void updateLEDMatrix(int index);*/
#endif /* INC_SOFTWARE_TIMER_H_ */
