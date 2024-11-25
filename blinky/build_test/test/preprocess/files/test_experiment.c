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

   ), (UNITY_UINT)(14), UNITY_DISPLAY_STYLE_INT);

}



void test_analyze_data_should_returnError_whenLengthIsZero(void) {

    uint8_t data[1] = {0};

    int result = analyze_data(data, 0);

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);

}
