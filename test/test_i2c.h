#ifndef TEST_I2C_H
#define TEST_I2C_H
void setUpI2C(void);
void tearDownI2C(void);
void test_I2C_Init_Should_Succeed_With_Valid_Configuration(void);
void test_I2C_Init_Should_Fail_With_Invalid_Configuration(void);
void test_I2C_SendByte_Should_Succeed(void) ;
void test_I2C_SendByte_Should_Fail_On_NACK(void);
void test_I2C_SendData_Should_Succeed(void);
void test_I2C_ReceiveByte_Should_Succeed(void);
void test_I2C_BusBusy_Should_Return_Error(void) ;
void test_I2C_RepeatedStart_Should_Succeed(void);
void test_I2C_ArbitrationLoss_Should_Detect_Error(void);
void test_I2C_Timeout_Should_Return_Error(void);
void test_I2C_StuckSDA_Should_Detect_And_Recover(void);
void test_I2C_StuckSCL_Should_Detect_And_Recover(void);
void test_I2C_LowestAddress_Should_Succeed(void);
void test_I2C_HighestAddress_Should_Succeed(void);
void test_I2C_ClockStretching_Should_Wait_Properly(void);
void test_I2C_ExcessiveClockStretching_Should_Timeout(void);
void test_I2C_CorruptedData_Should_Fail(void);
#endif