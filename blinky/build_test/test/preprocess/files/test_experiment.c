#include "src/analyzer.h"
#include "/home/megister/.rbenv/versions/3.0.7/lib/ruby/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"














void setUp(void) {



}



void tearDown(void) {



}



void test_analyze_data_should_returnError_whenDataIsNull(void) {

    int result = analyze_data(

                             ((void *)0)

                                 , 10);

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);

}



void test_analyze_data_should_returnError_whenLengthIsZero(void) {

    uint8_t data[1] = {0};

    int result = analyze_data(data, 0);

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

}



void test_analyze_data_should_returnLength_whenValidInput(void) {

    uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    int result = analyze_data(data, 8);

    UnityAssertEqualNumber((UNITY_INT)((8)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);

}





void test_is_data_valid_should_returnError_whenDataIsNull(void) {

    int result = is_data_valid(

                              ((void *)0)

                                  , 64);

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

}





void test_is_data_valid_should_returnError_whenLengthIsInvalid(void) {

    uint32_t data2[64] = {0};

    int result = is_data_valid(data2, 65);

    UnityAssertEqualNumber((UNITY_INT)((-2)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_INT);

}



void test_is_data_valid_should_zero_whenEverythingIsValid(void) {

    uint32_t data2[64] = {0};

    int result = is_data_valid(data2, 64);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

}
