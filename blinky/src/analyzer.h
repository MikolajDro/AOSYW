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

#define CIRCULAR_BUFFER_SIZE 100


typedef enum {
    NORMAL = NORMAL_DATA_SIZE,
    //MINIMUM = MINIMUM_DATA_SIZE,
} length_t;

typedef struct
{
    uint32_t is_data_present:1;
    uint32_t is_not_data_valid:1;
    uint32_t is_not_length_valid:1;
    uint32_t invalid_data_counter:29;
} data_status_normal_t;
typedef struct {
    uint32_t data[NORMAL_DATA_SIZE];
    uint32_t length;
    data_status_normal_t data_status;
} sensor_data_normal_size_t;

typedef enum
{
    CIRCULAR_BUFFER_INITILIZED_SUCCESSFULLY,
    CIRCULAR_BUFFER_INITILIZED_UNSUCCESSFULLY,
    CIRCLE_BUFFER_NOT_INITIALIZE,

} circular_buffer_err;
typedef struct {
    sensor_data_normal_size_t buffer[CIRCULAR_BUFFER_SIZE];
    uint32_t head;   
    uint32_t count;  
} circular_buffer_t;


circular_buffer_err init_circular_buffer(circular_buffer_t *cb) ;


sensor_data_normal_size_t *is_data_valid_normal_size(uint32_t *data, length_t length);

#endif // ANALYZER_H
