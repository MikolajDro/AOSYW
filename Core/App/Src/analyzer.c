/*
 * analyzer.c
 *
 *  Created on: Jan 4, 2025
 *      Author: mikol
 */


#include "../Inc/analyzer.h"


static uint8_t is_sample_data_present = NO;

static uint32_t resolution=0;

static uint32_t sample_data4x4[16] = {0};
static uint32_t sample_data8x8[64] = {0};
static uint32_t row_data4x4[16]={0};
static uint32_t row_data8x8[64]={0};

static int Analyzer_is_data_out_off_range(TOF_data_frame_t *data)
{
	if(data == NULL)
		return ERROR;

	uint32_t tmp;
	if(data->TOF_measurement.NumberOfZones == VL53L5CX_RESOLUTION_4X4)
	{
		for(int i=0; i<VL53L5CX_RESOLUTION_4X4; i++)
		{
			tmp = *data->TOF_measurement.ZoneResult[i].Distance;

			if(tmp > VL53L5CX_MAXIMUM_RANGE || tmp < VL53L5CX_MINIMUM_RANGE)
				return ERROR;
		}
	}
	else if(data->TOF_measurement.NumberOfZones == VL53L5CX_RESOLUTION_8X8)
	{
		for(int i=0; i<VL53L5CX_RESOLUTION_8X8; i++)
		{
			tmp = *data->TOF_measurement.ZoneResult[i].Distance;

			if(tmp > VL53L5CX_MAXIMUM_RANGE || tmp < VL53L5CX_MINIMUM_RANGE)
				return ERROR;
		}
	}
	else
	{
		return ERROR;
	}

	return SUCCESS;
}

static int Analyer_prepare_reference_data(RANGING_SENSOR_Result_t *data)
{
	if(data == NULL)
		return ERROR;

//	if(Analyzer_is_data_out_off_range(data) == ERROR)
//	{
//		return ERROR;
//	}

	resolution = data->NumberOfZones;
	if(resolution == VL53L5CX_RESOLUTION_4X4)
	{
		for(int i=0; i < 4; i++)
		{
			for(int j=0; j < 4; j++)
			{
				sample_data4x4[i*4 + j] = (uint32_t) data->ZoneResult[i*4+j].Distance[0];
			}
		}
	}
	else if(resolution == VL53L5CX_RESOLUTION_8X8)
	{
		for(int i=0; i < 8; i++)
		{
			for(int j=0; j < 8; j++)
			{
				sample_data8x8[i*8 + j] = (uint32_t) data->ZoneResult[i*8+j].Distance[0];
			}
		}
	}
	else
	{
#if MY_DEBUG > 0
		printf("Bad resolution!\r\n");
#endif
		return ERROR;
	}

	is_sample_data_present = YES;
	return SUCCESS;
}

static void Analyer_prepare_data(TOF_data_frame_t *data)
{
	if(data == NULL)
		return;

	if(Analyzer_is_data_out_off_range(data) == ERROR)
	{
		return;
	}

	resolution = data->TOF_measurement.NumberOfZones;
	if(resolution == VL53L5CX_RESOLUTION_4X4)
	{
		for(int i=0; i < 4; i++)
		{
			for(int j=0; j < 4; j++)
			{
				row_data4x4[i*4 + j] = (uint32_t) data->TOF_measurement.ZoneResult[i*4+j].Distance[0];
			}
		}
	}
	else if(resolution == VL53L5CX_RESOLUTION_8X8)
	{
		for(int i=0; i < 8; i++)
		{
			for(int j=0; j < 8; j++)
			{
				row_data8x8[i*8 + j] = (uint32_t) data->TOF_measurement.ZoneResult[i*8+j].Distance[0];
			}
		}
	}
	else
	{
#if MY_DEBUG > 0
		printf("Bad resolution!\r\n");
#endif
	}
}

int Analyzer_analyze(TOF_data_frame_t *data_buffer)
{
	if(data_buffer == NULL)
		return ERROR;

	TOF_data_frame_t *last_record = Data_Agregator_get_last_record(data_buffer);

	if(last_record == NULL)
		return ERROR;

	if(is_sample_data_present == NO)
	{
		if(Analyer_prepare_reference_data(Data_Agregator_get_reference_sample()) == ERROR)
		{
			printf("Get reference sample!\r\n");
			return ERROR;
		}
	}

	Analyer_prepare_data(last_record);

	printf("Ready to compare!\r\n");

	// TODO: analyze

	return SUCCESS;
}


uint8_t Analyzer_does_see_anything(void)
{
	uint32_t min, max;
	if(resolution == VL53L5CX_RESOLUTION_4X4)
	{
		min = row_data4x4[0];
		max = row_data4x4[0];
		for(int i=0; i < resolution; i++)
		{
			if(min > row_data4x4[i])
				min = row_data4x4[i];

			if(max < row_data4x4[i])
				max = row_data4x4[i];
		}
		if(max - min > 50)
			return SEE_SOMETHING;

		else
			return DONT_SEE_ANYTHING;
	}
	else if(resolution == VL53L5CX_RESOLUTION_8X8)
	{
		min = row_data8x8[0];
		max = row_data8x8[0];
		for(int i=0; i < resolution; i++)
		{
			if(min > row_data8x8[i])
				min = row_data8x8[i];

			if(max < row_data8x8[i])
				max = row_data8x8[i];
		}
		if(max - min > 50)
			return SEE_SOMETHING;

		else
			return DONT_SEE_ANYTHING;
	}
	else
	{
#if MY_DEBUG > 0
		printf("Bad resolution!\r\n");
#endif
	}

	return DONT_SEE_ANYTHING;
}


int Analyzer_compare(TOF_data_frame_t *data_buffer)
{
	if(data_buffer == NULL)
	{
		printf("missing data_buffer\r\n");
		return ERROR;
	}

	RANGING_SENSOR_Result_t *reference_data = (RANGING_SENSOR_Result_t *)Data_Agregator_get_reference_sample();

	if(reference_data == NULL)
	{
		printf("missing reference_data\r\n");
		return ERROR;
	}

	return SUCCESS;
}
