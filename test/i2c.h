#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C_STRETCH_SHORT  10   // Short stretch (in milliseconds)
#define I2C_STRETCH_LONG   500 //long
// Define I2C response types
typedef enum {
    I2C_SUCCESS,
    I2C_ERROR,
    I2C_TIMEOUT,
    I2C_ARBITRATION_LOSS,
    I2C_BUSY
} i2c_status_t;

// I2C line conditions
typedef enum {
    I2C_LINE_OK,
    I2C_SDA_STUCK_LOW,
    I2C_SCL_STUCK_LOW
} i2c_line_status_t;

typedef struct {
    uint32_t clock_speed;  // I2C clock speed in Hz (e.g., 100000 for 100kHz)
    uint8_t addressing_mode; // 0 = 7-bit, 1 = 10-bit
    uint8_t general_call_enable; // 0 = disabled, 1 = enabled
} i2c_config_t;

// I2C response for ACK/NACK
typedef enum {
    I2C_ACK,
    I2C_NACK
} i2c_ack_t;

// Mock setup functions
void i2c_mock_set_ack_response(i2c_ack_t response);
void i2c_mock_set_bus_status(i2c_status_t status);
void i2c_mock_set_response_delay(i2c_status_t delay);
void i2c_mock_set_line_status(i2c_line_status_t status);
void i2c_mock_set_received_data(uint8_t data);
void i2c_mock_set_clock_stretch(i2c_status_t stretch);

// I2C API (Mocked)
i2c_status_t i2c_init(void);
i2c_status_t i2c_deinit(void);
i2c_status_t i2c_init_with_config(i2c_config_t *config);
void i2c_mock_reset_config(void);
i2c_status_t i2c_send_byte(uint8_t address, uint8_t data);
i2c_status_t i2c_send_data(uint8_t address, uint8_t *data, uint8_t length);
i2c_status_t i2c_receive_byte(uint8_t address, uint8_t *data);
i2c_status_t i2c_start(uint8_t address);
i2c_status_t i2c_restart(uint8_t address);

#endif // MOCK_I2C_H
