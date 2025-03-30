#ifndef TIMER_TEST
#define TIMER_TEST
void setUpTIMER(void);

void tearDownTIMER(void);

// 1. Basic Timer Initialization Tests
void test_timer_initialization(void);
void test_timer_enable_disable(void);

// 2. Timer Counting Behavior Tests
void test_timer_counting(void);
// 3. Timer Overflow and Underflow Tests
void test_timer_overflow(void);
// 4. Timer Interrupt Tests
void test_timer_interrupt_triggered(void);
// 5. Counter Mode Tests
void test_counter_external_signal(void);

// 6. PWM Tests
void test_pwm_signal(void);

// 7. Edge Case and Error Handling Tests
void test_invalid_prescaler_setting(void);

//8.Prescaler and Clock Source Tests
void test_timer_prescaler(void);
void test_switch_clock_source(void) ;
void test_dynamic_prescaler_update(void);

//9.Capture/Compare Mode Tests
void test_timer_capture_event(void);
void test_timer_compare_match_interrupt(void);
void test_dynamic_compare_value_update(void);
//10.One-Pulse Mode (OPM) Tests
void test_timer_one_pulse_mode(void);

//11.Timer Synchronization and Multi-Timer Interaction
void test_multiple_timers_independent(void);
void test_timer_chaining(void);

//12.Watchdog Timer Tests
void test_watchdog_timer_reset(void);
void test_watchdog_timer_feeding(void);

//13.Low-Power and Sleep Mode Compatibility
void test_timer_low_power_mode(void);
void test_timer_interrupt_wakes_up(void);

//14.Edge-Case Stress Testing
void test_rapid_enable_disable(void);
void test_high_frequency_interrupts(void);

#endif