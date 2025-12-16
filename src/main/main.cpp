#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/uart.h"

#include "tests.h"
#include "drone.h"
#include "controller_3dof.h"
#include "mpu6050.h"


#define UART_NUM UART_NUM_2
#define RX_BUF_SIZE 1024
#define TIMEOUT_UART 20
#define FRAME_SIZE 16
#define FRAME_1_TYPE 0x54
#define FRAME_2_TYPE 0x5c

#define RECEIVER_MIN 343
#define RECEIVER_MAX 1705

#define THROTTLE_MIN_MAP 2
#define THROTTLE_MAX_MAP 10
#define YAW_MIN_MAP 180
#define YAW_MAX_MAP -180
#define PITCH_MIN_MAP 20
#define PITCH_MAX_MAP -20
#define ROLL_MIN_MAP 20
#define ROLL_MAX_MAP -20


struct ControllerInputs {
	float roll;
	float pitch;
	float yaw;
	float throttle;

	uint16_t toggle;
};

DRAM_ATTR static ControllerInputs myInputs;


void drone_control(void*){
	Drone drone(
		LEDC_TIMER_0,
		GPIO_NUM_15, LEDC_CHANNEL_0,
		GPIO_NUM_4, LEDC_CHANNEL_1,
		GPIO_NUM_18,  LEDC_CHANNEL_2,
		GPIO_NUM_19, LEDC_CHANNEL_3,
		GPIO_NUM_5
	);

	Controller controller;
	controller.initialize();

	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = pdMS_TO_TICKS(5);
	// good values: P: 0.009, D: 0.0013, N: 100

	while (true) {
		VectorFloat orientation = drone.rpy();

		controller.rtU.roll_target = myInputs.roll;
		controller.rtU.pitch_target = myInputs.pitch;
		controller.rtU.yaw_target = myInputs.yaw;
		controller.rtU.throttle = myInputs.throttle;

		controller.rtU.roll = orientation.x;
		controller.rtU.pitch = orientation.y;
		controller.rtU.yaw = orientation.z;

		controller.step();
		Controller::ExtY outputs = controller.rtY;

		drone.setThrottles(
			outputs.throttle_1, 
			outputs.throttle_2, 
			outputs.throttle_3, 
			outputs.throttle_4
		);
		
		printf(
			"%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n", 
			orientation.x, 
			orientation.y, 
			orientation.z, 
			myInputs.roll,
			myInputs.pitch,
			myInputs.yaw,
			outputs.throttle_1, 
			outputs.throttle_2, 
			outputs.throttle_3, 
			outputs.throttle_4
		);
		BaseType_t xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		if (xWasDelayed != pdTRUE) {
			ESP_LOGW("TASK", "drone_control delayed!");
		}
	}
}

uint16_t decode_channel(uint8_t msb, uint8_t lsb) {
    return ((msb & 0x07) << 8) | lsb;
}

float lin_map(uint16_t val, int16_t out_min, int16_t out_max) {
	return out_min + (float)(val - RECEIVER_MIN) * (out_max - out_min) / (RECEIVER_MAX - RECEIVER_MIN);
}

void process_frame(uint8_t* frame) {
    uint8_t frame_type = frame[12]; // 13th byte
    if (frame_type == 0x54) {
        uint16_t roll_val = decode_channel(frame[2], frame[3]); // Channel 1
		uint16_t pitch_val = decode_channel(frame[6], frame[7]); // Channel 2
		uint16_t throttle_val = decode_channel(frame[4], frame[5]); // Channel 3

		float throttle = lin_map(throttle_val, THROTTLE_MIN_MAP, THROTTLE_MAX_MAP);
		float roll = lin_map(roll_val, ROLL_MIN_MAP, ROLL_MAX_MAP);
		float pitch = lin_map(pitch_val, PITCH_MIN_MAP, PITCH_MAX_MAP);

		myInputs.roll = roll;
		myInputs.pitch = pitch;
		myInputs.throttle = throttle;
    } else if (frame_type == 0x5C) {
        uint16_t yaw_val = decode_channel(frame[6], frame[7]); // Channel 4
		uint16_t toggle_val = decode_channel(frame[2], frame[3]);

		float yaw = lin_map(yaw_val, YAW_MIN_MAP, YAW_MAX_MAP);

		myInputs.yaw = yaw;
		myInputs.toggle = toggle_val;
    } else {
        ESP_LOGE("RECV", "Unknown frame: 0x%02X\n", frame_type);
    }
}

void parse_uart_buffer(uint8_t* uart_buffer, uint32_t& uart_buffer_len) {
    int i = 0;

	if (uart_buffer_len < FRAME_SIZE) {
		return;
	}

    while (i <= uart_buffer_len - FRAME_SIZE) {
        if (uart_buffer[i] == 0x00 && uart_buffer[i+1] == 0x00 &&
            uart_buffer[i + FRAME_SIZE - 2] == 0xFF &&
            uart_buffer[i + FRAME_SIZE - 1] == 0xFF) {

            process_frame(&uart_buffer[i]);
            i += FRAME_SIZE;
            continue;
        }
        i++;
    }

    // Shift remaining bytes to start of buffer
    if (i < uart_buffer_len) {
        memmove(uart_buffer, &uart_buffer[i], uart_buffer_len - i);
        uart_buffer_len -= i;
    } else {
        uart_buffer_len = 0;
    }
}


void uart_task(void *arg) {
	uart_config_t uart_config = {
        .baud_rate = 115200,        // SRXL usually ~115200
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_APB,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, RX_BUF_SIZE, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(
        UART_NUM,
        UART_PIN_NO_CHANGE,  // TX not used
        16,                  // RX pin (change if needed)
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    ));


	uint8_t read_buf[128];
	uint8_t uart_buffer[RX_BUF_SIZE];
	uint32_t uart_buffer_len = 0;

    while (1) {
        int len = uart_read_bytes(UART_NUM, read_buf, sizeof(read_buf), pdMS_TO_TICKS(TIMEOUT_UART));
        if (len > 0) {
			// Prevent buffer overflow
            if (uart_buffer_len + len > RX_BUF_SIZE) {
				uart_buffer_len = 0;
                ESP_LOGW("RECV", "UART buffer overflow, clearing buffer!\n");
            }
			
            // Copy new bytes into accumulation buffer
            memcpy(&uart_buffer[uart_buffer_len], read_buf, len);
            uart_buffer_len += len;
			
            // Parse for full frames
            parse_uart_buffer(uart_buffer, uart_buffer_len);
        } else {
			ESP_LOGW("RECV", "No data: Len %d", len);
		}
    }
}


extern "C" void app_main(void)
{
	start_onboard_led_test();
	xTaskCreate(uart_task, "uart2_read_task", 4096, NULL, 2, NULL);

    xTaskCreate(&drone_control, "drone_control", 16384, NULL, 5, NULL);
}
