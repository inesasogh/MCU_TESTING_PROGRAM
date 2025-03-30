#include "dma.h"
#include <string.h>  


static DMA_HandleTypeDef dmaHandle;
static DMA_HandleTypeDef dmaHandle;
static volatile int dma_transfer_complete = 0;
static volatile int dma_transfer_error = 0;

int DMA_Init(DMA_InitTypeDef *config) {
    if (config == NULL) {
        return -1;
    }
    memcpy(&dmaHandle.config, config, sizeof(DMA_InitTypeDef));
    dmaHandle.isInitialized = 1;
    
    return 0;
}

int DMA_StartTransfer(uint8_t *src, uint8_t *dest, uint32_t size) {
    if (!dmaHandle.isInitialized || src == NULL || dest == NULL || size == 0) {
        return -1;
    }
    memcpy(dest, src, size);
    dmaHandle.transferComplete = 1;
    
    return 0;
}


int DMA_StartPeripheralToMemoryTransfer(uint8_t *peripheral, uint8_t *memory, uint32_t size) {
    if (!dmaHandle.isInitialized || peripheral == NULL || memory == NULL || size == 0) {
        return -1;
    }

 
    memcpy(memory, peripheral, size);

    dmaHandle.transferComplete = 1;

    return 0;
}


int DMA_StartMemoryToPeripheralTransfer(uint8_t *memory, uint8_t *peripheral, uint32_t size) {
    if (!dmaHandle.isInitialized || memory == NULL || peripheral == NULL || size == 0) {
        return -1;
    }

    memcpy(peripheral, memory, size);
    dmaHandle.transferComplete = 1;

    return 0;
}

int DMA_EnableCircularMode() {
    if (!dmaHandle.isInitialized) {
        return -1;
    }
    
    dmaHandle.config.circularMode = 1;
    return 0;
}
int DMA_SetPriority(uint8_t priority) {
    if (!dmaHandle.isInitialized || priority > 3) { 
        return -1;
    }

    dmaHandle.config.priority = priority;
    return 0;
}

int DMA_GetTransferStatus() {
    return dmaHandle.transferComplete;
}

int DMA_GetInterruptStatus() {
    return dmaHandle.transferComplete; 
}
