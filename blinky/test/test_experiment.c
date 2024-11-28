#include "unity.h"
#include "analyzer.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>



void setUp(void) {
    
}

void tearDown(void) {
    
}

void test_analyze_data_should_returnError_whenDataIsNull(void) {
    int result = analyze_data(NULL, 10);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_analyze_data_should_returnError_whenLengthIsZero(void) {
    uint8_t data[1] = {0};
    int result = analyze_data(data, 0);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_analyze_data_should_returnLength_whenValidInput(void) {
    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int result = analyze_data(data, 8);
    TEST_ASSERT_EQUAL(8, result);
}


// Test for is_data_valid function 
void test_is_data_valid_should_returnError_whenDataIsNull(void) {
    uint32_t *result = is_data_valid(NULL, NORMAL_DATA_SIZE);
    TEST_ASSERT_NULL(result);
}

// Test for is_data_valid function 
void test_is_data_valid_should_returnError_whenLengthIsInvalid(void) {
    uint32_t data2[NORMAL_DATA_SIZE] = {0};
    uint32_t *result = is_data_valid(data2, NORMAL_DATA_SIZE + 1);
    TEST_ASSERT_NULL(result);
}