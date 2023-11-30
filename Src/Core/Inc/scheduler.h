/*
 * scheduler.h
 *
 *  Created on: Nov 16, 2023
 *      Author: huaho
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

typedef struct{
	void(*pTask)(void);
	uint32_t	Delay;
	uint32_t	Period;
	uint8_t		RunMe;
	uint32_t	TaskID;
}sTasks;

#define SCH_MAX_TASKS 	5
#define	TICK_FREQ		100

void SCH_init(void);
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_update();
void SCH_Dispatch_Tasks(void);

#endif /* INC_SCHEDULER_H_ */
