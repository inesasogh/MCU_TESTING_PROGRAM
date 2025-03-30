#include "gpio.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
// Mock Arrays (Replace with actual registers in real hardware)
uint8_t mock_gpio_mode[256] = {0};  // Pin mode (Input/Output)
uint8_t mock_gpio_state[256] = {0}; // Pin state (High/Low)
uint8_t mock_gpio_pullup[256] = {0};  // Pull-up resistor
uint8_t mock_gpio_pulldown[256] = {0};  // Pull-down resistor
// Interrupt-related mock arrays

gpio_callback_t gpio_interrupt_callbacks[256] = {0};
uint8_t gpio_interrupt_modes[256] = {0};
uint8_t gpio_previous_state[256] = {0};

void GPIO_Init(uint8_t pin, uint8_t mode) {
    if (pin >= 256) return;
    mock_gpio_mode[pin] = mode;
}
int GPIO_Write(uint8_t pin, uint8_t value) {
    if (pin >= 256 || mock_gpio_mode[pin] != GPIO_MODE_OUTPUT) {
        return GPIO_ERROR;  // Return error code instead of void
    }
    mock_gpio_state[pin] = value;
    return GPIO_SUCCESS;  // Return success code
}


int GPIO_Read(uint8_t pin) {
    if (pin >= 256 || mock_gpio_mode[pin] != GPIO_MODE_OUTPUT) return GPIO_ERROR;
    return mock_gpio_state[pin];
}

void GPIO_Toggle(uint8_t pin) {
    if (pin >= 256 || mock_gpio_mode[pin] != GPIO_MODE_OUTPUT) return;
    mock_gpio_state[pin] = !mock_gpio_state[pin];
}

void GPIO_SetPullUp(uint8_t pin, uint8_t enable) {
    if (pin >= 256) return;
    mock_gpio_pullup[pin] = enable;
}

void GPIO_SetPullDown(uint8_t pin, uint8_t enable) {
    if (pin >= 256) return;
    mock_gpio_pulldown[pin] = enable;
}

int GPIO_Read_Debounced(uint8_t pin) {
    int stable_value = mock_gpio_state[pin];
    delay_ms(1);
    if (mock_gpio_state[pin] == stable_value) {
        return stable_value;
    }
    return GPIO_LOW;  // If unstable, return LOW
}

uint32_t get_current_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);  // Convert to milliseconds
}
void delay_ms(uint32_t ms) {
    usleep(ms * 1000);  // Convert ms to microseconds
}
void GPIO_SetInterrupt(uint8_t pin, uint8_t mode, gpio_callback_t callback) {
    if (pin >= 256) return;
    gpio_interrupt_modes[pin] = mode;
    gpio_interrupt_callbacks[pin] = callback;
    gpio_previous_state[pin] = mock_gpio_state[pin];
}

void GPIO_HandleInterrupt(uint8_t pin) {
    if (pin >= 256 || gpio_interrupt_callbacks[pin] == NULL) return;
    
    uint8_t prev_state = gpio_previous_state[pin];
    uint8_t curr_state = mock_gpio_state[pin];
    gpio_callback_t callback = gpio_interrupt_callbacks[pin];

    if ((gpio_interrupt_modes[pin] == GPIO_INTERRUPT_RISING && prev_state == 0 && curr_state == 1) ||
        (gpio_interrupt_modes[pin] == GPIO_INTERRUPT_FALLING && prev_state == 1 && curr_state == 0) ||
        (gpio_interrupt_modes[pin] == GPIO_INTERRUPT_BOTH && prev_state != curr_state)) {
        callback();
    }
    gpio_previous_state[pin] = curr_state;
}
