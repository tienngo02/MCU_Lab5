/*
 * scheduler.c
 *
 *  Created on: Nov 26, 2023
 *      Author: nvtie
 */

#include "scheduler.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct sTask{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t  RunMe;
	uint32_t TaskID;
	struct sTask *next;
} sTask;
sTask *head = NULL;

uint8_t current_index_task = 0;
int deleted_ID = -1;

uint32_t get_new_ID(){
	uint32_t newID;
    if(deleted_ID >= 0){
    	newID = deleted_ID;
    	deleted_ID = -1;
    	return newID;
    }
    else{
    	newID = current_index_task;
		current_index_task++;
		return newID;
    }
}

void SCH_Go_To_Sleep(){
	// Enter low-power mode (Sleep mode). The MCU will wake up on the next interrupt
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void SCH_Init(void){
	head = NULL;
	current_index_task = 0;
	deleted_ID = -1;
}

uint32_t SCH_Add_Task(void (*p_function)(), uint32_t DELAY, uint32_t PERIOD){
	sTask *newTask = (sTask*)malloc(sizeof(sTask));
    newTask->pTask = p_function;
    newTask->Delay = DELAY;
    newTask->Period = PERIOD;
    newTask->RunMe = 0;
    newTask->TaskID = get_new_ID();
    newTask->next = NULL;

    if(head == NULL){
    	newTask->next = head;
        head = newTask;
        return newTask->TaskID;
    }

    uint32_t sumDelay = 0;
    sTask *current = head;
    sTask *prev = NULL;
    while(current != NULL && (sumDelay + current->Delay) <= DELAY){
    	sumDelay += current->Delay;
    	prev = current;
    	current = current->next;
    }

    if (current != NULL){
        if (prev != NULL){
        	newTask->Delay -= sumDelay;
        	current->Delay -= newTask->Delay;
        	newTask->next = current;
            prev->next = newTask;
        }
        else{
        	newTask->next = head;
        	head = newTask;
        	newTask->next->Delay -= DELAY;
        }
    }
    else{
    	newTask->Delay -= sumDelay;
    	newTask->next = current;
    	prev->next = newTask;
    }
    return newTask->TaskID;
}

void SCH_Update(void){
	if(head != NULL){
		if(head->Delay > 0){
			head->Delay--;
		}
		if(head->Delay == 0){
			head->RunMe +=1;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	if(head == NULL) return;
	if(head->RunMe > 0){
		(*head->pTask)();
		head->RunMe--;

		deleted_ID = head->TaskID;
		if(head->Period > 0) {
			SCH_Add_Task(head->pTask, head->Period, head->Period);
		}
		SCH_Delete_Task(head->TaskID);

		if(head->Delay <= 0) head->RunMe += 1;
	}
	SCH_Go_To_Sleep();
}

void SCH_Delete_Task(uint32_t TASK_ID){

    sTask *current = head;
    sTask *prev = NULL;

    while(current != NULL && current->TaskID != TASK_ID) {
        prev = current;
        current = current->next;
    }
    if (current != NULL){
        if (prev != NULL){
            prev->next = current->next;
        }
        else{
            head = current->next;
        }
        free(current);
    }
}






