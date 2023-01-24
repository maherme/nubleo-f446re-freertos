/********************************************************************************************************//**
* @file timer_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the TIM peripheral.
*
* Public Functions:
*       - void     Timer_Init(Timer_Handle_t* Timer_Handle)
*       - void     Timer_Start(Timer_Handle_t* Timer_Handle)
*       - void     Timer_Stop(Timer_Handle_t* Timer_Handle)
*       - void     Timer_ICInit(Timer_Handle_t* Timer_Handle, IC_Handle_t IC_Handle, CC_Channel_t channel)
*       - uint32_t Timer_CCGetValue(Timer_Handle_t* Timer_Handle, CC_Channel_t channel)
*       - void     Timer_CCSetValue(Timer_Handle_t* Timer_Handle, CC_Channel_t channel, uint32_t value)
*       - void     Timer_PerClkCtrl(Timer_Num_t timer_num, uint8_t en_or_di)
*       - void     Timer_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di)
*       - void     Timer_IRQHandling(Timer_Handle_t* Timer_Handle)
*       - void     Timer_ApplicationEventCallback(void)
*/

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdint.h>
#include "stm32f446xx.h"

/**
 * @defgroup CC_POLARITY Capture/Compare polarity.
 * @{
 */
#define CC_POLARITY_RISING      0x00    /**< @brief Trigger in rising edge */
#define CC_POLARITY_FALLING     0x01    /**< @brief Trigger in falling edge */
#define CC_POLARITY_BOTH        0x05    /**< @brief Trigger in rising and falling edge */
/** @} */

/**
 * @defgroup CC_SELECT Capture/Compare selection input/output.
 * @{
 */
#define CC_OUTPUT       0x00    /**< @brief Capture compare channel configure as output */
#define CC_IN_TI1       0x01    /**< @brief Capture compare channel configure as input, mapped on TI1 */
#define CC_IN_TI2       0x02    /**< @brief Capture compare channel configure as input, mapped on TI2 */
#define CC_IN_TRC       0x03    /**< @brief Capture compare channel configure as input, mapped on TRC */
/** @} */

/**
 * @defgroup IC_PRESCALER Input capture prescaler value.
 * @{
 */
#define IC_NO_PRESCALER     0x00    /**< @brief No prescaler value */
#define IC_PRESCALER_2      0X01    /**< @brief Capture is done once every 2 events */
#define IC_PRESCALER_4      0x02    /**< @brief Capture is done once every 4 events */
#define IC_PRESCALER_8      0x03    /**< @brief Capture is done once every 8 events */
/** @} */

/**
 * @defgroup OC_MODE Output compare mode.
 * @{
 */
#define OC_MODE_TIMING          0x00    /**< @brief Timing mode */
#define OC_MODE_ACTIVE          0x01    /**< @brief Active mode */
#define OC_MODE_INACTIVE        0x02    /**< @brief Inactive mode */
#define OC_MODE_TOGGLE          0x03    /**< @brief Toggle mode */
#define OC_MODE_FORCED_INACTIVE 0x04    /**< @brief Forced inactive mode */
#define OC_MODE_FORCED_ACTIVE   0x05    /**< @brief Forced active mode */
#define OC_MODE_PWM1            0x06    /**< @brief PWM mode 1 */
#define OC_MODE_PWM2            0x07    /**< @brief PWM mode 2 */
/** @} */

/**
 * @defgroup OC_PRELOAD Output compare preload enable.
 * @{
 */
#define OC_PRELOAD_DISABLE      0x00    /**< @brief Preload disable */
#define OC_PRELOAD_ENABLE       0x01    /**< @brief Preload enable */
/** @} */

/**
 * @brief Enum for selecting timer peripheral.
 */
typedef enum
{
    TIMER1,     /**< TIM1 Advanced-control timer */
    TIMER2,     /**< TIM2 General-purpose timer */
    TIMER3,     /**< TIM3 General-purpose timer */
    TIMER4,     /**< TIM4 General-purpose timer */
    TIMER5,     /**< TIM5 General-purpose timer */
    TIMER6,     /**< TIM6 Basic timer */
    TIMER7,     /**< TIM7 Basic timer */
    TIMER8,     /**< TIM8 Advanced-control timer */
    TIMER9,     /**< TIM9 General-purpose timer */
    TIMER10,    /**< TIM10 General-purpose timer */
    TIMER11,    /**< TIM11 General-purpose timer */
    TIMER12,    /**< TIM12 General-purpose timer */
    TIMER13,    /**< TIM13 General-purpose timer */
    TIMER14     /**< TIM14 General purpose timer */
}Timer_Num_t;

/**
 * @brief Enum for selecting capture / compare channel.
 */
typedef enum
{
    CHANNEL1,   /**< Channel 1 */
    CHANNEL2,   /**< Channel 2 */
    CHANNEL3,   /**< Channel 3 */
    CHANNEL4    /**< Channel 4 */
}CC_Channel_t;

/**
 * @brief Enum for notifying the diferent interrupt events.
 */
typedef enum
{
    TIMER_UIF_EVENT,    /**< Update interrupt event */
    TIMER_CC1IF_EVENT,  /**< Capture/Compare 1 interrupt event */
    TIMER_CC2IF_EVENT,  /**< Capture/Compare 2 interrupt event */
    TIMER_CC3IF_EVENT,  /**< Capture/Compare 3 interrupt event */
    TIMER_CC4IF_EVENT   /**< Capture/Compare 4 interrupt event */
}Timer_Event_t;

/**
 * @brief Handle structure for timer peripheral.
 */
typedef struct
{
    Timer_Num_t tim_num;        /**< TIMx peripheral */
    TIM_RegDef_t* pTimer;       /**< Base address of the timer peripheral */
    uint16_t prescaler;         /**< Prescaler value */
    uint32_t period;            /**< Period value */
}Timer_Handle_t;

/**
 * @brief Configuration structure for input capture timer peripheral.
 */
typedef struct
{
    uint8_t ic_polarity;        /**< Possible values from @ref IC_POLARITY */
    uint8_t ic_select;          /**< Possible values from @ref CC_SELECT */
    uint8_t ic_prescaler;       /**< Possible values from @ref IC_PRESCALER */
    uint8_t ic_filter;          /**< Input capture filter (0 means no filter) */
}IC_Handle_t;

/**
 * @brief Configuration structure for output capture timer peripheral.
 */
typedef struct
{
    uint8_t oc_mode;            /**< Possible values from @ref OC_MODE */
    uint8_t oc_polarity;        /**< Possible values from @ref CC_POLARITY */
    uint32_t oc_pulse;          /**< Pulse count duration */
    uint8_t oc_preload;         /**< Possible values from @ref OC_PRELOAD */
}OC_Handle_t;

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to initialize the timer peripheral.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @return void
 */
void Timer_Init(Timer_Handle_t* Timer_Handle);

/**
 * @brief Function to start working the timer peripheral.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @return void
 */
void Timer_Start(Timer_Handle_t* Timer_Handle);

/**
 * @brief Function to stop working the timer peripheral.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @return void
 */
void Timer_Stop(Timer_Handle_t* Timer_Handle);

/**
 * @brief Function to initialize the input capture channel of a timer peripheral.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @param[in] IC_Handle handle configuration for input capture.
 * @param[in] channel channel number to be configured.
 * @return void
 */
void Timer_ICInit(Timer_Handle_t* Timer_Handle, IC_Handle_t IC_Handle, CC_Channel_t channel);

/**
 * @brief Function to initialize the output capture channel of a timer peripheral.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @param[in] OC_Handle handle configuration for output capture.
 * @param[in] channel channel number to be configured.
 * @return void
 */
void Timer_OCInit(Timer_Handle_t* Timer_Handle, OC_Handle_t OC_Handle, CC_Channel_t channel);

/**
 * @brief Function to get capture/compare value.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @param[in] channel channel number to be configured.
 * @return capture/compare value.
 */
uint32_t Timer_CCGetValue(Timer_Handle_t* Timer_Handle, CC_Channel_t channel);

/**
 * @brief Function to set capture/compare value.
 * @param[in] Timer_Handle handle structure for managing the timer peripheral.
 * @param[in] channel channel number to be configured.
 * @param[in] value is the value to be set.
 * @return void.
 */
void Timer_CCSetValue(Timer_Handle_t* Timer_Handle, CC_Channel_t channel, uint32_t value);

/**
 * @brief Function to control the peripheral clock of the timer peripheral.
 * @param[in] timer_num is the TIM peripheral number.
 * @param[in] en_or_di for enable or disable.
 * @return void
 */
void Timer_PerClkCtrl(Timer_Num_t timer_num, uint8_t en_or_di);

/**
 * @brief Function to configure the IRQ number of the timer peripheral.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] en_or_di for enable or disable.
 * @return void.
 */
void Timer_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di);

/**
 * @brief Function to handle the interrupt of the timer peripheral.
 * @param[in] Timer_Handle handle structure to timer peripheral.
 * @return void.
 */
void Timer_IRQHandling(Timer_Handle_t* Timer_Handle);

/**
 * @brief Function for application callback.
 * @return void.
 */
void Timer_ApplicationEventCallback(Timer_Num_t tim_num, Timer_Event_t timer_event);

#endif /* TIMER_DRIVER_H */
