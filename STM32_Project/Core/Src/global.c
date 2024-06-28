/*
 * global.c
 *
 *  Created on: 21 thg 10, 2023
 *      Author: nvtie
 */
#include "global.h"

int status = 0;
int red = 5;
int green = 3;
int yellow = 2;
int index_led = 0;
uint32_t taskID;

void display7SEG(int num){
	if(num==1 || num==4) HAL_GPIO_WritePin (SEG7_A_GPIO_Port, SEG7_A_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_A_GPIO_Port, SEG7_A_Pin, RESET);

	if(num==5 || num==6) HAL_GPIO_WritePin (SEG7_B_GPIO_Port, SEG7_B_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_B_GPIO_Port, SEG7_B_Pin, RESET);

	if(num==2) HAL_GPIO_WritePin (SEG7_C_GPIO_Port, SEG7_C_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_C_GPIO_Port, SEG7_C_Pin, RESET);

	if(num==1 || num==4 || num==7) HAL_GPIO_WritePin (SEG7_D_GPIO_Port, SEG7_D_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_D_GPIO_Port, SEG7_D_Pin, RESET);

	if(num==1 || num==3 || num==4 || num==5 || num==7 || num==9) HAL_GPIO_WritePin (SEG7_E_GPIO_Port, SEG7_E_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_E_GPIO_Port, SEG7_E_Pin, RESET);

	if(num==1 || num==2 || num==3 || num==7) HAL_GPIO_WritePin (SEG7_F_GPIO_Port, SEG7_F_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_F_GPIO_Port, SEG7_F_Pin, RESET);

	if(num==0 || num==1 || num==7) HAL_GPIO_WritePin (SEG7_G_GPIO_Port, SEG7_G_Pin, SET);
	else HAL_GPIO_WritePin (SEG7_G_GPIO_Port, SEG7_G_Pin, RESET);

}

int led_buffer[4] = {0, 0, 0, 0};

void update7SEG(int index){
	switch(index){
	case 0:
		// Display the first 7 SEG with led_buffer [0]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		// Display the second 7 SEG with led_buffer [1]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		display7SEG(led_buffer[1]);
		break;
	case 2:
		// Display the third 7 SEG with led_buffer [2]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		// Display the forth 7 SEG with led_buffer [3]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		display7SEG(led_buffer[3]);
		break;
	default:
		break;
	}
}

void updateClockBuffer(int sec1, int sec2){
	led_buffer[0] = sec1/10;
	led_buffer[1] = sec1%10;
	led_buffer[2] = sec2/10;
	led_buffer[3] = sec2%10;
}

void clearAllLED(){
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
	HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
	HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);
}

void turnonTrafficLight1(int led){
	switch(led){
	case RED:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, RESET);
	default:
		break;
	}
}

void turnonTrafficLight2(int led){
	switch(led){
	case RED:
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, RESET);
	default:
		break;
	}
}

void toggleLedRED(){
	HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
	HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
}

void toggleLedYELLOW(){
	HAL_GPIO_TogglePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin);
	HAL_GPIO_TogglePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin);
}

void toggleLedGREEN(){
	HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
	HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
}

void update4_7SEG(){
	update7SEG(index_led);
	index_led++;
	if(index_led >= MAX_LED) index_led = 0;
}
