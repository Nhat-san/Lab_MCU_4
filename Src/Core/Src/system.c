/*
 * system.c
 *
 *  Created on: Nov 30, 2023
 *      Author: huaho
 */

#include "system.h"

void Debug_led_0();
void Debug_led_1();
void Debug_led_2();
void Debug_led_3();
void oneshot_led();

void Tasks_init(){
	SCH_Add_Task(Debug_led_0, 0, 1000); 	//toggle led with cycle 2s first excuted after 0s
	SCH_Add_Task(Debug_led_1, 2000, 2000);	//toggle led with cycle 4s first excuted after 2s
	SCH_Add_Task(Debug_led_2, 4000, 2000);	//toggle led with cycle 4s first excuted after 4s
	SCH_Add_Task(Debug_led_3, 5000, 500);	//toggle led with cycle 0.5s first excuted after 5s
	SCH_Add_Task(oneshot_led, 5000, 0);		//oneshot
}


void Debug_led_0(){
	HAL_GPIO_TogglePin(DEBUG_LED_0_GPIO_Port, DEBUG_LED_0_Pin);
}
void Debug_led_1(){
	HAL_GPIO_TogglePin(DEBUG_LED_1_GPIO_Port, DEBUG_LED_1_Pin);
}
void Debug_led_2(){
	HAL_GPIO_TogglePin(DEBUG_LED_2_GPIO_Port, DEBUG_LED_2_Pin);
}
void Debug_led_3(){
	HAL_GPIO_TogglePin(DEBUG_LED_3_GPIO_Port, DEBUG_LED_3_Pin);
}
void oneshot_led(){
	HAL_GPIO_TogglePin(ONESHOT_LED_GPIO_Port, ONESHOT_LED_Pin);
}

void sys_loop(){
	SCH_Dispatch_Tasks();
}


