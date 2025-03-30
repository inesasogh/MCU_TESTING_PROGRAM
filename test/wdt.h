#ifndef MOCK_WATCHDOG_H
#define MOCK_WATCHDOG_H

#include <stdbool.h>
#include <stdint.h>

#define WDT_TIMEOUT 1000 // Default timeout in milliseconds

// Function prototypes
void WDT_Reset(void);
bool WDT_Init(void);
void WDT_Enable(void);
void WDT_Disable(void);
bool WDT_IsEnabled(void);
void WDT_SetTimeout(uint32_t timeout);
uint32_t WDT_GetTimeout(void);
void WDT_Feed(void);
bool WDT_DidReset(void);
void WDT_ForceReset(void);
bool WDT_WasLastResetDueToWDT(void);
void WDT_EnableInterruptMode(void);
bool WDT_InterruptTriggered(void);
void WDT_SimulateTimePassage(uint32_t milliseconds);
#endif // MOCK_WATCHDOG_H
