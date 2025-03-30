#ifndef TEST_WDT
#define TEST_WDT
void setUpWDT(void);
void tearDownWDT(void);
void test_WDT_initialization(void);
void test_WDT_enable(void);
void test_WDT_timeout(void);
void test_WDT_feed(void);
void test_WDT_disable(void);
void test_WDT_configure_timeout(void) ;
void test_WDT_interrupt_mode(void);
void test_WDT_reset_cause(void);
#endif