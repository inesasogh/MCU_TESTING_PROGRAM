#include "uart.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
// Mocked internal variables
static uint32_t mock_baudrate = 9600;
static uint8_t mock_received_byte = 'A';
static int mock_error_state = UART_SUCCESS;

// Mock UART initialization
int uart_init(uint32_t baudrate, uint8_t data_bits, char parity, uint8_t stop_bits) {
    if (baudrate == 0 || data_bits < 5 || data_bits > 8 || (parity != 'N' && parity != 'E' && parity != 'O') || (stop_bits < 1 || stop_bits > 2)) {
        return UART_ERROR;
    }
    mock_baudrate = baudrate;
    return UART_SUCCESS;
}

// Mock setting baud rate
int uart_set_baudrate(uint32_t baudrate) {
    if (baudrate < 1200 || baudrate > 115200) {
        return UART_ERROR;
    }
    mock_baudrate = baudrate;
    return UART_SUCCESS;
}

// Mock sending a single byte
int uart_send_byte(uint8_t byte) {
    (void)byte; // Avoid unused parameter warning
    return UART_SUCCESS;
}

// Mock sending multiple bytes
int uart_send_bytes(const uint8_t *data, uint16_t length) {
    if (data == NULL || length == 0) {
        return UART_ERROR;
    }
    return UART_SUCCESS;
}

// Mock receiving a byte
int uart_receive_byte(uint8_t *byte) {
    if (byte == NULL) {
        return UART_ERROR;
    }
    *byte = mock_received_byte; // Simulate receiving a byte
    return UART_SUCCESS;
}

// Mock error retrieval
int uart_get_error(void) {
    return mock_error_state;
}

// Function to manually set a mock error state (for test purposes)
void set_mock_uart_error(int error_code) {
    mock_error_state = error_code;
}
