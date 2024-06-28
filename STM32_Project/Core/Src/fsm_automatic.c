/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 10, 2023
 *      Author: nvtie
 */
#include "fsm_automatic.h"

int sec1 = 0;
int sec2 = 0;

void updateLightTime(){
	if(sec1 > 0) sec1--;
	if(sec2 > 0) sec2--;
}

void ifButton1Pressed(){
	if(isButtonPressed(0) == 1){
		status = MAN_RED;
		SCH_Delete_Task(taskID);
		taskID = SCH_Add_Task(toggleLedRED, 25, 25);
		clearAllLED();
	}
}

void fsm_automatic_run(){
	switch(status){
	case INIT:
		clearAllLED();
		status = RED1_GREEN2;
		sec1 = red;
		sec2 = green;
		updateClockBuffer(sec1, sec2);
		taskID = SCH_Add_Task(updateLightTime, 100, 100);
		break;
	case RED1_GREEN2:
		turnonTrafficLight1(RED);
		turnonTrafficLight2(GREEN);

		updateClockBuffer(sec1, sec2);

		if(sec2 <= 0){
			status = RED1_YELLOW2;
			sec2 = yellow;
		}
		ifButton1Pressed();
		break;
	case RED1_YELLOW2:
		turnonTrafficLight1(RED);
		turnonTrafficLight2(YELLOW);

		updateClockBuffer(sec1, sec2);

		if(sec2 <= 0){
			status = GREEN1_RED2;
			sec1 = green;
			sec2 = red;
		}
		ifButton1Pressed();
		break;
	case GREEN1_RED2:
		turnonTrafficLight1(GREEN);
		turnonTrafficLight2(RED);

		updateClockBuffer(sec1, sec2);

		if(sec1 <= 0){
			status = YELLOW1_RED2;
			sec1 = yellow;
		}
		ifButton1Pressed();
		break;
	case YELLOW1_RED2:
		turnonTrafficLight1(YELLOW);
		turnonTrafficLight2(RED);

		updateClockBuffer(sec1, sec2);

		if(sec1 <= 0){
			status = RED1_GREEN2;
			sec1 = red;
			sec2 = green;
		}
		ifButton1Pressed();
		break;
	default:
		break;
	}

}

