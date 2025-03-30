#include <stdio.h>
#include "adc.h"
#include <stdbool.h>

uint16_t mock_adc_values[16]={0};  // Assuming 16 channels max
bool conversion_done = false;

int  adc_init(void) {
    for (int i = 0; i < 16; i++) {
        mock_adc_values[i] = 0;
    }
    return 0;
}

uint16_t adc_read(uint8_t channel) {
    if (channel >= 16) return 0xFFFF;  // Simulate invalid channel error
    return mock_adc_values[channel];
}

void adc_set_mock_value(uint8_t channel, uint16_t value) {
    if (channel < 16) {
        mock_adc_values[channel] = value;
    }
}

void adc_start_conversion(uint8_t channel) {
    (void)channel;  // Ignore channel for mock
    conversion_done = false;
}

uint16_t adc_get_result(uint8_t channel) {
    return mock_adc_values[channel];
}

bool adc_is_conversion_done(void) {
    return conversion_done;
}

void adc_trigger_interrupt(void) {
    conversion_done = true;
}