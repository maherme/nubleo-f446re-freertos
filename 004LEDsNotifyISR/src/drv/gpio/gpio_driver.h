/********************************************************************************************************//**
* @file gpio_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the GPIO peripheral.
*
* Public Functions:
*       - void     GPIO_Init(GPIO_Handle_t* pGPIOHandle) 
*       - void     GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
*       - void     GPIO_PerClkCtrl(GPIO_RegDef_t* pGPIOx, uint8_t en_or_di)
*       - uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number)
*       - uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx)
*       - void     GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number, uint8_t value)
*       - void     GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value)
*       - void     GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number)
*       - void     GPIO_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di)
*       - void     GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
*       - void     GPIO_IRQHandling(uint8_t pin_number)
*/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include "stm32f446xx.h"

/**
 * @defgroup GPIO_Number possible GPIO pin number.
 * @{
 */
#define GPIO_PIN_NO_0       0   /**< @brief GPIO pin number 0 */
#define GPIO_PIN_NO_1       1   /**< @brief GPIO pin number 1 */
#define GPIO_PIN_NO_2       2   /**< @brief GPIO pin number 2 */
#define GPIO_PIN_NO_3       3   /**< @brief GPIO pin number 3 */
#define GPIO_PIN_NO_4       4   /**< @brief GPIO pin number 4 */
#define GPIO_PIN_NO_5       5   /**< @brief GPIO pin number 5 */
#define GPIO_PIN_NO_6       6   /**< @brief GPIO pin number 6 */
#define GPIO_PIN_NO_7       7   /**< @brief GPIO pin number 7 */
#define GPIO_PIN_NO_8       8   /**< @brief GPIO pin number 8 */
#define GPIO_PIN_NO_9       9   /**< @brief GPIO pin number 9 */
#define GPIO_PIN_NO_10      10  /**< @brief GPIO pin number 10 */
#define GPIO_PIN_NO_11      11  /**< @brief GPIO pin number 11 */
#define GPIO_PIN_NO_12      12  /**< @brief GPIO pin number 12 */
#define GPIO_PIN_NO_13      13  /**< @brief GPIO pin number 13 */
#define GPIO_PIN_NO_14      14  /**< @brief GPIO pin number 14 */
#define GPIO_PIN_NO_15      15  /**< @brief GPIO pin number 15 */
/** @} */

/**
 * @defgroup GPIO_Mode possible GPIO pin modes.
 * @{
 */
#define GPIO_MODE_IN        0   /**< @brief Input direction mode */
#define GPIO_MODE_OUT       1   /**< @brief General purpose output mode */
#define GPIO_MODE_ALTFN     2   /**< @brief Alternate function mode */
#define GPIO_MODE_ANALOG    3   /**< @brief Analog mode */
#define GPIO_MODE_IT_FT     4   /**< @brief Interrupt falling edge trigger */
#define GPIO_MODE_IT_RT     5   /**< @brief Interrupt rising edge trigger */
#define GPIO_MODE_IT_RFT    6   /**< @brief Interrupt rising and falling edge trigger */

/** @} */

/**
 * @defgroup GPIO_OPType possible GPIO pin output types.
 * @{
 */
#define GPIO_OP_TYPE_PP     0   /**< @brief Output push-pull configuration */
#define GPIO_OP_TYPE_OD     1   /**< @brief Output open-drain configuration */
/** @} */

/**
 * @defgroup GPIO_Speed possible GPIO pin output speed.
 * @{
 */
#define GPIO_SPEED_LOW      0   /**< @brief Low Speed */
#define GPIO_SPEED_MEDIUM   1   /**< @brief Medium Speed */
#define GPIO_SPEED_FAST     2   /**< @brief Fast Speed */
#define GPIO_SPEED_HIGH     3   /**< @brief High Speed */
/** @} */

/**
 * @defgroup GPIO_Pull GPIO pin pull-up/pull-down configuration.
 * @{
 */
#define GPIO_NO_PULL        0   /**< @brief No pull-up/pull-down.*/
#define GPIO_PIN_PU         1   /**< @brief Pull-up. */
#define GPIO_PIN_PD         2   /**< @brief Pull-down. */
/** @} */

/**
 * @brief Configuration structure for a GPIO pin.
 */
typedef struct
{
    uint8_t GPIO_PinNumber;         /**< Possible values from @ref GPIO_Number */
    uint8_t GPIO_PinMode;           /**< Possible values from @ref GPIO_Mode */
    uint8_t GPIO_PinSpeed;          /**< Possible values from @ref GPIO_Speed */
    uint8_t GPIO_PinPuPdControl;    /**< Possible values from @ref GPIO_Pull */
    uint8_t GPIO_PinOPType;         /**< Possible values from @ref GPIO_OPType */
    uint8_t GPIO_PinAltFunMode;     /**< Possible values for alternate functionality */
}GPIO_PinConfig_t;

/**
 * @brief Handle structure for a GPIO pin.
 */
typedef struct
{
    GPIO_RegDef_t* pGPIOx;              /**< Base address of the GPIO port to which the pin belongs */
    GPIO_PinConfig_t GPIO_PinConfig;    /**< GPIO pin configuration settings */
}GPIO_Handle_t;

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to initialize GPIO port.
 * @param[in] pGPIOHandle handle structure for the GPIO pin.
 * @return void
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle);

/**
 * @brief Function to reset all register of a GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @return void
 */
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);

/**
 * @brief Function to control the peripheral clock of the GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @param[in] en_or_di for enable or disable.
 * @return void
 */
void GPIO_PerClkCtrl(GPIO_RegDef_t* pGPIOx, uint8_t en_or_di);

/**
 * @brief Function to read from an input pin of the GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @param[in] pin_number the pin number of the port.
 * @return value of the pin: 1 or 0.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number);

/**
 * @brief Function to read the GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @return value of the all pins of the GPIO port.
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx);

/**
 * @brief Function to write to output pin of the GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @param[in] pin_number the pin number of the port.
 * @param[in] value to write to output in the pin.
 * @return void
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number, uint8_t value);

/**
 * @brief Function to write to output of the entire GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @param[in] value to write to output in the port.
 * @return void
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value);

/**
 * @brief Function to toggle the output pin of the GPIO port.
 * @param[in] pGPIOx the base address of the GPIOx peripheral port.
 * @param[in] pin_number the pin number of the port.
 * @return void
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number);

/**
 * @brief Function to configure the IRQ number of the GPIO pin.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] en_or_di for enable or disable.
 * @return void
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di);

/**
 * @brief Function to configure the IRQ number of the GPIO pin.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] IRQPriority priority of the interrupt.
 * @return void
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/**
 * @brief Function to handle the interrupt of the GPIO pin.
 * @param[in] pin_number the pin number of the port.
 * @return void
 */
void GPIO_IRQHandling(uint8_t pin_number);

#endif
