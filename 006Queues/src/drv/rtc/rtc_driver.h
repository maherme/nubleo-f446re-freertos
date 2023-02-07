/********************************************************************************************************//**
* @file rtc_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the RTC peripheral.
*
* Public Functions:
*       - void RTC_PerClkCtrl(uint8_t en_or_di)
*       - void RTC_ClkSource(RTC_ClkSource_t clk_source)
*       - void RTC_Init(RTC_Config_t RTC_Cfg)
*       - void RTC_SetTime(RTC_Time_t time)
*       - void RTC_GetTime(RTC_Time_t* time)
*       - void RTC_SetDate(RTC_Date_t date)
*       - void RTC_GetDate(RTC_Date_t* date)
*       - void RTC_ClearRSF(void)
*       - uint8_t RTC_GetRSF(void)
*       - void RTC_SetAlarm(RTC_Alarm_t alarm)
*       - void RTC_GetAlarm(RTC_Alarm_t* alarm)
*       - uint8_t RTC_CheckAlarm(RTC_AlarmSel_t alarm)
*       - uint8_t RTC_ClearAlarm(RTC_AlarmSel_t alarm)
*       - uint8_t RTC_DisableAlarm(RTC_AlarmSel_t alarm)
*       - void RTC_Alarm_IRQHandling(void)
*       - void RTC_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di)
*       - void RTC_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
*       - void RTC_AlarmEventCallback(RTC_AlarmSel_t alarm)
*/

#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

#include <stdint.h>

/**
 * @defgroup RTC_HoursFormat RTC possible hours format.
 * @{
 */
#define RTC_24                  0   /**< @brief 24 hour/day format */
#define RTC_AM_PM               1   /**< @brief AM/PM hour format */
/**@}*/

/**
 * @defgroup RTC_OutputSelection RTC possible values for RTC_ALARM output.
 * @{
 */
#define RTC_OUTPUT_DISABLE      0   /**< @brief Output disable */
#define RTC_OUTPUT_ALARMA       1   /**< @brief Alarm A output enable */
#define RTC_OUTPUT_ALARMB       2   /**< @brief Alarm B output enable */
#define RTC_OUTPUT_WAKEUP       3   /**< @brief Wakeup output enable */
/**@}*/

/**
 * @defgroup RTC_OutputPolarity RTC possible values for the output polarity.
 * @{
 */
#define RTC_POLARITY_HIGH       0   /**< @brief Output pin is high when ALRAF/ALRBF/WUTF is asserted */
#define RTC_POLARITY_LOW        1   /**< @brief Output pin is low when ALRAF/ALRBF/WUTF is asserted */
/**@}*/

/**
 * @defgroup RTC_OutpuType RTC possible values for the output polarity.
 * @{
 */
#define RTC_POLARITY_HIGH       0   /**< @brief Output pin is high when ALRAF/ALRBF/WUTF is asserted */
#define RTC_POLARITY_LOW        1   /**< @brief Output pin is low when ALRAF/ALRBF/WUTF is asserted */
/**@}*/

/**
 * @brief Possible options for RTC clock input source
 */
typedef enum
{
    RCC_NO_SOURCE,
    RCC_LSE_SOURCE,
    RCC_LSI_SOURCE,
    RCC_HSE_SOURCE
}RTC_ClkSource_t;

/**
 * @brief Possible options for RTC clock input source
 */
typedef enum
{
    RTC_ALARM_A,
    RTC_ALARM_B
}RTC_AlarmSel_t;

/**
 * @brief Configuration structure regarding the time for RTC peripheral.
 */
typedef struct
{
    uint8_t HourTens;               /**< Hour tens in BCD format */
    uint8_t HourUnits;              /**< Hour units in BCD format */
    uint8_t MinuteTens;             /**< Minute tens in BCD format */
    uint8_t MinuteUnits;            /**< Minute units in BCD format */
    uint8_t SecondTens;             /**< Second tens in BCD format */
    uint8_t SecondUnits;            /**< Second units in BCD format */
    uint8_t PM;                     /**< AM/PM notation */
}RTC_Time_t;

/**
 * @brief Configuration structure regarding the date for RTC peripheral.
 */
typedef struct
{
    uint8_t YearTens;               /**< Year tens in BCD format */
    uint8_t YearUnits;              /**< Year units in BCD format */
    uint8_t WeekDayUnits;           /**< Week day units */
    uint8_t MonthTens;              /**< Month tens in BCD format */
    uint8_t MonthUnits;             /**< Month units in BCD format */
    uint8_t DateTens;               /**< Date tens in BCD format */
    uint8_t DateUnits;              /**< Date units in BCD format */
}RTC_Date_t;

/**
 * @brief Configuration structure for RTC peripheral.
 */
typedef struct
{
    uint8_t RTC_HoursFormat;        /**< Possible values from @ref RTC_HoursFormat */
    uint8_t RTC_AsynchPrediv;       /**< Asynchronous prescaler factor */
    uint16_t RTC_SynchPrediv;       /**< Synchronous prescaler factor */
    uint8_t RTC_Output;             /**< Possible values from @ref RTC_OutputSelection */
    uint8_t RTC_OutputPolarity;     /**< Possible values from @ref RTC_OutputPolarity */
    RTC_Time_t RTC_Time;            /**< Struct with time configuration */
    RTC_Date_t RTC_Date;            /**< Struct with date configuration */
}RTC_Config_t;

/**
 * @brief Configuration structure regarding the alarm for RTC peripheral.
 */
typedef struct
{
    RTC_AlarmSel_t AlarmSel;       /**< Possible values from ref RTC_AlarmSel_t */
    uint8_t DateMask;               /**< Date mask */
    uint8_t WeekDaySelec;           /**< Week day selection */
    uint8_t DateTens;               /**< Date tens in BCD format */
    uint8_t DateUnits;              /**< Date units in BCD format */
    uint8_t HoursMask;              /**< Hours mask */
    uint8_t PM;                     /**< AM/PM notation */
    uint8_t HourTens;               /**< Hour tens in BCD format */
    uint8_t HourUnits;              /**< Hour units in BCD format */
    uint8_t MinutesMask;            /**< Minutes mask */
    uint8_t MinuteTens;             /**< Minute tens in BCD format */
    uint8_t MinuteUnits;            /**< Minute units in BCD format */
    uint8_t SecondsMask;            /**< Seconds mask */
    uint8_t SecondTens;             /**< Second tens in BCD format */
    uint8_t SecondUnits;            /**< Second units in BCD format */
    uint8_t IRQ;                    /**< Enable IRQ */
}RTC_Alarm_t;

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to control the peripheral clock of the RTC peripheral.
 * @param[in] en_or_di for enable or disable.
 * @return void
 */
void RTC_PerClkCtrl(uint8_t en_or_di);

/**
 * @brief Function to select the clock source for the RTC peripheral
 * @param[in] RTC_ClkSource_t possible values
 * @return void
 */
void RTC_ClkSource(RTC_ClkSource_t clk_source);

/**
 * @brief Function to initialize RTC peripheral.
 * @param[in] RTC_Cfg structure with the initial configuration
 * @return void
 */
void RTC_Init(RTC_Config_t RTC_Cfg);

/**
 * @brief Function to set time in the RTC peripheral.
 * @param[in] time structure with the time configuration
 * @return void
 */
void RTC_SetTime(RTC_Time_t time);

/**
 * @brief Function to get time from the RTC peripheral.
 * @param[out] time structure with the time is stored
 * @return void
 */
void RTC_GetTime(RTC_Time_t* time);

/**
 * @brief Function to set date in the RTC peripheral.
 * @param[in] date structure with the date configuration
 * @return void
 */
void RTC_SetDate(RTC_Date_t date);

/**
 * @brief Function to get date from the RTC peripheral.
 * @param[out] date structure with the date is stored
 * @return void
 */
void RTC_GetDate(RTC_Date_t* date);

/**
 * @brief Function to clear the RSF bit in the ISR register of the RTC peripheral.
 * @return void
 */
void RTC_ClearRSF(void);

/**
 * @brief Function to get the RSF bit value of the ISR register of the RTC peripheral..
 * @return RSF value (0 or 1)
 */
uint8_t RTC_GetRSF(void);

/**
 * @brief Function to set alarm in the RTC peripheral.
 * @param[in] structure with the alarm configuration
 * @return void
 */
void RTC_SetAlarm(RTC_Alarm_t alarm);

/**
 * @brief Function to get alarm configuration from the RTC peripheral.
 * @param[out] structure with the alarm configuration is stored
 * @return void
 */
void RTC_GetAlarm(RTC_Alarm_t* alarm);

/**
 * @brief Function to check if the alarm reached the configured date and hour of the RTC peripheral.
 * @param[out] possible values from RTC_AlarmSel_t
 * @return 0 if ALRxF bit in the ISR register is unset
 * @return 1 if ALRxF bit in the ISR register is set
 * @return 2 if the RTC_AlarmSel_t is not a valid value
 */
uint8_t RTC_CheckAlarm(RTC_AlarmSel_t alarm);

/**
 * @brief Function to clear the alarm ALRxF bit in the ISR register of the RTC peripheral.
 * @param[out] possible values from RTC_AlarmSel_t
 * @return 0 if operation was OK
 * @return 1 if the RTC_AlarmSel_t is not a valid value
 */
uint8_t RTC_ClearAlarm(RTC_AlarmSel_t alarm);

/**
 * @brief Function to disable the alarm of the RTC peripheral.
 * @param[out] possible values from RTC_AlarmSel_t
 * @return 0 if operation was OK
 * @return 1 if the RTC_AlarmSel_t is not a valid value
 */
uint8_t RTC_DisableAlarm(RTC_AlarmSel_t alarm);

/**
 * @brief Function to handle the alarm interrupt of the RTC peripheral.
 * @return void.
 */
void RTC_Alarm_IRQHandling(void);

/**
 * @brief Function to configure the IRQ number of the RTC peripheral.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] en_or_di for enable or disable.
 * @return void.
 */
void RTC_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di);

/**
 * @brief Function to configure the IRQ number of the RTC.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] IRQPriority priority of the interrupt.
 * @return void
 */
void RTC_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/**
 * @brief Function for application callback.
 * @return void.
 */
void RTC_AlarmEventCallback(RTC_AlarmSel_t alarm);

#endif /* RTC_DRIVER_H */
