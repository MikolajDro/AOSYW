/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../App/Inc/data_aggregator.h"
#include "../App/Inc/analyzer.h"
#include "../App/Inc/user_button.h"
#include "../App/Inc/observator.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticSemaphore_t osStaticSemaphoreDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

void sample_update(void *data);

static TOF_data_frame_t measurements_buffer[MEASUREMENTS_BUFFOR_SIZE];
static observer_t analyzer_observer = { .update = sample_update };

osThreadId_t aggregatorTaskHandle;
const osThreadAttr_t aggregatorTask_attributes = { .name = "aggregtorTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 8 };

osThreadId_t analyzerTaskHandle;
const osThreadAttr_t analyzerTask_attributes = { .name = "analyzerTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 24 };

osThreadId_t buttonTaskHandle;
const osThreadAttr_t buttonTask_attributes = { .name = "buttonTask", .priority =
		(osPriority_t) osPriorityNormal, .stack_size = 128 * 8 };

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = { .name = "defaultTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };
/* Definitions for userButtonState */
osSemaphoreId_t userButtonStateHandle;
const osSemaphoreAttr_t userButtonState_attributes =
		{ .name = "userButtonState" };
/* Definitions for isReadyToSaveSem */
osSemaphoreId_t isReadyToSaveSemHandle;
osStaticSemaphoreDef_t isReadyToSaveControlBlock;
const osSemaphoreAttr_t isReadyToSaveSem_attributes = { .name =
		"isReadyToSaveSem", .cb_mem = &isReadyToSaveControlBlock, .cb_size =
		sizeof(isReadyToSaveControlBlock), };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void aggregator_task(void *arg);
void task_analyzer(void *arg);
void button_task(void *arg);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */
	attach_observer(&analyzer_observer);
	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */
	/* creation of isReadyToSaveSem */
	isReadyToSaveSemHandle = osSemaphoreNew(1, 1, &isReadyToSaveSem_attributes);

	/* creation of userButtonState */
	userButtonStateHandle = osSemaphoreNew(4, 4, &userButtonState_attributes);

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	osSemaphoreAcquire(isReadyToSaveSemHandle, osWaitForever);
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */
	/* creation of defaultTask */
	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL,
			&defaultTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */

	analyzerTaskHandle = osThreadNew(task_analyzer, NULL,
			&analyzerTask_attributes);
	aggregatorTaskHandle = osThreadNew(aggregator_task, NULL,
			&aggregatorTask_attributes);
	buttonTaskHandle = osThreadNew(button_task, NULL, &buttonTask_attributes);

	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief Function implementing the defaultTask thread.
 * @param argument: Not used
 * @retval None
 */

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
	/* USER CODE BEGIN defaultTask */
	/* Infinite loop */
	for (;;) {
//	  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		printf(".");

		osDelay(1000);
	}
	/* USER CODE END defaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void aggregator_task(void *arg) {
	static RANGING_SENSOR_Result_t *res;
	int tmp = 0;
	TOF_Init();

	Data_Agregator_save_reference_sample();

	while (1) {
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);

		res = TOF_get_data();
		tmp = Data_Agregator_save_sample(measurements_buffer,
				DEAFULT_MEASUREMENTS_BUFFOR_SIZE, res);

		if (tmp == SUCCESS) {
			notify_observers(measurements_buffer);
//			osSemaphoreRelease(isReadyToSaveSemHandle);
		}

		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);

		osDelay(1000);
	}

}

void task_analyzer(void *arg) {
	while (1) {
//		if(){
//			osSemaphoreAcquire(isReadyToSaveSemHandle, osWaitForever);
//
//			Analyzer_analyze(measurements_buffer);
//
//			if(Analyzer_does_see_anything() == SUCCESS)
//				 printf("Analyze successes\r\n");
//
//			osDelay(10);
//		}
		osDelay(100);
	}
}

void button_task(void *arg) {
	while (1) {
		button_state_machine();

		osDelay(10);
	}
}

/* Observator */
void sample_update(void *data) {
	Analyzer_analyze((TOF_data_frame_t*) data);
}

void event_triggered(void *event_data) {
	notify_observers(event_data);
}

/* USER CODE END Application */

