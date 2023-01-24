/********************************************************************************************************//**
* @file pwr_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the power module.
*
* Public Functions:
*       - void PWR_SetOverDrive(void)
*/

#ifndef PWR_DRIVER_H
#define PWR_DRIVER_H

#include <stdint.h>
#include "stm32f446xx.h"

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to set the over drive power mode
 */
void PWR_SetOverDrive(void);

#endif
