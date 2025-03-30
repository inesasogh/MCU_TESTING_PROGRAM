#include "wdt.h"

static bool wdt_enabled = false;
static uint32_t wdt_timeout = WDT_TIMEOUT;
static bool wdt_reset_occurred = false;
static bool wdt_interrupt_triggered = false;
static bool wdt_last_reset_due_to_wdt = false;
static uint32_t mock_time_elapsed = 0;
void WDT_Reset(void) {
    wdt_enabled = false;
    wdt_reset_occurred = false;
    wdt_interrupt_triggered = false;
    wdt_last_reset_due_to_wdt = false;
    wdt_timeout = WDT_TIMEOUT;
}

bool WDT_Init(void) {
    return true; // Assume initialization is always successful
}

void WDT_Enable(void) {
    wdt_enabled = true;
}

void WDT_Disable(void) {
    wdt_enabled = false;
}

bool WDT_IsEnabled(void) {
    return wdt_enabled;
}

void WDT_SetTimeout(uint32_t timeout) {
    wdt_timeout = timeout;
}

uint32_t WDT_GetTimeout(void) {
    return wdt_timeout;
}

void WDT_Feed(void) {
    wdt_reset_occurred = false; // Feeding prevents reset
}

bool WDT_DidReset(void) {
    return wdt_reset_occurred;
}

void WDT_ForceReset(void) {
    wdt_reset_occurred = true;
    wdt_last_reset_due_to_wdt = true;
}

bool WDT_WasLastResetDueToWDT(void) {
    return wdt_last_reset_due_to_wdt;
}

void WDT_SimulateTimePassage(uint32_t milliseconds) {
    mock_time_elapsed += milliseconds;
    if (mock_time_elapsed >= wdt_timeout && wdt_enabled) {
        wdt_reset_occurred = true;  // Simulate Watchdog Timer Reset
    }
}

void WDT_EnableInterruptMode(void) {
    wdt_interrupt_triggered = true;
}

bool WDT_InterruptTriggered(void) {
    return wdt_interrupt_triggered;
}
