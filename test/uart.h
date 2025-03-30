#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_SUCCESS 0
#define UART_ERROR   -1
#define UART_PARITY_ERROR -2
#define UART_FRAME_ERROR -3

// Mock function prototypes
int uart_init(uint32_t baudrate, uint8_t data_bits, char parity, uint8_t stop_bits);
int uart_set_baudrate(uint32_t baudrate);
int uart_send_byte(uint8_t byte);
int uart_send_bytes(const uint8_t *data, uint16_t length);
int uart_receive_byte(uint8_t *byte);
int uart_get_error(void);

#endif 
