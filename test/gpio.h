#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <time.h>
// GPIO Modes
#define GPIO_MODE_INPUT  0
#define GPIO_MODE_OUTPUT 1

typedef enum {
    GPIO_INTERRUPT_NONE,
    GPIO_INTERRUPT_RISING,
    GPIO_INTERRUPT_FALLING,
    GPIO_INTERRUPT_BOTH
} gpio_interrupt_mode_t;

// GPIO States
#define GPIO_LOW  0
#define GPIO_HIGH 1

// Error Codes
#define GPIO_SUCCESS 1
#define GPIO_ERROR   -1

//embedded programming to enable certain features like pull-up or pull-down resistors.
#define ENABLE 1
#define DISABLE 0

// GPIO Functions

void GPIO_Init(uint8_t pin, uint8_t mode);
int GPIO_Write(uint8_t pin, uint8_t value);
int  GPIO_Read(uint8_t pin);
void GPIO_Toggle(uint8_t pin);
void GPIO_SetPullUp(uint8_t pin, uint8_t enable);
void GPIO_SetPullDown(uint8_t pin, uint8_t enable);
int GPIO_Read_Debounced(uint8_t pin);
uint32_t get_current_time_ms(void);
void delay_ms(uint32_t ms);
typedef void (*gpio_callback_t)(void);
void GPIO_SetInterrupt(uint8_t pin, uint8_t mode, gpio_callback_t callback);
void GPIO_HandleInterrupt(uint8_t pin);
// Expose mock variables for testing

extern uint8_t mock_gpio_mode[256];
extern uint8_t mock_gpio_state[256];
extern uint8_t mock_gpio_pullup[256]; 
extern uint8_t mock_gpio_pulldown[256] ;
extern gpio_callback_t gpio_interrupt_callbacks[256];
extern uint8_t gpio_interrupt_modes[256];
extern uint8_t gpio_previous_state[256];

#endif // GPIO_H
