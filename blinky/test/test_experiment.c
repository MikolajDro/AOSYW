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


void test_is_data_valid_should_returnError_whenLengthIsInvalid(void) {
    uint32_t data2[64] = {0};
    int result = is_data_valid(data2, 64);
    TEST_ASSERT_EQUAL(0, result);
}
