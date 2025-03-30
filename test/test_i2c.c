#include "unity.h"
#include "i2c.h"
#include "test_i2c.h"

void setUpI2C(void) {
    // Runs before each test
    i2c_init();
}

void tearDownI2C(void) {
    // Runs after each test
    i2c_deinit();
}

// Test I2C Initialization
void test_I2C_Init_Should_Succeed_With_Valid_Configuration(void) {
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_init());
}

void test_I2C_Init_Should_Fail_With_Invalid_Configuration(void) {
    i2c_config_t invalid_config = { .clock_speed = 0 }; // Invalid clock speed
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_init_with_config(&invalid_config));
}

// Test Single Byte Transmission
void test_I2C_SendByte_Should_Succeed(void) {
    uint8_t data = 0xA5;
    i2c_mock_set_ack_response(I2C_ACK);
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_send_byte(0x50, data));
}

void test_I2C_SendByte_Should_Fail_On_NACK(void) {
    uint8_t data = 0xA5;
    i2c_mock_set_ack_response(I2C_NACK);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, data));
}

// Test Multi-Byte Transmission
void test_I2C_SendData_Should_Succeed(void) {
    uint8_t data[] = { 0x10, 0x20, 0x30 };
    i2c_mock_set_ack_response(I2C_ACK);
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_send_data(0x50, data, sizeof(data)));
}

// Test Receiving a Single Byte
void test_I2C_ReceiveByte_Should_Succeed(void) {
    uint8_t received_data;
    i2c_mock_set_received_data(0x7F);
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_receive_byte(0x50, &received_data));
    TEST_ASSERT_EQUAL(0x7F, received_data);
}

// Test Error Handling: Bus Busy
void test_I2C_BusBusy_Should_Return_Error(void) {
    i2c_mock_set_bus_status(I2C_BUSY);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, 0xA5));
}

// Test Repeated Start Condition
void test_I2C_RepeatedStart_Should_Succeed(void) {
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_start(0x50));
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_restart(0x50));
}

// Test Arbitration Loss Handling
void test_I2C_ArbitrationLoss_Should_Detect_Error(void) {
    i2c_mock_set_bus_status(I2C_ARBITRATION_LOSS);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, 0xA5));
}

// Test Timeout Handling
void test_I2C_Timeout_Should_Return_Error(void) {
    i2c_mock_set_response_delay(I2C_TIMEOUT);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, 0xA5));
}

// Test Stuck SDA Line
void test_I2C_StuckSDA_Should_Detect_And_Recover(void) {
    i2c_mock_set_line_status(I2C_SDA_STUCK_LOW);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, 0xA5));
}

// Test Stuck SCL Line
void test_I2C_StuckSCL_Should_Detect_And_Recover(void) {
    i2c_mock_set_line_status(I2C_SCL_STUCK_LOW);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, 0xA5));
}

// Test Communication with Lowest and Highest Addresses
void test_I2C_LowestAddress_Should_Succeed(void) {
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_send_byte(0x03, 0xA5));
}

void test_I2C_HighestAddress_Should_Succeed(void) {
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_send_byte(0x77, 0xA5));
}

// Test Clock Stretching Handling
void test_I2C_ClockStretching_Should_Wait_Properly(void) {
    i2c_mock_set_clock_stretch(I2C_STRETCH_SHORT);
    TEST_ASSERT_EQUAL(I2C_SUCCESS, i2c_send_byte(0x50, 0xA5));
}

// Test Excessive Clock Stretching Triggers Timeout
void test_I2C_ExcessiveClockStretching_Should_Timeout(void) {
    i2c_mock_set_clock_stretch(I2C_STRETCH_LONG);
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_send_byte(0x50, 0xA5));
}

// Test Corrupted Data Detection
void test_I2C_CorruptedData_Should_Fail(void) {
    i2c_mock_set_received_data(0xFF); // Inject incorrect data
    uint8_t received;
    TEST_ASSERT_EQUAL(I2C_ERROR, i2c_receive_byte(0x50, &received));
}
