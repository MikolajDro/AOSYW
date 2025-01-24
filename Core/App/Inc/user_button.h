/*
 * user_button.h
 *
 *  Created on: Jan 6, 2025
 *      Author: mikol
 */

#ifndef APP_INC_USER_BUTTON_H_
#define APP_INC_USER_BUTTON_H_

#include "main.h"
#include "gpio.h"
#include "cmsis_os2.h"
#include "stdio.h"
#include "data_aggregator.h"



typedef enum {
	STATE_WAITING,
    STATE_IDLE,
    STATE_DEBOUNCE,
    STATE_PRESSED,
    STATE_RELEASED,
    STATE_SINGLE_PRESS,
    STATE_LONG_PRESS
} ButtonState_t;

void button_state_machine(void);

void button_task(void *arg);

#endif /* APP_INC_USER_BUTTON_H_ */
