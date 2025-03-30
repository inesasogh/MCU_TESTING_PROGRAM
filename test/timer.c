// timer.c - Timer Mock Implementation
#include "timer.h"
#include <string.h>
#include <stdio.h>

// Mocked timer registers
uint8_t timer_count[2] = {0};
bool timer_enabled[2] = {false};
Prescaler timer_prescaler[2] = {DEFAULT_PRESCALER};
ClockSource timer_clock_source[2] = {CLOCK_INTERNAL};
bool timer_interrupt_flag[2] = {false};
bool timer_overflow_flag[2] = {false};
uint8_t pwm_duty_cycle[2] = {0};

TimerMode timer_mode[2] = {TIMER_MODE_NORMAL, TIMER_MODE_NORMAL};
bool one_pulse_done[2] = {false, false};
uint8_t compare_value[2] = {0, 0};
uint32_t watchdog_timeout = 0;
bool watchdog_triggered = false;

/*void timer_set_mode(TimerID timer, TimerMode mode) {
    if (timer > TIMER2) {
        return;  // Invalid timer ID, do nothing
    }
    timer_mode[timer] = mode;

    // Reset state based on mode
    switch (mode) {
        case TIMER_MODE_NORMAL:
            one_pulse_done[timer] = false;
            break;
        case TIMER_MODE_ONE_PULSE:
            one_pulse_done[timer] = false;
            timer_count[timer] = 0;  // Reset counter
            break;
        case TIMER_MODE_CAPTURE_COMPARE:
            compare_value[timer] = 0;  // Reset compare value
            break;
        case TIMER_MODE_PWM:
            // PWM setup (if needed, e.g., resetting duty cycle)
            break;
        default:
            break;
    }
}
void timer_set_compare_value(TimerID timer, uint8_t value) {
    compare_value[timer] = value;
}

uint8_t timer_capture_event(TimerID timer) {
    return timer_count[timer];  // Simulating capture of current counter value
}

void timer_start_one_pulse(TimerID timer) {
    if (timer_mode[timer] == TIMER_MODE_ONE_PULSE) {
        one_pulse_done[timer] = false;
        timer_count[timer] = 0;  // Reset counter
    }
}

bool is_timer_one_pulse_done(TimerID timer) {
    return one_pulse_done[timer];
}

void watchdog_enable(uint32_t timeout) {
    watchdog_timeout = timeout;
    watchdog_triggered = false;
}

void watchdog_feed(void) {
    watchdog_triggered = false;  // Reset watchdog
}

bool is_watchdog_triggered(void) {
    return watchdog_triggered;
}

void timer_reset(TimerID timer) {
    timer_count[timer] = 0;
}

uint8_t timer_get_counter(TimerID timer) {
    return timer_count[timer];
}

void timer_set_counter(TimerID timer, uint8_t count) {
    timer_count[timer] = count;
}


*/
void timer_init(TimerID timer, Prescaler prescaler, ClockSource source){
    if (timer > TIMER2) return;
    timer_prescaler[timer] = (prescaler != INVALID_PRESCALER) ? prescaler : DEFAULT_PRESCALER;
    timer_clock_source[timer] = source;
    timer_count[timer] = 0;
}
void set_mock_timer_count(TimerID timer, uint8_t count) {
    if (count > MAX_TIMER_VALUE) {
        count = 0; 
    }
    timer_count[timer] = count;
}

void timer_enable(TimerID timer) {
    if (timer > TIMER2) return;
    timer_enabled[timer] = true;
}
void timer_disable(TimerID timer) {
    if (timer > TIMER2) return;
    timer_enabled[timer] = false;
}

void timer_set_external_clock(TimerID timer, EdgeMode edge) {
    // Mock external clock behavior, ignoring edge for now
    timer_clock_source[timer] = CLOCK_EXTERNAL;
}

void timer_set_pwm_mode(TimerID timer, uint8_t duty_cycle) {
    pwm_duty_cycle[timer] = duty_cycle;
}

void reset_mock_timer(void) {
    memset(timer_count, 0, sizeof(timer_count));
    memset(timer_enabled, 0, sizeof(timer_enabled));
    memset(timer_interrupt_flag, 0, sizeof(timer_interrupt_flag));
    memset(timer_overflow_flag, 0, sizeof(timer_overflow_flag));
    memset(pwm_duty_cycle, 0, sizeof(pwm_duty_cycle));
}


uint8_t get_mock_timer_count(TimerID timer) {
    return timer_count[timer];
}
bool is_mock_timer_enabled(TimerID timer) {
    return timer_enabled[timer];
}

Prescaler get_mock_prescaler(TimerID timer) {
    return timer_prescaler[timer];
}

ClockSource get_mock_clock_source(TimerID timer) {
    return timer_clock_source[timer];
}

bool get_mock_interrupt_flag(TimerID timer) {
    return timer_interrupt_flag[timer];
}
bool get_mock_timer_overflow_flag(TimerID timer) {
    return timer_overflow_flag[timer];
}
void enable_mock_timer_interrupt(TimerID timer) {
    timer_interrupt_flag[timer] = true;
}
void mock_timer_tick(TimerID timer, uint8_t ticks) {
    if (timer_enabled[timer]) {
        uint16_t new_count = timer_count[timer] + ticks;
        if (new_count > MAX_TIMER_VALUE) {
            timer_count[timer] = 0;
            timer_overflow_flag[timer] = true;
        } else {
            timer_count[timer] = (uint8_t)new_count;
        }
    }
}

void mock_external_signal_pulse(TimerID timer, uint8_t pulses) {
    if (timer_clock_source[timer] == CLOCK_EXTERNAL && timer_enabled[timer]) {
        timer_count[timer] += pulses;
    }
}
uint8_t get_mock_pwm_duty_cycle(TimerID timer) {
    return pwm_duty_cycle[timer];
}

