/*
 * tof_app.h
 *
 *  Created on: Dec 9, 2024
 *      Author: mikol
 */

#ifndef APP_INC_DATA_AGGREGATOR_H_
#define APP_INC_DATA_AGGREGATOR_H_

/* Includes */
#include "custom_tof_conf.h"
#include "debug.h"
#include "tof_app.h"
#include "rtc.h"

/* Defines */
#define DEAFULT_MEASUREMENTS_BUFFOR_SIZE 		10u
#define MEASUREMENTS_BUFFOR_SIZE				DEAFULT_MEASUREMENTS_BUFFOR_SIZE

/* Typedefs */
typedef struct{
	RANGING_SENSOR_Result_t TOF_measurement;
	RTC_TimeTypeDef RTC_time;
	RTC_DateTypeDef RTC_data;
	float 	similaryty_rate;
} TOF_data_frame_t;

/* Functions*/
int Data_Agregator_save_sample(TOF_data_frame_t *data_buffer,
		const uint8_t buffer_size, RANGING_SENSOR_Result_t *NewData);
void Data_Agregator_save_reference_sample(void);
TOF_data_frame_t* Data_Agregator_get_last_record(TOF_data_frame_t data_buffer[]);
RANGING_SENSOR_Result_t *Data_Agregator_get_reference_sample(void);

/* Task Functions*/
void aggregator_task(void *arg);

#endif /* APP_INC_DATA_AGGREGATOR_H_ */
