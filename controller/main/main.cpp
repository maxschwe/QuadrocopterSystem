#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "tests.h"
#include "drone.h"
#include "controller.h"
#include "MPU6050.h"


void task_display(void*){
	Drone drone(
		LEDC_TIMER_0,
		GPIO_NUM_15, LEDC_CHANNEL_0,
		GPIO_NUM_2, LEDC_CHANNEL_1,
		GPIO_NUM_4,  LEDC_CHANNEL_2,
		GPIO_NUM_5, LEDC_CHANNEL_3
	);

	Model controller;
	controller.initialize();

	while (true) {
		VectorFloat ypr = drone.ypr();

		controller.rtU.roll = ypr.x;
		controller.rtU.pitch = ypr.y;
		// controller.rtU.yaw = ypr.z;
		controller.rtU.x = 0.0f;
		controller.rtU.y = 0.0f;
		// controller.rtU.z = 10.0f;

		controller.step();

		drone.rotor1.setThrottle(controller.rtY.Out1);
		drone.rotor2.setThrottle(controller.rtY.Out2);
		drone.rotor3.setThrottle(controller.rtY.Out3);
		drone.rotor4.setThrottle(controller.rtY.Out4);
		// printf("r1: %f, r2: %f, r3: %f, r4: %f\n", controller.rtY.Out1, controller.rtY.Out2, controller.rtY.Out3, controller.rtY.Out4);
		vTaskDelay(pdMS_TO_TICKS(4));
	}
}


extern "C" void app_main(void)
{
	start_onboard_led_test();
    xTaskCreate(&task_display, "disp_task", 8192, NULL, 5, NULL);
}
