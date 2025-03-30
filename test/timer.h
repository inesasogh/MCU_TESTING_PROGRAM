#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_TIMER_VALUE 255
#define DEFAULT_PRESCALER 8
#define INVALID_PRESCALER 999

typedef enum {
    TIMER1,
    TIMER2
} TimerID;

typedef enum {
    CLOCK_INTERNAL,
    CLOCK_EXTERNAL
} ClockSource;

typedef enum {
    PRESCALER_1,
    PRESCALER_8,
    PRESCALER_64,
    PRESCALER_256,
    PRESCALER_1024
} Prescaler;

typedef enum {
    EDGE_RISING,
    EDGE_FALLING
} EdgeMode;
typedef enum {
    TIMER_MODE_NORMAL,
    TIMER_MODE_ONE_PULSE,
    TIMER_MODE_CAPTURE_COMPARE,
    TIMER_MODE_PWM
} TimerMode;

typedef enum {
    TIMER_OK,
    TIMER_ERROR
} TimerStatus;
void timer_init(TimerID timer, Prescaler prescaler, ClockSource source);
void timer_set_mode(TimerID timer, TimerMode mode);
void timer_enable(TimerID timer);
void timer_disable(TimerID timer);
void timer_set_external_clock(TimerID timer, EdgeMode edge);
void timer_set_pwm_mode(TimerID timer, uint8_t duty_cycle);

void timer_set_compare_value(TimerID timer, uint8_t compare_value);
uint8_t timer_capture_event(TimerID timer);

void timer_start_one_pulse(TimerID timer);
bool is_timer_one_pulse_done(TimerID timer);

void watchdog_enable(uint32_t timeout);
void watchdog_feed(void);
bool is_watchdog_triggered(void);

void enable_mock_timer_interrupt(TimerID timer);
void mock_timer_tick(TimerID timer, uint8_t ticks);
void mock_external_signal_pulse(TimerID timer, uint8_t pulses);
void reset_mock_timer(void);
void set_mock_timer_count(TimerID timer, uint8_t count);

extern TimerMode timer_mode[2];
extern bool one_pulse_done[2];
extern uint8_t compare_value[2];
extern uint32_t watchdog_timeout;
extern bool watchdog_triggered;
extern uint8_t get_mock_timer_count(TimerID timer);
extern bool is_mock_timer_enabled(TimerID timer);
extern Prescaler get_mock_prescaler(TimerID timer);
extern ClockSource get_mock_clock_source(TimerID timer);
extern bool get_mock_interrupt_flag(TimerID timer);
extern uint8_t get_mock_pwm_duty_cycle(TimerID timer);
extern bool get_mock_timer_overflow_flag(TimerID timer);

#endif // TIMER_H
