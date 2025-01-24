/*
 * user_button.c
 *
 *  Created on: Jan 6, 2025
 *      Author: mikol
 */

#include "../Inc/user_button.h"

// Opóźnienia w ms
#define DEBOUNCE_DELAY 			50		// 50 ms
#define LONG_PRESS_THRESHOLD 	1000	// 1000 ms

#define BUTTON_GPIO_Port 		USER_BUTTON_GPIO_Port
#define BUTTON_Pin 				USER_BUTTON_Pin

#define BUTTON_IS_PRESSED		GPIO_PIN_SET


// Zmienna do przechowywania aktualnego stanu
static ButtonState_t currentState = STATE_WAITING;

// Zmienna do przechowywania czasu naciśnięcia przycisku
static uint32_t pressTime = 0;

static uint32_t pressDuration;

void button_state_machine(void);
// Handlery dla poszczególnych stanów
static void handle_waiting(void);
static void handle_idle(void);
static void handle_debounce(void);
static void handle_is_pressed(void);
static void handle_single_press(void);
static void handle_release(void);
static void handle_long_press(void);


void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
    if(__HAL_GPIO_EXTI_GET_IT(USER_BUTTON_Pin) == __HAL_GPIO_EXTI_GET_IT(GPIO_Pin))
    {
        __HAL_GPIO_EXTI_CLEAR_IT(USER_BUTTON_Pin);

        currentState = STATE_IDLE;
    }
}


void button_state_machine(void)
{
	switch(currentState)
	{
		case STATE_WAITING:
			handle_waiting();
			break;
		case STATE_IDLE:
			handle_idle();
			break;
		case STATE_DEBOUNCE:
			handle_debounce();
			break;
		case STATE_PRESSED:
			handle_is_pressed();
			break;
		case STATE_RELEASED:
			handle_release();
			break;
		case STATE_SINGLE_PRESS:
			handle_single_press();
			break;
		case STATE_LONG_PRESS:
			handle_long_press();
			break;
		default:
			currentState = STATE_WAITING;
			break;
	}
}

static void handle_waiting(void)
{
	// do nothing
}

// Handler stanu IDLE
static void handle_idle(void)
{
	currentState = STATE_DEBOUNCE;
	pressTime = HAL_GetTick();

	osDelay(1);
}

static void handle_debounce(void)
{
    if((HAL_GetTick() - pressTime) >= DEBOUNCE_DELAY)
    {
        if(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == BUTTON_IS_PRESSED)
        {
            currentState = STATE_PRESSED;
        }
        else
        {
            currentState = STATE_IDLE; // False call
        }
    }
}

static void handle_is_pressed(void)
{
    if(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == BUTTON_IS_PRESSED)
    {
        pressDuration = HAL_GetTick() - pressTime;

        if(pressDuration >= LONG_PRESS_THRESHOLD)
        {
            currentState = STATE_LONG_PRESS;
            printf("Long Press Detected\n");
        }
    }
    else
    {
    	pressDuration = HAL_GetTick() - pressTime;
		currentState = STATE_RELEASED;
    }
}

static void handle_single_press(void)
{
	//TODO: logika zapisu nowego stanu.


	//TODO: zmienić
	Data_Agregator_save_reference_sample();

	currentState = STATE_WAITING;
}

static void handle_release(void)
{
	if(pressDuration >= DEBOUNCE_DELAY && pressDuration < LONG_PRESS_THRESHOLD)
	{
		currentState = STATE_SINGLE_PRESS;
	}
	else if (pressDuration >= LONG_PRESS_THRESHOLD)
	{
		currentState = STATE_LONG_PRESS;
	}
	else
	{
		currentState = STATE_WAITING;
	}
}

static void handle_long_press(void)
{
	osDelay(1000);

    currentState = STATE_WAITING;
}
