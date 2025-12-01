#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "tests.h"
#include "drone.h"
#include "controller_3dof.h"
#include "mpu6050.h"


void drone_control(void*){
	Drone drone(
		LEDC_TIMER_0,
		GPIO_NUM_15, LEDC_CHANNEL_0,
		GPIO_NUM_4, LEDC_CHANNEL_1,
		GPIO_NUM_16,  LEDC_CHANNEL_2,
		GPIO_NUM_17, LEDC_CHANNEL_3,
		GPIO_NUM_5
	);

	Controller controller;
	controller.initialize();

	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = pdMS_TO_TICKS(5);
	// good values: P: 0.009, D: 0.0013, N: 100
	
	while (true) {
		VectorFloat orientation = drone.rpy();

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
			"%.3f, %.3f, %.3f; %.3f, %.3f, %.3f, %.3f\n", 
			orientation.x, 
			orientation.y, 
			orientation.z, 
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


extern "C" void app_main(void)
{
	start_onboard_led_test();
    xTaskCreate(&drone_control, "drone_control", 16384, NULL, 5, NULL);
}
