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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT32);

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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2000)), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT32);

    }

}





void test_is_data_valid_normal_size_some_data_invalid_below_minimum(void) {

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

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(60))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_invalid)), (UNITY_INT)(UNITY_UINT32)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_UINT32);



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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(88), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_invalid)), (UNITY_INT)(UNITY_UINT32)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_UINT32);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((data[i])), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_UINT32);

    }

}





void test_is_data_valid_normal_size_invalid_data_counter_above_minimum(void) {

    uint32_t data2[64];

    uint32_t invalid_count = 16 + 1;



    for(int i = 0; i < 64; i++) {

        if(i < invalid_count) {

            data2[i] = 5000;

        }

        else {

            data2[i] = 1000;

        }

    }



    sensor_data_normal_size_t *result = is_data_valid_normal_size(data2, 64);

    do {if ((((result)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(112))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((invalid_count)), (UNITY_INT)(UNITY_UINT32)((result->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((result->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_UINT32);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((data2[i])), (UNITY_INT)(UNITY_UINT32)((result->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_UINT32);

    }

}





void test_init_circular_buffer(void) {

    circular_buffer_t cb;



    init_circular_buffer(&cb);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((cb.head)), (

   ((void *)0)

   ), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((cb.count)), (

   ((void *)0)

   ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT);



    for(int i = 0; i < 100; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((cb.buffer[i].length)), (

       ((void *)0)

       ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_UINT32);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((cb.buffer[i].data_status.is_data_present)), (

       ((void *)0)

       ), (UNITY_UINT)(135), UNITY_DISPLAY_STYLE_UINT32);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((cb.buffer[i].data_status.is_not_length_valid)), (

       ((void *)0)

       ), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_UINT32);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((cb.buffer[i].data_status.invalid_data_counter)), (

       ((void *)0)

       ), (UNITY_UINT)(137), UNITY_DISPLAY_STYLE_UINT32);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((cb.buffer[i].data_status.is_not_data_valid)), (

       ((void *)0)

       ), (UNITY_UINT)(138), UNITY_DISPLAY_STYLE_UINT32);

        for(int j = 0; j < 64; j++) {

            UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((cb.buffer[i].data[j])), (

           ((void *)0)

           ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT32);

        }

    }

}





sensor_data_normal_size_t create_data_frame(uint32_t base_value) {

    sensor_data_normal_size_t frame;

    frame.length = 64;

    frame.data_status.is_data_present = 1;

    frame.data_status.is_not_data_valid = 0;

    frame.data_status.is_not_length_valid = 0;

    frame.data_status.invalid_data_counter = 0;



    for(int i = 0; i < 64; i++) {

        frame.data[i] = base_value + i;

    }



    return frame;

}





void test_normal_data_circle_buffer_add_single_frame(void) {

    circular_buffer_t cb;

    init_circular_buffer(&cb);



    sensor_data_normal_size_t frame = create_data_frame(1000);



    circular_buffer_err err = normal_data_circle_buffer(&cb, &frame);

    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((err)), (

   ((void *)0)

   ), (UNITY_UINT)(169), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((cb.head)), (

   ((void *)0)

   ), (UNITY_UINT)(171), UNITY_DISPLAY_STYLE_UINT32);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((cb.count)), (

   ((void *)0)

   ), (UNITY_UINT)(173), UNITY_DISPLAY_STYLE_UINT32);



    sensor_data_normal_size_t *retrieved_frame = get_data_from_buffer(&cb, 0);

    do {if ((((retrieved_frame)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(176))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((frame.length)), (UNITY_INT)(UNITY_UINT32)((retrieved_frame->length)), (

   ((void *)0)

   ), (UNITY_UINT)(177), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((frame.data_status.is_data_present)), (UNITY_INT)(UNITY_UINT8 )((retrieved_frame->data_status.is_data_present)), (

   ((void *)0)

   ), (UNITY_UINT)(178), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((frame.data_status.is_not_data_valid)), (UNITY_INT)(UNITY_UINT8 )((retrieved_frame->data_status.is_not_data_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(179), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((frame.data_status.is_not_length_valid)), (UNITY_INT)(UNITY_UINT8 )((retrieved_frame->data_status.is_not_length_valid)), (

   ((void *)0)

   ), (UNITY_UINT)(180), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((frame.data_status.invalid_data_counter)), (UNITY_INT)(UNITY_UINT32)((retrieved_frame->data_status.invalid_data_counter)), (

   ((void *)0)

   ), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_UINT32);



    for(int i = 0; i < 64; i++) {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((frame.data[i])), (UNITY_INT)(UNITY_UINT32)((retrieved_frame->data[i])), (

       ((void *)0)

       ), (UNITY_UINT)(184), UNITY_DISPLAY_STYLE_UINT32);

    }

}
