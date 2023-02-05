/********************************************************************************************************//**
* @file menu_cmd.h
*
* @brief Header file containing the prototypes of the APIs for managing the main menu and the received
* commands.
*
* Public Functions:
*       - void    void menu_task_handler(void* parameters)
*       - void    void cmd_task_handler(void* parameters)
*/

#ifndef MENU_CMD_H
#define MENU_CMD_H

#include <stdint.h>

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

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Task for printing the starting menu and managing the received command.
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
void menu_task_handler(void* parameters);

/**
 * @brief Task for managing a received command.
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
void cmd_task_handler(void* parameters);

#endif /* MENU_CMD_H */
