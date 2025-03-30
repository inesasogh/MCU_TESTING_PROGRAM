#ifndef DAC_TEST
#define DAC_TEST
void setUpDAC();
void tearDownDAC();
void test_DAC_Initialization();
void test_DAC_BoundaryValues();
void test_DAC_MidScale();
void test_DAC_Resolution();
void test_DAC_SettlingTime();
void test_DAC_DefaultValue();
void test_DAC_No_Glitch();
void test_DAC_IncrementalSteps();
void test_DAC_NoiseHandling();
void test_DAC_Stability();
void test_DAC_RapidUpdates();
void test_DAC_NonLinearity();
void test_DAC_FullRangeSweep();
#endif