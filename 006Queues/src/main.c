/********************************************************************************************************//**
* @file main.c
*
* @brief File containing the main function.
**/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "rcc_driver.h"
#include "flash_driver.h"
#include "pwr_driver.h"
#include "gpio_driver.h"
#include "usart_driver.h"
#include "timer_driver.h"
#include <stdio.h>
#include <string.h>

#define DWT_CTRL  (*(volatile uint32_t*)0xE0001000)

/**
 * @brief Enum with the different states of the application
 */
typedef enum{
    sMainMenu = 0,
    sLedEffect,
    sRtcMenu,
    sRtcTimeConfig,
    sRtcDateConfig,
    sRtcReport
}state_t;

/**
 * @brief Structure for managing the received command
 */
typedef struct{
    uint8_t payload[10];    /**< Received command */
    uint8_t len;            /**< Command lenght */
}command_s;

/** @brief Variable for storing the current system core clock */
uint32_t SystemCoreClock = 8000000;
/** @brief Handler structure for Timer peripheral */
static Timer_Handle_t Timer = {0};
/** @brief Variable for storing the current tick */
static uint32_t tick = 0;

/** @brief Handler structure for USART peripheral */
USART_Handle_t USART3Handle;

/** @brief Extern function for initialize the UART for SEGGER SystemView */
extern void SEGGER_UART_init(uint32_t);

/** @brief Variable for handling the menu_task_handler task */
static TaskHandle_t menu_task_handle;
/** @brief Variable for handling the cmd_task_handler task */
static TaskHandle_t cmd_task_handle;
/** @brief Variable for handling the print_task_handler task */
static TaskHandle_t print_task_handle;
/** @brief Variable for handling the queue used for printing */
static QueueHandle_t q_print;
/** @brief Variable for handling the queue used for managing the information received by UART */
static QueueHandle_t q_data;
/** @brief Variable for storing the character received by UART */
static volatile uint8_t user_data;
/** @brief Variable for storing and managing the possible states of the application */
static state_t curr_state = sMainMenu;

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
 * @brief Task for printing the starting menu and managing the received command.
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
static void menu_task_handler(void* parameters);

/**
 * @brief Task for managing a received command.
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
static void cmd_task_handler(void* parameters);

/**
 * @brief Task for printing a message received through a queue
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
static void print_task_handler(void* parameters);

/**
 * @brief Function for notifying the regarding task depending on the received command
 * @return None
 */
static void process_command(void);

/**
 * @brief Function for extracting the command value from the data queue. The command is finished by a '\0'
 * @param[out] cmd is a pointer to the extracted command
 * @return None
 */
static uint8_t extract_command(command_s* cmd);

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
    /* Create queues */
    q_print = xQueueCreate(10, sizeof(size_t));
    configASSERT(q_print != NULL);
    q_data = xQueueCreate(10, sizeof(char));
    configASSERT(q_data != NULL);

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

static void menu_task_handler(void* parameters){

    uint32_t cmd_addr;
    command_s* cmd;
    uint8_t option;
    const char* msg_menu = "\n========================\n"
                         "|         Menu         |\n"
                         "========================\n"
                         "LED effect    ----> 0\n"
                         "Date and time ----> 1\n"
                         "Exit          ----> 2\n"
                         "Enter your choice here : ";

    for(;;){
        /* Print menu */
        xQueueSend(q_print, &msg_menu, portMAX_DELAY);
        /* Wait for commands */
        xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
        cmd = (command_s*)cmd_addr;
    }
}

static void print_task_handler(void* parameters){

    uint32_t *msg;

    for(;;){
        xQueueReceive(q_print, &msg, portMAX_DELAY);
        (void)USART_SendDataIT(&USART3Handle, (uint8_t*)msg, strlen((char*)msg));
    }
}

static void cmd_task_handler(void* parameters){

    BaseType_t ret;

    for(;;){
        ret = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        if(ret == pdTRUE){
            process_command();
        }
    }
}

static void process_command(void){

    command_s cmd;

    extract_command(&cmd);

    switch(curr_state){
        case sMainMenu:
            xTaskNotify(menu_task_handle, (uint32_t)&cmd, eSetValueWithOverwrite);
            break;
        case sLedEffect:
//            xTaskNotify(LED_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
            break;
        case sRtcMenu:
        case sRtcTimeConfig:
        case sRtcDateConfig:
        case sRtcReport:
//            xTaskNotify(rtc_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
            break;
        default:
            break;
    }
}

static uint8_t extract_command(command_s* cmd){

    uint8_t item;
    BaseType_t status;
    uint8_t i = 0;

    status = uxQueueMessagesWaiting(q_data);
    if(!status){return 1;}

    do{
        status = xQueueReceive(q_data, &item, 0);
        if(status == pdTRUE){
            cmd->payload[i++] = item;
        }
    }while(item != '\r');

    cmd->payload[i-1] = '\0';
    cmd ->len = i-1;

    return 0;
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
