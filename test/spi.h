#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>

// SPI Modes (Mode 0 to Mode 3)
#define SPI_MODE_0 0
#define SPI_MODE_1 1
#define SPI_MODE_2 2
#define SPI_MODE_3 3

// SPI Error and OK statuses
#define SPI_OK 0
#define SPI_ERROR -1

// SPI Handle Definition (Mocked version)
typedef struct {
    uint32_t baudRate;   // SPI baud rate
    uint8_t mode;        // SPI mode (0 to 3)
    uint8_t chipSelect;  // CS pin state
    uint8_t rxData;      // Data received from SPI
    uint8_t txData;      // Data to send via SPI
    int errorStatus;     // Error flag
} SPI_HandleTypeDef;

// Function Prototypes
int SPI_Init(SPI_HandleTypeDef* hspi); // Initialize SPI
int SPI_SetMode(SPI_HandleTypeDef* hspi, uint8_t mode); // Set SPI mode
int SPI_SetClockSpeed(SPI_HandleTypeDef* hspi, uint32_t baudRate); // Set SPI clock speed
int SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size); // Transmit data
int SPI_TransmitHalfDuplex(SPI_HandleTypeDef* hspi, uint8_t* txData, uint16_t size);
int SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size); // Receive data
int SPI_TransmitReceive(SPI_HandleTypeDef* hspi, uint8_t* txData, uint8_t* rxData, uint16_t size); // Full-duplex communication
int SPI_LoopbackEnable(SPI_HandleTypeDef* hspi); // Enable loopback mode
int SPI_SelectChip(SPI_HandleTypeDef* hspi, uint8_t chipSelect); // Select chip
int SPI_DeselectChip(SPI_HandleTypeDef* hspi, uint8_t chipSelect); // Deselect chip
int SPI_InterruptTriggered(SPI_HandleTypeDef* hspi); // Check if SPI interrupt was triggered
int SPI_ForceError(SPI_HandleTypeDef* hspi); // Force SPI error
int SPI_GetErrorStatus(SPI_HandleTypeDef* hspi); // Get SPI error status
int SPI_EnableInterrupt(SPI_HandleTypeDef* hspi); // Enable SPI interrupt
int SPI_TransmitReceiveDMA(SPI_HandleTypeDef* hspi, uint8_t* txData, uint8_t* rxData, uint16_t size); // DMA transfer

#endif // SPI_DRIVER_H
