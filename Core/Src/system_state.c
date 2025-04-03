/*
 * system_state.c
 *
 *  Created on: Mar 27, 2025
 *      Author: tydav
 */

#include "system_state.h"

// default values
MotorState azm_motor_state = {
    .motor_enable = 0,
    .motor_count = 0,
    .motor_direction = 0,
    .motor_pulse_rev = 800,
    .tooth_ratio = 11875,
    .motor_position = 0
};

MotorState elv_motor_state = {
    .motor_enable = 0,
    .motor_count = 0,
    .motor_direction = 0,
    .motor_pulse_rev = 800,
    .tooth_ratio = 1200,
    .motor_position = 0
};
