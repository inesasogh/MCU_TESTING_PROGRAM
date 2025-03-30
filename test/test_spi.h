#ifndef TEST_SPI
#define TEST_SPI
void setUpSPI(void);
void tearDownSPI(void);
void test_SPI_Initialization(void);
void test_SPI_Mode_Config(void);
void test_SPI_Clock_Speed(void);
void test_SPI_Data_Transmission(void);
void test_SPI_Data_Reception(void);
void test_SPI_Loopback(void);
void test_SPI_Chip_Select(void);
void test_SPI_Full_Duplex(void);
void test_SPI_Half_Duplex(void);
void test_SPI_Interrupt(void);
void test_SPI_Error_Handling(void);
void test_SPI_DMA_Transfer(void);
#endif