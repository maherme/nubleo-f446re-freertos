/********************************************************************************************************//**
* @file RTC_task.h
*
* @brief Header file containing the prototypes of the APIs for managing the task regarding the real time
* clock.
*
* Public Functions:
*       - void rtc_task_handler(void* parameters)
*       - void rtc_report_callback(TimerHandle_t xTimer)
*/

#ifndef RTC_H
#define RTC_H

#include "FreeRTOS.h"
#include "timers.h"

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Task for printing the RTC control menu and managing the received command.
 * @param[in] parameters is a pointer to the input parameters to the task
 * @return None
 */
void rtc_task_handler(void* parameters);

/**
 * @brief Callback function for reporting information of the RTC when the timer expires.
 * @param[out] xTimer is the timer handler.
 * @return None
 */
void rtc_report_callback(TimerHandle_t xTimer);

#endif /* RTC_H  */
