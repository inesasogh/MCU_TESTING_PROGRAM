#include "dac.h"

uint16_t last_dac_value = 0;
bool dac_initialized = false;
bool stable = false;

void dac_init(void) {
    last_dac_value = 0;
    dac_initialized = true;
    stable = true;
}

void dac_write(uint16_t value) {
    if (!dac_initialized) return;

    if (value > DAC_MAX_VALUE) {
        value = DAC_MAX_VALUE;
    }

    last_dac_value = value;
    
    // Simulate instability before settling
    stable = false;
}

uint16_t dac_get_last_value(void) {
    return last_dac_value;
}

float dac_read_voltage(void) {
    return (last_dac_value / (float)DAC_MAX_VALUE) * DAC_REF_VOLTAGE;
}

bool dac_is_initialized(void) {
    return dac_initialized;
}

bool dac_is_stable(void) {
    // Simulating DAC stabilization delay
    stable = true;  // You can implement a delay if needed
    return stable;
}
