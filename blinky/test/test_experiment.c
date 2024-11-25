#include "unity.h"
#include "analyzer.h"

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
