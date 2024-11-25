#include "analyzer.h"

int is_data_valid(const uint32_t *data, const uint32_t length)
{
    uint32_t tmp[64] = {0}; // Temporary array to store data    

    // Seafety check for NULL pointer
    if (data == NULL) {
        return -1; // Wrong value
    }
    
    // Check if length is valid
    if (!(length == MINIMUM_DATA_SIZE || length == NORMAL_DATA_SIZE)){
       return -2; // Wrong length value
    }

    for (int i = 0; i < length; i++){
        tmp[i] = data[i]; // Copy data to temporary array
    }

    // Check if data is in range otherwise set it to 0
    for(int i=0; i < length; i++) {
        if (tmp[i] > MAX_SENSOR_RANGE || tmp[i] < MIN_SENSOR_RANGE) {
            tmp[i] = 0; // Set data to 0 if it is out of range
        }
    }




    return 0; // Returns valid data
}

int analyze_data(const uint8_t *data, uint8_t length) {
    if (!data || length == 0) {
        return -1; // Wrong value
    }
    
    //TODO: Analyze data

    return length; // Returns length
}
