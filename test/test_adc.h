#ifndef ADC_TEST
#define ADC_TEST
void setUpADC(void);
void tearDownADC(void);
void test_adc_initialization(void);
void test_adc_single_conversion(void);
void test_adc_multiple_conversions(void);
void test_adc_min_value(void);
void test_adc_max_value(void);
void test_adc_mid_value(void);
void test_adc_invalid_channel(void);
void test_adc_power_on_default(void);
void test_adc_sampling_time(void);
void test_adc_voltage_scaling(void);
void test_adc_noise_stability(void);
void test_adc_conversion_time(void);

void test_adc_interrupt_trigger(void);
void test_adc_interrupt_value_handling(void);
void test_adc_multiple_interrupts(void);
void test_adc_unexpected_interrupt(void);


#endif