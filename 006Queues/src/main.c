/********************************************************************************************************//**
* @file main.c
*
* @brief File containing the main function.
**/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "rcc_driver.h"
#include "flash_driver.h"
#include "pwr_driver.h"
#include "gpio_driver.h"
#include "usart_driver.h"
#include "timer_driver.h"
#include "rtc_driver.h"
#include "menu_cmd_task.h"
#include "LEDs_task.h"
#include "RTC_task.h"
#include <stdio.h>
#include <string.h>

#define DWT_CTRL  (*(volatile uint32_t*)0xE0001000)

/** @brief Variable for storing the current system core clock */
uint32_t SystemCoreClock = 8000000;
/** @brief Handler structure for Timer peripheral */
static Timer_Handle_t Timer = {0};
/** @brief Variable for storing the current tick */
static uint32_t tick = 0;

/** @brief Handler structure for USART peripheral */
static USART_Handle_t USART3Handle = {0};
/** @brief Structure for RTC configuration */
static RTC_Config_t RTC_Cfg = {0};

/** @brief Extern function for initialize the UART for SEGGER SystemView */
extern void SEGGER_UART_init(uint32_t);

/** @brief Variable for handling the menu_task_handler task */
TaskHandle_t menu_task_handle;
/** @brief Variable for handling the cmd_task_handler task */
static TaskHandle_t cmd_task_handle;
/** @brief Variable for handling the print_task_handler task */
static TaskHandle_t print_task_handle;
/** @brief Variable for handling the rtc_task_handler task */
TaskHandle_t rtc_task_handle;
/** @brief Variable for handling the LED_task_handler task */
TaskHandle_t LED_task_handle;
/** @brief Variable for handling the queue used for printing */
QueueHandle_t q_print;
/** @brief Variable for handling the queue used for managing the information received by UART */
QueueHandle_t q_data;
/** @brief Variable for storing the character received by UART */
static volatile uint8_t user_data;
/** @brief Variable for storing the invalid option message */
const char* msg_invalid = "////Invalid option////\n";
/** @brief Array for handling the LED timers */
TimerHandle_t led_timer_handle[4];
/** @brief handler for managing the RTC timer */
TimerHandle_t rtc_timer;

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
 * @brief Function to initialize USART3 peripheral.
 * @return void.
 */
static void USART3_Init(USART_Handle_t* pUSART_Handle);

/**
 * @brief Function to initialize GPIO port for the USART3 peripheral.
 * @return void.
 *
 * @note
 *      PC10 -> USART3 TX
 *      PC11 -> USART3 RX
 *      Alt function mode -> 7
 */
static void USART3_GPIOInit(void);

/**
  * @brief GPIO initialization for LEDs
  * @return None
  */
static void LEDS_GPIOInit(void);

/**
 * @brief Function for setting the intial values to the RTC_Cfg structure
 * @return None
 */
static void RTC_Time_Init(void);

/**
 * @brief Function for configure and initialize the RTC peripheral
 * @return None
 */
static void RTC_Config(void);

/**
 * @brief Task for printing a message received through a queue
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
static void print_task_handler(void* parameters);

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
    /* Init USART2 for Systemview */
    USART2_GPIOInit();
    /* Init USART3 for application */
    USART3_GPIOInit();
    USART3_Init(&USART3Handle);
    USART_IRQPriorityConfig(IRQ_NO_USART3, 6);
    USART_IRQConfig(IRQ_NO_USART3, ENABLE);
    USART_Enable(USART3, ENABLE);
    /* Init LED pins */
    LEDS_GPIOInit();
    /* Init RTC */
    RTC_Config();

    SEGGER_UART_init(500000);
    SEGGER_SYSVIEW_Conf();
    //SEGGER_SYSVIEW_Start();

    /* Create tasks */
    status = xTaskCreate(menu_task_handler, "Menu-Task", 250, NULL, 2, &menu_task_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate(print_task_handler, "Print-Task", 250, NULL, 2, &print_task_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate(cmd_task_handler, "Cmd-Task", 250, NULL, 2, &cmd_task_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate(LED_task_handler, "LED-Task", 250, NULL, 2, &LED_task_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate(rtc_task_handler, "Rtc-Task", 250, NULL, 2, &rtc_task_handle);
    configASSERT(status == pdPASS);
    /* Create queues */
    q_print = xQueueCreate(10, sizeof(size_t));
    configASSERT(q_print != NULL);
    q_data = xQueueCreate(10, sizeof(char));
    configASSERT(q_data != NULL);
    /* Create software timers for LEDs effect, the id for the timers is a number between 1 and 4 */
    for(uint8_t i = 0; i < 4; i++){
        led_timer_handle[i] = xTimerCreate("LED_timer",
                                           pdMS_TO_TICKS(500),
                                           pdTRUE,
                                           (void*)(i+1),
                                           led_effect_callback);
    }
    /* Create software timer for RTC */
    rtc_timer = xTimerCreate ("rtc_report_timer", pdMS_TO_TICKS(1000), pdTRUE,NULL, rtc_report_callback);

    (void)USART_ReceiveDataIT(&USART3Handle, (uint8_t*)&user_data, 1);

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

static void USART3_GPIOInit(void){

    GPIO_Handle_t USARTPins;

    memset(&USARTPins, 0, sizeof(USARTPins));

    USARTPins.pGPIOx = GPIOC;
    USARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    USARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    USARTPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    USARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    USARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

    /* USART3 TX */
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    GPIO_Init(&USARTPins);

    /* USART3 RX */
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
    GPIO_Init(&USARTPins);
}

static void USART3_Init(USART_Handle_t* pUSART_Handle){

    memset(pUSART_Handle, 0, sizeof(*pUSART_Handle));

    pUSART_Handle->pUSARTx = USART3;
    pUSART_Handle->USART_Config.USART_Baud = USART_STD_BAUD_115200;
    pUSART_Handle->USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
    pUSART_Handle->USART_Config.USART_Mode = USART_MODE_TXRX;
    pUSART_Handle->USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    pUSART_Handle->USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    pUSART_Handle->USART_Config.USART_ParityControl = USART_PARITY_DISABLE;

    USART_Init(pUSART_Handle);
}

static void LEDS_GPIOInit(void){

    GPIO_Handle_t LEDSPins;

    memset(&LEDSPins, 0, sizeof(LEDSPins));

    LEDSPins.pGPIOx = GPIOC;
    LEDSPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    LEDSPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    LEDSPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PULL;
    LEDSPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    LEDSPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&LEDSPins);
    LEDSPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&LEDSPins);
    LEDSPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&LEDSPins);
    LEDSPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIO_Init(&LEDSPins);
}

static void RTC_Time_Init(void){

    RTC_Cfg.RTC_HoursFormat = RTC_AM_PM;
    RTC_Cfg.RTC_Time.SecondUnits = 0;
    RTC_Cfg.RTC_Time.SecondTens = 5;
    RTC_Cfg.RTC_Time.MinuteUnits = 9;
    RTC_Cfg.RTC_Time.MinuteTens = 5;
    RTC_Cfg.RTC_Time.HourUnits = 1;
    RTC_Cfg.RTC_Time.HourTens = 1;
    RTC_Cfg.RTC_Time.PM = 1;
    RTC_Cfg.RTC_Date.YearUnits = 8;
    RTC_Cfg.RTC_Date.YearTens = 9;
    RTC_Cfg.RTC_Date.MonthUnits = 2;
    RTC_Cfg.RTC_Date.MonthTens = 1;
    RTC_Cfg.RTC_Date.DateUnits = 1;
    RTC_Cfg.RTC_Date.DateTens = 3;
}

static void RTC_Config(void){

    /* Turn on required input clock */
    RCC->CSR |= (1 << 0);
    while(!(RCC->CSR & (1 << 1)));

    /* Select clock source */
    RTC_ClkSource(RCC_LSI_SOURCE);

    RTC_PerClkCtrl(ENABLE);

    RTC_Time_Init();

    RTC_Init(RTC_Cfg);
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
    if (wait < 0xFFFFFFFF){
        wait += 1;
    }

    while((Get_Tick() - tickstart) < wait);
}

static void print_task_handler(void* parameters){

    uint32_t *msg;

    for(;;){
        xQueueReceive(q_print, &msg, portMAX_DELAY);
        (void)USART_SendData(&USART3Handle, (uint8_t*)msg, strlen((char*)msg));
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

void USART3_Handler(void){

    USART_IRQHandling(&USART3Handle);
}

void USART_ApplicationEventCallback(USART_Handle_t* pUSART_Handle, uint8_t app_event){

    if(app_event == USART_EVENT_RX_CMPLT){
        uint8_t dummy;

        if(!xQueueIsQueueFullFromISR(q_data)){
            xQueueSendFromISR(q_data, (void*)&user_data, NULL);
        }
        else{
            if(user_data == '\r'){
                /* Put the \r character at the end of the queue */
                xQueueReceiveFromISR(q_data, (void*)&dummy, NULL);
                xQueueSendFromISR(q_data, (void*)&user_data, NULL);
            }
        }

        if(user_data == '\r'){
            xTaskNotifyFromISR(cmd_task_handle, 0, eNoAction, NULL);
        }
        (void)USART_ReceiveDataIT(&USART3Handle, (uint8_t*)&user_data, 1);
    }
    else if(app_event == USART_EVENT_TX_CMPLT){
        /* do nothing */
    }
    else{
        /* do nothing */
    }
}
