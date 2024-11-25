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


void test_is_data_valid_should_returnError_whenDataIsNull(void) {
    int result = is_data_valid(NULL, NORMAL_DATA_SIZE);
    TEST_ASSERT_EQUAL(-1, result);
}


void test_is_data_valid_should_returnError_whenLengthIsInvalid(void) {
    uint32_t data2[64] = {0};
    int result = is_data_valid(data2, NORMAL_DATA_SIZE + 1);
    TEST_ASSERT_EQUAL(-2, result);
}

void test_is_data_valid_should_ConvertAllMinusOneToZero(void) {
    uint32_t data[NORMAL_DATA_SIZE];
    uint32_t expected[NORMAL_DATA_SIZE];
    
    // Wypełnienie tablicy wejściowej wartościami -1
    for (int i = 0; i < NORMAL_DATA_SIZE; i++) {
        data[i] = (uint32_t) (-1);
        expected[i] = 0; // Oczekiwane wartości po przetworzeniu
    }

    int result = is_data_valid(data, NORMAL_DATA_SIZE);

    TEST_ASSERT_EQUAL(0, result);
    
    // Sprawdzamy, czy wszystkie wartości zostały zamienione na 0
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, data, NORMAL_DATA_SIZE);
}