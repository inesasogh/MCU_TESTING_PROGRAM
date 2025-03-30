#ifndef TEST_RTC
#define TEST_RTC
void setUpRTC(void);
void tearDownRTC(void);
void test_rtc_initialization(void);
void test_rtc_set_get_time(void);
void test_rtc_time_progression(void);
void test_rtc_alarm(void);
void test_rtc_leap_year(void);
void test_rtc_invalid_date(void);
void test_rtc_backup_power(void);
#endif









