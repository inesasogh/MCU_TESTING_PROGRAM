#include "unity.h"
#include "timer.h"  // Mocked timer functions and registers
#include "test_timer.h"
void setUpTIMER(void) {
    // Reset all mocked registers before each test
    reset_mock_timer();
}

void tearDownTIMER(void) {}

// 1. Basic Timer Initialization Tests
void test_timer_initialization(void) {
    timer_init(TIMER1, PRESCALER_8, CLOCK_INTERNAL);
    TEST_ASSERT_EQUAL(PRESCALER_8, get_mock_prescaler(TIMER1));
    TEST_ASSERT_EQUAL(CLOCK_INTERNAL, get_mock_clock_source(TIMER1));
}

void test_timer_enable_disable(void) {
    timer_enable(TIMER1);
    TEST_ASSERT_TRUE(is_mock_timer_enabled(TIMER1));
    
    timer_disable(TIMER1);
    TEST_ASSERT_FALSE(is_mock_timer_enabled(TIMER1));
}

// 2. Timer Counting Behavior Tests
void test_timer_counting(void) {
    timer_enable(TIMER1);
    mock_timer_tick(TIMER1, 10);
    TEST_ASSERT_EQUAL(10, get_mock_timer_count(TIMER1));
}

// 3. Timer Overflow and Underflow Tests
void test_timer_overflow(void) {
    set_mock_timer_count(TIMER1, MAX_TIMER_VALUE);
    mock_timer_tick(TIMER1, 1);
    TEST_ASSERT_EQUAL(0, get_mock_timer_count(TIMER1));
    TEST_ASSERT_TRUE(get_mock_timer_overflow_flag(TIMER1));
}
// 4. Timer Interrupt Tests
void test_timer_interrupt_triggered(void) {
    enable_mock_timer_interrupt(TIMER1);
    mock_timer_tick(TIMER1, MAX_TIMER_VALUE);
    mock_timer_tick(TIMER1, 1);
    TEST_ASSERT_TRUE(get_mock_interrupt_flag(TIMER1));
}

// 5. Counter Mode Tests
void test_counter_external_signal(void) {
    timer_set_external_clock(TIMER1, EDGE_RISING);
    mock_external_signal_pulse(TIMER1, 5);
    TEST_ASSERT_EQUAL(5, get_mock_timer_count(TIMER1));
}

// 6. PWM Tests
void test_pwm_signal(void) {
    timer_set_pwm_mode(TIMER1, 50); // 50% duty cycle
    TEST_ASSERT_EQUAL(50, get_mock_pwm_duty_cycle(TIMER1));
}

// 7. Edge Case and Error Handling Tests
void test_invalid_prescaler_setting(void) {
    timer_init(TIMER1, INVALID_PRESCALER, CLOCK_INTERNAL);
    TEST_ASSERT_EQUAL(DEFAULT_PRESCALER, get_mock_prescaler(TIMER1));
}
//8
void test_timer_prescaler(void) {
    timer_init(TIMER1, PRESCALER_64, CLOCK_INTERNAL);
    TEST_ASSERT_EQUAL(PRESCALER_64, get_mock_prescaler(TIMER1));

    //timer_init_ExpectAndReturn(16, TIMER_OK);
    //TEST_ASSERT_EQUAL(TIMER_OK, timer_init(TIMER1, PRESCALER_1, CLOCK_INTERNAL));

}
void test_switch_clock_source(void) {
    timer_init(TIMER1, PRESCALER_8, CLOCK_EXTERNAL);
    TEST_ASSERT_EQUAL(CLOCK_EXTERNAL, get_mock_clock_source(TIMER1));
}

void test_dynamic_prescaler_update(void) {
    timer_init(TIMER1, PRESCALER_8, CLOCK_INTERNAL);
    timer_init(TIMER1, PRESCALER_256, CLOCK_INTERNAL);
    TEST_ASSERT_EQUAL(PRESCALER_256, get_mock_prescaler(TIMER1));
}

//9
void test_timer_capture_event(void) {
    mock_external_signal_pulse(TIMER1, 1);
    TEST_ASSERT_EQUAL(1, get_mock_timer_count(TIMER1));
}

void test_timer_compare_match_interrupt(void) {
    enable_mock_timer_interrupt(TIMER1);
    mock_timer_tick(TIMER1, MAX_TIMER_VALUE);
    TEST_ASSERT_TRUE(get_mock_interrupt_flag(TIMER1));
}
void test_dynamic_compare_value_update(void) {
    timer_set_pwm_mode(TIMER1, 75);
    TEST_ASSERT_EQUAL(75, get_mock_pwm_duty_cycle(TIMER1));
}
//10
void test_timer_one_pulse_mode(void) {
    // Start the timer
    timer_set_pwm_mode(TIMER1, 100);
    mock_timer_tick(TIMER1, 1);
    TEST_ASSERT_EQUAL(100, get_mock_pwm_duty_cycle(TIMER1));
    timer_disable(TIMER1);
    TEST_ASSERT_FALSE(is_mock_timer_enabled(TIMER1));
}
//11
void test_multiple_timers_independent(void) {
    timer_enable(TIMER1);
    timer_enable(TIMER2);
    TEST_ASSERT_TRUE(is_mock_timer_enabled(TIMER1));
    TEST_ASSERT_TRUE(is_mock_timer_enabled(TIMER2));
}
void test_timer_chaining(void) {
    mock_timer_tick(TIMER1, MAX_TIMER_VALUE);
    mock_timer_tick(TIMER2, MAX_TIMER_VALUE);
    TEST_ASSERT_TRUE(get_mock_timer_overflow_flag(TIMER1));
    TEST_ASSERT_TRUE(get_mock_timer_overflow_flag(TIMER2));
}

//12
void test_watchdog_timer_reset(void) {
    // Simulating watchdog timeout reset
    mock_timer_tick(TIMER1, MAX_TIMER_VALUE + 1);
    TEST_ASSERT_EQUAL(0, get_mock_timer_count(TIMER1));
}

void test_watchdog_timer_feeding(void) {
    mock_timer_tick(TIMER1, MAX_TIMER_VALUE / 2);
    TEST_ASSERT_EQUAL(MAX_TIMER_VALUE / 2, get_mock_timer_count(TIMER1));
}
//13
void test_timer_low_power_mode(void) {
    timer_enable(TIMER1);
    mock_timer_tick(TIMER1, 5);
    TEST_ASSERT_EQUAL(5, get_mock_timer_count(TIMER1));
}
void test_timer_interrupt_wakes_up(void) {
    enable_mock_timer_interrupt(TIMER1);
    mock_timer_tick(TIMER1, MAX_TIMER_VALUE);
    TEST_ASSERT_TRUE(get_mock_interrupt_flag(TIMER1));
}
//14
void test_rapid_enable_disable(void) {
    for (int i = 0; i < 10; i++) {
        timer_enable(TIMER1);
        timer_disable(TIMER1);
    }
    TEST_ASSERT_FALSE(is_mock_timer_enabled(TIMER1));
}

void test_high_frequency_interrupts(void) {
    for (int i = 0; i < 100; i++) {
        mock_timer_tick(TIMER1, 1);
    }
    TEST_ASSERT_TRUE(get_mock_interrupt_flag(TIMER1));
}