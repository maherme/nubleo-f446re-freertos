/********************************************************************************************************//**
* @file main.c
*
* @brief File containing the main function.
**/

#include "FreeRTOS.h"
#include "task.h"
#include "rcc_driver.h"
#include "flash_driver.h"
#include "pwr_driver.h"
#include "gpio_driver.h"
#include "usart_driver.h"
#include "timer_driver.h"
#include <stdio.h>
#include <string.h>

#define DWT_CTRL  (*(volatile uint32_t*)0xE0001000)

/** @brief Variable for storing the current system core clock */
uint32_t SystemCoreClock = 8000000;
/** @brief Handler structure for Timer peripheral */
static Timer_Handle_t Timer = {0};
/** @brief Variable for storing the current tick */
static uint32_t tick = 0;
/** @brief Variables for handling the FreeRTOS tasks */
static TaskHandle_t task1_handle;
static TaskHandle_t task2_handle;
static volatile BaseType_t status_button = 0;

/** @brief Extern function for initialize the UART for SEGGER SystemView */
extern void SEGGER_UART_init(uint32_t);

/***********************************************************************************************************/
/*                                       Static Function Prototypes                                        */
/***********************************************************************************************************/

/**
  * @brief System clock configuration
  * @return None
  */
static void RCC_Config(void);

/**
  * @brief Timer 6 peripheral configuration
  * @return None
  */
static void Timer6_Config(void);

/**
  * @brief Increment the tick variable each interruption of the timer (TIM6).
  * @return None
  */
static void Inc_Tick(void);

/**
  * @brief Return the tick variable
  * @return current tick value
  */
static uint32_t Get_Tick(void);

/**
  * @brief Generate a delay in milliseconds
  * @param[in] Delay in milliseconds
  * @return None
  */
static void Delay(uint32_t Delay);

/**
  * @brief GPIO initialization for USART2
  * @return None
  */
static void USART2_GPIOInit(void);

/**
  * @brief GPIO initialization for LEDs
  * @return None
  */
static void LEDS_GPIOInit(void);

/**
  * @brief GPIO initialization for button
  * @return None
  */
static void Button_GPIOInit(void);

/**
  * @brief Task handler to manage LED1
  * @param[in] parameters is a pointer to the input parameters to the task
  * @return None
  */
static void Task1_handler(void* parameters);

/**
  * @brief Task handler to manage LED2
  * @param[in] parameters is a pointer to the input parameters to the task
  * @return None
  */
static void Task2_handler(void* parameters);

/**
  * @brief Function for inverting the priority of the tasks
  * @return None
  */
static void switch_priority(void);

/***********************************************************************************************************/
/*                                       Main Function                                                     */
/***********************************************************************************************************/

int main(void)
{
    BaseType_t status;

    /* Configure the system clock */
    RCC_Config();
    SystemCoreClock = RCC_GetPLLOutputClock();

    /* Enable the CYCNT counter */
    DWT_CTRL |= (1 << 0);

    /* Init timer 6 */
    Timer6_Config();
    /* Init LED pins */
    LEDS_GPIOInit();
    /* Init button pin */
    Button_GPIOInit();
    /* IRQ configuration for button */
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIORITY6);
    GPIO_IRQConfig(IRQ_NO_EXTI15_10, ENABLE);
    /* Init USART */
    USART2_GPIOInit();

    SEGGER_UART_init(500000);
    SEGGER_SYSVIEW_Conf();
    //SEGGER_SYSVIEW_Start();

    /* Create tasks */
    status = xTaskCreate(Task1_handler, "Task1", 200, NULL, 2, &task1_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate(Task2_handler, "Task2", 200, NULL, 3, &task2_handle);
    configASSERT(status == pdPASS);
    /* Start the freeRTOS scheduler */
    vTaskStartScheduler();

    /* Infinite loop */
    while (1)
    {
    }
}

/***********************************************************************************************************/
/*                                       Static Function Definitions                                       */
/***********************************************************************************************************/

static void RCC_Config(void)
{
    RCC_Config_t RCC_Cfg = {0};

    /* Set FLASH latency according to clock frequency (see reference manual) */
    Flash_SetLatency(5);

    /* Set the over drive mode */
    PWR_PCLK_EN();
    PWR_SetOverDrive();

    /* Set configuration */
    RCC_Cfg.clk_source = RCC_CLK_SOURCE_PLL_P;
    RCC_Cfg.pll_source = PLL_SOURCE_HSE;
    RCC_Cfg.ahb_presc = AHB_NO_PRESC;
    RCC_Cfg.apb1_presc = APB1_PRESC_4;
    RCC_Cfg.apb2_presc = APB2_PRESC_2;
    RCC_Cfg.pll_n = 180;
    RCC_Cfg.pll_m = 4;
    RCC_Cfg.pll_p = PLL_P_2;
    /* Set clock */
    RCC_SetSystemClock(RCC_Cfg);
}

static void USART2_GPIOInit(void){

    GPIO_Handle_t USARTPins;

    memset(&USARTPins, 0, sizeof(USARTPins));

    USARTPins.pGPIOx = GPIOA;
    USARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    USARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    USARTPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PULL;
    USARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    USARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

    /* USART2 TX */
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&USARTPins);

    /* USART2 RX */
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&USARTPins);
}

static void LEDS_GPIOInit(void){

    GPIO_Handle_t GpioLed;

    memset(&GpioLed, 0, sizeof(GpioLed));

    GpioLed.pGPIOx = GPIOA;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PULL;

    GPIO_Init(&GpioLed);
}

static void Button_GPIOInit(void){

    GPIO_Handle_t GpioBtn;

    memset(&GpioBtn, 0, sizeof(GpioBtn));

    GpioBtn.pGPIOx = GPIOC;
    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
    GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

    GPIO_Init(&GpioBtn);
}

static void Timer6_Config(void){

    Timer.tim_num = TIMER6;
    Timer.pTimer = TIM6;
    Timer.prescaler = 8;
    Timer.period = 10000 - 1;

    Timer_Init(&Timer);
    Timer_IRQConfig(IRQ_NO_TIM6_DAC, ENABLE);
    Timer_Start(&Timer);
}

static void Inc_Tick(void){
    tick++;
}

static uint32_t Get_Tick(void){
    return tick;
}

__attribute__((unused)) static void Delay(uint32_t Delay){

  uint32_t tickstart = Get_Tick();
  uint32_t wait = Delay;

  /* Guarantee minimum wait */
  if (wait < 0xFFFFFFFF)
  {
    wait += 1;
  }

  while((Get_Tick() - tickstart) < wait);
}

static void Task1_handler(void* parameters){

    for(;;){
        SEGGER_SYSVIEW_PrintfTarget("LED1 Task");
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
        Delay(100);
        switch_priority();
    }
}

static void Task2_handler(void* parameters){

    for(;;){
        SEGGER_SYSVIEW_PrintfTarget("LED2 Task");
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
        Delay(1000);
        switch_priority();
    }
}

static void switch_priority(void){

    UBaseType_t p1, p2;
    xTaskHandle t1, t2, current_t;
    BaseType_t switch_priority = 0;

    portENTER_CRITICAL();
    if(status_button){
        status_button = 0;
        switch_priority = 1;
    }
    portEXIT_CRITICAL();

    if(switch_priority){
        t1 = xTaskGetHandle("Task1");
        t2 = xTaskGetHandle("Task2");
        p1 = uxTaskPriorityGet(t1);
        p2 = uxTaskPriorityGet(t2);
        current_t = xTaskGetCurrentTaskHandle();
        if(current_t == t1){
            vTaskPrioritySet(t1, p2);
            vTaskPrioritySet(t2, p1);
        }
        else{
          vTaskPrioritySet(t2, p1);
          vTaskPrioritySet(t1, p2);
        }
    }
}

/***********************************************************************************************************/
/*                               Weak Function Overwrite Definitions                                       */
/***********************************************************************************************************/

void TIM6_DAC_Handler(void){
    Timer_IRQHandling(&Timer);
}

void Timer_ApplicationEventCallback(Timer_Num_t tim_num, Timer_Event_t timer_event){

    if(timer_event == TIMER_UIF_EVENT){
        if(tim_num == TIMER6){
            Inc_Tick();
        }
    }
    else{
        /* do nothing */
    }
}

void EXTI15_10_Handler(void){

    GPIO_IRQHandling(GPIO_PIN_NO_13);
    traceISR_ENTER();
    status_button = 1;
    traceISR_EXIT();
}
