import tkinter as tk
from tkinter import ttk
import subprocess
import csv
from datetime import datetime
import time
import threading
peripherals = {
    "GPIO":["test_GPIO_Init_Should_Set_Pin_Mode","test_GPIO_Write_Should_Set_Pin_High","test_GPIO_Write_Should_Set_Pin_Low","test_GPIO_Read_Should_Return_Correct_Value","test_GPIO_Write_Should_Handle_Invalid_Pin","test_GPIO_Write_Should_Fail_If_Pin_Not_Initialized","test_GPIO_SetPullUp_Should_Enable_PullUp","test_GPIO_SetPullDown_Should_Enable_PullDown","test_GPIO_Toggle_Should_Work_Fast","test_GPIO_Read_Should_Debounce_Noise","test_GPIO_Interrupt_RisingEdge_Should_Trigger_Callback","test_GPIO_Interrupt_FallingEdge_Should_Trigger_Callback","test_GPIO_Interrupt_Debounce_Should_Filter_Noise","test_GPIO_Multiple_Pins_Should_Work_Independently","test_GPIO_Input_Controls_Output"],
    "TIMER":["test_timer_initialization","test_timer_enable_disable","test_timer_counting","test_timer_overflow","test_timer_interrupt_triggered","test_counter_external_signal","test_pwm_signal","test_invalid_prescaler_setting","test_timer_prescaler","test_switch_clock_source","test_dynamic_prescaler_update","test_timer_capture_event","test_timer_compare_match_interrupt","test_dynamic_compare_value_update","test_timer_one_pulse_mode","test_multiple_timers_independent","test_timer_chaining","test_watchdog_timer_reset","test_watchdog_timer_feeding","test_timer_low_power_mode","test_timer_interrupt_wakes_up","test_rapid_enable_disable","test_high_frequency_interrupts"],
    "ANALOG TO DIGITAL CONVENTER":["test_adc_initialization","test_adc_single_conversion","test_adc_multiple_conversions","test_adc_min_value","test_adc_max_value","test_adc_mid_value","test_adc_invalid_channel","test_adc_power_on_default","test_adc_sampling_time","test_adc_voltage_scaling","test_adc_noise_stability","test_adc_conversion_time","test_adc_interrupt_trigger","test_adc_interrupt_value_handling","test_adc_multiple_interrupts","test_adc_unexpected_interrupt"],
    "DIGITAL TO ANALOG CONVENTER":["test_DAC_Initialization","test_DAC_BoundaryValues","test_DAC_MidScale","test_DAC_Resolution","test_DAC_SettlingTime","test_DAC_DefaultValue","test_DAC_No_Glitch","test_DAC_IncrementalSteps","test_DAC_NoiseHandling","test_DAC_Stability","test_DAC_RapidUpdates","test_DAC_NonLinearity","test_DAC_FullRangeSweep"],
    "WATCHDOG TIMER":["test_WDT_initialization","test_WDT_enable","test_WDT_timeout","test_WDT_feed","test_WDT_disable","test_WDT_configure_timeout","test_WDT_interrupt_mode","test_WDT_reset_cause"],
    "DIRECT MEMORY ACCESS":["test_DMA_Init_ShouldInitializeProperly","test_DMA_MemoryToMemory_ShouldTransferCorrectly","test_DMA_PeripheralToMemory_ShouldTransferCorrectly","test_DMA_MemoryToPeripheral_ShouldTransferCorrectly","test_DMA_TransferComplete_ShouldTriggerInterrupt","test_DMA_TransferError_ShouldHandleErrors","test_DMA_CircularMode_ShouldWorkCorrectly","test_DMA_PriorityLevels_ShouldBeConfigurable","test_DMA_Interrupt_ShouldBeTriggered","test_DMA_MultipleTransfers_ShouldRunSimultaneously",],
    "REAL-TIME CLOCK":["test_rtc_initialization","test_rtc_set_get_time","test_rtc_time_progression","test_rtc_alarm","test_rtc_leap_year","test_rtc_invalid_date","test_rtc_backup_power"],
    "UART":["test_uart_initialization","test_uart_set_baudrate","test_uart_send_byte","test_uart_send_multiple_bytes","test_uart_receive_byte","test_uart_parity_error","test_uart_frame_error"],
    "SPI": ["test_SPI_Initialization", "test_SPI_Mode_Config", "test_SPI_Clock_Speed)","test_SPI_Data_Transmission","test_SPI_Data_Reception","test_SPI_Loopback","test_SPI_Chip_Select","test_SPI_Full_Duplex","test_SPI_Half_Duplex","test_SPI_Interrupt","test_SPI_Error_Handling","test_SPI_DMA_Transfer"],
    "I2C": ["test_I2C_Init_Should_Succeed_With_Valid_Configuration", "test_I2C_Init_Should_Fail_With_Invalid_Configuration", "test_I2C_SendByte_Should_Succeed","test_I2C_SendByte_Should_Fail_On_NACK","test_I2C_SendData_Should_Succeed","test_I2C_ReceiveByte_Should_Succeed","test_I2C_BusBusy_Should_Return_Error","test_I2C_RepeatedStart_Should_Succeed","test_I2C_ArbitrationLoss_Should_Detect_Error","test_I2C_Timeout_Should_Return_Error","test_I2C_StuckSDA_Should_Detect_And_Recover","test_I2C_StuckSCL_Should_Detect_And_Recover","test_I2C_LowestAddress_Should_Succeed","test_I2C_HighestAddress_Should_Succeed","test_I2C_ClockStretching_Should_Wait_Properly","test_I2C_ExcessiveClockStretching_Should_Timeout","test_I2C_CorruptedData_Should_Fail"]
}
user_friendly_names = {
    # GPIO
    "test_GPIO_Init_Should_Set_Pin_Mode": "Set Pin Mode During Initialization",
    "test_GPIO_Write_Should_Set_Pin_High": "Write High Value to GPIO Pin",
    "test_GPIO_Write_Should_Set_Pin_Low": "Write Low Value to GPIO Pin",
    "test_GPIO_Read_Should_Return_Correct_Value": "Read GPIO Value Correctly",
    "test_GPIO_Write_Should_Handle_Invalid_Pin": "Handle Invalid GPIO Pin",
    "test_GPIO_Write_Should_Fail_If_Pin_Not_Initialized": "Fail If GPIO Pin Not Initialized",
    "test_GPIO_SetPullUp_Should_Enable_PullUp": "Enable Pull-Up Resistor",
    "test_GPIO_SetPullDown_Should_Enable_PullDown": "Enable Pull-Down Resistor",
    "test_GPIO_Toggle_Should_Work_Fast": "Fast GPIO Pin Toggling",
    "test_GPIO_Read_Should_Debounce_Noise": "Debounce GPIO Read Noise",
    "test_GPIO_Interrupt_RisingEdge_Should_Trigger_Callback": "Trigger Interrupt on Rising Edge",
    "test_GPIO_Interrupt_FallingEdge_Should_Trigger_Callback": "Trigger Interrupt on Falling Edge",
    "test_GPIO_Interrupt_Debounce_Should_Filter_Noise": "Filter Interrupt Noise with Debounce",
    "test_GPIO_Multiple_Pins_Should_Work_Independently": "Multiple GPIO Pins Work Independently",
    "test_GPIO_Input_Controls_Output": "GPIO Input Controls Output Logic",

    # TIMER
    "test_timer_initialization": "Initialize Timer",
    "test_timer_enable_disable": "Enable/Disable Timer",
    "test_timer_counting": "Timer Counting",
    "test_timer_overflow": "Timer Overflow Detection",
    "test_timer_interrupt_triggered": "Timer Interrupt Trigger",
    "test_counter_external_signal": "Counter with External Signal",
    "test_pwm_signal": "PWM Signal Generation",
    "test_invalid_prescaler_setting": "Invalid Prescaler Handling",
    "test_timer_prescaler": "Configure Timer Prescaler",
    "test_switch_clock_source": "Switch Clock Source",
    "test_dynamic_prescaler_update": "Dynamic Prescaler Update",
    "test_timer_capture_event": "Timer Capture Event",
    "test_timer_compare_match_interrupt": "Compare Match Interrupt",
    "test_dynamic_compare_value_update": "Update Compare Value Dynamically",
    "test_timer_one_pulse_mode": "One Pulse Mode",
    "test_multiple_timers_independent": "Multiple Timers Independent",
    "test_timer_chaining": "Timer Chaining",
    "test_watchdog_timer_reset": "Watchdog Timer Reset",
    "test_watchdog_timer_feeding": "Feed Watchdog Timer",
    "test_timer_low_power_mode": "Timer in Low Power Mode",
    "test_timer_interrupt_wakes_up": "Timer Interrupt Wake-Up",
    "test_rapid_enable_disable": "Rapid Enable/Disable",
    "test_high_frequency_interrupts": "High-Frequency Interrupts",

    # ADC
    "test_adc_initialization": "Initialize ADC",
    "test_adc_single_conversion": "Single ADC Conversion",
    "test_adc_multiple_conversions": "Multiple ADC Conversions",
    "test_adc_min_value": "Minimum ADC Value",
    "test_adc_max_value": "Maximum ADC Value",
    "test_adc_mid_value": "Mid-Range ADC Value",
    "test_adc_invalid_channel": "Invalid ADC Channel",
    "test_adc_power_on_default": "ADC Default After Power-On",
    "test_adc_sampling_time": "ADC Sampling Time",
    "test_adc_voltage_scaling": "Voltage Scaling on ADC",
    "test_adc_noise_stability": "Noise Stability of ADC",
    "test_adc_conversion_time": "ADC Conversion Time",
    "test_adc_interrupt_trigger": "Trigger ADC Interrupt",
    "test_adc_interrupt_value_handling": "Handle ADC Interrupt Value",
    "test_adc_multiple_interrupts": "Multiple ADC Interrupts",
    "test_adc_unexpected_interrupt": "Unexpected ADC Interrupt",

    # DAC
    "test_DAC_Initialization": "Initialize DAC",
    "test_DAC_BoundaryValues": "DAC Boundary Values",
    "test_DAC_MidScale": "DAC Mid-Scale Output",
    "test_DAC_Resolution": "DAC Resolution Test",
    "test_DAC_SettlingTime": "DAC Settling Time",
    "test_DAC_DefaultValue": "DAC Default Value",
    "test_DAC_No_Glitch": "Glitch-Free DAC Output",
    "test_DAC_IncrementalSteps": "DAC Incremental Steps",
    "test_DAC_NoiseHandling": "DAC Noise Handling",
    "test_DAC_Stability": "DAC Output Stability",
    "test_DAC_RapidUpdates": "Rapid DAC Updates",
    "test_DAC_NonLinearity": "DAC Non-Linearity",
    "test_DAC_FullRangeSweep": "Full Range DAC Sweep",

    # WATCHDOG TIMER
    "test_WDT_initialization": "Initialize Watchdog Timer",
    "test_WDT_enable": "Enable Watchdog Timer",
    "test_WDT_timeout": "Watchdog Timeout",
    "test_WDT_feed": "Feed the Watchdog",
    "test_WDT_disable": "Disable Watchdog Timer",
    "test_WDT_configure_timeout": "Configure Watchdog Timeout",
    "test_WDT_interrupt_mode": "Watchdog Interrupt Mode",
    "test_WDT_reset_cause": "Detect Watchdog Reset Cause",

    # DMA
    "test_DMA_Init_ShouldInitializeProperly": "Initialize DMA Properly",
    "test_DMA_MemoryToMemory_ShouldTransferCorrectly": "DMA Memory-to-Memory Transfer",
    "test_DMA_PeripheralToMemory_ShouldTransferCorrectly": "DMA Peripheral-to-Memory Transfer",
    "test_DMA_MemoryToPeripheral_ShouldTransferCorrectly": "DMA Memory-to-Peripheral Transfer",
    "test_DMA_TransferComplete_ShouldTriggerInterrupt": "Trigger Interrupt on DMA Completion",
    "test_DMA_TransferError_ShouldHandleErrors": "Handle DMA Transfer Errors",
    "test_DMA_CircularMode_ShouldWorkCorrectly": "DMA Circular Mode",
    "test_DMA_PriorityLevels_ShouldBeConfigurable": "DMA Priority Level Configuration",
    "test_DMA_Interrupt_ShouldBeTriggered": "DMA Interrupt Trigger",
    "test_DMA_MultipleTransfers_ShouldRunSimultaneously": "Run Multiple DMA Transfers",

    # RTC
    "test_rtc_initialization": "Initialize RTC",
    "test_rtc_set_get_time": "Set and Get RTC Time",
    "test_rtc_time_progression": "RTC Time Progression",
    "test_rtc_alarm": "RTC Alarm Functionality",
    "test_rtc_leap_year": "RTC Leap Year Handling",
    "test_rtc_invalid_date": "Handle Invalid RTC Date",
    "test_rtc_backup_power": "RTC Backup Power Mode",

    # UART
    "test_uart_initialization": "Initialize UART",
    "test_uart_set_baudrate": "Set UART Baudrate",
    "test_uart_send_byte": "Send Byte over UART",
    "test_uart_send_multiple_bytes": "Send Multiple Bytes over UART",
    "test_uart_receive_byte": "Receive Byte over UART",
    "test_uart_parity_error": "UART Parity Error Detection",
    "test_uart_frame_error": "UART Frame Error Detection",

    # SPI
    "test_SPI_Initialization": "Initialize SPI",
    "test_SPI_Mode_Config": "SPI Mode Configuration",
    "test_SPI_Clock_Speed)": "SPI Clock Speed Test",
    "test_SPI_Data_Transmission": "SPI Data Transmission",
    "test_SPI_Data_Reception": "SPI Data Reception",
    "test_SPI_Loopback": "SPI Loopback Test",
    "test_SPI_Chip_Select": "SPI Chip Select Handling",
    "test_SPI_Full_Duplex": "SPI Full Duplex Communication",
    "test_SPI_Half_Duplex": "SPI Half Duplex Communication",
    "test_SPI_Interrupt": "SPI Interrupt Test",
    "test_SPI_Error_Handling": "SPI Error Handling",
    "test_SPI_DMA_Transfer": "SPI DMA Transfer",

    # I2C
    "test_I2C_Init_Should_Succeed_With_Valid_Configuration": "I2C Valid Configuration",
    "test_I2C_Init_Should_Fail_With_Invalid_Configuration": "I2C Invalid Configuration Failure",
    "test_I2C_SendByte_Should_Succeed": "I2C Send Byte Success",
    "test_I2C_SendByte_Should_Fail_On_NACK": "I2C Send Byte NACK Failure",
    "test_I2C_SendData_Should_Succeed": "I2C Send Data Success",
    "test_I2C_ReceiveByte_Should_Succeed": "I2C Receive Byte Success",
    "test_I2C_BusBusy_Should_Return_Error": "I2C Bus Busy Error",
    "test_I2C_RepeatedStart_Should_Succeed": "I2C Repeated Start Success",
    "test_I2C_ArbitrationLoss_Should_Detect_Error": "I2C Arbitration Loss Detection",
    "test_I2C_Timeout_Should_Return_Error": "I2C Timeout Error",
    "test_I2C_StuckSDA_Should_Detect_And_Recover": "I2C Stuck SDA Recovery",
    "test_I2C_StuckSCL_Should_Detect_And_Recover": "I2C Stuck SCL Recovery",
    "test_I2C_LowestAddress_Should_Succeed": "I2C Lowest Address Access",
    "test_I2C_HighestAddress_Should_Succeed": "I2C Highest Address Access",
    "test_I2C_ClockStretching_Should_Wait_Properly": "I2C Clock Stretching Wait",
    "test_I2C_ExcessiveClockStretching_Should_Timeout": "I2C Clock Stretching Timeout",
    "test_I2C_CorruptedData_Should_Fail": "I2C Corrupted Data Handling"
}

selected_tests = set()
test_vars = {}
label_widgets = {}
test_widgets = {}

def toggle_test(peripheral, test, var):
    if var.get():
        selected_tests.add(test)
    else:
        selected_tests.discard(test)

def toggle_peripheral(peripheral, var, test_vars_local):
    if var.get():
        label_widgets[peripheral].config(fg="black")
        for test, test_var in test_vars_local.items():
            test_var.set(1)
            selected_tests.add(test)
    else:
        label_widgets[peripheral].config(fg="gray")
        for test, test_var in test_vars_local.items():
            test_var.set(0)
            selected_tests.discard(test)

def filter_tests(query):
    query = query.lower()
    for test, widget in test_widgets.items():
        if query in test.lower():
            widget.pack(anchor="w")
        else:
            widget.pack_forget()

def create_selection_page(root):
    frame = tk.Frame(root)
    frame.pack(fill="both", expand=True)

    tk.Label(frame, text="Փնտրել թեստ", font=("Arial", 10)).pack(anchor="w", padx=10, pady=(10, 0))
    search_entry = tk.Entry(frame)
    search_entry.pack(fill="x", padx=10)
    search_entry.bind("<KeyRelease>", lambda e: filter_tests(search_entry.get()))

    canvas = tk.Canvas(frame)
    scrollbar = tk.Scrollbar(frame, orient="vertical", command=canvas.yview)
    scrollable_frame = tk.Frame(canvas)

    scrollable_frame.bind("<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
    canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
    canvas.configure(yscrollcommand=scrollbar.set)

    canvas.pack(side="left", fill="both", expand=True)
    scrollbar.pack(side="right", fill="y")

    arrow_vars = {}
    test_frames = {}

    for peripheral, tests in peripherals.items():
        var = tk.IntVar()
        p_frame = tk.Frame(scrollable_frame)
        p_frame.pack(anchor="w", pady=5, fill="x")

        header_frame = tk.Frame(p_frame)
        header_frame.pack(anchor="w", fill="x")

        arrow_var = tk.StringVar(value="▶")
        arrow_vars[peripheral] = arrow_var

        test_frame = tk.Frame(p_frame)
        test_frames[peripheral] = test_frame  

        def make_toggle_func(p):  
            return lambda: (
                test_frames[p].pack(anchor="w", padx=20)
                if not test_frames[p].winfo_ismapped()
                else test_frames[p].pack_forget(),
                arrow_vars[p].set("▼" if not test_frames[p].winfo_ismapped() else "▶")
            )

        arrow_btn = tk.Button(header_frame, textvariable=arrow_var, width=2, command=make_toggle_func(peripheral))
        arrow_btn.pack(side="left")

        p_checkbox = tk.Checkbutton(header_frame, variable=var, command=lambda p=peripheral, v=var: toggle_peripheral(p, v, test_vars[p]))
        p_checkbox.pack(side="left")

        label = tk.Label(header_frame, text=peripheral, font=("Arial", 12))
        label.pack(side="left", padx=5)
        label_widgets[peripheral] = label

        test_vars[peripheral] = {}
        for test in tests:
            t_var = tk.IntVar()
            test_vars[peripheral][test] = t_var
            display_name = user_friendly_names.get(test, test)
            cb = tk.Checkbutton(test_frame, text="   " + display_name, variable=t_var, command=lambda t=test, v=t_var: toggle_test(peripheral, t, v))
            cb.pack(anchor="w")
            test_widgets[test] = cb


    run_button = tk.Button(p_frame, text="Run Tests", command=lambda: display_results_page(root, list(selected_tests)))
    run_button.pack(pady=20)


def display_results_page(parent, selected):
    result_window = tk.Toplevel(parent)
    result_window.title("Test Results")
    result_window.geometry("900x900")

    canvas = tk.Canvas(result_window)
    scrollbar = tk.Scrollbar(result_window, orient="vertical", command=canvas.yview)
    scrollable_frame = tk.Frame(canvas)

    scrollable_frame.bind("<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
    canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
    canvas.configure(yscrollcommand=scrollbar.set)

    canvas.pack(side="left", fill="both", expand=True)
    scrollbar.pack(side="right", fill="y")

    top_frame = tk.Frame(scrollable_frame)
    top_frame.pack(pady=10)

    left_frame = tk.LabelFrame(top_frame, text="Passed Tests", fg="green", font=("Arial", 12, "bold"), bd=2, relief="solid")
    left_frame.pack(side="left", fill="both", expand=True, padx=20)

    right_frame = tk.LabelFrame(top_frame, text="Failed Tests", fg="red", font=("Arial", 12, "bold"), bd=2, relief="solid")
    right_frame.pack(side="right", fill="both", expand=True, padx=20)

    result = subprocess.run(["platformio", "test"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    output = result.stdout

    passed_tests = []
    failed_tests = []

    for line in output.splitlines():
        for test_name in selected:
            if test_name in line:
                if "[PASSED]" in line:
                    passed_tests.append(line.strip())
                elif "[FAILED]" in line:
                    failed_tests.append(line.strip())

    def show_results_sequentially():
        for test in passed_tests:
            name= next((t for t in selected if t in test),test)
            friendly_names=user_friendly_names.get(name,name)
            tk.Label(left_frame, text=f"{friendly_names}(PASSED)", fg="green", font=("Arial", 10), anchor="w", justify="left").pack(anchor="w", pady=(0, 8))
            time.sleep(0.2)
        for test in failed_tests:
            name= next((t for t in selected if t in test),test)
            friendly_names=user_friendly_names.get(name,name)
            tk.Label(right_frame, text=f"{friendly_names}(FAILED)", fg="red", font=("Arial", 10), anchor="w", justify="left").pack(anchor="w", pady=(0, 8))
            time.sleep(0.2)

    threading.Thread(target=show_results_sequentially, daemon=True).start()

    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    filename = f"test_results_{timestamp}.csv"
    with open(filename, "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Status", "Test Name"])
        for test in passed_tests:
            writer.writerow(["PASSED", test])
        for test in failed_tests:
            writer.writerow(["FAILED", test])


    back_button = tk.Button(result_window, text="Վերադառնալ", command=result_window.destroy)
    back_button.pack(pady=10)
    def show_log():
        log_window = tk.Toplevel(result_window)
        log_window.title("Test Log Output")
        log_window.geometry("800x400")

        text_widget = tk.Text(log_window, wrap="word")
        text_widget.insert("1.0", output)
        text_widget.config(state="disabled")
        text_widget.pack(fill="both", expand=True)

        scrollbar = tk.Scrollbar(text_widget, command=text_widget.yview)
        text_widget.config(yscrollcommand=scrollbar.set)
        scrollbar.pack(side="right", fill="y")

    view_log_button = tk.Button(result_window, text="Դիտել Լոգը", command=show_log)
    view_log_button.pack(pady=10)


root = tk.Tk()
root.title("Microcontroller Test GUI")
root.geometry("900x600")

create_selection_page(root)

root.mainloop()
