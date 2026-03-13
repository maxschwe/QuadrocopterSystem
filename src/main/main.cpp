#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/uart.h"
#include <string.h>
#include <math.h>

const bool REMOTE_CONTROL_ENABLED = false;

#include "tests.h"
#include "drone.h"

#include "mpu6050.h"

#if CONTROLLER_3DOF
#include "controller_3dof_container.h"
struct ControllerState {
    ReferenceInputs referenceInputs;
    real_T throttles[4];
    real_T x_pred[6];
    real_T values[6];
};
#else
#include "controller_6dof_container.h"
struct ControllerState {
    ReferenceInputs referenceInputs;
    real_T throttles[4];
    real_T x_pred[12];
    real_T values[6];
};
#endif

struct SystemState {
    Drone& drone;
    ControllerState controllerState;
};

void host_com(void* params) {
    SystemState *systemState = static_cast<SystemState*>(params);
    Drone& drone = systemState->drone;
    ControllerState& controllerState = systemState->controllerState;

    ReferenceInputs& referenceInputs = drone.getReferenceInputs();
    PositionData& position = drone.getPosition();

    char rx_buffer[128];
    int rx_idx = 0;
    uint8_t byte;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(20); // 20ms loop time = 50Hz

    while (1) {
        OrientationData orientation = drone.orientation();
        
        // send telemetry data to host pc
        printf("#%ld\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
            portTICK_PERIOD_MS * xTaskGetTickCount(),
            orientation.roll, orientation.pitch, orientation.yaw,
            position.x, position.y, position.z,
            #if CONTROLLER_3DOF
                controllerState.referenceInputs.roll, controllerState.referenceInputs.pitch, controllerState.referenceInputs.yaw, controllerState.referenceInputs.throttle,
            #else
                controllerState.referenceInputs.x, controllerState.referenceInputs.y, controllerState.referenceInputs.z, controllerState.referenceInputs.yaw,
            #endif
            controllerState.throttles[0], controllerState.throttles[1], controllerState.throttles[2], controllerState.throttles[3],
            controllerState.x_pred[0], controllerState.x_pred[1], controllerState.x_pred[2], controllerState.x_pred[3], controllerState.x_pred[4], controllerState.x_pred[5],
            controllerState.values[0], controllerState.values[1], controllerState.values[2], controllerState.values[3], controllerState.values[4], controllerState.values[5]
        );
        
        // read incoming data from host pc
        while (uart_read_bytes(UART_NUM_0, &byte, 1, 0) > 0) {
            if (byte == '\n' || byte == '\r') {
                if (rx_idx > 0) {
                    rx_buffer[rx_idx] = '\0';
                    // Parse: Expecting #p,i,d or #TRAJ,type,dur,amp,freq
                    
                    float input1, input2, input3;
                    if (sscanf(rx_buffer, "#P;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        drone.updatePosition(input1, input2, input3);
                    #if PID_3DOF
                    } else if (sscanf(rx_buffer, "#RPID;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        Controller3dof::rtP.kp_roll = input1;
                        Controller3dof::rtP.ki_roll = input2;
                        Controller3dof::rtP.kd_roll = input3;
                        ESP_LOGI("PID", "Updated Roll PID: P=%.4f I=%.4f D=%.4f", input1, input2, input3);
                    } else if (sscanf(rx_buffer, "#PPID;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        Controller3dof::rtP.kp_pitch = input1;
                        Controller3dof::rtP.ki_pitch = input2;
                        Controller3dof::rtP.kd_pitch = input3;
                        ESP_LOGI("PID", "Updated Pitch PID: P=%.4f I=%.4f D=%.4f", input1, input2, input3);
                    } else if (sscanf(rx_buffer, "#YPID;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        Controller3dof::rtP.kp_yaw = input1;
                        Controller3dof::rtP.ki_yaw = input2;
                        Controller3dof::rtP.kd_yaw = input3;
                        ESP_LOGI("PID", "Updated Yaw PID: P=%.4f I=%.4f D=%.4f", input1, input2, input3);
                    #endif
                    #if PID_6DOF
                    } else if (sscanf(rx_buffer, "#xPID;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        Controller6dof::rtP.kp_x = input1;
                        Controller6dof::rtP.ki_x = input2;
                        Controller6dof::rtP.kd_x = input3;
                        ESP_LOGI("PID", "Updated X PID: P=%.4f I=%.4f D=%.4f", input1, input2, input3);
                    } else if (sscanf(rx_buffer, "#yPID;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        Controller6dof::rtP.kp_y = input1;
                        Controller6dof::rtP.ki_y = input2;
                        Controller6dof::rtP.kd_y = input3;
                        ESP_LOGI("PID", "Updated Y PID: P=%.4f I=%.4f D=%.4f", input1, input2, input3);
                    } else if (sscanf(rx_buffer, "#zPID;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        Controller6dof::rtP.kp_z = input1;
                        Controller6dof::rtP.ki_z = input2;
                        Controller6dof::rtP.kd_z = input3;
                        ESP_LOGI("PID", "Updated Z PID: P=%.4f I=%.4f D=%.4f", input1, input2, input3);
                    #endif
                    } else if (sscanf(rx_buffer, "#R;%f,%f,%f", &input1, &input2, &input3) == 3) {
                        #if CONTROLLER_3DOF
                            referenceInputs.roll = input1;
                            referenceInputs.pitch = input2;
                            referenceInputs.yaw = input3;
                        #else
                            referenceInputs.x = input1;
                            referenceInputs.y = input2;
                            referenceInputs.z = input3;
                        #endif
                    #if CONTROLLER_3DOF   
                    } else if (sscanf(rx_buffer, "#RT;%f", &input1) == 1) {
                        // set reference thrust
                        referenceInputs.throttle = input1;
                    #endif
                    } else {
                        ESP_LOGW("ExternalInputs", "Invalid command: %s", rx_buffer);
                    }
                    rx_idx = 0; // Reset for next line
                }
            } else if (rx_idx < sizeof(rx_buffer) - 1) {
                rx_buffer[rx_idx++] = byte;
            }
        }

        BaseType_t thisCallDelayedLoop = xTaskDelayUntil(&xLastWakeTime, xFrequency);
        if (thisCallDelayedLoop != pdTRUE) {
            ESP_LOGW("TASK", "Log delayed");
        }
    }
}

void drone_control(void*) {
    // Initialize UART for host pc communication
    uart_config_t uart_config = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_APB,
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);

    Drone drone(
        LEDC_TIMER_0,
        GPIO_NUM_15, LEDC_CHANNEL_0,
        GPIO_NUM_4, LEDC_CHANNEL_1,
        GPIO_NUM_18, LEDC_CHANNEL_2,
        GPIO_NUM_19, LEDC_CHANNEL_3,
        GPIO_NUM_5,
        REMOTE_CONTROL_ENABLED
    );

    ReferenceInputs& referenceInputs = drone.getReferenceInputs();
    #if !CONTROLLER_3DOF
    PositionData& position = drone.getPosition();
    #endif

    uint16_t lastToggleState = referenceInputs.toggle;

    bool motorsActive = !REMOTE_CONTROL_ENABLED;
    if (REMOTE_CONTROL_ENABLED) {
        ESP_LOGI("TASK", "Waiting for controller toggle...");
        while (true) {
            if (referenceInputs.toggle != lastToggleState) {
                lastToggleState = referenceInputs.toggle;
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    #if (CONTROLLER_3DOF)
    Controller3dof controller;
    #else
    Controller6dof controller;
    #endif
    controller.initialize();

    SystemState systemState{drone, ControllerState{}};

    // Start host communication task for external control and telemetry
    xTaskCreate(&host_com, "host com", 16384, &systemState, 2, NULL);

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(5); // 5ms loop time = 200Hz

    float t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    while (true) {
        OrientationData orientation = drone.orientation();
        if (motorsActive && (xTaskGetTickCount() - orientation.lastUpdate > pdMS_TO_TICKS(100))) {
            motorsActive = false;
            ESP_LOGE("TASK", "MPU Connection lost - Deactivating");
        }
        
        if (REMOTE_CONTROL_ENABLED) {
            // 1. Toggle Motor State
            if (referenceInputs.toggle != lastToggleState) {
                lastToggleState = referenceInputs.toggle;
                motorsActive = !motorsActive;
                ESP_LOGI("TASK", "Motors active: %s", motorsActive ? "ON" : "OFF");
            }

            // 2. Failsafe: Connection Timeout
            if (motorsActive && (xTaskGetTickCount() - referenceInputs.lastUpdate > pdMS_TO_TICKS(100))) {
                motorsActive = false;
                ESP_LOGE("TASK", "Remote Controller Connection lost - Deactivating");
            }
        }

        if (motorsActive) {
            #if CONTROLLER_3DOF
            controller.rtU.w[0] = referenceInputs.throttle;
            controller.rtU.w[1] = referenceInputs.roll;
            controller.rtU.w[2] = referenceInputs.pitch;
            controller.rtU.w[3] = referenceInputs.yaw;
            controller.rtU.y[0] = orientation.roll;
            controller.rtU.y[1] = orientation.pitch;
            controller.rtU.y[2] = orientation.yaw;
            #else
            controller.rtU.w[0] = referenceInputs.x;
            controller.rtU.w[1] = referenceInputs.y;
            controller.rtU.w[2] = referenceInputs.z;
            controller.rtU.w[3] = referenceInputs.yaw;
            controller.rtU.y[0] = position.x;
            controller.rtU.y[1] = position.y;
            controller.rtU.y[2] = position.z;
            controller.rtU.y[3] = orientation.roll;
            controller.rtU.y[4] = orientation.pitch;
            controller.rtU.y[5] = orientation.yaw;
            #endif

            controller.step();
            
            t1 = controller.rtY.throttles[0];
            t2 = controller.rtY.throttles[1];
            t3 = controller.rtY.throttles[2];
            t4 = controller.rtY.throttles[3];
        } else {
            t1 = t2 = t3 = t4 = 0.0f; 
        }
        drone.setThrottles(t1, t2, t3, t4);

        // update controller state for comm task to send telemetry to host pc
        #if CONTROLLER_3DOF
        systemState.controllerState.referenceInputs.roll = referenceInputs.roll;
        systemState.controllerState.referenceInputs.pitch = referenceInputs.pitch;
        systemState.controllerState.referenceInputs.yaw = referenceInputs.yaw;
        systemState.controllerState.referenceInputs.throttle = referenceInputs.throttle;
        #else
        systemState.controllerState.referenceInputs.x = referenceInputs.x;
        systemState.controllerState.referenceInputs.y = referenceInputs.y;
        systemState.controllerState.referenceInputs.z = referenceInputs.z;
        systemState.controllerState.referenceInputs.yaw = referenceInputs.yaw;
        #endif
        systemState.controllerState.throttles[0] = t1;
        systemState.controllerState.throttles[1] = t2;
        systemState.controllerState.throttles[2] = t3;
        systemState.controllerState.throttles[3] = t4;
        systemState.controllerState.x_pred[0] = controller.rtY.x_pred[0];
        systemState.controllerState.x_pred[1] = controller.rtY.x_pred[1];
        systemState.controllerState.x_pred[2] = controller.rtY.x_pred[2];
        systemState.controllerState.x_pred[3] = controller.rtY.x_pred[3];
        systemState.controllerState.x_pred[4] = controller.rtY.x_pred[4];
        systemState.controllerState.x_pred[5] = controller.rtY.x_pred[5];

        #if !CONTROLLER_3DOF
        systemState.controllerState.x_pred[6] = controller.rtY.x_pred[6];
        systemState.controllerState.x_pred[7] = controller.rtY.x_pred[7];
        systemState.controllerState.x_pred[8] = controller.rtY.x_pred[8];
        systemState.controllerState.x_pred[9] = controller.rtY.x_pred[9];
        systemState.controllerState.x_pred[10] = controller.rtY.x_pred[10];
        systemState.controllerState.x_pred[11] = controller.rtY.x_pred[11];
        #endif
        systemState.controllerState.values[0] = controller.rtY.values[0];
        systemState.controllerState.values[1] = controller.rtY.values[1];
        systemState.controllerState.values[2] = controller.rtY.values[2];
        systemState.controllerState.values[3] = controller.rtY.values[3];
        systemState.controllerState.values[4] = controller.rtY.values[4];
        systemState.controllerState.values[5] = controller.rtY.values[5];

        BaseType_t thisCallDelayedLoop = xTaskDelayUntil(&xLastWakeTime, xFrequency);
        if (thisCallDelayedLoop != pdTRUE) {
            ESP_LOGW("TASK", "Control delayed");
        }
    }
}

extern "C" void app_main(void)
{
    start_onboard_led_test();

    xTaskCreate(&drone_control, "drone_control", 16384, NULL, 5, NULL);
}
