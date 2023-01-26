# 002 LEDs

In this project three tasks are scheduled. Each task controls an LED, toggling this LED periodically (400, 800 and 1000ms periodic cycle). The idea here is to use the ```xTaskDelay``` and ```xTaskDelayUntil``` APIs to free the CPU.  
For testing this project you need to follow the connection diagram below:

![Alt text](doc/nucleo-freertos-002LEDs.png)

If you use the Delay function (which basically is implementing a for loop) for waiting in each task, you will see the CPU is blocked in that task and will not be free anytime. You can see this behaviour below where the CPU Load is distributed between the three LED tasks:

![Alt text](doc/002_Preemptive_1.png)

The code for the tasks is as follow:
```c
static void LED1_handler(void* parameters){

//    TickType_t last_wakeup_time;
//    last_wakeup_time = xTaskGetTickCount();

    for(;;){
        SEGGER_SYSVIEW_PrintfTarget("Toggling LED1");
        GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_5);
        Delay(400);
//        vTaskDelay(pdMS_TO_TICKS(400));
//        vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(400));
//        taskYIELD();
    }
}

```
