#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/uart.h"

#include "tests.h"
#include "drone.h"
#include "controller_3dof.h"
#include "mpu6050.h"


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

	bool motorsActive = false;
	ControllerInputs inputs = drone.getInputs();
	uint16_t lastToggleState = inputs.toggle;

	ESP_LOGI("TASK", "Waiting for controller to be toggled...");
	while (true) {
		inputs = drone.getInputs();
		if (inputs.toggle != lastToggleState) {
			lastToggleState = inputs.toggle;
			ESP_LOGI("TASK", "Controller connected");
			break;
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}

	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = pdMS_TO_TICKS(5);
	// good values: P: 0.009, D: 0.0013, N: 100

	while (true) {
		inputs = drone.getInputs();
		VectorFloat orientation = drone.rpy();

		controller.rtU.roll_target = inputs.roll;
		controller.rtU.pitch_target = inputs.pitch;
		controller.rtU.yaw_target = inputs.yaw;
		controller.rtU.throttle = inputs.throttle;

		if (inputs.toggle != lastToggleState) {
			lastToggleState = inputs.toggle;
			motorsActive = !motorsActive;
			ESP_LOGI("TASK", "Motors active toggled");
		}

		if (motorsActive && (xTaskGetTickCount() - inputs.last_update > pdMS_TO_TICKS(1000))) {
			motorsActive = false;
			ESP_LOGW("TASK", "Connection lost - Motors deactivated");
		}

		controller.rtU.roll = orientation.x;
		controller.rtU.pitch = orientation.y;
		controller.rtU.yaw = orientation.z;

		Controller::ExtY outputs = controller.rtY;
		if (motorsActive) {
			controller.step();
			drone.setThrottles(
				outputs.throttle_1, 
				outputs.throttle_2, 
				outputs.throttle_3, 
				outputs.throttle_4
			);

			printf(
				"-- %.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",
				inputs.roll,
				inputs.pitch,
				inputs.yaw,
				orientation.x, 
				orientation.y, 
				orientation.z, 
				outputs.throttle_1, 
				outputs.throttle_2, 
				outputs.throttle_3, 
				outputs.throttle_4
			);
		} else {
			drone.setThrottles(0, 0, 0, 0);
		}
		
		BaseType_t xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		if (xWasDelayed != pdTRUE) {
			ESP_LOGW("TASK", "drone_control delayed!");
		}
	}
}

extern "C" void app_main(void)
{
	start_onboard_led_test();
    xTaskCreate(&drone_control, "drone_control", 16384, NULL, 5, NULL);
}
