#include "i2c.h"
#include <stdbool.h>
#include <stdio.h>

// Static variables for mocking behavior
static i2c_ack_t mock_ack_response = I2C_ACK;
static i2c_status_t mock_bus_status = I2C_SUCCESS;
static i2c_status_t mock_response_delay = I2C_SUCCESS;
static i2c_config_t mock_i2c_config = {100000, 0, 0};
static i2c_line_status_t mock_line_status = I2C_LINE_OK;
static uint8_t mock_received_data = 0;
static i2c_status_t mock_clock_stretch = I2C_SUCCESS;

void i2c_mock_set_ack_response(i2c_ack_t response) {
    mock_ack_response = response;
}

void i2c_mock_set_bus_status(i2c_status_t status) {
    mock_bus_status = status;
}


i2c_status_t i2c_init_with_config(i2c_config_t *config) {
    if (!config) {
        return I2C_ERROR; // NULL pointer protection
    }

    // Validate clock speed (cannot be 0)
    if (config->clock_speed == 0) {
        return I2C_ERROR;
    }

    // Validate addressing mode (should be either 0 (7-bit) or 1 (10-bit))
    if (config->addressing_mode > 1) {
        return I2C_ERROR;
    }

    // Store configuration
    mock_i2c_config.clock_speed = config->clock_speed;
    mock_i2c_config.addressing_mode = config->addressing_mode;
    mock_i2c_config.general_call_enable = config->general_call_enable;

    printf("[MOCK] I2C Initialized with:\n");
    printf("  - Clock Speed: %u Hz\n", mock_i2c_config.clock_speed);
    printf("  - Addressing Mode: %s-bit\n", mock_i2c_config.addressing_mode ? "10" : "7");
    printf("  - General Call: %s\n", mock_i2c_config.general_call_enable ? "Enabled" : "Disabled");

    return I2C_SUCCESS;
}

void i2c_mock_reset_config(void) {
    mock_i2c_config.clock_speed = 100000;
    mock_i2c_config.addressing_mode = 0;
    mock_i2c_config.general_call_enable = 0;
}

void i2c_mock_set_response_delay(i2c_status_t delay) {
    mock_response_delay = delay;
}

void i2c_mock_set_line_status(i2c_line_status_t status) {
    mock_line_status = status;
}

void i2c_mock_set_received_data(uint8_t data) {
    mock_received_data = data;
}

void i2c_mock_set_clock_stretch(i2c_status_t stretch) {
    mock_clock_stretch = stretch;
}

// Mock I2C API implementation
i2c_status_t i2c_init(void) {
    if (mock_bus_status == I2C_BUSY) return I2C_ERROR;
    return I2C_SUCCESS;
}

i2c_status_t i2c_deinit(void) {
    return I2C_SUCCESS;
}

i2c_status_t i2c_send_byte(uint8_t address, uint8_t data) {
    printf("[MOCK] Sending byte 0x%X to address 0x%X\n", data, address);
    
    if (mock_bus_status == I2C_BUSY) return I2C_ERROR;
    if (mock_response_delay == I2C_TIMEOUT) return I2C_TIMEOUT;
    if (mock_ack_response == I2C_NACK) return I2C_ERROR;
    if (mock_line_status != I2C_LINE_OK) return I2C_ERROR;
    
    return I2C_SUCCESS;
}

i2c_status_t i2c_send_data(uint8_t address, uint8_t *data, uint8_t length) {
    printf("[MOCK] Sending %d bytes to address 0x%X\n", length, address);
    
    if (mock_bus_status == I2C_BUSY) return I2C_ERROR;
    if (mock_response_delay == I2C_TIMEOUT) return I2C_TIMEOUT;
    if (mock_ack_response == I2C_NACK) return I2C_ERROR;
    if (mock_line_status != I2C_LINE_OK) return I2C_ERROR;
    
    return I2C_SUCCESS;
}

i2c_status_t i2c_receive_byte(uint8_t address, uint8_t *data) {
    printf("[MOCK] Receiving byte from address 0x%X\n", address);
    
    if (mock_bus_status == I2C_BUSY) return I2C_ERROR;
    if (mock_response_delay == I2C_TIMEOUT) return I2C_TIMEOUT;
    if (mock_line_status != I2C_LINE_OK) return I2C_ERROR;

    *data = mock_received_data;
    return I2C_SUCCESS;
}

i2c_status_t i2c_start(uint8_t address) {
    printf("[MOCK] I2C Start condition for address 0x%X\n", address);
    
    if (mock_bus_status == I2C_BUSY) return I2C_ERROR;
    return I2C_SUCCESS;
}

i2c_status_t i2c_restart(uint8_t address) {
    printf("[MOCK] I2C Repeated Start condition for address 0x%X\n", address);
    
    if (mock_bus_status == I2C_BUSY) return I2C_ERROR;
    return I2C_SUCCESS;
}