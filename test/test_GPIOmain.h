#ifndef GPIO_TEST
#define GPIO_TEST//These tests check if GPIO pins behave as expected when configured as input or output.
void test_GPIO_Init_Should_Set_Pin_Mode(void);
void test_GPIO_Write_Should_Set_Pin_High(void);
void test_GPIO_Write_Should_Set_Pin_Low(void);
void test_GPIO_Read_Should_Return_Correct_Value(void);
void test_GPIO_Write_Should_Handle_Invalid_Pin(void);
void test_GPIO_Write_Should_Fail_If_Pin_Not_Initialized(void);
void test_GPIO_SetPullUp_Should_Enable_PullUp(void);
void test_GPIO_SetPullDown_Should_Enable_PullDown(void);
void test_GPIO_Toggle_Should_Work_Fast(void);
void test_GPIO_Read_Should_Debounce_Noise(void);
void test_GPIO_Interrupt_RisingEdge_Should_Trigger_Callback(void);
void test_GPIO_Interrupt_FallingEdge_Should_Trigger_Callback(void);
void test_GPIO_Interrupt_Debounce_Should_Filter_Noise(void) ;
void test_GPIO_Multiple_Pins_Should_Work_Independently(void);
void test_GPIO_Input_Controls_Output(void);
#endif