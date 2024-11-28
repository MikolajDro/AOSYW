#include "analyzer.h"

sensor_data_normal_size_t tmp;

sensor_data_normal_size_t *is_data_valid_normal_size(uint32_t *data, const length_t length)
{
    memset(&tmp, 0, sizeof(sensor_data_normal_size_t));

    if (data == NULL) {
        tmp.data_status.is_data_present = 1;
        return &tmp; // Returns sensor_data_normal_size_t with is_data_present flag set to 1 and previous data
    }
    
    if (length != NORMAL_DATA_SIZE) {
       tmp.data_status.is_not_length_valid = 1;
    }
    else{
        tmp.length = length;
    }
    

    for (uint32_t i = 0; i < length; i++){
        if (data[i] > MAX_SENSOR_RANGE){
            tmp.data_status.invalid_data_counter++;
        }
        tmp.data[i] = data[i];
    }

    if(tmp.data_status.invalid_data_counter > MINIMUM_VAILD_DATA_NORMAL){
        tmp.data_status.is_not_data_valid = 1;
    }

    return &tmp; // Returns sensor_data_normal_size_t
}
