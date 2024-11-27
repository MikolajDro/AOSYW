#include "analyzer.h"

uint32_t *is_data_valid(const uint32_t const *data, const uint32_t length)
{
    uint32_t* tmp[64]={0};
    // Seafety check for NULL pointer
    if (data == NULL) {
        return NULL; // Wrong value
    }
    
    // Check if length is valid
    if (!(length == MINIMUM_DATA_SIZE || length == NORMAL_DATA_SIZE)){
       return NULL; // Wrong length value
    }
    else{
        for (int i = 0; i < length; i++){
            if (data[i] > MAX_SENSOR_RANGE || data[i] < MIN_SENSOR_RANGE){
                tmp[i] = 0; // Set tmp to 0 if it is out of range
            }
            else{
                tmp[i] = data[i];
            }
        }
    }




    return tmp; // Returns valid data
}

int analyze_data(const uint8_t *data, uint8_t length) {
    if (!data || length == 0) {
        return -1; // Wrong value
    }
    
    //TODO: Analyze data

    return length; // Returns length
}
