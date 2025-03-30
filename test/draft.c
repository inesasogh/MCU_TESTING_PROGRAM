
/*
//static char mock_uart_buffer[100] = {0};

// Մոքի ֆունկցիա, որը կփոխարինի hardware-ի իրական ֆունկցիան
/*void UART_Write(const char* data) {
    strncpy(mock_uart_buffer, data, sizeof(mock_uart_buffer) - 1);
}

// Թեստ 1․ ստուգում ենք՝ արդյոք ճիշտ տվյալն է փոխանցվում
void test_UART_Send_Should_Transmit_Correct_Data(void) {
    UART_Send("Hello, UART!");
    TEST_ASSERT_EQUAL_STRING("Hello, UART!", mock_uart_buffer);
}

// Թեստ 2․ դատարկ կամ NULL տվյալը չպետք է փոխի buffer-ը
void test_UART_Send_Should_Not_Send_Empty_Data(void) {
    strcpy(mock_uart_buffer, "PreviousData");  // Նախորդ արժեքը
    UART_Send("");  // Ուղարկում ենք դատարկ string
    TEST_ASSERT_EQUAL_STRING("PreviousData", mock_uart_buffer);
}


// Թեստ 1․ երբ կոճակը սեղմված է, ֆունկցիան պետք է վերադարձնի 1
void test_Button_Should_Be_Detected_As_Pressed(void) {
    mock_gpio_state = 1;  // Սիմուլյացիա՝ կոճակը սեղմված է
    TEST_ASSERT_EQUAL(1, is_button_pressed(5));
}

// Թեստ 2․ երբ կոճակը սեղմված չէ, ֆունկցիան պետք է վերադարձնի 0
void test_Button_Should_Be_Detected_As_Not_Pressed(void) {
    mock_gpio_state = 0;  // Սիմուլյացիա՝ կոճակը ազատ է
    TEST_ASSERT_EQUAL(0, is_button_pressed(5));
}
// Պահպանում ենք ADC-ի mock արժեքը
static int mock_adc_value = 0;

// Մոքի ֆունկցիա, որը կփոխարինի hardware-ի իրական ADC ֆունկցիան
int ADC_Read(int channel) {
    return mock_adc_value;  
}

// Թեստ 1․ ստուգում ենք 0 ADC արժեքը
void test_ADC_ReadVoltage_Should_Return_Zero_For_ADC_Zero(void) {
    mock_adc_value = 0;
    TEST_ASSERT_EQUAL_FLOAT(0.0, ADC_ReadVoltage(1));
}

// Թեստ 2․ ADC առավելագույն արժեքը պետք է վերադարձնի 3.3V
void test_ADC_ReadVoltage_Should_Return_Max_Voltage(void) {
    mock_adc_value = 4095;
    TEST_ASSERT_EQUAL_FLOAT(3.3, ADC_ReadVoltage(1));
}

// Թեստ 3․ ADC 2048-ը պետք է մոտավորապես վերադարձնի 1.65V
void test_ADC_ReadVoltage_Should_Return_Half_Voltage(void) {
    mock_adc_value = 2048;
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.65, ADC_ReadVoltage(1));
}

// Թեստ 4․ բացասական ADC արժեքը պետք է վերադարձնի -1
void test_ADC_ReadVoltage_Should_Return_Negative_One_For_Invalid_Low_Value(void) {
    mock_adc_value = -5;
    TEST_ASSERT_EQUAL_FLOAT(-1, ADC_ReadVoltage(1));
}

// Թեստ 5․ ADC 5000-ը պետք է վերադարձնի -1, քանի որ այն գերազանցում է 4095-ը
void test_ADC_ReadVoltage_Should_Return_Negative_One_For_Invalid_High_Value(void) {
    mock_adc_value = 5000;
    TEST_ASSERT_EQUAL_FLOAT(-1, ADC_ReadVoltage(1));
}

// Unity Test Runner

*/
// Մոքի ֆունկցիա, որը կփոխարինի hardware-ի իրական ֆունկցիան
/*void UART_Write(const char* data);
// Թեստ 1․ ստուգում ենք՝ արդյոք ճիշտ տվյալն է փոխանցվում
void test_UART_Send_Should_Transmit_Correct_Data(void) ;

// Թեստ 2․ դատարկ կամ NULL տվյալը չպետք է փոխի buffer-ը
void test_UART_Send_Should_Not_Send_Empty_Data(void) ;
// Մոքի ֆունկցիա, որը կփոխարինի hardware-ի իրական ֆունկցիան

// Թեստ 1․ երբ կոճակը սեղմված է, ֆունկցիան պետք է վերադարձնի 1
void test_Button_Should_Be_Detected_As_Pressed(void) ;
// Թեստ 2․ երբ կոճակը սեղմված չէ, ֆունկցիան պետք է վերադարձնի 0
void test_Button_Should_Be_Detected_As_Not_Pressed(void);
// Պահպանում ենք ADC-ի mock արժեքը
static int mock_adc_value = 0;

// Մոքի ֆունկցիա, որը կփոխարինի hardware-ի իրական ADC ֆունկցիան
int ADC_Read(int channel);

// Թեստ 1․ ստուգում ենք 0 ADC արժեքը
void test_ADC_ReadVoltage_Should_Return_Zero_For_ADC_Zero(void);

// Թեստ 2․ ADC առավելագույն արժեքը պետք է վերադարձնի 3.3V
void test_ADC_ReadVoltage_Should_Return_Max_Voltage(void) ;
// Թեստ 3․ ADC 2048-ը պետք է մոտավորապես վերադարձնի 1.65V
void test_ADC_ReadVoltage_Should_Return_Half_Voltage(void) ;

// Թեստ 4․ բացասական ADC արժեքը պետք է վերադարձնի -1
void test_ADC_ReadVoltage_Should_Return_Negative_One_For_Invalid_Low_Value(void) ;

// Թեստ 5․ ADC 5000-ը պետք է վերադարձնի -1, քանի որ այն գերազանցում է 4095-ը
void test_ADC_ReadVoltage_Should_Return_Negative_One_For_Invalid_High_Value(void) ;
*/
