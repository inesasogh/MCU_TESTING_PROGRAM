#include "test_GPIOmain.h"
#include "test_timer.h"
#include "test_adc.h"
#include "test_dac.h"
#include "test_wdt.h"
#include "test_dma.h"
#include "test_uart.h"
#include "test_rtc.h"
#include "test_i2c.h"
#include "test_spi.h"
#include <time.h>
#include "unity.h"
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_GPIO_Init_Should_Set_Pin_Mode);
    RUN_TEST(test_GPIO_Write_Should_Set_Pin_High);
    RUN_TEST(test_GPIO_Write_Should_Set_Pin_Low);
    RUN_TEST(test_GPIO_Read_Should_Return_Correct_Value);
    RUN_TEST(test_GPIO_Write_Should_Handle_Invalid_Pin);
    RUN_TEST(test_GPIO_Write_Should_Fail_If_Pin_Not_Initialized);
    RUN_TEST(test_GPIO_SetPullUp_Should_Enable_PullUp);
    RUN_TEST(test_GPIO_SetPullDown_Should_Enable_PullDown);
    RUN_TEST(test_GPIO_Toggle_Should_Work_Fast);
    RUN_TEST(test_GPIO_Read_Should_Debounce_Noise);
    RUN_TEST(test_GPIO_Interrupt_RisingEdge_Should_Trigger_Callback);
    RUN_TEST(test_GPIO_Interrupt_FallingEdge_Should_Trigger_Callback);
    RUN_TEST(test_GPIO_Interrupt_Debounce_Should_Filter_Noise);
    RUN_TEST(test_GPIO_Multiple_Pins_Should_Work_Independently);
    RUN_TEST(test_GPIO_Input_Controls_Output);
    RUN_TEST(test_timer_initialization);
    RUN_TEST(test_timer_enable_disable);
    RUN_TEST(test_timer_counting);
    RUN_TEST(test_timer_overflow);
    RUN_TEST(test_timer_interrupt_triggered);
    RUN_TEST(test_counter_external_signal);
    RUN_TEST(test_pwm_signal);
    RUN_TEST(test_invalid_prescaler_setting);
    RUN_TEST(test_timer_prescaler);
    RUN_TEST(test_switch_clock_source);
    RUN_TEST(test_dynamic_prescaler_update);
    RUN_TEST(test_timer_capture_event);
    RUN_TEST(test_timer_compare_match_interrupt);
    RUN_TEST(test_dynamic_compare_value_update);
    RUN_TEST(test_timer_one_pulse_mode);
    RUN_TEST(test_multiple_timers_independent);
    RUN_TEST(test_timer_chaining);
    RUN_TEST(test_watchdog_timer_reset);
    RUN_TEST(test_watchdog_timer_feeding);
    RUN_TEST(test_timer_low_power_mode);
    RUN_TEST(test_timer_interrupt_wakes_up);
    RUN_TEST(test_rapid_enable_disable);
    RUN_TEST(test_high_frequency_interrupts);
    RUN_TEST(test_adc_initialization);
    RUN_TEST(test_adc_single_conversion);
    RUN_TEST(test_adc_multiple_conversions);
    RUN_TEST(test_adc_min_value);
    RUN_TEST(test_adc_max_value);
    RUN_TEST(test_adc_mid_value);
    RUN_TEST(test_adc_invalid_channel);
    RUN_TEST(test_adc_power_on_default);
    RUN_TEST(test_adc_sampling_time);
    RUN_TEST(test_adc_voltage_scaling);
    RUN_TEST(test_adc_noise_stability);
    RUN_TEST(test_adc_conversion_time);
    RUN_TEST(test_adc_interrupt_trigger);
    RUN_TEST(test_adc_interrupt_value_handling);
    RUN_TEST(test_adc_multiple_interrupts);
    RUN_TEST(test_adc_unexpected_interrupt);
    RUN_TEST(test_DAC_Initialization);
    RUN_TEST(test_DAC_BoundaryValues);
    RUN_TEST(test_DAC_MidScale);
    RUN_TEST(test_DAC_Resolution);
    RUN_TEST(test_DAC_SettlingTime);
    RUN_TEST(test_DAC_DefaultValue);
    RUN_TEST(test_DAC_No_Glitch);
    RUN_TEST(test_DAC_IncrementalSteps);
    RUN_TEST(test_DAC_NoiseHandling);
    RUN_TEST(test_DAC_Stability);
    RUN_TEST(test_DAC_RapidUpdates);
    RUN_TEST(test_DAC_NonLinearity);
    RUN_TEST(test_DAC_FullRangeSweep);
    RUN_TEST(test_WDT_initialization);
    RUN_TEST(test_WDT_enable);
    RUN_TEST(test_WDT_timeout);
    RUN_TEST(test_WDT_feed);
    RUN_TEST(test_WDT_disable);
    RUN_TEST(test_WDT_configure_timeout);
    RUN_TEST(test_WDT_interrupt_mode);
    RUN_TEST(test_WDT_reset_cause);
    RUN_TEST(test_DMA_Init_ShouldInitializeProperly);
    RUN_TEST(test_DMA_MemoryToMemory_ShouldTransferCorrectly);
    RUN_TEST(test_DMA_PeripheralToMemory_ShouldTransferCorrectly);
    RUN_TEST(test_DMA_MemoryToPeripheral_ShouldTransferCorrectly);
    RUN_TEST(test_DMA_TransferComplete_ShouldTriggerInterrupt);
    RUN_TEST(test_DMA_TransferError_ShouldHandleErrors);
    RUN_TEST(test_DMA_CircularMode_ShouldWorkCorrectly);
    RUN_TEST(test_DMA_PriorityLevels_ShouldBeConfigurable);
    RUN_TEST(test_DMA_Interrupt_ShouldBeTriggered);
    RUN_TEST(test_DMA_MultipleTransfers_ShouldRunSimultaneously);
    RUN_TEST(test_rtc_initialization);
    RUN_TEST(test_rtc_set_get_time);
    RUN_TEST(test_rtc_time_progression);
    RUN_TEST(test_rtc_alarm);
    RUN_TEST(test_rtc_leap_year);
    RUN_TEST(test_rtc_invalid_date);
    RUN_TEST(test_rtc_backup_power);
    RUN_TEST(test_uart_initialization);
    RUN_TEST(test_uart_set_baudrate);
    RUN_TEST(test_uart_send_byte);
    RUN_TEST(test_uart_send_multiple_bytes);
    RUN_TEST(test_uart_receive_byte);
    RUN_TEST(test_uart_parity_error);
    RUN_TEST(test_uart_frame_error);
    RUN_TEST(test_I2C_Init_Should_Succeed_With_Valid_Configuration);
    RUN_TEST(test_I2C_Init_Should_Fail_With_Invalid_Configuration);
    RUN_TEST(test_I2C_SendByte_Should_Succeed);
    RUN_TEST(test_I2C_SendByte_Should_Fail_On_NACK);
    RUN_TEST(test_I2C_SendData_Should_Succeed);
    RUN_TEST(test_I2C_ReceiveByte_Should_Succeed);
    RUN_TEST(test_I2C_BusBusy_Should_Return_Error);
    RUN_TEST(test_I2C_RepeatedStart_Should_Succeed);
    RUN_TEST(test_I2C_ArbitrationLoss_Should_Detect_Error);
    RUN_TEST(test_I2C_Timeout_Should_Return_Error);
    RUN_TEST(test_I2C_StuckSDA_Should_Detect_And_Recover);
    RUN_TEST(test_I2C_StuckSCL_Should_Detect_And_Recover);
    RUN_TEST(test_I2C_LowestAddress_Should_Succeed);
    RUN_TEST(test_I2C_HighestAddress_Should_Succeed);
    RUN_TEST(test_I2C_ClockStretching_Should_Wait_Properly);
    RUN_TEST(test_I2C_ExcessiveClockStretching_Should_Timeout);
    RUN_TEST(test_I2C_CorruptedData_Should_Fail);
    RUN_TEST(test_SPI_Initialization);
    RUN_TEST(test_SPI_Mode_Config);
    RUN_TEST(test_SPI_Clock_Speed);
    RUN_TEST(test_SPI_Data_Transmission);
    RUN_TEST(test_SPI_Data_Reception);
    RUN_TEST(test_SPI_Loopback);
    RUN_TEST(test_SPI_Chip_Select);
    RUN_TEST(test_SPI_Full_Duplex);
    RUN_TEST(test_SPI_Half_Duplex);
    RUN_TEST(test_SPI_Interrupt);
    RUN_TEST(test_SPI_Error_Handling);
    RUN_TEST(test_SPI_DMA_Transfer);

    return UNITY_END();
    
}