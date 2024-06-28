/*
 * global.h
 *
 *  Created on: 21 thg 10, 2023
 *      Author: nvtie
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "button.h"
#include "main.h"
#include "scheduler.h"

#define INIT          1
#define RED1_GREEN2   2
#define RED1_YELLOW2  3
#define GREEN1_RED2   4
#define YELLOW1_RED2  5

#define MAN_RED       12
#define MAN_GREEN     13
#define MAN_YELLOW    14

#define RED           1
#define GREEN         2
#define YELLOW        3

#define MAX_LED       4

extern int status;
extern int index_led;
extern int red;
extern int green;
extern int yellow;
extern uint32_t taskID;

void clearAllLED();
void turnonTrafficLight1(int led);
void turnonTrafficLight2(int led);
void toggleLedRED();
void toggleLedGREEN();
void toggleLedYELLOW();
void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer(int sec1, int sec2);
void update4_7SEG();

#endif /* INC_GLOBAL_H_ */
