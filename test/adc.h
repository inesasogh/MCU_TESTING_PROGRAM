#ifndef ADC_MOCK_H
#define ADC_MOCK_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int adc_init(void);
uint16_t adc_read(uint8_t channel);
void adc_set_mock_value(uint8_t channel, uint16_t value);
void adc_start_conversion(uint8_t channel);
uint16_t adc_get_result(uint8_t channel);
bool adc_is_conversion_done(void);
void adc_trigger_interrupt(void);
extern uint16_t mock_adc_values[16];
extern bool conversion_done;
#endif

