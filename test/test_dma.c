#include "unity.h"
#include "dma.h" 
#include "test_dma.h"
#include <string.h>

uint8_t peripheralData[BUFFER_SIZE];
uint8_t memoryBuffer[BUFFER_SIZE];
uint8_t srcBuffer[BUFFER_SIZE];
uint8_t destBuffer[BUFFER_SIZE];

void setUpDMA() {
    memset(srcBuffer, 0xAA, BUFFER_SIZE);
    memset(destBuffer, 0x00, BUFFER_SIZE);
    memset(peripheralData, 0xBB, BUFFER_SIZE);
    memset(memoryBuffer, 0x00, BUFFER_SIZE);
}

void tearDownDMA() {
    memset(destBuffer, 0x00, BUFFER_SIZE);
    memset(memoryBuffer, 0x00, BUFFER_SIZE);
}
void test_DMA_Init_ShouldInitializeProperly() {
    DMA_InitTypeDef dma_config = {0};
    DMA_Init(&dma_config);
    TEST_ASSERT_EQUAL(0, DMA_Init(&dma_config));
}
void test_DMA_MemoryToMemory_ShouldTransferCorrectly() {
    DMA_StartTransfer(srcBuffer, destBuffer, BUFFER_SIZE);
    TEST_ASSERT_EQUAL(0, DMA_StartTransfer(srcBuffer, destBuffer, BUFFER_SIZE));
}
void test_DMA_PeripheralToMemory_ShouldTransferCorrectly() {
    DMA_StartPeripheralToMemoryTransfer(peripheralData, memoryBuffer, BUFFER_SIZE);
    TEST_ASSERT_EQUAL(0, DMA_StartPeripheralToMemoryTransfer(peripheralData, memoryBuffer, BUFFER_SIZE));
}
void test_DMA_MemoryToPeripheral_ShouldTransferCorrectly() {
    DMA_StartMemoryToPeripheralTransfer(memoryBuffer, peripheralData, BUFFER_SIZE);
    TEST_ASSERT_EQUAL(0, DMA_StartMemoryToPeripheralTransfer(memoryBuffer, peripheralData, BUFFER_SIZE));
}
void test_DMA_TransferComplete_ShouldTriggerInterrupt() {
    DMA_GetTransferStatus(1);
    TEST_ASSERT_TRUE(DMA_GetTransferStatus());
}
void test_DMA_TransferError_ShouldHandleErrors() {
    DMA_StartTransfer(NULL, destBuffer, BUFFER_SIZE);
    TEST_ASSERT_EQUAL(-1, DMA_StartTransfer(NULL, destBuffer, BUFFER_SIZE));
}
void test_DMA_CircularMode_ShouldWorkCorrectly() {
    DMA_EnableCircularMode(0);
    TEST_ASSERT_EQUAL(0, DMA_EnableCircularMode());
}
void test_DMA_PriorityLevels_ShouldBeConfigurable() {
    DMA_SetPriority(2);
    TEST_ASSERT_EQUAL(0, DMA_SetPriority(2));
}
void test_DMA_Interrupt_ShouldBeTriggered() {
    DMA_GetInterruptStatus(1);
    TEST_ASSERT_TRUE(DMA_GetInterruptStatus());
}
void test_DMA_MultipleTransfers_ShouldRunSimultaneously() {
    DMA_StartTransfer(peripheralData, memoryBuffer, BUFFER_SIZE);
    DMA_StartTransfer(memoryBuffer, peripheralData, BUFFER_SIZE);
    
    TEST_ASSERT_EQUAL(0, DMA_StartTransfer(peripheralData, memoryBuffer, BUFFER_SIZE));
    TEST_ASSERT_EQUAL(0, DMA_StartTransfer(memoryBuffer, peripheralData, BUFFER_SIZE));
}