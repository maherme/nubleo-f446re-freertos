/********************************************************************************************************//**
* @file gpio_driver.c
*
* @brief File containing the APIs for configuring the GPIO peripheral.
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
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include <stdint.h>
#include "gpio_driver.h"

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void GPIO_Init(GPIO_Handle_t* pGPIOHandle){

    uint32_t temp = 0;
    uint8_t temp1, temp2 = 0;
    uint8_t portcode = 0;

    /* Enable the peripheral clock */
    GPIO_PerClkCtrl(pGPIOHandle->pGPIOx, ENABLE);

    /* Configure the mode */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
        /* Non-interrupt mode */
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* clearing */
        pGPIOHandle->pGPIOx->MODER |= temp; /* setting */
    }
    else{
        /* Interrupt mode */
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
            /* Configure the FTSR */
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            /* Clear the corresponding RTSR bit */
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
            /* Configure both the FTSR and RTSR */
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
        }

        /* Configure the GPIO port selection in SYSCFG_EXTICR */
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[temp1] = portcode << (temp2*4);

        /* Enable the EXTI interrupt delivery using IMR */
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;

    /* Configure the speed */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* clearing */
    pGPIOHandle->pGPIOx->OSPEEDER |= temp; /* setting */
    temp = 0;

    /* Configure the pupd settings */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl <<
            (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* clearing */
    pGPIOHandle->pGPIOx->PUPDR |= temp; /* setting */
    temp = 0;

    /* Configure the optype */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* clearing */
    pGPIOHandle->pGPIOx->OTYPER |= temp; /* setting */
    temp = 0;

    /* Configure the alternate functionality */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4*temp2));
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));
    }
}

void GPIO_DeInit(GPIO_RegDef_t* pGPIOx){

    if(pGPIOx == GPIOA){
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB){
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC){
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD){
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE){
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOF){
        GPIOF_REG_RESET();
    }
    else if(pGPIOx == GPIOG){
        GPIOG_REG_RESET();
    }
    else if(pGPIOx == GPIOH){
        GPIOH_REG_RESET();
    }
    else{
        /* do nothing */
    }
}

void GPIO_PerClkCtrl(GPIO_RegDef_t* pGPIOx, uint8_t en_or_di){

    if(en_or_di == ENABLE){
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB){
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC){
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD){
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE){
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOF){
            GPIOF_PCLK_EN();
        }
        else if(pGPIOx == GPIOG){
            GPIOG_PCLK_EN();
        }
        else if(pGPIOx == GPIOH){
            GPIOH_PCLK_EN();
        }
        else{
            /* do nothing */
        }
    }
    else{
        if(pGPIOx == GPIOA){
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB){
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC){
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD){
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOE){
            GPIOE_PCLK_DI();
        }
        else if(pGPIOx == GPIOF){
            GPIOF_PCLK_DI();
        }
        else if(pGPIOx == GPIOG){
            GPIOG_PCLK_DI();
        }
        else if(pGPIOx == GPIOH){
            GPIOH_PCLK_DI();
        }
        else{
            /* do nothing */
        }
    }
}

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number){

    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> pin_number) & 0x00000001);

    return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx){

    uint16_t value;
    value = (uint16_t)pGPIOx->IDR;

    return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number, uint8_t value){

    if(value == GPIO_PIN_SET){
        pGPIOx->ODR |= (1 << pin_number);
    }
    else{
        pGPIOx->ODR &= ~(1 << pin_number);
    }
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value){

    pGPIOx->ODR = value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pin_number){
    pGPIOx->ODR ^= (1 << pin_number);
}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di){

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

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
    /* Find out the IPR register */
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift = (8*iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift);
}

void GPIO_IRQHandling(uint8_t pin_number){
    /* Clear the EXTI PR register corresponding to the pin_number */
    if(EXTI->PR & (1 << pin_number)){
        /* clear */
        EXTI->PR |= (1 << pin_number);
    }
}
