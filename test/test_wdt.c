#include "unity.h"
#include "wdt.h"
#include "test_wdt.h"

void setUpWDT(void){
    WDT_Reset();
}
void tearDownWDT(void){}

void test_WDT_initialization(void){
    TEST_ASSERT_TRUE(WDT_Init());
}
void test_WDT_enable(void){
    WDT_Enable();
    TEST_ASSERT_TRUE(WDT_IsEnabled());
}
void test_WDT_timeout(void) {
    WDT_Enable();
    WDT_SimulateTimePassage(WDT_TIMEOUT + 10); // Simulate waiting beyond the timeout
    TEST_ASSERT_TRUE(WDT_DidReset());
}
void test_WDT_feed(void) {
    WDT_Enable();
    WDT_Feed();
    WDT_SimulateTimePassage(WDT_TIMEOUT / 2); // Less than timeout
    TEST_ASSERT_FALSE(WDT_DidReset());
}

void test_WDT_disable(void) {
    WDT_Enable();
    WDT_Disable();
    TEST_ASSERT_FALSE(WDT_IsEnabled());
}
void test_WDT_configure_timeout(void) {
    WDT_SetTimeout(500); // 500ms
    TEST_ASSERT_EQUAL(500, WDT_GetTimeout());
}
void test_WDT_interrupt_mode(void) {
    WDT_EnableInterruptMode();
    WDT_SimulateTimePassage(WDT_TIMEOUT - 10); // Just before reset
    TEST_ASSERT_TRUE(WDT_InterruptTriggered());
}
void test_WDT_reset_cause(void) {
    WDT_ForceReset();
    TEST_ASSERT_TRUE(WDT_WasLastResetDueToWDT());
}
