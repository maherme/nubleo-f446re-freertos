/********************************************************************************************************//**
* @file usart_driver.c
*
* @brief File containing the APIs for configuring the USART peripheral.
*
* Public Functions:
*       - void    USART_Init(USART_Handle_t* pUSART_Handle)
*       - void    USART_DeInit(USART_RegDef_t* pUSARTx)
*       - void    USART_PerClkCtrl(USART_RegDef_t* pUSARTx, uint8_t en_or_di)
*       - void    USART_SendData(USART_Handle_t* pUSART_Handle, uint8_t* pTxBuffer, uint32_t len)
*       - void    USART_ReceiveData(USART_Handle_t* pUSART_Handle, uint8_t* pRxBuffer, uint32_t len)
*       - uint8_t USART_SendDataIT(USART_Handle_t* pUSART_Handle, uint8_t* pTxBuffer, uint32_t len)
*       - uint8_t USART_ReceiveDataIT(USART_Handle_t* pUSART_Handle, uint8_t* pRxBuffer, uint32_t len)
*       - void    USART_SetBaudRate(USART_RegDef_t* pUSARTx, uint32_t baudrate)
*       - void    USART_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di)
*       - void    USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
*       - void    USART_IRQHandling(USART_Handle_t* pUSART_Handle)
*       - void    USART_Enable(USART_RegDef_t* pUSARTx, uint8_t en_or_di)
*       - uint8_t USART_GetFlagStatus(USART_RegDef_t* pUSARTx, uint32_t flagname)
*       - void    USART_ClearFlag(USART_RegDef_t* pUSARTx, uint16_t status_flagname)
*       - void    USART_ApplicationEventCallback(USART_Handle_t* pUSART_Handle, uint8_t app_event)
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include <stdint.h>
#include <stddef.h>
#include "usart_driver.h"
#include "rcc_driver.h"

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void USART_Init(USART_Handle_t* pUSART_Handle){

    uint32_t temp = 0;

    /* Enable the peripheral clock */
    USART_PerClkCtrl(pUSART_Handle->pUSARTx, ENABLE);

    /* Enable USART TX and RX engines */
    if(pUSART_Handle->USART_Config.USART_Mode == USART_MODE_ONLY_RX){
        /* Enable receiver bit field */
        temp |= (1 << USART_CR1_RE);
    }
    else if(pUSART_Handle->USART_Config.USART_Mode == USART_MODE_ONLY_TX){
        /* Enable transmitter bit field */
        temp |= (1 << USART_CR1_TE);
    }
    else if(pUSART_Handle->USART_Config.USART_Mode == USART_MODE_TXRX){
        /* Enable both transmitter and receiver bit field */
        temp |= ((1 << USART_CR1_TE) | (1 << USART_CR1_RE));
    }
    else{
        /* do nothing */
    }

    /* Configure the word length */
    temp |= pUSART_Handle->USART_Config.USART_WordLength << USART_CR1_M;

    /* Configure parity control bit field */
    if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN){
        /* Enable parity control */
        /* EVEN parity set by default, so no need to implement */
        temp |= (1 << USART_CR1_PCE);
    }
    else if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD){
        /* Enable parity control */
        temp |= (1 << USART_CR1_PCE);

        /* Enable ODD parity */
        temp |= (1 << USART_CR1_PS);
    }
    else{
        /* do nothing */
    }

    /* Program CR1 register */
    pUSART_Handle->pUSARTx->CR1 = temp;

    temp = 0;

    /* Configure stop bits */
    temp |= pUSART_Handle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

    /* Program CR2 register */
    pUSART_Handle->pUSARTx->CR2 = temp;

    temp = 0;

    /* Configure flow control */
    if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS){
        /* Enable CTS flow control */
        temp |= (1 << USART_CR3_CTSE);
    }
    else if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS){
        /* Enable RTS flow control */
        temp |= (1 << USART_CR3_RTSE);
    }
    else if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS){
        /*Enable CTS and RTS flow control */
        temp |= (1 << USART_CR3_CTSE);
        temp |= (1 << USART_CR3_RTSE);
    }
    else{
        /* do nothing */
    }

    /* Program CR3 register */
    pUSART_Handle->pUSARTx->CR3 = temp;

    /* Configure baud rate */
    USART_SetBaudRate(pUSART_Handle->pUSARTx, pUSART_Handle->USART_Config.USART_Baud);
}

void USART_DeInit(USART_RegDef_t* pUSARTx){

    if(pUSARTx == USART1){
        USART1_REG_RESET();
    }
    else if(pUSARTx == USART2){
        USART2_REG_RESET();
    }
    else if(pUSARTx == USART3){
        USART3_REG_RESET();
    }
    else if(pUSARTx == UART4){
        UART4_REG_RESET();
    }
    else if(pUSARTx == UART5){
        UART5_REG_RESET();
    }
    else if(pUSARTx == USART6){
        USART6_REG_RESET();
    }
    else{
        /* do nothing */
    }
}

void USART_PerClkCtrl(USART_RegDef_t* pUSARTx, uint8_t en_or_di){

    if(en_or_di == ENABLE){
        if(pUSARTx == USART1){
            USART1_PCLK_EN();
        }
        else if(pUSARTx == USART2){
            USART2_PCLK_EN();
        }
        else if(pUSARTx == USART3){
            USART3_PCLK_EN();
        }
        else if(pUSARTx == UART4){
            UART4_PCLK_EN();
        }
        else if(pUSARTx == UART5){
            UART5_PCLK_EN();
        }
        else if(pUSARTx == USART6){
            USART6_PCLK_EN();
        }
        else{
            /* do nothing */
        }
    }
    else{
        if(pUSARTx == USART1){
            USART1_PCLK_DI();
        }
        else if(pUSARTx == USART2){
            USART2_PCLK_DI();
        }
        else if(pUSARTx == USART3){
            USART3_PCLK_DI();
        }
        else if(pUSARTx == UART4){
            UART4_PCLK_DI();
        }
        else if(pUSARTx == UART5){
            UART5_PCLK_DI();
        }
        else if(pUSARTx == USART6){
            USART6_PCLK_DI();
        }
        else{
            /* do nothing */
        }
    }
}

void USART_SendData(USART_Handle_t* pUSART_Handle, uint8_t* pTxBuffer, uint32_t len){

    uint32_t i;
    uint16_t* pdata;

    /* Loop for transmitting len bytes */
    for(i = 0; i < len; i++){
        /* Wait until TXE flag is set in SR */
        while(!USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_FLAG_TXE));

        /* Check USART word length for 9 bits or 8 bits in a frame */
        if(pUSART_Handle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS){
            /* If 9 bits load the DR with 2 bytes masking the bits other than first 9 bits */
            pdata = (uint16_t*)pTxBuffer;
            pUSART_Handle->pUSARTx->DR = (*pdata & (uint16_t)0x1FF);

            /* Check for USART parity control */
            if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
                /* 9 bits of user data will be sent */
                pTxBuffer++;
                pTxBuffer++;
            }
            else{
                /* 8 bits of user data will be sent */
                /* 9th bit will be replaced by parity bit by hardware */
                pTxBuffer++;
            }
        }
        else{
            /* 8 bits data transfer */
            pUSART_Handle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);

            /* Increment buffer adddress */
            pTxBuffer++;
        }
    }

    /* Wait until TC flag is set in SR */
    while(!USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_FLAG_TC));
}

void USART_ReceiveData(USART_Handle_t* pUSART_Handle, uint8_t* pRxBuffer, uint32_t len){

    uint32_t i;

    for(i = 0; i < len; i++){
        /* Wait until RXNE flag is set in SR */
        while(!USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_FLAG_RXNE));

        /* Check USART word length for 9 bits or 8 bits in a frame */
        if(pUSART_Handle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS){
            /* Reception of 9 bits data frame */
            /* Check for USART parity control */
            if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
                /* 9 bits are user data */
                *((uint16_t*)pRxBuffer) = (pUSART_Handle->pUSARTx->DR & (uint16_t)0x01FF);
                /* Increment the pRxBuffer two times, once per byte */
                pRxBuffer++;
                pRxBuffer++;
            }
            else{
                /* 8 bits are user data and 1 bit is parity */
                *pRxBuffer = (pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
                pRxBuffer++;
            }
        }
        else{
            /* Reception of 8 bits data frame */
            /* Check for USART parity control */
            if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
                /* 8 bits are user data */
                *pRxBuffer = (uint8_t)(pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
            }
            else{
                /* 7 bits are user data and 1 bit is parity */
                *pRxBuffer = (uint8_t)(pUSART_Handle->pUSARTx->DR & (uint8_t)0x7F);
            }
            pRxBuffer++;
        }
    }
}

uint8_t USART_SendDataIT(USART_Handle_t* pUSART_Handle, uint8_t* pTxBuffer, uint32_t len){

    uint8_t txstate = pUSART_Handle->TxBusyState;

    if(txstate != USART_BUSY_IN_TX){
        pUSART_Handle->TxLen = len;
        pUSART_Handle->pTxBuffer = pTxBuffer;
        pUSART_Handle->TxBusyState = USART_BUSY_IN_TX;

        /* Enable interrupt for TXE */
        pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);

        /* Enable interrupt for TC */
        pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);
    }

    return txstate;
}

uint8_t USART_ReceiveDataIT(USART_Handle_t* pUSART_Handle, uint8_t* pRxBuffer, uint32_t len){

    uint8_t rxstate = pUSART_Handle->RxBusyState;

    if(rxstate != USART_BUSY_IN_RX){
        pUSART_Handle->RxLen = len;
        pUSART_Handle->pRxBuffer = pRxBuffer;
        pUSART_Handle->RxBusyState = USART_BUSY_IN_RX;

        /* Enable interrupt for RXNE */
        pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);
    }

    return rxstate;
}

void USART_SetBaudRate(USART_RegDef_t* pUSARTx, uint32_t baudrate){

    uint32_t PCLKx;
    uint32_t usartdiv;
    uint32_t mantissa, fraction;
    uint32_t temp = 0;

    /* Get the value of APB bus clock into the variable PCLKx */
    if(pUSARTx == USART1 || pUSARTx == USART6){
        /* USART1 and USART6 are hanging on APB2 bus */
        PCLKx = RCC_GetPCLK2Value();
    }
    else{
        PCLKx = RCC_GetPCLK1Value();
    }

    /* Check OVER8 config bit */
    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8)){
        /* Over sampling by 8 */
        usartdiv = ((25 * PCLKx) / (2 * baudrate));
    }
    else{
        /* Over sampling by 16 */
        usartdiv = ((25 * PCLKx) / (4 * baudrate)); 
    }

    /* Calculate the mantissa */
    mantissa = usartdiv/100;
    temp |= mantissa << 4;

    /* Calculate the fraction part */
    fraction = (usartdiv - (mantissa * 100));

    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8)){
        /* Over sampling by 8 */
        fraction = (((fraction * 8) + 50) / 100) & ((uint8_t)0x07);
    }
    else{
        /* Over sampling by 16 */
        fraction = (((fraction * 16) + 50) / 100) & ((uint8_t)0x0F);
    }

    temp |= fraction;

    /* Set configuration in BRR register */
    pUSARTx->BRR = temp;
}

void USART_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di){

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

void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
    /* Find out the IPR register */
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift = (8*iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift);
}

void USART_IRQHandling(USART_Handle_t* pUSART_Handle){

    uint32_t temp1, temp2, temp3;
    uint32_t dummy_read;
    uint16_t* pdata;

    /* Handle for interrupt generated by TC event */

    /* Check state of TC bit in SR */
    temp1 = pUSART_Handle->pUSARTx->SR & (1 << USART_SR_TC);

    /* Check state of TCIE bit in CR1 */
    temp2 = pUSART_Handle->pUSARTx->CR1 & (1 << USART_CR1_TCIE);

    if(temp1 && temp2){
        /* Close transmission and call application callback if TxLen is zero */
        if(pUSART_Handle->TxBusyState == USART_BUSY_IN_TX){
            /* Check the TxLen */
            if(!pUSART_Handle->TxLen){
                /* Clear TC flag */
                pUSART_Handle->pUSARTx->SR &= ~(1 << USART_SR_TC);
                /* Clear TCIE control bit */
                pUSART_Handle->pUSARTx->CR1 &= ~(1 << USART_CR1_TCIE);
                /* Reset application state */
                pUSART_Handle->TxBusyState = USART_READY;
                /* Reset buffer adddress to NULL */
                pUSART_Handle->pTxBuffer = NULL;
                /* Reset length to zero */
                pUSART_Handle->TxLen = 0;
                /* Call application callback */
                USART_ApplicationEventCallback(pUSART_Handle, USART_EVENT_TX_CMPLT);
            }
        }
    }

    /* Handle for interrupt generated by TXE event */

    /* Check state of TXE bit in SR */
    temp1 = pUSART_Handle->pUSARTx->SR & (1 << USART_SR_TXE);

    /* Check state of TXEIE bit in CR1 */
    temp2 = pUSART_Handle->pUSARTx->CR1 & (1 << USART_CR1_TXEIE);

    if(temp1 && temp2){
        if(pUSART_Handle->TxBusyState == USART_BUSY_IN_TX){
            /* Keep sending data unitl TxLen reaches to zero */
            if(pUSART_Handle->TxLen > 0){
                /* Check USART word length for 9 bits or 8 bits in a frame */
                if(pUSART_Handle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS){
                    /* 9 bits data transfer */
                    /* Load the DR with 2 bytes masking the bits other than first 9 bits */
                    pdata = (uint16_t*)pUSART_Handle->pTxBuffer;
                    pUSART_Handle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);
                    /* Check parity control */
                    if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
                        /* 9 bits of user data will be sent */
                        pUSART_Handle->pTxBuffer++;
                        pUSART_Handle->pTxBuffer++;
                        pUSART_Handle->TxLen -= 2;
                    }
                    else{
                        /* 8 bits of user data will be sent */
                        /* 9th bit will be replaced by parity bit by HW */
                        pUSART_Handle->pTxBuffer++;
                        pUSART_Handle->TxLen--;
                    }
                }
                else{
                    /* 8 bits data transfer */
                    pUSART_Handle->pUSARTx->DR = (*pUSART_Handle->pTxBuffer & (uint8_t)0xFF);
                    pUSART_Handle->pTxBuffer++;
                    pUSART_Handle->TxLen--;
                }
            }
            if(pUSART_Handle->TxLen == 0){
                /* Clear TXEIE bit (disable interrupt for TXE flag) */
                pUSART_Handle->pUSARTx->CR1 &= ~(1 << USART_CR1_TXEIE);
            }
        }
    }

    /* Handle for interrupt generated by RXNE event */

    /* Check the state of RXNE bit in SR */
    temp1 = pUSART_Handle->pUSARTx->SR & (1 << USART_SR_RXNE);
    /* Check the state of RXNEIE bit in CR1 */
    temp2 = pUSART_Handle->pUSARTx->CR1 & (1 << USART_CR1_RXNEIE);

    if(temp1 & temp2){
        if(pUSART_Handle->RxBusyState == USART_BUSY_IN_RX){
            if(pUSART_Handle->RxLen > 0){
                /* Check USART word length for receiving 9 bits or 8 bits of data frame */
                if(pUSART_Handle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS){
                    /* 9 bits data in a frame */
                    /* Check parity control */
                    if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
                        /* 9 bits will be of user data */
                        *((uint16_t*)pUSART_Handle->pRxBuffer) = (pUSART_Handle->pUSARTx->DR &
                                                                  (uint16_t)0x01FF);
                        pUSART_Handle->pRxBuffer++;
                        pUSART_Handle->pRxBuffer++;
                        pUSART_Handle->RxLen -= 2;
                    }
                    else{
                        /* 8 bits will be of user data and 1 bit is parity */
                        *pUSART_Handle->pRxBuffer = (pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
                        pUSART_Handle->pRxBuffer++;
                        pUSART_Handle->RxLen--;
                    }
                }
                else{
                    /* 8 bits data in a frame */
                    /* Check parity control */
                    if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
                        /* 8 bits will be of user data */
                        *pUSART_Handle->pRxBuffer = (uint8_t)(pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
                    }
                    else{
                        /* 7 bits will be of user data and 1 bit is parity */
                        *pUSART_Handle->pRxBuffer = (uint8_t)(pUSART_Handle->pUSARTx->DR & (uint8_t)0x7F);
                    }
                    pUSART_Handle->pRxBuffer++;
                    pUSART_Handle->RxLen--;
                }
            }

            if(!pUSART_Handle->RxLen){
                /* Disable RXNE */
                pUSART_Handle->pUSARTx->CR1 &= ~(1 << USART_CR1_RXNEIE);
                /* Reset application state */
                pUSART_Handle->RxBusyState = USART_READY;
                /* Call application callback */
                USART_ApplicationEventCallback(pUSART_Handle, USART_EVENT_RX_CMPLT);
            }
        }
    }

    /* Handle for interrupt generated by CTS event */
    /* Note: CTS feature is not applicable for UART4 and UART5 */

    /* Check the state of CTS bit in SR */
    temp1 = pUSART_Handle->pUSARTx->SR & (1 << USART_SR_CTS);

    /* Check the state of CTSE bit in CR3 */
    temp2 = pUSART_Handle->pUSARTx->CR1 & (1 << USART_CR3_CTSE);

    /* Check the state of CTSIE bit in CR3 (not available in UART4 and UART5 */
    temp3 = pUSART_Handle->pUSARTx->CR3 & (1 << USART_CR3_CTSIE);

    if(temp1 && temp2 && temp3){
        /* Clear CTS flag in SR */
        pUSART_Handle->pUSARTx->SR &= ~(1 << USART_SR_CTS);
        /* Call application callback */
        USART_ApplicationEventCallback(pUSART_Handle, USART_EVENT_CTS);
    }

    /* Handle for interrupt generated by IDLE event */

    /* Check the state of IDLE bit in SR */
    temp1 = pUSART_Handle->pUSARTx->SR & (1 << USART_SR_IDLE);

    /* Check the state of IDLEIE bit in CR1 */
    temp2 = pUSART_Handle->pUSARTx->CR1 & (1 << USART_CR1_IDLEIE);

    if(temp1 && temp2){
        /* Clear IDLE flag in SR */
        dummy_read = pUSART_Handle->pUSARTx->SR;
        dummy_read = pUSART_Handle->pUSARTx->DR;
        (void)dummy_read;

        /* Call application callback */
        USART_ApplicationEventCallback(pUSART_Handle, USART_EVENT_IDLE);
    }

    /* Handle for interrupt generated by overrun event */

    /* Check the state of ORE bit in SR */
    temp1 = pUSART_Handle->pUSARTx->SR & (1 << USART_SR_ORE);

    /* Check the state of RXNEIE bit in CR1 */
    temp2 = pUSART_Handle->pUSARTx->CR1 & (1 << USART_CR1_RXNEIE);

    if(temp1 && temp2){
        /* Clear ORE flag in SR */
        dummy_read = pUSART_Handle->pUSARTx->SR;
        dummy_read = pUSART_Handle->pUSARTx->DR;
        (void)dummy_read;

        /* Call application callback */
        USART_ApplicationEventCallback(pUSART_Handle, USART_ERROR_ORE);
    }

    /* Handle for interrupt generated by error event */
    /* Note: EIE bit is required to enable interrupt generation in case of a framing error, */
    /*       overrun error or noise flag in case of Multi Buffer Communication */

    /* Check the state of EIE bit in CR3 */
    temp1 = pUSART_Handle->pUSARTx->CR3 & (1 << USART_CR3_EIE);

    if(temp1){
        temp2 = pUSART_Handle->pUSARTx->SR;
        if(temp2 & (1 << USART_SR_FE)){
            USART_ApplicationEventCallback(pUSART_Handle, USART_ERROR_FE);
        }

        if(temp2 & (1 << USART_SR_NF)){
            USART_ApplicationEventCallback(pUSART_Handle, USART_ERROR_NF);
        }

        if(temp2 & (1 << USART_SR_ORE)){
            USART_ApplicationEventCallback(pUSART_Handle, USART_ERROR_ORE);
        }
    }
}

void USART_Enable(USART_RegDef_t* pUSARTx, uint8_t en_or_di){

    if(en_or_di == ENABLE){
        pUSARTx->CR1 |= (1 << USART_CR1_UE);
    }
    else{
        pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
    }
}

uint8_t USART_GetFlagStatus(USART_RegDef_t* pUSARTx, uint32_t flagname){

    if(pUSARTx->SR & flagname){
        return SET;
    }

    return RESET;
}

void USART_ClearFlag(USART_RegDef_t* pUSARTx, uint16_t status_flagname){
}

__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t* pUSART_Handle, uint8_t app_event){

    /* This is a weak implementation. The application may override this function */
}
