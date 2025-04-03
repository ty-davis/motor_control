/*
 * command_parser.c
 *
 *  Created on: Apr 1, 2025
 *      Author: tydav
 */

#include "stm32l0xx_hal.h"
#include "system_state.h"
#include "uart_handler.h"
#include "motor_controls.h"

extern UART_HandleTypeDef huart2;

enum status
{
    GET_POSITION = 16,   // 0x10
    MOVE_AZM_BY = 17,    // 0x11
    MOVE_AZM_TO = 18,    // 0x12
    MOVE_ELV_BY = 19,    // 0x13
    MOVE_ELV_TO = 20,    // 0x14
    MOVE_TO = 21,        // 0x15
    GET_SPEED = 32,      // 0x20
    SET_AZM_SPEED = 33,  // 0x21
    SET_ELV_SPEED = 34,  // 0x22
    SET_SPEED = 35,      // 0x23
    DANCE = 36,          // 0x24
    SET_AZM_TOOTH = 64,  // 0x40
    GET_AZM_TOOTH = 65,  // 0x41
    SET_ELV_TOOTH = 66,  // 0x42
    GET_ELV_TOOTH = 67,  // 0x43
    SET_AZM_STEP = 80,   // 0x50
    GET_AZM_STEP = 81,   // 0x51
    SET_ELV_STEP = 82,   // 0x52
    GET_ELV_STEP = 83,   // 0x53
    READY = 0,           // 0x0
    CALIBRATE = 1,       // 0x1
};

enum response
{
    OK_PAYLOAD = 16,   // 0x10
    OK = 32,           // 0x20
    BUSY = 48,         // 0x30
    BAD_REQUEST = 64,  // 0x40
    INTL_ERROR = 80,   // 0x50
};



uint8_t hb(uint16_t val) { return (uint8_t)((val >> 8) & 0xFF); }

uint8_t lb(uint16_t val) { return (uint8_t)(val & 0xFF); }


void ParseCommand(uint8_t *message, uint8_t length) {
	uint8_t status = message[0];
	uint8_t version = message[1];
	uint8_t msg_length = message[2];
	uint8_t response[50];
	uint8_t response_len;


	// some debug stuff
	uint8_t uart_buf[50];
	uart_buf[0] = status;
	uart_buf[1] = msg_length;
	uart_buf[2] = length;
	uint8_t uart_buf_len = 3;
//	uint8_t uart_buf_len = sprintf(uart_buf, "%d", msg_length, length);
	HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 100);




	if (version != 0 || length - MSG_HEADER_SIZE != msg_length) {
		response[0] = BAD_REQUEST;
		response_len = 1;
		HAL_UART_Transmit(&huart2, response, response_len, 100);
		return;
	}


	switch (status) {
		case GET_POSITION:
			response[0] = OK_PAYLOAD;
			response[1] = hb(azm_motor_state.motor_position);
			response[2] = lb(azm_motor_state.motor_position);
			response[3] = hb(elv_motor_state.motor_position);
			response[4] = lb(elv_motor_state.motor_position);
			response_len = 5;
			break;
		case GET_SPEED: // TODO: FINISH
			response[0] = OK_PAYLOAD;
			break;
		case GET_AZM_TOOTH:
			response[0] = OK_PAYLOAD;
			response[1] = hb(azm_motor_state.tooth_ratio);
			response[2] = lb(azm_motor_state.tooth_ratio);
			response_len = 3;
			break;
		case GET_ELV_TOOTH:
			response[0] = OK_PAYLOAD;
			response[1] = hb(elv_motor_state.tooth_ratio);
			response[2] = lb(elv_motor_state.tooth_ratio);
			response_len = 3;
			break;
		case GET_AZM_STEP:
			response[0] = OK_PAYLOAD;
			response[1] = hb(azm_motor_state.motor_pulse_rev);
			response[2] = lb(elv_motor_state.motor_pulse_rev);
			response_len = 3;
			break;
		case GET_ELV_STEP:
			response[0] = OK_PAYLOAD;
			response[1] = hb(elv_motor_state.motor_pulse_rev);
			response[2] = lb(elv_motor_state.motor_pulse_rev);
			response_len = 3;
			break;
		default:
			response[0] = BAD_REQUEST;
			response_len = 1;
	}
	HAL_UART_Transmit(&huart2, response, response_len, 100);
}
