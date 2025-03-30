#include "unity.h"
#include "test_dac.h"
#include "dac.h"
#include <time.h>

void setUpDAC() {
    dac_init();
}

void tearDownDAC() {}

uint32_t get_mock_time() {
    return (uint32_t)clock();  // Returns time in clock ticks
}

void test_DAC_Initialization() {
    TEST_ASSERT_TRUE(dac_is_initialized());
}

void test_DAC_BoundaryValues() {
    dac_write(0); // Min value
    TEST_ASSERT_EQUAL(0.0, dac_read_voltage());

    dac_write(4095); // Max value (assuming 12-bit DAC)
    TEST_ASSERT_EQUAL(3.3, dac_read_voltage()); // Assuming 3.3V reference
}


void test_DAC_MidScale() {
    dac_write(2048); // Half-scale for 12-bit
    TEST_ASSERT_EQUAL_FLOAT(1.65, dac_read_voltage());
}

void test_DAC_Resolution() {
    float prev_voltage = dac_read_voltage();
    dac_write(dac_get_last_value() + 1);
    TEST_ASSERT_FLOAT_WITHIN(0.001, prev_voltage + (3.3 / 4096), dac_read_voltage());
}

void test_DAC_SettlingTime() {
    uint32_t start_time = get_mock_time();
    dac_write(1000);
    while (!dac_is_stable());
    uint32_t elapsed_time = get_mock_time() - start_time;

    TEST_ASSERT_LESS_THAN_UINT32(10, elapsed_time); // Example: DAC should stabilize within 10ms
}

// 1. Power-on Default Test
void test_DAC_DefaultValue() {
    TEST_ASSERT_EQUAL_UINT16(0, dac_get_last_value());
    TEST_ASSERT_EQUAL_FLOAT(0.0, dac_read_voltage());
}

// 2. Glitch Test
void test_DAC_No_Glitch() {
    dac_write(1000);
    float v1 = dac_read_voltage();

    dac_write(1001);
    float v2 = dac_read_voltage();

    TEST_ASSERT_FLOAT_WITHIN(0.01, v1 + (DAC_REF_VOLTAGE / DAC_MAX_VALUE), v2);
}

// 3. Incremental Steps Test
void test_DAC_IncrementalSteps() {
    for (uint16_t i = 0; i < 1000; i += 50) {
        dac_write(i);
        float expected_voltage = (i / (float)DAC_MAX_VALUE) * DAC_REF_VOLTAGE;
        TEST_ASSERT_FLOAT_WITHIN(0.01, expected_voltage, dac_read_voltage());
    }
}

// 4. Noise Handling Test
void test_DAC_NoiseHandling() {
    dac_write(2000);
    float v1 = dac_read_voltage();

    dac_write(2001); // Small increment
    float v2 = dac_read_voltage();

    TEST_ASSERT_FLOAT_WITHIN(0.01, v1 + (DAC_REF_VOLTAGE / DAC_MAX_VALUE), v2);
}

// 5. Stability Test
void test_DAC_Stability() {
    dac_write(2500);
    TEST_ASSERT_FALSE(dac_is_stable()); // Initially unstable
    while (!dac_is_stable()); // Wait for stabilization
    TEST_ASSERT_TRUE(dac_is_stable());
}

// 6. Rapid Updates Test
void test_DAC_RapidUpdates() {
    for (uint16_t i = 0; i < 500; i++) {
        dac_write(i);
    }
    TEST_ASSERT_EQUAL_UINT16(499, dac_get_last_value());
}

// 7. Non-linearity Test
void test_DAC_NonLinearity() {
    dac_write(1024);
    float v1 = dac_read_voltage();
    
    dac_write(2048);
    float v2 = dac_read_voltage();
    
    dac_write(3072);
    float v3 = dac_read_voltage();

    TEST_ASSERT_FLOAT_WITHIN(0.02, v1 * 2, v2);
    TEST_ASSERT_FLOAT_WITHIN(0.02, v2 * 1.5, v3);
}

// 8. Full-Range Sweep Test
void test_DAC_FullRangeSweep() {
    for (uint16_t i = 0; i <= DAC_MAX_VALUE; i += 512) {
        dac_write(i);
        float expected_voltage = (i / (float)DAC_MAX_VALUE) * DAC_REF_VOLTAGE;
        TEST_ASSERT_FLOAT_WITHIN(0.02, expected_voltage, dac_read_voltage());
    }
}