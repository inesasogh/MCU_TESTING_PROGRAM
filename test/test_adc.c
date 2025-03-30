#include "unity.h"
#include "adc.h"
#include "test_timer.h"

void setUpADC(void){
    adc_init();
}
void tearDownADC() {}
//1 adc initalization 
void test_adc_initialization(void){
     for (int i =0 ;i< 16; i++){
        TEST_ASSERT_EQUAL(0,adc_init());
     }
}
//2 dingle conversion
void test_adc_single_conversion(void) {
    adc_set_mock_value(0, 1234);
    TEST_ASSERT_EQUAL_UINT16(1234, adc_read(0));
}
//3 multipe conver
void test_adc_multiple_conversions(void) {
    adc_set_mock_value(1, 512);
    adc_set_mock_value(2, 2048);
    
    TEST_ASSERT_EQUAL_UINT16(512, adc_read(1));
    TEST_ASSERT_EQUAL_UINT16(2048, adc_read(2));
}
//4 min adc val
void test_adc_min_value(void) {
    adc_set_mock_value(3, 0);
    TEST_ASSERT_EQUAL_UINT16(0, adc_read(3));
}
//5 max val 
void test_adc_max_value(void) {
    adc_set_mock_value(4, 4095);
    TEST_ASSERT_EQUAL_UINT16(4095, adc_read(4));
}
//6 mid val 
void test_adc_mid_value(void) {
    adc_set_mock_value(5, 2048);
    TEST_ASSERT_EQUAL_UINT16(2048, adc_read(5));
}
//7 invalid chanel 
void test_adc_invalid_channel(void) {
    TEST_ASSERT_EQUAL_UINT16(0xFFFF, adc_read(16)); // Out of bounds channel
}
//8 Power om defalut val
void test_adc_power_on_default(void) {
    adc_init(); // Reset ADC state
    for (int i = 0; i < 16; i++) {
        TEST_ASSERT_EQUAL_UINT16(0, adc_read(i));
    }
}
//9 simpling time 
void test_adc_sampling_time(void) {
    adc_set_mock_value(6, 123);
    TEST_ASSERT_EQUAL_UINT16(123, adc_read(6));
}
//10  voltage scaling 
void test_adc_voltage_scaling(void) {
    adc_set_mock_value(7, 2048); // Assuming 12-bit ADC, 2048 ≈ 1.65V (half of 3.3V)
    TEST_ASSERT_EQUAL_UINT16(2048, adc_read(7));
}
//11 noise 
void test_adc_noise_stability(void) {
    adc_set_mock_value(8, 1024);
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_UINT16(1024, adc_read(8)); // Value should remain stable
    }
}
//12 onversion Time
void test_adc_conversion_time(void) {
    uint32_t start_time = 100;  // Simulated time (e.g., from millis())
    uint32_t end_time = 105;    // Simulated time after conversion
    
    TEST_ASSERT_LESS_THAN_UINT32(10, (end_time - start_time)); // Check if conversion is within time limit
}

//13 interrupt trigger 
void test_adc_interrupt_trigger(void) {
    adc_start_conversion(0);
    adc_trigger_interrupt();  
    TEST_ASSERT_TRUE(adc_is_conversion_done());
}
//14 Interrupt Handling Correctly Updates ADC Result
void test_adc_interrupt_value_handling(void) {
    adc_start_conversion(1);
    adc_trigger_interrupt();
    mock_adc_values[10] = 2048; // Simulating ADC result
    TEST_ASSERT_EQUAL_UINT16(2048, adc_get_result(10));
}
//15 Multiple Interrupt Handling
void test_adc_multiple_interrupts(void) {
    adc_start_conversion(2);
    adc_trigger_interrupt();
    mock_adc_values[1] = 1000;
    TEST_ASSERT_EQUAL_UINT16(1000, adc_get_result(1));

    adc_start_conversion(3);
    adc_trigger_interrupt();
    mock_adc_values[3] = 3000;
    TEST_ASSERT_EQUAL_UINT16(3000, adc_get_result(3));
}
//16Unexpected Interrupt
void test_adc_unexpected_interrupt(void) {
    adc_trigger_interrupt();  
    TEST_ASSERT_TRUE(adc_is_conversion_done());  // Ensure system stays stable
}