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
		GPIO_NUM_2, LEDC_CHANNEL_1,
		GPIO_NUM_4,  LEDC_CHANNEL_2,
		GPIO_NUM_16, LEDC_CHANNEL_3,
		GPIO_NUM_5
	);

	Controller controller;
	controller.initialize();

	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = pdMS_TO_TICKS(10);

	
	while (true) {
		VectorFloat orientation = drone.ypr();
		printf("YAW: %3.1f, ", orientation.x);
		printf("PITCH: %3.1f, ", orientation.y);
		printf("ROLL: %3.1f \n", orientation.z);

		// controller.rtU.roll = ypr.x;
		// controller.rtU.pitch = ypr.y;
		// // controller.rtU.yaw = ypr.z;
		// controller.rtU.x = 0.0f;
		// controller.rtU.y = 0.0f;
		// // controller.rtU.z = 10.0f;

		controller.step();
		Controller::ExtY outputs = controller.rtY;

		drone.rotor1.setThrottle(outputs.throttle_1);
		drone.rotor2.setThrottle(outputs.throttle_2);
		drone.rotor3.setThrottle(outputs.throttle_3);
		drone.rotor4.setThrottle(outputs.throttle_4);
		// printf("t1: %f, t2: %f, t3: %f, t4: %f\n", outputs.throttle_1, outputs.throttle_2, outputs.throttle_3, outputs.throttle_4);
		BaseType_t xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		if (xWasDelayed != pdTRUE) {
			ESP_LOGW("TASK", "task_display delayed!");
		}
	}
}


extern "C" void app_main(void)
{
	start_onboard_led_test();
    xTaskCreate(&drone_control, "drone_control", 16384, NULL, 5, NULL);
}
