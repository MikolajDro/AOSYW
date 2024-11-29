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
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_data_present); // ? Act weird
    TEST_ASSERT_EQUAL_UINT32(0, result->data_status.is_not_length_valid);
    TEST_ASSERT_EQUAL_UINT32(invalid_count, result->data_status.invalid_data_counter);
    TEST_ASSERT_EQUAL_UINT32(1, result->data_status.is_not_data_valid);

    for(int i = 0; i < NORMAL_DATA_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT32(data2[i], result->data[i]);
    }
}


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