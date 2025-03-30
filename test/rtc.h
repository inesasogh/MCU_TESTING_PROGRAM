#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <stdbool.h>

// Structure to hold time (HH:MM:SS)
typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} rtc_time_t;

// Structure to hold date (DD:MM:YYYY)
typedef struct {
    uint8_t day;
    uint8_t month;
    uint16_t year;
} rtc_date_t;

// RTC Initialization
void rtc_init(void);
bool rtc_is_initialized(void);

// Time Functions
void rtc_set_time(rtc_time_t time);
rtc_time_t rtc_get_time(void);

// Date Functions
bool rtc_set_date(rtc_date_t date);
rtc_date_t rtc_get_date(void);

// Alarm Functions
void rtc_set_alarm(rtc_time_t time);
bool rtc_alarm_triggered(void);

// Power Backup Simulation (if applicable)
void rtc_simulate_power_loss(void);
void rtc_restore_power(void);

void delay(int number_of_seconds);
#endif // RTC_H
