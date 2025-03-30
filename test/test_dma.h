#ifndef TEST_DMA
#define TEST_DMA 

#define BUFFER_SIZE 10
void setUpDMA();
void tearDownDMA();
void test_DMA_Init_ShouldInitializeProperly() ;
void test_DMA_MemoryToMemory_ShouldTransferCorrectly() ;
void test_DMA_PeripheralToMemory_ShouldTransferCorrectly();
void test_DMA_MemoryToPeripheral_ShouldTransferCorrectly();
void test_DMA_TransferComplete_ShouldTriggerInterrupt();
void test_DMA_TransferError_ShouldHandleErrors();
void test_DMA_CircularMode_ShouldWorkCorrectly();
void test_DMA_PriorityLevels_ShouldBeConfigurable();
void test_DMA_Interrupt_ShouldBeTriggered();
void test_DMA_MultipleTransfers_ShouldRunSimultaneously();
#endif