#include "analyzer.h"

sensor_data_normal_size_t *is_data_valid_normal_size(uint32_t *data, length_t length)
{
    static sensor_data_normal_size_t tmp;

    tmp.length = 0;
    tmp.data_status.is_data_present = 0;
    tmp.data_status.is_not_length_valid = 0;
    tmp.data_status.invalid_data_counter = 0;
    tmp.data_status.is_not_data_valid = 0;
    for(uint32_t i = 0; i < NORMAL_DATA_SIZE; i++) {
        tmp.data[i] = 0;
    }

    if (data == NULL) {
        tmp.data_status.is_data_present = 1;
        return &tmp; // Returns sensor_data_normal_size_t with is_data_present flag set to 1 and previous data
    }
    
    if (length != NORMAL_DATA_SIZE) {
        tmp.data_status.is_not_length_valid = 1;
        return &tmp;
    }
    tmp.length = length;
    
    for (uint32_t i = 0; i < tmp.length; i++){
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

circular_buffer_err init_circular_buffer(circular_buffer_t *cb) {
    if (cb == NULL){
        return CIRCLE_BUFFER_NOT_INITIALIZE;
    }

    cb->head = 0;
    cb->count = 0;
    for(uint32_t i = 0; i < CIRCULAR_BUFFER_SIZE; i++) {
        cb->buffer[i].length = 0;
        cb->buffer[i].data_status.is_data_present = 0;
        cb->buffer[i].data_status.is_not_length_valid = 0;
        cb->buffer[i].data_status.invalid_data_counter = 0;
        cb->buffer[i].data_status.is_not_data_valid = 0;
        for(uint32_t j = 0; j < NORMAL_DATA_SIZE; j++) {
            cb->buffer[i].data[j] = 0;
        }
    }

    return CB_OK;
}

circular_buffer_err normal_data_circle_buffer(circular_buffer_t *cb, sensor_data_normal_size_t *new_data_frame) {
    if (cb == NULL){
        return CIRCLE_BUFFER_NOT_INITIALIZE;
    }
    if (new_data_frame == NULL)
    {
        return NO_NEW_DATA_FRAME;
    }
    

    uint32_t index = cb->head % CIRCULAR_BUFFER_SIZE;

    cb->buffer[index].length = new_data_frame->length;
    cb->buffer[index].data_status.is_data_present = new_data_frame->data_status.is_data_present;
    cb->buffer[index].data_status.is_not_data_valid = new_data_frame->data_status.is_not_data_valid;
    cb->buffer[index].data_status.is_not_length_valid = new_data_frame->data_status.is_not_length_valid;
    cb->buffer[index].data_status.invalid_data_counter = new_data_frame->data_status.invalid_data_counter;

    for(uint32_t j = 0; j < NORMAL_DATA_SIZE; j++) {
        cb->buffer[index].data[j] = new_data_frame->data[j];
    }

    cb->head++;

    if (cb->count < CIRCULAR_BUFFER_SIZE) {
        cb->count++;
    }

    return CB_OK;
}

sensor_data_normal_size_t* get_data_from_buffer(circular_buffer_t *cb, uint32_t index) {
    if (cb == NULL || index < 0 || index >= cb->count){
        return NULL;
    }

    uint32_t actual_index = (cb->head - cb->count + index) % CIRCULAR_BUFFER_SIZE;
    if (actual_index < 0) actual_index += CIRCULAR_BUFFER_SIZE;

    return (sensor_data_normal_size_t*)&cb->buffer[actual_index];
}
