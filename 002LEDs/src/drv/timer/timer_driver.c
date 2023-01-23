/********************************************************************************************************//**
* @file timer_driver.c
*
* @brief File containing the APIs for configuring the TIM peripheral.
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
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include <stdint.h>
#include "timer_driver.h"
#include "stm32f446xx.h"

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void Timer_Init(Timer_Handle_t* Timer_Handle){

    /* Enable peripheral clock */
    Timer_PerClkCtrl(Timer_Handle->tim_num, ENABLE);
    /* Clear and set prescaler value */
    Timer_Handle->pTimer->PSC &= ~(0xFFFF << TIM_PSC);
    Timer_Handle->pTimer->PSC |= (Timer_Handle->prescaler << TIM_PSC);
    /*Clear and set period value */
    /* TIM2 and TIM5 have 32 bits of counter capacity */
    if((Timer_Handle->tim_num == TIMER2) || (Timer_Handle->tim_num == TIMER5)){
        Timer_Handle->pTimer->ARR &= ~(0xFFFFFFFF << TIM_ARR);
        Timer_Handle->pTimer->ARR |= (Timer_Handle->period << TIM_ARR);
    }
    /* Rest of the TIMx have 16 bits of counter capacity */
    else{
        Timer_Handle->pTimer->ARR &= ~(0xFFFF << TIM_ARR);
        Timer_Handle->pTimer->ARR |= (uint16_t)(Timer_Handle->period << TIM_ARR);
    }
    /* Enable interrupt */
    Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_UIE);
}

void Timer_Start(Timer_Handle_t* Timer_Handle){

    /* Clear UIF bit in SR register */
    Timer_Handle->pTimer->SR &= ~(1 << TIM_SR_UIF);
    /* Set counter enable */
    Timer_Handle->pTimer->CR1 |= (1 << TIM_CR1_CEN);
}

void Timer_Stop(Timer_Handle_t* Timer_Handle){

    /* Set counter disable */
    Timer_Handle->pTimer->CR1 &= ~(1 << TIM_CR1_CEN);
}

void Timer_ICInit(Timer_Handle_t* Timer_Handle, IC_Handle_t IC_Handle, CC_Channel_t channel){

    switch(channel){
        case CHANNEL1:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC1P);
            Timer_Handle->pTimer->CCER |= (IC_Handle.ic_polarity << TIM_CCER_CC1P);
            /* Set input capture selection */
            Timer_Handle->pTimer->CCMR1 &= ~(0x03 << TIM_CCMR1_CC1S);
            Timer_Handle->pTimer->CCMR1 |= (IC_Handle.ic_select << TIM_CCMR1_CC1S);
            /* Set input capture prescaler */
            Timer_Handle->pTimer->CCMR1 &= ~(0x03 << TIM_CCMR1_IC1PSC);
            Timer_Handle->pTimer->CCMR1 |= (IC_Handle.ic_prescaler << TIM_CCMR1_IC1PSC);
            /* Set input capture filter */
            Timer_Handle->pTimer->CCMR1 &= ~(0x0F << TIM_CCMR1_IC1F);
            Timer_Handle->pTimer->CCMR1 |= (IC_Handle.ic_filter << TIM_CCMR1_IC1F);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC1IE);
            /* Enable capture/compare 1 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC1E);
            break;
        case CHANNEL2:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC2P);
            Timer_Handle->pTimer->CCER |= (IC_Handle.ic_polarity << TIM_CCER_CC2P);
            /* Set input capture selection */
            Timer_Handle->pTimer->CCMR1 &= ~(0x03 << TIM_CCMR1_CC2S);
            Timer_Handle->pTimer->CCMR1 |= (IC_Handle.ic_select << TIM_CCMR1_CC2S);
            /* Set input capture prescaler */
            Timer_Handle->pTimer->CCMR1 &= ~(0x03 << TIM_CCMR1_IC2PSC);
            Timer_Handle->pTimer->CCMR1 |= (IC_Handle.ic_prescaler << TIM_CCMR1_IC2PSC);
            /* Set input capture filter */
            Timer_Handle->pTimer->CCMR1 &= ~(0x0F << TIM_CCMR1_IC2F);
            Timer_Handle->pTimer->CCMR1 |= (IC_Handle.ic_filter << TIM_CCMR1_IC2F);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC2IE);
            /* Enable capture/compare 2 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC2E);
            break;
        case CHANNEL3:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC3P);
            Timer_Handle->pTimer->CCER |= (IC_Handle.ic_polarity << TIM_CCER_CC3P);
            /* Set input capture selection */
            Timer_Handle->pTimer->CCMR2 &= ~(0x03 << TIM_CCMR2_CC3S);
            Timer_Handle->pTimer->CCMR2 |= (IC_Handle.ic_select << TIM_CCMR2_CC3S);
            /* Set input capture prescaler */
            Timer_Handle->pTimer->CCMR2 &= ~(0x03 << TIM_CCMR2_IC3PSC);
            Timer_Handle->pTimer->CCMR2 |= (IC_Handle.ic_prescaler << TIM_CCMR2_IC3PSC);
            /* Set input capture filter */
            Timer_Handle->pTimer->CCMR2 &= ~(0x0F << TIM_CCMR2_IC3F);
            Timer_Handle->pTimer->CCMR2 |= (IC_Handle.ic_filter << TIM_CCMR2_IC3F);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC3IE);
            /* Enable capture/compare 3 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC3E);
            break;
        case CHANNEL4:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC4P);
            Timer_Handle->pTimer->CCER |= (IC_Handle.ic_polarity << TIM_CCER_CC4P);
            /* Set input capture selection */
            Timer_Handle->pTimer->CCMR2 &= ~(0x03 << TIM_CCMR2_CC4S);
            Timer_Handle->pTimer->CCMR2 |= (IC_Handle.ic_select << TIM_CCMR2_CC4S);
            /* Set input capture prescaler */
            Timer_Handle->pTimer->CCMR2 &= ~(0x03 << TIM_CCMR2_IC4PSC);
            Timer_Handle->pTimer->CCMR2 |= (IC_Handle.ic_prescaler << TIM_CCMR2_IC4PSC);
            /* Set input capture filter */
            Timer_Handle->pTimer->CCMR2 &= ~(0x0F << TIM_CCMR2_IC4F);
            Timer_Handle->pTimer->CCMR2 |= (IC_Handle.ic_filter << TIM_CCMR2_IC4F);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC4IE);
            /* Enable capture/compare 4 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC4E);
            break;
        default:
            break;
    }
}

uint32_t Timer_CCGetValue(Timer_Handle_t* Timer_Handle, CC_Channel_t channel){

    uint32_t ret_val = 0;

    switch(channel){
        case CHANNEL1:
            ret_val = Timer_Handle->pTimer->CCR1;
            break;
        case CHANNEL2:
            ret_val = Timer_Handle->pTimer->CCR2;
            break;
        case CHANNEL3:
            ret_val = Timer_Handle->pTimer->CCR3;
            break;
        case CHANNEL4:
            ret_val = Timer_Handle->pTimer->CCR4;
            break;
        default:
            break;
    }

    return ret_val;
}

void Timer_CCSetValue(Timer_Handle_t* Timer_Handle, CC_Channel_t channel, uint32_t value){

    /* Disable timer */
    Timer_Handle->pTimer->CR1 &= ~(1 << TIM_CR1_CEN);

    switch(channel){
        case CHANNEL1:
            Timer_Handle->pTimer->CCR1 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR1 |= value;
            break;
        case CHANNEL2:
            Timer_Handle->pTimer->CCR2 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR2 |= value;
            break;
        case CHANNEL3:
            Timer_Handle->pTimer->CCR3 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR3 |= value;
            break;
        case CHANNEL4:
            Timer_Handle->pTimer->CCR4 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR4 |= value;
            break;
        default:
            break;
    }

    /* Enable timer */
    Timer_Handle->pTimer->CR1 |= (1 << TIM_CR1_CEN);

}

void Timer_OCInit(Timer_Handle_t* Timer_Handle, OC_Handle_t OC_Handle, CC_Channel_t channel){

    /* Disable update event interrupt */
    Timer_Handle->pTimer->DIER &= ~(1 << TIM_DIER_UIE);

    switch(channel){
        case CHANNEL1:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC1P);
            Timer_Handle->pTimer->CCER |= (OC_Handle.oc_polarity << TIM_CCER_CC1P);
            /* Set capture/compare selection as output */
            Timer_Handle->pTimer->CCMR1 &= ~(0x03 << TIM_CCMR1_CC1S);
            /* Set output compare mode */
            Timer_Handle->pTimer->CCMR1 &= ~(0x07 << TIM_CCMR1_OC1M);
            Timer_Handle->pTimer->CCMR1 |= (OC_Handle.oc_mode << TIM_CCMR1_OC1M);
            /* Set initial pulse value */
            Timer_Handle->pTimer->CCR1 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR1 |= OC_Handle.oc_pulse;
            /* Enable preload */
            Timer_Handle->pTimer->CCMR1 |= (OC_Handle.oc_preload << TIM_CCMR1_OC1PE);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC1IE);
            /* Enable capture/compare 1 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC1E);
            break;
        case CHANNEL2:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC2P);
            Timer_Handle->pTimer->CCER |= (OC_Handle.oc_polarity << TIM_CCER_CC2P);
            /* Set capture/compare selection as output */
            Timer_Handle->pTimer->CCMR1 &= ~(0x03 << TIM_CCMR1_CC2S);
            /* Set output compare mode */
            Timer_Handle->pTimer->CCMR1 &= ~(0x07 << TIM_CCMR1_OC2M);
            Timer_Handle->pTimer->CCMR1 |= (OC_Handle.oc_mode << TIM_CCMR1_OC2M);
            /* Set initial pulse value */
            Timer_Handle->pTimer->CCR2 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR2 |= OC_Handle.oc_pulse;
            /* Enable preload */
            Timer_Handle->pTimer->CCMR1 |= (OC_Handle.oc_preload << TIM_CCMR1_OC2PE);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC2IE);
            /* Enable capture/compare 2 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC2E);
            break;
        case CHANNEL3:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC3P);
            Timer_Handle->pTimer->CCER |= (OC_Handle.oc_polarity << TIM_CCER_CC3P);
            /* Set capture/compare selection as output */
            Timer_Handle->pTimer->CCMR2 &= ~(0x03 << TIM_CCMR2_CC3S);
            /* Set output compare mode */
            Timer_Handle->pTimer->CCMR2 &= ~(0x07 << TIM_CCMR2_OC3M);
            Timer_Handle->pTimer->CCMR2 |= (OC_Handle.oc_mode << TIM_CCMR2_OC3M);
            /* Set initial pulse value */
            Timer_Handle->pTimer->CCR3 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR3 |= OC_Handle.oc_pulse;
            /* Enable preload */
            Timer_Handle->pTimer->CCMR2 |= (OC_Handle.oc_preload << TIM_CCMR2_OC3PE);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC3IE);
            /* Enable capture/compare 3 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC3E);
            break;
        case CHANNEL4:
            /* Set polarity value */
            Timer_Handle->pTimer->CCER &= ~(0x05 << TIM_CCER_CC4P);
            Timer_Handle->pTimer->CCER |= (OC_Handle.oc_polarity << TIM_CCER_CC4P);
            /* Set capture/compare selection as output */
            Timer_Handle->pTimer->CCMR2 &= ~(0x03 << TIM_CCMR2_CC4S);
            /* Set output compare mode */
            Timer_Handle->pTimer->CCMR2 &= ~(0x07 << TIM_CCMR2_OC4M);
            Timer_Handle->pTimer->CCMR2 |= (OC_Handle.oc_mode << TIM_CCMR2_OC4M);
            /* Set initial pulse value */
            Timer_Handle->pTimer->CCR4 &= ~(0xFFFFFFFF);
            Timer_Handle->pTimer->CCR4 |= OC_Handle.oc_pulse;
            /* Enable preload */
            Timer_Handle->pTimer->CCMR2 |= (OC_Handle.oc_preload << TIM_CCMR2_OC4PE);
            /* Enable interrupt */
            Timer_Handle->pTimer->DIER |= (1 << TIM_DIER_CC4IE);
            /* Enable capture/compare 4 channel */
            Timer_Handle->pTimer->CCER |= (1 << TIM_CCER_CC4E);
            break;
        default:
            break;
    }
}

void Timer_PerClkCtrl(Timer_Num_t timer_num, uint8_t en_or_di){

    if(en_or_di == ENABLE){
        switch(timer_num){
            case TIMER1:
                TIM1_PCLK_EN();
                break;
            case TIMER2:
                TIM2_PCLK_EN();
                break;
            case TIMER3:
                TIM3_PCLK_EN();
                break;
            case TIMER4:
                TIM4_PCLK_EN();
                break;
            case TIMER5:
                TIM5_PCLK_EN();
                break;
            case TIMER6:
                TIM6_PCLK_EN();
                break;
            case TIMER7:
                TIM7_PCLK_EN();
                break;
            case TIMER8:
                TIM8_PCLK_EN();
                break;
            case TIMER9:
                TIM9_PCLK_EN();
                break;
            case TIMER10:
                TIM10_PCLK_EN();
                break;
            case TIMER11:
                TIM11_PCLK_EN();
                break;
            case TIMER12:
                TIM12_PCLK_EN();
                break;
            case TIMER13:
                TIM13_PCLK_EN();
                break;
            case TIMER14:
                TIM14_PCLK_EN();
                break;
            default:
                break;
        }
    }
    else{
        switch(timer_num){
            case TIMER1:
                TIM1_PCLK_DI();
                break;
            case TIMER2:
                TIM2_PCLK_DI();
                break;
            case TIMER3:
                TIM3_PCLK_DI();
                break;
            case TIMER4:
                TIM4_PCLK_DI();
                break;
            case TIMER5:
                TIM5_PCLK_DI();
                break;
            case TIMER6:
                TIM6_PCLK_DI();
                break;
            case TIMER7:
                TIM7_PCLK_DI();
                break;
            case TIMER8:
                TIM8_PCLK_DI();
                break;
            case TIMER9:
                TIM9_PCLK_DI();
                break;
            case TIMER10:
                TIM10_PCLK_DI();
                break;
            case TIMER11:
                TIM11_PCLK_DI();
                break;
            case TIMER12:
                TIM12_PCLK_DI();
                break;
            case TIMER13:
                TIM13_PCLK_DI();
                break;
            case TIMER14:
                TIM14_PCLK_DI();
                break;
            default:
                break;
        }
    }
}

void Timer_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di){

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

void Timer_IRQHandling(Timer_Handle_t* Timer_Handle){

    /* Check if TIM update interrupt happened */
    if(Timer_Handle->pTimer->SR & (1 << TIM_SR_UIF)){
        /* Clear UIF bit in SR register */
        Timer_Handle->pTimer->SR &= ~(1 << TIM_SR_UIF);
        /* Call application callback */
        Timer_ApplicationEventCallback(Timer_Handle->tim_num, TIMER_UIF_EVENT);
    }

    /* Check if capture/compare interrupt happened */
    if(Timer_Handle->pTimer->SR & (1 << TIM_SR_CC1IF)){
        /* Clear CC1IF bit in SR register */
        Timer_Handle->pTimer->SR &= ~(1 << TIM_SR_CC1IF);
        /* Call application callback */
        Timer_ApplicationEventCallback(Timer_Handle->tim_num, TIMER_CC1IF_EVENT);
    }
    else if(Timer_Handle->pTimer->SR & (1 << TIM_SR_CC2IF)){
        /* Clear CC2IF bit in SR register */
        Timer_Handle->pTimer->SR &= ~(1 << TIM_SR_CC2IF);
        /* Call application callback */
        Timer_ApplicationEventCallback(Timer_Handle->tim_num, TIMER_CC2IF_EVENT);
    }
    else if(Timer_Handle->pTimer->SR & (1 << TIM_SR_CC3IF)){
        /* Clear CC3IF bit in SR register */
        Timer_Handle->pTimer->SR &= ~(1 << TIM_SR_CC3IF);
        /* Call application callback */
        Timer_ApplicationEventCallback(Timer_Handle->tim_num, TIMER_CC3IF_EVENT);
    }
    else if(Timer_Handle->pTimer->SR & (1 << TIM_SR_CC4IF)){
        /* Clear CC4IF bit in SR register */
        Timer_Handle->pTimer->SR &= ~(1 << TIM_SR_CC4IF);
        /* Call application callback */
        Timer_ApplicationEventCallback(Timer_Handle->tim_num, TIMER_CC4IF_EVENT);
    }
    else{
        /* do nothing */
    }
}

__attribute__((weak)) void Timer_ApplicationEventCallback(Timer_Num_t tim_num, Timer_Event_t timer_event){

    /* This is a weak implementation. The application may override this function */
}
