/*
 * analyzer.h
 *
 *  Created on: Jan 4, 2025
 *      Author: mikol
 */

#ifndef APP_INC_ANALYZER_H_
#define APP_INC_ANALYZER_H_

#include "main.h"
#include <stdint.h>
#include "data_aggregator.h"
#include "vl53l5cx.h"


#define VL53L5CX_MAXIMUM_RANGE 4000
#define VL53L5CX_MINIMUM_RANGE 0

typedef enum{
	SEE_SOMETHING = 0,
	DONT_SEE_ANYTHING = !SEE_SOMETHING
}DOES_SEE_SOMETHING;

int Analyzer_analyze(TOF_data_frame_t *data_buffer);
uint8_t Analyzer_does_see_anything(void);
void task_analyzer(void *arg);

#endif /* APP_INC_ANALYZER_H_ */
