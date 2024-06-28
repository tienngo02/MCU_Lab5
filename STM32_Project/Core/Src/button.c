/*
 * button.c
 *
 *  Created on: Oct 21, 2023
 *      Author: nvtie
 */
#include "button.h"

int KeyReg0[MAX_BUTTON] = {NORMAL_STATE};
int KeyReg1[MAX_BUTTON] = {NORMAL_STATE};
int KeyReg2[MAX_BUTTON] = {NORMAL_STATE};
int KeyReg3[MAX_BUTTON] = {NORMAL_STATE};

int TimeOutForKeyPress[MAX_BUTTON] = {200};
int button_flag[MAX_BUTTON] = {0};

int isButtonPressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	//TODO
//	HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
	button_flag[index] = 1;
}

void getKeyInput(){
	for(int i=0; i<MAX_BUTTON; i++){
	  KeyReg0[i] = KeyReg1[i];
	  KeyReg1[i] = KeyReg2[i];
	  //Add your button here
	  KeyReg2[0] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	  KeyReg2[1] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
	  KeyReg2[2] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
	  if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])){
		if (KeyReg3[i] != KeyReg2[i]){
		  KeyReg3[i] = KeyReg2[i];
		  if (KeyReg2[i] == PRESSED_STATE){
			TimeOutForKeyPress[i] = 200;
			subKeyProcess(i);
		  }
		}else{
		   TimeOutForKeyPress[i]--;
			if (TimeOutForKeyPress[i] == 0){
				KeyReg3[i] = NORMAL_STATE;
			}
		}
	  }
	}
}



