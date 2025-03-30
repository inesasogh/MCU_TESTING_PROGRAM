#ifndef DAC_MOCK_H
#define DAC_MOCK_H

#include <stdint.h>
#include <stdbool.h>

#define DAC_MAX_VALUE 4095  // 12-bit DAC (0 to 4095)
#define DAC_REF_VOLTAGE 3.3  // Reference voltage in volts

void dac_init(void);
void dac_write(uint16_t value);
uint16_t dac_get_last_value(void);
float dac_read_voltage(void);
bool dac_is_initialized(void);
bool dac_is_stable(void);

extern uint16_t last_dac_value;
extern bool dac_initialized;
extern bool stable;
#endif