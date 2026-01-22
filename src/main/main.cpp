#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/uart.h"
#include <string.h>

#include "tests.h"
#include "drone.h"
#include "controller_3dof.h"
#include "mpu6050.h"

const bool USE_ON_DEVICE_CONTROLLER = false; // Set to false for remote control

void drone_control(void*) {
    Drone drone(
        LEDC_TIMER_0,
        GPIO_NUM_15, LEDC_CHANNEL_0,
        GPIO_NUM_4, LEDC_CHANNEL_1,
        GPIO_NUM_18, LEDC_CHANNEL_2,
        GPIO_NUM_19, LEDC_CHANNEL_3,
        GPIO_NUM_5
    );

    // Initialize UART for communication if using external controller
    const uart_port_t uart_num = UART_NUM_0;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(uart_num, &uart_config);
    uart_driver_install(uart_num, 1024, 0, 0, NULL, 0);

    bool motorsActive = false;
    ControllerInputs inputs = drone.getInputs();
    uint16_t lastToggleState = inputs.toggle;

    ESP_LOGI("TASK", "Waiting for controller toggle...");
    while (true) {
        inputs = drone.getInputs();
        if (inputs.toggle != lastToggleState) {
            lastToggleState = inputs.toggle;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    Controller controller;
    if (USE_ON_DEVICE_CONTROLLER) {
        controller.initialize();
    }

	char rx_buffer[128];
    int rx_idx = 0;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(5);

    while (true) {
        inputs = drone.getInputs();
        VectorFloat orientation = drone.rpy();

        // 1. Toggle Motor State
        if (inputs.toggle != lastToggleState) {
            lastToggleState = inputs.toggle;
            motorsActive = !motorsActive;
            ESP_LOGI("TASK", "Motors active: %s", motorsActive ? "ON" : "OFF");
        }

        // 2. Failsafe: Connection Timeout
        if (motorsActive && (xTaskGetTickCount() - inputs.last_update > pdMS_TO_TICKS(1000))) {
            motorsActive = false;
            ESP_LOGW("TASK", "Connection lost - Deactivating");
        }

        float t1 = 0, t2 = 0, t3 = 0, t4 = 0;

        if (motorsActive) {
            // ALWAYS Output measurements to Serial
            printf("#%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                   orientation.x, orientation.y, orientation.z,
                   inputs.roll, inputs.pitch, inputs.yaw, inputs.throttle);

            if (USE_ON_DEVICE_CONTROLLER) {
                // INTERNAL MODE
                controller.rtU.roll_target = inputs.roll;
                controller.rtU.pitch_target = inputs.pitch;
                controller.rtU.yaw_target = inputs.yaw;
                controller.rtU.throttle = inputs.throttle;
                controller.rtU.roll = orientation.x;
                controller.rtU.pitch = orientation.y;
                controller.rtU.yaw = orientation.z;

                controller.step();
                
                t1 = controller.rtY.throttle_1;
                t2 = controller.rtY.throttle_2;
                t3 = controller.rtY.throttle_3;
                t4 = controller.rtY.throttle_4;
            } else {
                // EXTERNAL MODE: Wait for throttles back via Serial
                uint8_t byte;
                while (uart_read_bytes(uart_num, &byte, 1, 0) > 0) {
                    if (byte == '\n' || byte == '\r') {
                        if (rx_idx > 0) {
                            rx_buffer[rx_idx] = '\0';
                            // Parse: Expecting #t1,t2,t3,t4
                            sscanf(rx_buffer, "#%f,%f,%f,%f", &t1, &t2, &t3, &t4);
                            rx_idx = 0; // Reset for next line
                        }
                    } else if (rx_idx < sizeof(rx_buffer) - 1) {
                        rx_buffer[rx_idx++] = byte;
                    }
                }
            }
            drone.setThrottles(t1, t2, t3, t4);
        } else {
            drone.setThrottles(0, 0, 0, 0);
        }

        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

 extern "C" void app_main(void)

{

    start_onboard_led_test();

    xTaskCreate(&drone_control, "drone_control", 16384, NULL, 5, NULL);

} 
