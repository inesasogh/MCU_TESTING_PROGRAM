#ifndef DMA_H
#define DMA_H

#include <stdint.h>

typedef struct {
    uint8_t priority;
    uint8_t circularMode;
} DMA_InitTypeDef;

typedef struct {
    DMA_InitTypeDef config;
    uint8_t isInitialized;
    uint8_t transferComplete;
} DMA_HandleTypeDef;

int DMA_Init(DMA_InitTypeDef *config);
int DMA_StartTransfer(uint8_t *src, uint8_t *dest, uint32_t size);
int DMA_StartPeripheralToMemoryTransfer(uint8_t *peripheral, uint8_t *memory, uint32_t size);
int DMA_StartMemoryToPeripheralTransfer(uint8_t *memory, uint8_t *peripheral, uint32_t size);
int DMA_EnableCircularMode();
int DMA_SetPriority(uint8_t priority);
int DMA_GetTransferStatus();
int DMA_GetInterruptStatus();

#endif // DMA_H
