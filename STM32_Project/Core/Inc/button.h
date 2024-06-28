/*
 * button.h
 *
 *  Created on: Oct 21, 2023
 *      Author: nvtie
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET
#define MAX_BUTTON 3

extern int button1_flag;

int isButtonPressed(int index);
void getKeyInput();

#endif /* INC_BUTTON_H_ */
