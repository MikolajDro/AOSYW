/*
 * data_aggregator.c
 *
 *  Created on: Dec 9, 2024
 *      Author: mikol
 */


/* Includes */
#include "../Inc/data_aggregator.h"


/* Variables */
static uint32_t head =0, counter = 0;
static RANGING_SENSOR_Result_t reference_sample = {0};

/* Functions */


static int Data_Agregator_is_data_ok(RANGING_SENSOR_Result_t *data)
{
	if(data == NULL)
		return ERROR;

	if(data->NumberOfZones != 16 && data->NumberOfZones != 64)
		return ERROR;

	if(data->NumberOfZones == 16)
	{
		for(int i=0; i<16; i++)
		{
			if(*data->ZoneResult[i].Status != HAL_OK)
				return ERROR;
		}
	}
	if(data->NumberOfZones == 64)
	{
		for(int i=0; i<64; i++)
		{
			if(data->ZoneResult[i].Status != HAL_OK)
				return ERROR;
		}
	}
	// XXX: might add a signal power check in future
	return SUCCESS;
}

int Data_Agregator_save_sample(TOF_data_frame_t *data_buffer, const uint8_t buffer_size, RANGING_SENSOR_Result_t *NewData)
{
	if(Data_Agregator_is_data_ok(NewData) == ERROR)
	{
#if MY_DEBUG > 0
  printf("TOF measurement misses.\r\n");
#endif
		return ERROR;
	}
	if(data_buffer == NULL)
	{
#if MY_DEBUG > 0
  printf("data_buffer measurement misses.\r\n");
#endif
		return ERROR;
	}

	if(head >= DEAFULT_MEASUREMENTS_BUFFOR_SIZE)
		head = 0;

	data_buffer[head].TOF_measurement  = *NewData;

	static HAL_StatusTypeDef status;
	static uint8_t format;
	if(hrtc.Init.BinMode == RTC_BINARY_NONE){
		format = RTC_FORMAT_BCD;
	}
	else{
		format = RTC_FORMAT_BIN;
	}
    status = HAL_RTC_GetDate(&hrtc, &data_buffer[head].RTC_data, format);
    if(status != HAL_OK)
    {
#if MY_DEBUG > 0
    	printf("RTC_GetDate failed.\r\n");
#endif
		return ERROR;
    }
    status = HAL_RTC_GetTime(&hrtc, &data_buffer[head].RTC_time, format);
	if(status != HAL_OK)
	{
#if MY_DEBUG > 0
		printf("RTC_GetTime failed.\r\n");
#endif
		return ERROR;
	}

#if MY_DEBUG > 1
	printf("\033[0;33m");
	printf("MY_DEBUG over 1 level:\r\n");
	printf("\033[0m");
	print_result(NewData);
#endif

	if(counter <= buffer_size)
		counter++;

	if(head < buffer_size)
		head++;

	return SUCCESS;
}


TOF_data_frame_t* Data_Agregator_get_last_record(TOF_data_frame_t data_buffer[])
{
	return &data_buffer[(head+ (MEASUREMENTS_BUFFOR_SIZE - 1)) % MEASUREMENTS_BUFFOR_SIZE];
	// oddaje ostatni element, ale head jest o 1 dalej niż ostatni element to jest modulo
}

void Data_Agregator_save_reference_sample(void)
{
	reference_sample = (RANGING_SENSOR_Result_t ) *TOF_get_data();
}

RANGING_SENSOR_Result_t *Data_Agregator_get_reference_sample(void)
{
	if(reference_sample.NumberOfZones != 64 && reference_sample.NumberOfZones != 16)
	{
		return NULL;
	}

	return &reference_sample;
}
