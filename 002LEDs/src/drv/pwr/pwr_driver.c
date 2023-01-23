/********************************************************************************************************//**
* @file pwr_driver.c
*
* @brief File containing the APIs for configuring the power module.
*
* Public Functions:
*       - void PWR_SetOverDrive(void)
*
* @note
*       For further information about functions refer to the corresponding header file.
**/

#include <stdint.h>
#include "pwr_driver.h"
#include "stm32f446xx.h"

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void PWR_SetOverDrive(void){
    /* Set ODEN bit to enable */
    PWR->CR |= (1 << PWR_CR_ODEN);
    /* Wait for the ODRDY flag to be set */
    while(!(PWR->CSR & (1 << PWR_CSR_ODRDY)));
    /* Switch the voltage regulator form normal mode to over-drive mode */
    PWR->CR |= (1 << PWR_CR_ODSWEN);
    /* Wait for the ODSWRDY flag to be set */
    while(!(PWR->CSR & (1 << PWR_CSR_ODSWRDY)));
}
