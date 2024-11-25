#include "analyzer.h"

#define NORMAL_DATA_SIZE 64
#define MAX_SENSOR_RANGE 4000         // 4000 mm == 400 cm, max sensor range
#define MIN_SENSOR_RANGE 0            // min sensor range

int is_data_valid(const uint32_t *data, const uint8_t length)
{
    if (!data || length != NORMAL_DATA_SIZE) {
        // Seafety check for NULL pointer
        return -1; // Wrong value
    }
    for(int i=0; i < length; i++) {
        if (data[i] > MAX_SENSOR_RANGE || data[i] < MIN_SENSOR_RANGE) {
            return -2; // Wrong value
        }
    }




    return 0; // Returns 0 if data is valid
}

int analyze_data(const uint8_t *data, uint8_t length) {
    if (!data || length == 0) {
        return -1; // Wrong value
    }
    
    //TODO: Analyze data

    return length; // Returns length
}
