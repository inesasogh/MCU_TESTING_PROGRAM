#include "unity.h"
#include "test_uart.h"
#include "uart.h"

void setUp(void) {
    // This runs before each test
}

void tearDown(void) {
    // This runs after each test
}

// Test: UART Initialization
void test_uart_initialization(void) {
    TEST_ASSERT_EQUAL(0, uart_init(9600, 8, 'N', 1)); // Expect success
    TEST_ASSERT_NOT_EQUAL(0, uart_init(0, 8, 'N', 1)); // Invalid baud rate should fail
}

// Test: UART Baud Rate Setting
void test_uart_set_baudrate(void) {
    TEST_ASSERT_EQUAL(0, uart_set_baudrate(115200)); // Valid baud rate
    TEST_ASSERT_NOT_EQUAL(0, uart_set_baudrate(9999999)); // Invalid baud rate
}

// Test: UART Transmission
void test_uart_send_byte(void) {
    TEST_ASSERT_EQUAL(0, uart_send_byte('A'));
}

void test_uart_send_multiple_bytes(void) {
    uint8_t data[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    TEST_ASSERT_EQUAL(0, uart_send_bytes(data, 5));
}

// Test: UART Reception
void test_uart_receive_byte(void) {
    uint8_t received;
    TEST_ASSERT_EQUAL(0, uart_receive_byte(&received));
    TEST_ASSERT_EQUAL('B', received);
}

// Test: UART Error Handling
void test_uart_parity_error(void) {
    set_mock_uart_error(UART_PARITY_ERROR);
    TEST_ASSERT_EQUAL(UART_PARITY_ERROR, uart_get_error());
}

void test_uart_frame_error(void) {
    set_mock_uart_error(UART_FRAME_ERROR);
    TEST_ASSERT_EQUAL(UART_FRAME_ERROR, uart_get_error());
}
