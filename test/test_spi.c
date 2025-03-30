#include "unity.h"
#include "test_spi.h"
#include "spi.h"

// Mock or real SPI instance
SPI_HandleTypeDef spiHandle;

void setUpSPI(void) {
    // Initialize SPI before each test
    SPI_Init(&spiHandle);
}

void tearDownSPI(void) {
    // Cleanup if necessary
}

// Test Initialization
void test_SPI_Initialization(void) {
    TEST_ASSERT_EQUAL(SPI_OK, SPI_Init(&spiHandle));
}

// Test Mode Configuration
void test_SPI_Mode_Config(void) {
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SetMode(&spiHandle, SPI_MODE_0));
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SetMode(&spiHandle, SPI_MODE_1));
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SetMode(&spiHandle, SPI_MODE_2));
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SetMode(&spiHandle, SPI_MODE_3));
}

// Test Clock Speed
void test_SPI_Clock_Speed(void) {
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SetClockSpeed(&spiHandle, 1000000));  // 1 MHz
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SetClockSpeed(&spiHandle, 5000000));  // 5 MHz
}

// Test Data Transmission
void test_SPI_Data_Transmission(void) {
    uint8_t txData = 0xA5; 
    uint8_t rxData = 0x00;

    TEST_ASSERT_EQUAL(SPI_OK, SPI_Transmit(&spiHandle, &txData, 1));
}

// Test Data Reception
void test_SPI_Data_Reception(void) {
    uint8_t rxData = 0x00;
    TEST_ASSERT_EQUAL(SPI_OK, SPI_Receive(&spiHandle, &rxData, 1));
}

// Loopback Test (MOSI connected to MISO)
void test_SPI_Loopback(void) {
    uint8_t txData = 0x55;
    uint8_t rxData = 0x00;

    SPI_LoopbackEnable(&spiHandle);
    SPI_Transmit(&spiHandle, &txData, 1);
    SPI_Receive(&spiHandle, &rxData, 1);

    TEST_ASSERT_EQUAL_UINT8(txData, rxData);
}

// Test Chip Select (CS) Behavior
void test_SPI_Chip_Select(void) {
    TEST_ASSERT_EQUAL(SPI_OK, SPI_SelectChip(&spiHandle, 1));
    TEST_ASSERT_EQUAL(SPI_OK, SPI_DeselectChip(&spiHandle, 1));
}

// Full-Duplex Communication Test
void test_SPI_Full_Duplex(void) {
    uint8_t txData = 0x3C;
    uint8_t rxData = 0x00;

    TEST_ASSERT_EQUAL(SPI_OK, SPI_TransmitReceive(&spiHandle, &txData, &rxData, 1));
}

// Half-Duplex Communication Test
void test_SPI_Half_Duplex(void) {
    uint8_t txData = 0x7F;

    TEST_ASSERT_EQUAL(SPI_OK, SPI_TransmitHalfDuplex(&spiHandle, &txData, 1));
}

// Interrupt Handling Test
void test_SPI_Interrupt(void) {
    SPI_EnableInterrupt(&spiHandle);
    TEST_ASSERT_TRUE(SPI_InterruptTriggered(&spiHandle));
}

// Error Handling Test
void test_SPI_Error_Handling(void) {
    SPI_ForceError(&spiHandle);
    TEST_ASSERT_EQUAL(SPI_ERROR, SPI_GetErrorStatus(&spiHandle));
}

// DMA Integration Test
void test_SPI_DMA_Transfer(void) {
    uint8_t txData[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    uint8_t rxData[10] = {0};

    TEST_ASSERT_EQUAL(SPI_OK, SPI_TransmitReceiveDMA(&spiHandle, txData, rxData, 10));
}