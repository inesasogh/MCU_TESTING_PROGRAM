#include <stdint.h>
#include <stdio.h>
#include "spi.h"

// Mock SPI instance
SPI_HandleTypeDef mockSPIHandle;

// Mock SPI Init function
int SPI_Init(SPI_HandleTypeDef* hspi) {
    if (hspi == NULL) {
        return SPI_ERROR;
    }

    hspi->baudRate = 1000000;  // Default baud rate 1 MHz
    hspi->mode = SPI_MODE_0;   // Default mode
    hspi->chipSelect = 0;      // CS deactivated by default
    hspi->errorStatus = SPI_OK;
    return SPI_OK;
}

// Mock function to set SPI mode
int SPI_SetMode(SPI_HandleTypeDef* hspi, uint8_t mode) {
    if (mode > 3) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR;
    }
    hspi->mode = mode;
    return SPI_OK;
}

// Mock function to set SPI clock speed
int SPI_SetClockSpeed(SPI_HandleTypeDef* hspi, uint32_t baudRate) {
    if (baudRate == 0) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR;
    }
    hspi->baudRate = baudRate;
    return SPI_OK;
}

// Mock function for data transmission
int SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size) {
    if (data == NULL || size == 0) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR;
    }

    // Simulating transmission by storing data in txData
    hspi->txData = *data;
    printf("SPI Transmitted: 0x%02X\n", *data);
    return SPI_OK;
}

// Mock function for data reception
int SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size) {
    if (data == NULL || size == 0) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR;
    }

    // Simulating reception by returning mock data
    *data = 0xAA;  // Example received data
    printf("SPI Received: 0x%02X\n", *data);
    return SPI_OK;
}

// Mock function for full-duplex communication (transmit and receive simultaneously)
int SPI_TransmitReceive(SPI_HandleTypeDef* hspi, uint8_t* txData, uint8_t* rxData, uint16_t size) {
    if (txData == NULL || rxData == NULL || size == 0) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR;
    }

    // Simulating transmission and reception
    *rxData = *txData;  // Simulating loopback
    printf("SPI Transmit/Receive: Sent 0x%02X, Received 0x%02X\n", *txData, *rxData);
    return SPI_OK;
}
// Mock function for half-duplex communication (transmit only)
int SPI_TransmitHalfDuplex(SPI_HandleTypeDef* hspi, uint8_t* txData, uint16_t size) {
    if (txData == NULL || size == 0) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR; // Check for invalid input
    }

    // Simulate transmitting data in half-duplex mode (only send, no receive)
    for (int i = 0; i < size; i++) {
        // Simulate transmitting each byte
        hspi->txData = txData[i];
        printf("SPI Half-Duplex Transmit: 0x%02X\n", hspi->txData);
    }

    return SPI_OK; // Successfully transmitted data
}


// Mock function to enable loopback mode (connect MOSI to MISO for testing)
int SPI_LoopbackEnable(SPI_HandleTypeDef* hspi) {
    printf("SPI Loopback enabled\n");
    return SPI_OK;
}

// Mock function to select the chip
int SPI_SelectChip(SPI_HandleTypeDef* hspi, uint8_t chipSelect) {
    hspi->chipSelect = chipSelect;
    printf("SPI Chip Select: %d\n", chipSelect);
    return SPI_OK;
}

// Mock function to deselect the chip
int SPI_DeselectChip(SPI_HandleTypeDef* hspi, uint8_t chipSelect) {
    hspi->chipSelect = 0;
    printf("SPI Chip Deselect: %d\n", chipSelect);
    return SPI_OK;
}

// Mock function to check SPI interrupt
int SPI_InterruptTriggered(SPI_HandleTypeDef* hspi) {
    return 1;  // Simulate that an interrupt was triggered
}

// Mock function to force an error in SPI
int SPI_ForceError(SPI_HandleTypeDef* hspi) {
    hspi->errorStatus = SPI_ERROR;
    printf("SPI Error Forced\n");
    return SPI_ERROR;
}

// Mock function to get SPI error status
int SPI_GetErrorStatus(SPI_HandleTypeDef* hspi) {
    return hspi->errorStatus;
}

// Mock function to enable SPI interrupt (for testing purposes)
int SPI_EnableInterrupt(SPI_HandleTypeDef* hspi) {
    printf("SPI Interrupt Enabled\n");
    return SPI_OK;
}

// Mock function for DMA transfer (simulating transfer via DMA)
int SPI_TransmitReceiveDMA(SPI_HandleTypeDef* hspi, uint8_t* txData, uint8_t* rxData, uint16_t size) {
    if (txData == NULL || rxData == NULL || size == 0) {
        hspi->errorStatus = SPI_ERROR;
        return SPI_ERROR;
    }

    // Simulate DMA transfer
    *rxData = *txData;  // Simulate loopback
    printf("SPI DMA Transmit/Receive: Sent 0x%02X, Received 0x%02X\n", *txData, *rxData);
    return SPI_OK;
}
