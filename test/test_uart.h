#ifndef TEST_UART
#define TEST_UART
void setUpUART(void) ;
void tearDownUART(void); 
void test_uart_initialization(void);
void test_uart_set_baudrate(void);
void test_uart_send_byte(void) ;
void test_uart_send_multiple_bytes(void);
void test_uart_receive_byte(void);
void test_uart_parity_error(void);
void test_uart_frame_error(void);
#endif