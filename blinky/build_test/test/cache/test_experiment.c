#include "src/analyzer.h"
#include "/home/megister/.rbenv/versions/3.0.7/lib/ruby/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
















void setUp(void) {



}



void tearDown(void) {



}





void test_is_data_valid_normal_size_should_set_data_present_flag_when_data_is_null(void) {

    sensor_data_normal_size_t *result = is_data_valid_normal_size(

                                                                 ((void *)0)

                                                                     , 64);

    do {if ((((result)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(22))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT8);

}





void test_is_data_valid_normal_size_all_data_valid(void) {

    uint32_t data[64];

    for(int i = 0; i < 64; i++) {

        data[i] = 2000;

    }



    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, 64);

    do {if ((((result)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(34))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2000)), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT32);

    }

}





void test_is_data_valid_normal_size_some_data_invalid_below_minimum(void) {

    uint32_t data[64];

    uint32_t expected_invalid = 16 / 4;



    for(int i = 0; i < 64; i++) {

        if(i < expected_invalid) {

            data[i] = 5000;

        }

        else {

            data[i] = 1000;

        }

    }



    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, 64);

    do {if ((((result)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(60))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_invalid)), (UNITY_INT)(UNITY_UINT16)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_UINT16);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((data[i])), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_UINT32);

    }

}





void test_is_data_valid_normal_size_invalid_data_counter_equal_minimum(void) {

    uint32_t data[64];

    uint32_t expected_invalid = 16;



    for(int i = 0; i < 64; i++) {

        if(i < expected_invalid) {

            data[i] = 5000;

        }

        else {

            data[i] = 1000;

        }

    }



    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, 64);

    do {if ((((result)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(86))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(88), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_invalid)), (UNITY_INT)(UNITY_UINT16)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_UINT16);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((data[i])), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_UINT32);

    }

}





void test_is_data_valid_normal_size_invalid_data_counter_above_minimum(void) {

    uint32_t data[64];

    uint32_t invalid_count = 16 / 4 + 1;



    for(int i = 0; i < 64; i++) {

        if(i < invalid_count) {

            data[i] = 5000;

        }

        else {

            data[i] = 1000;

        }

    }



    sensor_data_normal_size_t *result = is_data_valid_normal_size(data, 64);

    do {if ((((result)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(112))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((invalid_count)), (UNITY_INT)(UNITY_UINT16)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_UINT16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_UINT16);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((data[i])), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_UINT32);

    }

}
