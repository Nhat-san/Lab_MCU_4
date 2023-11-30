/*
 * scheduler.c
 *
 *  Created on: Nov 16, 2023
 *      Author: huaho
 */
#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];

uint8_t SCH_Delete_Tasks(uint32_t i);

/* @brief	Add task
 * @param	pFuntion: name of funtion, DELAY: delay first executed,
 * 			PERIOD: interval (in ticks) between repeated executions
 * @retval 	return ID that is corresponding with the added task, SCH_MAX_TASKS is cannot add task
 */
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint8_t index = 0;
	while(index < SCH_MAX_TASKS && (SCH_tasks_G[index].pTask != 0)){
		index++;
	}
	if(index == SCH_MAX_TASKS){
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[index].pTask 	= pFunction;
	SCH_tasks_G[index].Delay 	= DELAY * TICK_FREQ / 1000;
	SCH_tasks_G[index].Period 	= PERIOD * TICK_FREQ / 1000;
	SCH_tasks_G[index].RunMe	= 0;
	return index;
}

/* @brief	Update task
 * @param	pFuntion: name of funtion, DELAY: delay first executed,
 * 			PERIOD: interval (in ticks) between repeated executions
 * @retval 	none
 */
void SCH_update(){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask){
			if(SCH_tasks_G[i].Delay > 0){
				SCH_tasks_G[i].Delay--;
			}
			else{
				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				SCH_tasks_G[i].RunMe++;
			}
		}
	}
}

/* @brief	get the task in the queue to run
 * @param	none
 * @retval 	none
 */
void SCH_Dispatch_Tasks(){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].RunMe && SCH_tasks_G[i].pTask){
			(*SCH_tasks_G[i].pTask)();
			SCH_tasks_G[i].RunMe--;
			if(SCH_tasks_G[i].Period == 0){
				SCH_Delete_Tasks(i);
			}
		}
	}
}

/* @brief	Delete task
 * @param	i: ID of delete task
 * @retval 	1: is task deleted, 0 is cannot delete task
 */
uint8_t SCH_Delete_Tasks(uint32_t i){
	if(i >= SCH_MAX_TASKS){
		return 0;
	}
	SCH_tasks_G[i].pTask = 0;
	return 1;
}
