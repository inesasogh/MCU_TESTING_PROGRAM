#include "rtc.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

static rtc_time_t current_time = {0, 0, 0};
static rtc_date_t current_date = {1, 1, 2000};
static rtc_time_t alarm_time = {0, 0, 0};
static bool alarm_set = false;
static bool rtc_initialized = false;
static bool alarm_triggered = false;
static bool in_low_power_mode = false;

// RTC Initialization
void rtc_init(void) {
    rtc_initialized = true;
}

// Check if RTC is initialized
bool rtc_is_initialized(void) {
    return rtc_initialized;
}

// Set RTC time
void rtc_set_time(rtc_time_t time) {
    current_time = time;
}

// Get RTC time
rtc_time_t rtc_get_time(void) {
    return current_time;
}

// Set RTC date
bool rtc_set_date(rtc_date_t date) {
    if (date.month < 1 || date.month > 12 || date.day < 1 || date.day > 31) {
        return false; // Invalid date
    }
    current_date = date;
    return true;
}

// Get RTC date
rtc_date_t rtc_get_date(void) {
    return current_date;
}

// Set RTC alarm
void rtc_set_alarm(rtc_time_t time) {
    alarm_time = time;
    alarm_set = true;
}

// Disable RTC alarm
void rtc_disable_alarm(void) {
    alarm_set = false;
}

// Check if alarm has triggered
bool rtc_alarm_triggered(void) {
    if (alarm_set && 
        current_time.hours == alarm_time.hours &&
        current_time.minutes == alarm_time.minutes &&
        current_time.seconds == alarm_time.seconds) {
        alarm_triggered = true;
    } else {
        alarm_triggered = false;
    }
    return alarm_triggered;
}

// Simulate time progression (for software tests)
void rtc_increment_time(void) {
    if (in_low_power_mode) return; // RTC freezes in low power mode

    current_time.seconds++;
    if (current_time.seconds >= 60) {
        current_time.seconds = 0;
        current_time.minutes++;
    }
    if (current_time.minutes >= 60) {
        current_time.minutes = 0;
        current_time.hours++;
    }
    if (current_time.hours >= 24) {
        current_time.hours = 0;
    }
}

// Simulate power loss
void rtc_simulate_power_loss(void) {
    rtc_initialized = false; // RTC loses power
}

// Restore RTC power
void rtc_restore_power(void) {
    rtc_initialized = true; // Power is back, but RTC should retain time
}

// Simulate DST change
void rtc_apply_dst_change(void) {
    current_time.hours += 1;
    if (current_time.hours >= 24) {
        current_time.hours = 0;
    }
}

// Simulate external interrupt
void rtc_simulate_interrupt(void) {
    // Simulating an external event that pauses RTC temporarily
    printf("RTC Interrupted! Time updates paused.\n");
}

// Enter low power mode (simulation)
void rtc_enter_low_power_mode(void) {
    in_low_power_mode = true;
    printf("RTC is now in low power mode.\n");
}

// Exit low power mode (simulation)
void rtc_exit_low_power_mode(void) {
    in_low_power_mode = false;
    printf("RTC exited low power mode.\n");
}
void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}
