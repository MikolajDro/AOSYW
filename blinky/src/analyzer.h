#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAX_SENSOR_RANGE 4000         // 4000 mm == 400 cm, max sensor range
#define MIN_SENSOR_RANGE 0            // min sensor range

#define NORMAL_DATA_SIZE 64
#define MAX_DATA_SIZE NORMAL_DATA_SIZE// max data size for vl5 sensor
#define MINIMUM_VAILD_DATA_NORMAL 16


typedef enum {
    NORMAL = NORMAL_DATA_SIZE,
    // MINIMUM = MINIMUM_DATA_SIZE,
} length_t;

typedef union
{
    uint16_t is_data_present:1;
    uint16_t is_not_data_valid:1;
    uint16_t is_not_length_valid:1;
    uint16_t invalid_data_counter:13;
} data_status_normal_t;

typedef struct {
    uint32_t data[NORMAL_DATA_SIZE];
    uint32_t length;
    data_status_normal_t data_status;
} sensor_data_normal_size_t;


sensor_data_normal_size_t *is_data_valid_normal_size(uint32_t *data, const length_t const length);

#endif // ANALYZER_H
