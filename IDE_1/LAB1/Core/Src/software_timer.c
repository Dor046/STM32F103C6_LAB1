/*
 * software_timer.c
 *
 *  Created on: Sep 28, 2025
 *      Author: User
 */

#include "software_timer.h"
#include "main.h"
int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int currentDigit = 0;

//=====================================================
void setTimer1(int duration){
	timer1_counter = duration;
	timer1_flag = 0;
}
//=====================================================
void setTimer2(int duration){
	timer2_counter = duration;
	timer2_flag = 0;
}
//=====================================================
void timerRun(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}

	if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter <= 0){
				timer2_flag = 1;
			}
		}
}
//=====================================================
void display7SEG(int num)
	{
	    // Tắt hết
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
	                             GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,
	                             GPIO_PIN_SET);

	    switch(num) {
	        case 0: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
	                                         GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET); break;
	        case 1: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET); break;
	        case 2: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|
	                                         GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        case 3: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
	                                         GPIO_PIN_3|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        case 4: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        case 5: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        case 6: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|
	                                         GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        case 7: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET); break;
	        case 8: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
	                                         GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        case 9: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
	                                         GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET); break;
	        default: break;
	    }
	}
//=====================================================
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4}; // có thể đổi giá trị để test
void update7SEG(int index) {
    // Tắt hết các EN trước
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);
    switch (index) {
    case 0:
        display7SEG(led_buffer[0]);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // bật EN1
        break;

    case 1:
        display7SEG(led_buffer[1]);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); // bật EN2
        break;

    case 2:
        display7SEG(led_buffer[2]);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // bật EN3
        break;

    case 3:
        display7SEG(led_buffer[3]);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // bật EN4
        break;

    default:
        break;
    }
}
//ex5=====================================================
int hour = 15, minute = 8, second = 50;
void updateClockBuffer(){
	 // Hiển thị giờ: 2 chữ số
	    led_buffer[0] = hour / 10;   // hàng chục giờ
	    led_buffer[1] = hour % 10;   // hàng đơn vị giờ

	    // Hiển thị phút: 2 chữ số
	    led_buffer[2] = minute / 10; // hàng chục phút
	    led_buffer[3] = minute % 10; // hàng đơn vị phút
}



