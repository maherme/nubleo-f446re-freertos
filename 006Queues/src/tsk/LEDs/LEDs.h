/********************************************************************************************************//**
* @file LEDs.h
*
* @brief Header file containing the prototypes of the APIs for managing the task regarding the control of
* LEDs
*
* Public Functions:
*       - void LED_task_handler(void* parameters)
*       - void led_effect_callback(TimerHandle_t xTimer)
*/

#ifndef LEDs_H
#define LEDs_H

#include "FreeRTOS.h"
#include "timers.h"

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Task for printing the LEDs control menu and managing the received command.
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
void LED_task_handler(void* parameters);

/**
 * @brief Callback function for managing the effect of the LEDs when the timer expires.
 * @param[out] xTimer is the timer handler.
 * @return None
 */
void led_effect_callback(TimerHandle_t xTimer);

#endif /* LEDs_H */
