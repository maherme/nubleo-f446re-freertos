/********************************************************************************************************//**
* @file menu_cmd.c
*
* @brief File containing the APIs for managing the main menu and the received commands.
*
* Public Functions:
*       - void menu_task_handler(void* parameters)
*       - void cmd_task_handler(void* parameters)
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include "menu_cmd.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>

/** @brief Variable for handling the menu_task_handler task */
extern TaskHandle_t menu_task_handle;
/** @brief Variable for handling the LED_task_handler task */
extern TaskHandle_t LED_task_handle;
/** @brief Variable for handling the queue used for printing */
extern QueueHandle_t q_print;
/** @brief Variable for handling the queue used for managing the information received by UART */
extern QueueHandle_t q_data;
/** @brief Variable for storing and managing the possible states of the application */
state_t curr_state = sMainMenu;
/** @brief Variable for storing the invalid option message */
extern const char* msg_invalid;

/***********************************************************************************************************/
/*                                       Static Function Prototypes                                        */
/***********************************************************************************************************/

/**
 * @brief Function for notifying the regarding task depending on the received command
 * @param[out] cmd is a pointer to the received command
 * @return None
 */
static void process_command(command_s* cmd);

/**
 * @brief Function for extracting the command value from the data queue. The command is finished by a '\0'
 * @param[out] cmd is a pointer to the extracted command
 * @return None
 */
static uint8_t extract_command(command_s* cmd);

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void menu_task_handler(void* parameters){

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

        if(cmd->len == 1){
            option = cmd->payload[0] - 48;
            switch(option){
                case 0:
                    curr_state = sLedEffect;
                    xTaskNotify(LED_task_handle, 0, eNoAction);
                    break;
                case 1:
                    curr_state = sRtcMenu;
//                    xTaskNotify(rtc_task_handle, 0, eNoAction);
                    break;
                case 2:
                    break;
                default:
                    xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
                    continue;
            }
        }
        else{
            xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
        }
        /* Wait for running again when other tasks notifies */
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
    }
}

void cmd_task_handler(void* parameters){

    BaseType_t ret;
    command_s cmd;

    for(;;){
        ret = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        if(ret == pdTRUE){
            process_command(&cmd);
        }
    }
}

/***********************************************************************************************************/
/*                                       Static Function Definitions                                       */
/***********************************************************************************************************/

static void process_command(command_s* cmd){

    extract_command(cmd);

    switch(curr_state){
        case sMainMenu:
            xTaskNotify(menu_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
            break;
        case sLedEffect:
            xTaskNotify(LED_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
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
