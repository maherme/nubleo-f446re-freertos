/********************************************************************************************************//**
* @file rtc_driver.c
*
* @brief File containing the APIs for configuring the RTC peripheral.
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
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include "rtc_driver.h"
#include "stm32f446xx.h"
#include <stdint.h>

/***********************************************************************************************************/
/*                                       Static Function Prototypes                                        */
/***********************************************************************************************************/

/**
 * @brief Function for unlocking the RTC write protected registers.
 * @return void.
 */
static void RTC_Unlock(void);

/**
 * @brief Function for entering in configuration mode for the RTC.
 * @return void.
 */
static void RTC_EnterConfig(void);

/**
 * @brief Function for exiting from configuration mode for the RTC.
 * @return void.
 */
static void RTC_ExitConfig(void);

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void RTC_PerClkCtrl(uint8_t en_or_di){

    if(en_or_di == ENABLE){
        RTC_PCLK_EN();
    }
    else{
        RTC_PCLK_DI();
    }
}

void RTC_ClkSource(RTC_ClkSource_t clk_source){

    /* Disable backup protection */
    PWR_PCLK_EN();
    PWR->CR |= (1 << PWR_CR_DBP);

    RCC->BDCR &= ~(0x3 << RCC_BDCR_RTCSEL);
    RCC->BDCR |= (clk_source << RCC_BDCR_RTCSEL);
}

void RTC_Init(RTC_Config_t RTC_Cfg){

    uint32_t temp = 0;

    RTC_Unlock();
    RTC_EnterConfig();

    /* Set hours format */
    RTC->CR &= ~(1 << RTC_CR_FMT);
    RTC->CR |= (RTC_Cfg.RTC_HoursFormat << RTC_CR_FMT);

    temp |= ((RTC_Cfg.RTC_Time.SecondUnits << RTC_TR_SU) |
            (RTC_Cfg.RTC_Time.SecondTens << RTC_TR_ST) |
            (RTC_Cfg.RTC_Time.MinuteUnits << RTC_TR_MNU) |
            (RTC_Cfg.RTC_Time.MinuteTens << RTC_TR_MNT) |
            (RTC_Cfg.RTC_Time.HourUnits << RTC_TR_HU) |
            (RTC_Cfg.RTC_Time.HourTens << RTC_TR_HT) |
            (RTC_Cfg.RTC_Time.PM << RTC_TR_PM));

    /* Set time */
    RTC->TR &= ~(0xFFFFFFFF);
    RTC->TR = temp;

    temp = 0;
    temp |= ((RTC_Cfg.RTC_Date.DateUnits << RTC_DR_DU) |
            (RTC_Cfg.RTC_Date.DateTens << RTC_DR_DT) |
            (RTC_Cfg.RTC_Date.MonthUnits << RTC_DR_MU) |
            (RTC_Cfg.RTC_Date.MonthTens << RTC_DR_MT) |
            (RTC_Cfg.RTC_Date.WeekDayUnits << RTC_DR_WDU) |
            (RTC_Cfg.RTC_Date.YearUnits << RTC_DR_YU) |
            (RTC_Cfg.RTC_Date.YearTens << RTC_DR_YT));

    /* Set date */
    RTC->DR &= ~(0xFFFFFFFF);
    RTC->DR = temp;

    RTC_ExitConfig();
}

void RTC_SetTime(RTC_Time_t time){

    uint32_t temp = 0;

    temp |= ((time.SecondUnits << RTC_TR_SU) |
            (time.SecondTens << RTC_TR_ST) |
            (time.MinuteUnits << RTC_TR_MNU) |
            (time.MinuteTens << RTC_TR_MNT) |
            (time.HourUnits << RTC_TR_HU) |
            (time.HourTens << RTC_TR_HT) |
            (time.PM << RTC_TR_PM));

    RTC_Unlock();
    RTC_EnterConfig();

    /* Set time */
    RTC->TR &= ~(0xFFFFFFFF);
    RTC->TR = temp;

    RTC_ExitConfig();
}

void RTC_GetTime(RTC_Time_t* time){

    time->SecondUnits = (RTC->TR >> RTC_TR_SU) & 0xF;
    time->SecondTens = (RTC->TR >> RTC_TR_ST) & 0x7;
    time->MinuteUnits = (RTC->TR >> RTC_TR_MNU) & 0xF;
    time->MinuteTens = (RTC->TR >> RTC_TR_MNT) & 0x7;
    time->HourUnits = (RTC->TR >> RTC_TR_HU) & 0xF;
    time->HourTens = (RTC->TR >> RTC_TR_HT) & 0x3;
    time->PM = (RTC->TR >> RTC_TR_PM) & 0x1;
}

void RTC_SetDate(RTC_Date_t date){

    uint32_t temp = 0;

    temp |= ((date.DateUnits << RTC_DR_DU) |
            (date.DateTens << RTC_DR_DT) |
            (date.MonthUnits << RTC_DR_MU) |
            (date.MonthTens << RTC_DR_MT) |
            (date.WeekDayUnits << RTC_DR_WDU) |
            (date.YearUnits << RTC_DR_YU) |
            (date.YearTens << RTC_DR_YT));

    RTC_Unlock();
    RTC_EnterConfig();

    /* Set date */
    RTC->DR &= ~(0xFFFFFFFF);
    RTC->DR = temp;

    RTC_ExitConfig();
}

void RTC_GetDate(RTC_Date_t* date){

    date->DateUnits = (RTC->DR >> RTC_DR_DU) & 0xF;
    date->DateTens = (RTC->DR >> RTC_DR_DT) & 0x3;
    date->WeekDayUnits = (RTC->DR >> RTC_DR_WDU) & 0x7;
    date->MonthUnits = (RTC->DR >> RTC_DR_MU) & 0xF;
    date->MonthTens = (RTC->DR >> RTC_DR_MT) & 0x1;
    date->YearUnits = (RTC->DR >> RTC_DR_YU) & 0xF;
    date->YearTens = (RTC->DR >> RTC_DR_YT) & 0xF;
}

void RTC_ClearRSF(void){

    RTC_Unlock();
    RTC->ISR &= ~(1 << RTC_ISR_RSF);
}

uint8_t RTC_GetRSF(void){

    uint8_t ret = 0;

    if(RTC->ISR & (1 << RTC_ISR_RSF)){
       ret = 1;
    }

    return ret;
}

void RTC_SetAlarm(RTC_Alarm_t alarm){

    uint32_t temp = 0;

    temp |= ((alarm.DateMask << RTC_ALRMxR_MSK4) |
            (alarm.WeekDaySelec << RTC_ALRMxR_WDSEL) |
            (alarm.DateTens << RTC_ALRMxR_DT) |
            (alarm.DateUnits << RTC_ALRMxR_DU) |
            (alarm.HoursMask << RTC_ALRMxR_MSK3) |
            (alarm.PM << RTC_ALRMxR_PM) |
            (alarm.HourTens << RTC_ALRMxR_HT) |
            (alarm.HourUnits << RTC_ALRMxR_HU) |
            (alarm.MinutesMask << RTC_ALRMxR_MSK2) |
            (alarm.MinuteTens << RTC_ALRMxR_MNT) |
            (alarm.MinuteUnits << RTC_ALRMxR_MNU) |
            (alarm.SecondsMask << RTC_ALRMxR_MSK1) |
            (alarm.SecondTens << RTC_ALRMxR_ST) |
            (alarm.SecondUnits << RTC_ALRMxR_SU));

    /* Configure and enable the EXTI Line 17 in interrupt mode and select the rising edge sensitivity */
    if(alarm.IRQ == 1){
        EXTI->IMR |= (1 << 17);
        EXTI->RTSR |= (1 << 17);
    }

    RTC_Unlock();

    switch(alarm.AlarmSel){
        case RTC_ALARM_A:
            /* Clear ALRAE in RTC_CR register to disable Alarm A */
            RTC->CR &= ~(1 << RTC_CR_ALRAE);
            /* Poll ALRAWF in RTC_ISR until it is set to make sure the access to alarm reg is allowed */
            while(!(RTC->ISR & (1 << RTC_ISR_ALRAWF)));
            /* Set alarm A values */
            RTC->ALRMAR &= ~(0xFFFFFFFF);
            RTC->ALRMAR = temp;
            /* Set ALRAE in the RTC_CR register to enable Alarm A */
            RTC->CR |= (1 << RTC_CR_ALRAE);
            /* Set ALRAIE in the RTC CR register to enable Alarm A interrupt */
            if(alarm.IRQ == 1){
                RTC->CR |= (1 << RTC_CR_ALRAIE);
            }
            break;
        case RTC_ALARM_B:
            /* Clear ALRBE in RTC_CR register to disable Alarm B */
            RTC->CR &= ~(1 << RTC_CR_ALRBE);
            /* Poll ALRBWF in RTC_ISR until it is set to make sure the access to alarm reg is allowed */
            while(!(RTC->ISR & (1 << RTC_ISR_ALRBWF)));
            /* Set alarm B values */
            RTC->ALRMBR &= ~(0xFFFFFFFF);
            RTC->ALRMBR = temp;
            /* Set ALRBE in the RTC_CR register to enable Alarm B */
            RTC->CR |= (1 << RTC_CR_ALRBE);
            /* Set ALRBIE in the RTC CR register to enable Alarm B interrupt */
            if(alarm.IRQ == 1){
                RTC->CR |= (1 << RTC_CR_ALRBIE);
            }
            break;
        default:
            break;
    }
}

void RTC_GetAlarm(RTC_Alarm_t* alarm){

    uint32_t alarm_reg;

    switch(alarm->AlarmSel){
        case RTC_ALARM_A:
            alarm_reg = RTC->ALRMAR;
            break;
        case RTC_ALARM_B:
            alarm_reg = RTC->ALRMBR;
            break;
        default:
            break;
    }

    alarm->DateMask = (alarm_reg >> RTC_ALRMxR_MSK4) & 0x1;
    alarm->WeekDaySelec = (alarm_reg >> RTC_ALRMxR_WDSEL) & 0x1;
    alarm->DateTens = (alarm_reg >> RTC_ALRMxR_DT) & 0x3;
    alarm->DateUnits = (alarm_reg >> RTC_ALRMxR_DU) & 0xF;
    alarm->HoursMask = (alarm_reg >> RTC_ALRMxR_MSK3) & 0x1;
    alarm->PM = (alarm_reg >> RTC_ALRMxR_PM) & 0x1;
    alarm->HourTens = (alarm_reg >> RTC_ALRMxR_HT) & 0x3;
    alarm->HourUnits = (alarm_reg >> RTC_ALRMxR_HU) & 0xF;
    alarm->MinutesMask = (alarm_reg >> RTC_ALRMxR_MSK2) & 0x1;
    alarm->MinuteTens = (alarm_reg >> RTC_ALRMxR_MNT) & 0x7;
    alarm->MinuteUnits = (alarm_reg >> RTC_ALRMxR_MNU) & 0xF;
    alarm->SecondsMask = (alarm_reg >> RTC_ALRMxR_MSK1) & 0x1;
    alarm->SecondTens = (alarm_reg >> RTC_ALRMxR_ST) & 0x7;
    alarm->SecondUnits = (alarm_reg >> RTC_ALRMxR_SU) & 0xF;
}

uint8_t RTC_CheckAlarm(RTC_AlarmSel_t alarm){

    uint8_t ret = 0;

    switch(alarm){
        case RTC_ALARM_A:
            if(RTC->ISR & (1 << RTC_ISR_ALRAF)){
                ret = 1;
            }
            break;
        case RTC_ALARM_B:
            if(RTC->ISR & (1 << RTC_ISR_ALRBF)){
                ret = 1;
            }
            break;
        default:
            ret = 2;
            break;
    }

    return ret;
}

uint8_t RTC_ClearAlarm(RTC_AlarmSel_t alarm){

    uint8_t ret = 0;

    switch(alarm){
        case RTC_ALARM_A:
            RTC->ISR &= ~(1 << RTC_ISR_ALRAF);
            break;
        case RTC_ALARM_B:
            RTC->ISR &= ~(1 << RTC_ISR_ALRBF);
            break;
        default:
            ret = 1;
            break;
    }

    return ret;
}

uint8_t RTC_DisableAlarm(RTC_AlarmSel_t alarm){

    uint8_t ret = 0;

    RTC_Unlock();

    switch(alarm){
        case RTC_ALARM_A:
            RTC->CR &= ~(1 << RTC_CR_ALRAE);
            break;
        case RTC_ALARM_B:
            RTC->CR &= ~(1 << RTC_CR_ALRBE);
            break;
        default:
            ret = 1;
            break;
    }

    return ret;
}

void RTC_Alarm_IRQHandling(void){

    /* Clear the EXTI PR register corresponding to the Alarm (EXTI 17) */
    if(EXTI->PR & (1 << 17)){
        /* clear */
        EXTI->PR |= (1 << 17);
    }

    if(RTC->ISR & (1 << RTC_ISR_ALRAF)){
        RTC_AlarmEventCallback(RTC_ALARM_A);
    }
    else if(RTC->ISR & (1 << RTC_ISR_ALRBF)){
        RTC_AlarmEventCallback(RTC_ALARM_B);
    }
    else{
        /* do nothing */
    }
}

void RTC_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di){

    if(en_or_di == ENABLE){
        if(IRQNumber <= 31){
            /* Program ISER0 register */
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64){
            /* Program ISER1 register */
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96){
            /* Program ISER2 register */
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
        else{
            /* do nothing */
        }
    }
    else{
        if(IRQNumber <= 31){
            /* Program ICER0 register */
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64){
            /* Program ICER1 register */
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96){
            /* Program ICER2 register */
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
        else{
            /* do nothing */
        }
    }
}

void RTC_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
    /* Find out the IPR register */
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift = (8*iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift);
}

__attribute__((weak)) void RTC_AlarmEventCallback(RTC_AlarmSel_t alarm){

    /* This is a weak implementation. The application may override this function */
}

/***********************************************************************************************************/
/*                                       Static Function Definitions                                       */
/***********************************************************************************************************/

static void RTC_Unlock(void){

    RTC->WPR |= 0xCA;
    RTC->WPR |= 0x53;
}

static void RTC_EnterConfig(void){

    /* Set INIT bit to 1 in the RTC_ISR register to enter initialization mode */
    RTC->ISR |= (1 << RTC_ISR_INIT);
    /* Poll INITF bit of in the RTC_ISR register */
    while(!(RTC->ISR & (1 << RTC_ISR_INITF)));
}

static void RTC_ExitConfig(void){

    /* Exit the initialization mode by clearing the INIT bit */
    RTC->ISR &= ~(1 << RTC_ISR_INIT);
}
