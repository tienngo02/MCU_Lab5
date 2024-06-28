/*
 * fsm_manual.c
 *
 *  Created on: Oct 21, 2023
 *      Author: nvtie
 */

#include "fsm_manual.h"

int redMod = 1;
int yellowMod = 1;
int greenMod = 1;

void ledBalance(){
	if(red == (green + yellow)) return;
	else if(red < (green + yellow)){
		red = green + yellow;
	}
	else{
		green = red - yellow;
	}
}

void fsm_manual_run(){
	switch(status){
	case MAN_RED:
		updateClockBuffer(2, redMod);

		if(isButtonPressed(0) == 1){
			status = MAN_YELLOW;
			SCH_Delete_Task(taskID);
			taskID = SCH_Add_Task(toggleLedYELLOW, 25, 25);
			clearAllLED();
		}
		if(isButtonPressed(1) == 1){
			redMod++;
			if(redMod > 99) redMod = 1;
		}
		if(isButtonPressed(2) == 1){
			red = redMod;
		}
		break;
	case MAN_YELLOW:
		updateClockBuffer(3, yellowMod);
		if(isButtonPressed(0) == 1){
			status = MAN_GREEN;
			SCH_Delete_Task(taskID);
			taskID = SCH_Add_Task(toggleLedGREEN, 25, 25);
			clearAllLED();
		}
		if(isButtonPressed(1) == 1){
			yellowMod++;
			if(yellowMod > 99) yellowMod = 1;
		}
		if(isButtonPressed(2) == 1){
			yellow = yellowMod;
		}
		break;
	case MAN_GREEN:
		updateClockBuffer(4, greenMod);
		if(isButtonPressed(0) == 1){
			status = INIT;
			ledBalance();
			SCH_Delete_Task(taskID);
		}
		if(isButtonPressed(1) == 1){
			greenMod++;
			if(greenMod > 99) greenMod = 1;
		}
		if(isButtonPressed(2) == 1){
			green = greenMod;
		}
		break;
	default:
		break;
	}
}
