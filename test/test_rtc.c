#include "unity.h"
#include <time.h>
#include "rtc.h"  // RTC module you are testing

void setUpRTC(void) {
    rtc_init(); 
}


void tearDownRTC(void) {
}

void test_rtc_initialization(void) {
    TEST_ASSERT_TRUE(rtc_is_initialized());  
}

void test_rtc_set_get_time(void) {
    rtc_time_t time = {12, 30, 45}; 
    rtc_set_time(time);
    
    rtc_time_t read_time = rtc_get_time();
    TEST_ASSERT_EQUAL_UINT8(12, read_time.hours);
    TEST_ASSERT_EQUAL_UINT8(30, read_time.minutes);
    TEST_ASSERT_EQUAL_UINT8(45, read_time.seconds);
}

void test_rtc_time_progression(void) {
    rtc_time_t start_time = {23, 59, 58}; 
    rtc_set_time(start_time);

    delay(2000);  

    rtc_time_t read_time = rtc_get_time();
    TEST_ASSERT_EQUAL_UINT8(0, read_time.hours);  
    TEST_ASSERT_EQUAL_UINT8(0, read_time.minutes);
    TEST_ASSERT_EQUAL_UINT8(0, read_time.seconds);
}

// Test: Alarm Functionality
void test_rtc_alarm(void) {
    rtc_time_t alarm_time = {7, 0, 0};  
    rtc_set_alarm(alarm_time);
    
    rtc_time_t current_time = {6, 59, 59};  
    rtc_set_time(current_time);
    delay(1000);  
    
    TEST_ASSERT_TRUE(rtc_alarm_triggered());  
}


void test_rtc_leap_year(void) {
    rtc_date_t leap_year = {29, 2, 2024};  
    rtc_set_date(leap_year);
    
    rtc_date_t read_date = rtc_get_date();
    TEST_ASSERT_EQUAL_UINT8(29, read_date.day);
    TEST_ASSERT_EQUAL_UINT8(2, read_date.month);
    TEST_ASSERT_EQUAL_UINT16(2024, read_date.year);
}


void test_rtc_invalid_date(void) {
    rtc_date_t invalid_date = {30, 2, 2025};  
    TEST_ASSERT_FALSE(rtc_set_date(invalid_date));  
}


void test_rtc_backup_power(void) {
    rtc_time_t saved_time = {10, 15, 30};
    rtc_set_time(saved_time);
    
    rtc_simulate_power_loss();  
    rtc_restore_power();        
    rtc_time_t restored_time = rtc_get_time();
    TEST_ASSERT_EQUAL_UINT8(10, restored_time.hours);
    TEST_ASSERT_EQUAL_UINT8(15, restored_time.minutes);
    TEST_ASSERT_EQUAL_UINT8(30, restored_time.seconds);
}

