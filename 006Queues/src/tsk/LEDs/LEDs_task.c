/********************************************************************************************************//**
* @file LEDs_task.c
*
* @brief File containing the APIs for managing the task regarding the control of LEDs
*
* Public Functions:
*       - void LED_task_handler(void* parameters)
*       - void led_effect_callback(TimerHandle_t xTimer)
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include "LEDs_task.h"
#include "menu_cmd_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "timers.h"
#include "gpio_driver.h"
#include <stdint.h>
#include <string.h>

/** @brief Variable for handling the queue used for printing */
extern QueueHandle_t q_print;
/** @brief Variable for storing and managing the possible states of the application */
extern state_t curr_state;
/** @brief Variable for storing the invalid option message */
extern const char* msg_invalid;
/** @brief Variable for handling the menu_task_handler task */
extern TaskHandle_t menu_task_handle;
/** @brief Array for handling the LED timers */
extern TimerHandle_t led_timer_handle[4];

/***********************************************************************************************************/
/*                                       Static Function Prototypes                                        */
/***********************************************************************************************************/

/**
 * @brief Function for stopping all the effects for the LEDs
 * @return None
 */
static void led_effect_stop(void);

/**
 * @brief Function to select an effect for the LEDs
 * @param[in] effect is the effect number, can be from 1 to 4
 * @return None
 */
static void led_effect(uint8_t effect);

/**
 * @brief Function for creating the LED effect 1: all LEDs blink at the same time.
 * @return None
 */
static void led_effect1(void);

/**
 * @brief Function for creating the LED effect 2: even or odd LEDs blink at the same time.
 * @return None
 */
static void led_effect2(void);

/**
 * @brief Function for creating the LED effect 3: LEDs blink from right to left in a shift.
 * @return None
 */
static void led_effect3(void);

/**
 * @brief Function for creating the LED effect 4: LEDs blink from left to right in a shift.
 * @return None
 */
static void led_effect4(void);

/**
 * @brief Function for setting all LEDs to off.
 * @return None
 */
static void turn_off_all_leds(void);

/**
 * @brief Function for setting all LEDs to on.
 * @return None
 */
static void turn_on_all_leds(void);

/**
 * @brief Function for setting even LEDs to on and odd LEDs to off.
 * @return None
 */
static void turn_on_even_leds(void);

/**
 * @brief Function for setting odd LEDs to on and even LEDs to off.
 * @return None
 */
static void turn_on_odd_leds(void);

/**
 * @brief Function for setting one LED to on and the rest to off
 * @param[in] The LED is selected using 4 lsb of the value
 *            0000_0001 is for the first LED
 *            0000_0010 is for the second LED
 *            0000_0100 is for the third LED
 *            0000_1000 is for the last LED.
 * @return None
 */
static void led_control(uint8_t value);

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void LED_task_handler(void* parameters){

    uint32_t cmd_addr;
    command_s* cmd;
    const char* msg_led = "========================\n"
                        "|      LED Effect     |\n"
                        "========================\n"
                        "(none,e1,e2,e3,e4)\n"
                        "Enter your choice here : ";

    for(;;){
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        /* Print menu */
        xQueueSend(q_print, &msg_led, portMAX_DELAY);
        /* Wait for commands */
        xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
        cmd = (command_s*)cmd_addr;

        if(cmd->len <= 4){
            if(!strcmp((char*)cmd->payload,"none")){
                led_effect_stop();
            }
            else if(!strcmp((char*)cmd->payload, "e1")){
                led_effect(1);
            }
            else if(!strcmp((char*)cmd->payload, "e2")){
                led_effect(2);
            }
            else if(!strcmp((char*)cmd->payload, "e3")){
                led_effect(3);
            }
            else if(!strcmp((char*)cmd->payload, "e4")){
                led_effect(4);
            }
            else{
                xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
            }
        }
        else{
            xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
        }

        curr_state = sMainMenu;
        xTaskNotify(menu_task_handle, 0, eNoAction);
    }
}

void led_effect_callback(TimerHandle_t xTimer){

    uint32_t id = (uint32_t)pvTimerGetTimerID(xTimer);

    /* The id of the timers for the LEDs is a number between 1 and 4 */
    switch(id){
        case 1:
            led_effect1();
            break;
        case 2:
            led_effect2();
            break;
        case 3:
            led_effect3();
            break;
        case 4:
            led_effect4();
            break;
        default:
            break;
    }
}

/***********************************************************************************************************/
/*                                       Static Function Definitions                                       */
/***********************************************************************************************************/

static void led_effect_stop(void){

    for(uint8_t i = 0; i < 4; i++){
        xTimerStop(led_timer_handle[i], portMAX_DELAY);
    }
}

static void led_effect(uint8_t effect){

    led_effect_stop();
    xTimerStart(led_timer_handle[effect-1], portMAX_DELAY);
}

static void led_effect1(void){

    static uint8_t flag = 1;
    (flag ^= 1) ? turn_off_all_leds() : turn_on_all_leds();
}

static void led_effect2(void){

    static uint8_t flag = 1;
    (flag ^= 1) ? turn_on_even_leds() : turn_on_odd_leds();
}

static void led_effect3(void){

    static uint8_t i = 0;
    led_control(0x1 << (i++ % 4));
}

static void led_effect4(void){

    static uint8_t i = 0;
    led_control(0x08 >> (i++ % 4));
}

static void turn_off_all_leds(void){

    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_5, DISABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_6, DISABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_7, DISABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_8, DISABLE);
}

static void turn_on_all_leds(void){

    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_5, ENABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_6, ENABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_7, ENABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_8, ENABLE);
}

static void turn_on_even_leds(void){

    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_5, DISABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_6, ENABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_7, DISABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_8, ENABLE);
}

static void turn_on_odd_leds(void){

    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_5, ENABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_6, DISABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_7, ENABLE);
    GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_NO_8, DISABLE);
}

static void led_control(uint8_t value){

    for(uint8_t i = 0; i < 4; i++){
        GPIO_WriteToOutputPin(GPIOC, (GPIO_PIN_NO_5 + i), ((value >> i)&0x1));
    }
}
