#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NORMAL_DATA_SIZE 64
#define MINIMUM_DATA_SIZE 16
#define MAX_SENSOR_RANGE 4000         // 4000 mm == 400 cm, max sensor range
#define MIN_SENSOR_RANGE 0            // min sensor range


int is_data_valid(uint32_t *data, const uint32_t length);
int analyze_data(const uint8_t *data, uint8_t length);

#endif // ANALYZER_H
