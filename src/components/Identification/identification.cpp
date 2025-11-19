// void scale_init()
// {
//     uart_config_t uart_config = {
//         .baud_rate = 9600,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
//     uart_param_config(UART_NUM_2, &uart_config);
//     uart_set_pin(UART_NUM_2, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
//     uart_driver_install(UART_NUM_2, 1024, 0, 0, NULL, 0);
// }

// float measure_weight_average()
// {
//     const int samples = 10;
//     float total_weight = 0.0;

//     const int RESPONSE_BUFFER_SIZE = 18;
//     char data[RESPONSE_BUFFER_SIZE];

//     for (int i = 0; i < samples; i++)
//     {
//         uart_write_bytes(UART_NUM_2, "w", 1);

//         int len = uart_read_bytes(UART_NUM_2, data, RESPONSE_BUFFER_SIZE, 2000 / portTICK_PERIOD_MS);

//         if (len == RESPONSE_BUFFER_SIZE)
//         {
//             data[12] = '\0';
//             float weight = atoi(&data[2]);
//             total_weight += weight;
//         }
//         else
//         {
//             ESP_LOGE("SCALE", "Failed to read weight data, Len: %d", len);
//         }
//     }

//     float average_weight = total_weight / samples;
//     ESP_LOGI("SCALE", "Average Weight: %.2f", average_weight);

//     return average_weight;
// }

// void test_motor_ramp(void *pvParameters)
// {
//     scale_init();
//     rotors_init();

//     int lowest_throttle = 10;
//     int highest_throttle = 100;
//     int step_size = 2;

//     int measurement_count = (highest_throttle - lowest_throttle) / step_size + 1;

//     float weights[measurement_count];

//     // Ramp up motor
//     for (int duty = lowest_throttle, i = 0; duty <= highest_throttle && run_tasks; duty += step_size, i++)
//     {
//         set_throttle(duty, ROTOR_1);
//         ESP_LOGI("ESC", "Throttle: %d", duty);
//         vTaskDelay(pdMS_TO_TICKS(1000));
//         weights[i] = measure_weight_average();
//     }

//     set_throttle(0, ROTOR_1);

//     printf("WEIGHT_DATA: [ %.2f", weights[0]);
//     for (int i = 1; i < measurement_count; i++)
//     {
//         printf(", %.2f", weights[i]);
//     }
//     printf(" ]\n");

//     vTaskDelete(NULL);
// }

// void uart_monitor_task(void *pvParameter)
// {
//     // Initialize UART0
//     uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
//     uart_param_config(UART_NUM_0, &uart_config);
//     uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);

//     uint8_t data[1024];
//     while (1)
//     {
//         int len = uart_read_bytes(UART_NUM_0, data, 1024, 20 / portTICK_PERIOD_MS);
//         if (len > 0)
//         {
//             for (int i = 0; i < len; i++)
//             {
//                 if (data[i] == 0x03)
//                 { // ASCII for Ctrl+C
//                     printf("Ctrl+C received! Stopping all tasks...\n");
//                     run_tasks = false;
//                 }
//             }
//         }
//         vTaskDelay(pdMS_TO_TICKS(10));
//     }
// }
