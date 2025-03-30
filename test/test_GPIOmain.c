#include "gpio.h"
#include "unity.h"
#include "uart.h"
#include "test_GPIOmain.h"
#include <string.h>
#include <stdio.h>
//void test_LED_On_Should_Set_GPIO_High(void) {
   // LED_On(5);
    //TEST_ASSERT_EQUAL(1, mock_gpio_state);
//}
// Global variable to track callback calls
int mock_callback_called = 0;

// Mock callback function
void mock_callback(void) {
    mock_callback_called = 1;  // Set the flag when the callback is called
}
void test_GPIO_Init_Should_Set_Pin_Mode(void) {
    GPIO_Init(5, GPIO_MODE_OUTPUT);
    TEST_ASSERT_EQUAL(GPIO_MODE_OUTPUT, mock_gpio_mode[5]);
    GPIO_Init(7, GPIO_MODE_INPUT);
    TEST_ASSERT_EQUAL(GPIO_MODE_INPUT, mock_gpio_mode[7]);
}
void test_GPIO_Write_Should_Set_Pin_High(void) {
    GPIO_Write(5, GPIO_HIGH);
    TEST_ASSERT_EQUAL(GPIO_HIGH, mock_gpio_state[5]);
}

void test_GPIO_Write_Should_Set_Pin_Low(void) {
    GPIO_Write(5, GPIO_LOW);
    TEST_ASSERT_EQUAL(GPIO_LOW, mock_gpio_state[5]);
}
void test_GPIO_Read_Should_Return_Correct_Value(void) {
    mock_gpio_state[5] = GPIO_HIGH;
    TEST_ASSERT_EQUAL(GPIO_HIGH, GPIO_Read(5));

    mock_gpio_state[5] = GPIO_LOW;
    TEST_ASSERT_EQUAL(GPIO_LOW, GPIO_Read(5));
}
void test_GPIO_Write_Should_Handle_Invalid_Pin(void) {
    TEST_ASSERT_EQUAL(GPIO_ERROR, GPIO_Write(99, GPIO_HIGH));
}

void test_GPIO_Write_Should_Fail_If_Pin_Not_Initialized(void) {
    TEST_ASSERT_EQUAL(GPIO_ERROR, GPIO_Write(3, GPIO_HIGH));
}
void test_GPIO_SetPullUp_Should_Enable_PullUp(void) {
    GPIO_SetPullUp(5, ENABLE);
    TEST_ASSERT_EQUAL(ENABLE, mock_gpio_pullup[5]);
}

void test_GPIO_SetPullDown_Should_Enable_PullDown(void) {
    GPIO_SetPullDown(5, ENABLE);
    TEST_ASSERT_EQUAL(ENABLE, mock_gpio_pulldown[5]);
}
void test_GPIO_Toggle_Should_Work_Fast(void) {
    uint32_t start_time = get_current_time_ms();
    
    for (int i = 0; i < 1000; i++) {
        GPIO_Toggle(5);
    }
    
    uint32_t end_time = get_current_time_ms();
    uint32_t elapsed_time = end_time - start_time;

    printf("Elapsed time: %u ms\n", elapsed_time);  // Debug print
    
    TEST_ASSERT_LESS_THAN(5, elapsed_time);  // Should run in <5ms
}



void test_GPIO_Read_Should_Debounce_Noise(void) {
    // Simulating noise
    mock_gpio_state[5] = GPIO_HIGH;
    delay_ms(2);
    mock_gpio_state[5] = GPIO_LOW;
    delay_ms(2);
    mock_gpio_state[5] = GPIO_HIGH;
    
    TEST_ASSERT_EQUAL(GPIO_HIGH, GPIO_Read_Debounced(5));
}


/// @brief ///////////////////////////////////////////////
/// @param  /

void test_GPIO_Interrupt_RisingEdge_Should_Trigger_Callback(void) {
    mock_gpio_state[5] = GPIO_LOW;  // Initial state low
    GPIO_SetInterrupt(5, GPIO_INTERRUPT_RISING, mock_callback);

    mock_gpio_state[5] = GPIO_HIGH; // Simulating rising edge
    GPIO_HandleInterrupt(5); // Manually trigger interrupt handler

    TEST_ASSERT_EQUAL(1, mock_callback_called); // Verify callback was called
}

void test_GPIO_Interrupt_FallingEdge_Should_Trigger_Callback(void) {
    mock_gpio_state[5] = GPIO_HIGH;  
    GPIO_SetInterrupt(5, GPIO_INTERRUPT_FALLING, mock_callback);

    mock_gpio_state[5] = GPIO_LOW;  
    GPIO_HandleInterrupt(5);

    TEST_ASSERT_EQUAL(1, mock_callback_called);
}

void test_GPIO_Interrupt_Debounce_Should_Filter_Noise(void) {
    GPIO_SetInterrupt(5, GPIO_INTERRUPT_RISING, mock_callback);
    
    mock_gpio_state[5] = GPIO_HIGH; 
    delay_ms(2); 
    mock_gpio_state[5] = GPIO_LOW;  
    delay_ms(2);  
    mock_gpio_state[5] = GPIO_HIGH;  

    GPIO_HandleInterrupt(5);
    TEST_ASSERT_EQUAL(1, mock_callback_called);  // Should only trigger once
}

void test_GPIO_Multiple_Pins_Should_Work_Independently(void) {
    GPIO_Write(3, GPIO_LOW);
    GPIO_Write(5, GPIO_LOW);
    TEST_ASSERT_EQUAL(GPIO_LOW, mock_gpio_state[3]);
    TEST_ASSERT_EQUAL(GPIO_LOW, mock_gpio_state[5]);
}

void test_GPIO_Input_Controls_Output(void) {
    GPIO_Init(2, GPIO_MODE_INPUT);
    GPIO_Init(4, GPIO_MODE_OUTPUT);

    mock_gpio_state[2] = GPIO_LOW;
    if (GPIO_Read(2) == GPIO_LOW) {
        GPIO_Write(4, GPIO_LOW);
    }

    TEST_ASSERT_EQUAL(GPIO_LOW, mock_gpio_state[4]);
}
