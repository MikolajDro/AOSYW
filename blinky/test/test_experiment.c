#include "unity.h"
#include "analyzer.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void setUp(void) {
    
}

void tearDown(void) {
    
}

// Test 1: Tests if the function sets the data_present flag when data is NULL
void test_is_data_valid_normal_size_should_set_data_present_flag_when_data_is_null(void) {
    sensor_data_normal_size_t *result = is_data_valid_normal_size(NULL, NORMAL_DATA_SIZE);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_UINT32(1, result->data_status.is_data_present);
}

// Test  2:Tests if the function sets the length_valid flag when the length is NORMAL
void test_is_data_valid_normal_size_all_data_valid(void) {
    uint32_t data[NORMAL_DATA_SIZE];
    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        data[i] = 2000; 
    }

    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, NORMAL_DATA_SIZE);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_data_present);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_length_valid);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.invalid_data_counter);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_data_valid);

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(2000, result->data[i]);
    }
}

// Test 3: Tests if the function sets the invalid_data_counter flag when some data is invalid
void test_is_data_valid_normal_size_some_data_invalid_below_minimum(void) {
    uint32_t data[NORMAL_DATA_SIZE];
    uint32_t expected_invalid = MINIMUM_VAILD_DATA_NORMAL;

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        if(i < expected_invalid) {
            data[i] = 5000; 
        }
        else {
            data[i] = 1000; 
        }
    }

    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, NORMAL_DATA_SIZE);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_data_present);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_length_valid);
    TEST_ASSERT_EQUAL_UINT32(expected_invalid, result->data_status.invalid_data_counter);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_data_valid);

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(data[i], result->data[i]);
    }
}

// Test 4: Tests if the function sets the invalid_data_counter flag when some data is invalid
void test_is_data_valid_normal_size_invalid_data_counter_equal_minimum(void) {
    uint32_t data[NORMAL_DATA_SIZE];
    uint32_t expected_invalid = MINIMUM_VAILD_DATA_NORMAL; 

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        if(i < expected_invalid) {
            data[i] = 5000; 
        }
        else {
            data[i] = 1000; 
        }
    }

    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, NORMAL_DATA_SIZE);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_data_present);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_length_valid);
    TEST_ASSERT_EQUAL_UINT32(expected_invalid, result->data_status.invalid_data_counter);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_data_valid);

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(data[i], result->data[i]);
    }
}

// Test 5: Tests if the function sets the invalid_data_counter flag when some data is invalid
void test_is_data_valid_normal_size_invalid_data_counter_above_minimum(void) {
    uint32_t data2[NORMAL_DATA_SIZE];
    uint32_t invalid_count = MINIMUM_VAILD_DATA_NORMAL + 1;

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        if(i < invalid_count) {
            data2[i] = 5000; 
        }
        else {
            data2[i] = 1000;
        }
    }
    
    sensor_data_normal_size_t *result = is_data_valid_normal_size(data2, NORMAL_DATA_SIZE);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_data_present); 
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_length_valid);
    TEST_ASSERT_EQUAL_UINT32(invalid_count, result->data_status.invalid_data_counter);
    TEST_ASSERT_EQUAL_UINT32(1, result->data_status.is_not_data_valid);

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(data2[i], result->data[i]);
    }
}

// Test 6: Test if the function initializes the circular buffer correctly
void test_init_circular_buffer(void) {
    circular_buffer_t cb;
    
    init_circular_buffer(&cb);
    
    TEST_ASSERT_EQUAL_INT(0, cb.head);
    
    TEST_ASSERT_EQUAL_INT(0, cb.count);
    
    for(int i = 0; i < CIRCULAR_BUFFER_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(0, cb.buffer[i].length);
        TEST_ASSERT_EQUAL_UINT32(0, cb.buffer[i].data_status.is_data_present);
        TEST_ASSERT_EQUAL_UINT32(0, cb.buffer[i].data_status.is_not_length_valid);
        TEST_ASSERT_EQUAL_UINT32(0, cb.buffer[i].data_status.invalid_data_counter);
        TEST_ASSERT_EQUAL_UINT32(0, cb.buffer[i].data_status.is_not_data_valid);
        for(int j = 0; j < NORMAL_DATA_SIZE; j++) {
            TEST_ASSERT_EQUAL_UINT32(0, cb.buffer[i].data[j]);
        }
    }
}

// Helper function 1: Creates a data frame with NORMAL_DATA_SIZE data points
sensor_data_normal_size_t create_data_frame(uint32_t base_value) {
    sensor_data_normal_size_t frame;
    frame.length = NORMAL_DATA_SIZE;
    frame.data_status.is_data_present = 1;
    frame.data_status.is_not_data_valid = 0;
    frame.data_status.is_not_length_valid = 0;
    frame.data_status.invalid_data_counter = 0;

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        frame.data[i] = base_value + i;
    }

    return frame;
}

// Test 7: Test if the function adds a single frame to the circular buffer
void test_normal_data_circle_buffer_add_single_frame(void) {
    circular_buffer_t cb;
    init_circular_buffer(&cb);

    sensor_data_normal_size_t frame = create_data_frame(1000);

    circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);
    TEST_ASSERT_EQUAL_INT(CB_OK, err);

    TEST_ASSERT_EQUAL_UINT32(1, cb.head);

    TEST_ASSERT_EQUAL_UINT32(1, cb.count);

    sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, 0);
    TEST_ASSERT_NOT_NULL(retrieved_frame);
    TEST_ASSERT_EQUAL_UINT32(frame.length, retrieved_frame->length);
    TEST_ASSERT_EQUAL_UINT8(frame.data_status.is_data_present, retrieved_frame->data_status.is_data_present);
    TEST_ASSERT_EQUAL_UINT8(frame.data_status.is_not_data_valid, retrieved_frame->data_status.is_not_data_valid);
    TEST_ASSERT_EQUAL_UINT8(frame.data_status.is_not_length_valid, retrieved_frame->data_status.is_not_length_valid);
    TEST_ASSERT_EQUAL_UINT32(frame.data_status.invalid_data_counter, retrieved_frame->data_status.invalid_data_counter);

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(frame.data[i], retrieved_frame->data[i]);
    }
}

// Test 8: Test if the function adds multiple frames to the circular buffer
void test_normal_data_circle_buffer_add_multiple_frames(void) {
    circular_buffer_t cb;
    init_circular_buffer(&cb);

    for(uint32_t i = 0; i < 50; i++) {
        sensor_data_normal_size_t frame = create_data_frame(1000 + i * 100);
        circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);
        TEST_ASSERT_EQUAL_INT(CB_OK, err);
    }

    TEST_ASSERT_EQUAL_UINT32(50, cb.head);
    TEST_ASSERT_EQUAL_UINT32(50, cb.count);

    for(uint32_t i = 0; i < 50; i++) {
        sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, i);
        TEST_ASSERT_NOT_NULL(retrieved_frame);
        TEST_ASSERT_EQUAL_UINT32(1000 + i * 100, retrieved_frame->data[0]);
    }
}

// Test 9: Test if the function overflows the circular buffer
//TODO: Fix this test
void test_normal_data_circle_buffer_overflow(void) {
    circular_buffer_t cb;
    init_circular_buffer(&cb);

    for(uint32_t i = 0; i < CIRCULAR_BUFFER_SIZE; i++) {
        sensor_data_normal_size_t frame = create_data_frame(2000 + i * 100);
        circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);
        TEST_ASSERT_EQUAL_INT(CB_OK, err);
    }

    TEST_ASSERT_EQUAL_UINT32(CIRCULAR_BUFFER_SIZE, cb.head);
    TEST_ASSERT_EQUAL_UINT32(CIRCULAR_BUFFER_SIZE, cb.count);

    for(uint32_t i = CIRCULAR_BUFFER_SIZE; i < CIRCULAR_BUFFER_SIZE + 10; i++) {
        sensor_data_normal_size_t frame = create_data_frame(3000 + (i * 100));
        circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);
        TEST_ASSERT_EQUAL_INT(CB_OK, err);
    }

    TEST_ASSERT_EQUAL_UINT32(CIRCULAR_BUFFER_SIZE + 10, cb.head);

    TEST_ASSERT_EQUAL_UINT32(CIRCULAR_BUFFER_SIZE, cb.count);

    for(uint32_t i = 0; i < 10; i++) {
        sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, i);
        TEST_ASSERT_NOT_NULL(retrieved_frame);
        TEST_ASSERT_EQUAL_UINT32(3000 + i * 100, retrieved_frame->data[0]);
    }

    for(uint32_t i = 90; i < CIRCULAR_BUFFER_SIZE; i++) {
        sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, i);
        TEST_ASSERT_NOT_NULL(retrieved_frame);
        TEST_ASSERT_EQUAL_UINT32(2000 + i * 100, retrieved_frame->data[0]);
    }
}

// Test 10: Test if the function returns NULL when the index is invalid
void test_get_data_from_buffer_valid_index(void) {
    circular_buffer_t cb;
    init_circular_buffer(&cb);

    for(uint32_t i = 0; i < 10; i++) {
        sensor_data_normal_size_t frame = create_data_frame(4000 + i * 100);
        circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);
        TEST_ASSERT_EQUAL_INT(CB_OK, err);
    }

    for(uint32_t i = 0; i < 10; i++) {
        sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, i);
        TEST_ASSERT_NOT_NULL(retrieved_frame);
        TEST_ASSERT_EQUAL_UINT32(4000 + i * 100, retrieved_frame->data[0]);
    }
}

// Test 11: Test if the function returns NULL when the index is invalid
void test_get_data_from_buffer_invalid_index(void) {
    circular_buffer_t cb;
    init_circular_buffer(&cb);

    for(uint32_t i = 0; i < 5; i++) {
        sensor_data_normal_size_t frame = create_data_frame(5000 + i * 100);
        circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);
        TEST_ASSERT_EQUAL_INT(CB_OK, err);
    }

    sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, 5);
    TEST_ASSERT_NULL(retrieved_frame);
}
