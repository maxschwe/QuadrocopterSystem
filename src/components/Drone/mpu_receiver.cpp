


TaskHandle_t processingTaskHandle = NULL;
MPU6050 mpu;
QueueHandle_t mpuMailbox = NULL;


static void IRAM_ATTR gpio_isr_handler(void* arg) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Notify the processing task that an interrupt occurred.
    // This increments the task's notification value.
    vTaskNotifyGiveFromISR(processingTaskHandle, &xHigherPriorityTaskWoken);

    // If waking the task changes the scheduler priority, run scheduler immediately and
    // switch to the woken up task immediately.
    if (xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

void mpu_receive_task(void* params) {
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        Quaternion q;           // [w, x, y, z]         quaternion container

        VectorInt16 accel;

        VectorFloat gravity;    // [x, y, z]            gravity vector
        float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
        uint16_t packetSize = 42;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU

        do {
            mpuIntStatus = mpu.getIntStatus();
            fifoCount = mpu.getFIFOCount();

            if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
                // reset because in this case FIFO overflowed, so now
                // there's new data in the lower addresses and old data in the higher addresses
                // you can't know which data is old and which is new
                mpu.resetFIFO();
                ESP_LOGW("MPU6050", "FIFO overflowed, Resetting it (Int Status: %x)", mpuIntStatus);
            }
        } while (!(mpuIntStatus & 0x02));

        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        VectorFloat ypr_vec(ypr[2]* 180/M_PI, ypr[1] * 180/M_PI, ypr[0] * 180/M_PI);

        xQueueOverwrite(mpuMailbox, &ypr_vec);
    }

    vTaskDelete(NULL);
}


class MpuReceiver {

}