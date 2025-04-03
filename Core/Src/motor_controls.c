/*
 * motor_controls.c
 *
 *  Created on: Apr 2, 2025
 *      Author: tydav
 */

#include "motor_controls.h"
#include "stm32l0xx_it.h"

extern UART_HandleTypeDef huart2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	uint8_t msg[10];
	msg[0] = 64;
	uint8_t msg_len = 1;
	HAL_UART_Transmit(&huart2, msg, msg_len, 100);
}

