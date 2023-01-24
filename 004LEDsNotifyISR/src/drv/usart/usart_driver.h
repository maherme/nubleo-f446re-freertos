/********************************************************************************************************//**
* @file usart_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the USART peripheral.
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
*/

#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include <stdint.h>
#include "stm32f446xx.h"

/**
 * @defgroup USART_Mode USART possible device mode.
 * @{
 */

#define USART_MODE_ONLY_TX      0   /**< @brief Mode transmission only. */
#define USART_MODE_ONLY_RX      1   /**< @brief Mode reception only. */
#define USART_MODE_TXRX         2   /**< @brief Mode transmission and reception. */
/** @} */

/**
 * @defgroup USART_Baudrate USART possible options for baudrate.
 * @{
 */
#define USART_STD_BAUD_1200     1200        /**< @brief Baudrate 1200 */
#define USART_STD_BAUD_2400     2400        /**< @brief Baudrate 2400 */
#define USART_STD_BAUD_9600     9600        /**< @brief Baudrate 9600 */
#define USART_STD_BAUD_19200    19200       /**< @brief Baudrate 19200 */
#define USART_STD_BAUD_38400    38400       /**< @brief Baudrate 38400 */
#define USART_STD_BAUD_57600    57600       /**< @brief Baudrate 57600 */
#define USART_STD_BAUD_115200   115200      /**< @brief Baudrate 115200 */
#define USART_STD_BAUD_230400   230400      /**< @brief Baudrate 230400 */
#define USART_STD_BAUD_460800   460800      /**< @brief Baudrate 460800 */
#define USART_STD_BAUD_921600   921600      /**< @brief Baudrate 921600 */
#define USART_STD_BAUD_2M       2000000     /**< @brief Baudrate 2M */
#define USART_STD_BAUD_3M       3000000     /**< @brief Baudrate 3M */
/** @} */

/**
 * @defgroup USART_Parity USART possible options for parity control.
 * @{
 */
#define USART_PARITY_DISABLE    0   /**< @brief Partity control disabled */
#define USART_PARITY_EN_EVEN    1   /**< @brief Even parity control enabled */
#define USART_PARITY_EN_ODD     2   /**< @brief Odd parity control enabled */
/** @} */

/**
 * @defgroup USART_WLength USART possible options for word length.
 * @{
 */
#define USART_WORDLEN_8BITS     0   /**< @brief Word length of 8 bits */
#define USART_WORDLEN_9BITS     1   /**< @brief Word length of 9 bits */
/** @} */

/**
 * @defgroup USART_StopBits USART possible options for number of stop bits.
 * @{
 */
#define USART_STOPBITS_1        0   /**< @brief Number stop bits 1 */
#define USART_STOPBITS_0_5      1   /**< @brief Number stop bits 1/2 */
#define USART_STOPBITS_2        2   /**< @brief Number stop bits 2 */
#define USART_STOPBITS_1_5      3   /**< @brief Number stop bits 3/2 */
/** @} */

/**
 * @defgroup USART_FlowCtl USART possible options for hardware flow control.
 * @{
 */
#define USART_HW_FLOW_CTRL_NONE     0   /**< @brief Flow control disabled */
#define USART_HW_FLOW_CTRL_CTS      1   /**< @brief Clear to send flow control enabled */
#define USART_HW_FLOW_CTRL_RTS      2   /**< @brief Ready to send flow control enabled */
#define USART_HW_FLOW_CTRL_CTS_RTS  3   /**< @brief CTS and RTS flow control enabled */
/** @} */

/**
 * @defgroup USART_Status USART related status flags definitions.
 * @{
 */
#define USART_FLAG_TXE      (1 << USART_SR_TXE)     /**< @brief TXE of USART status register */
#define USART_FLAG_TC       (1 << USART_SR_TC)      /**< @brief TC of USART status register */
#define USART_FLAG_RXNE     (1 << USART_SR_RXNE)    /**< @brief RXNE of USART status register */
/** @} */

/**
 * @defgroup USART_AppState USART possible application states.
 * @{
 */
#define USART_READY         0   /**< @brief USART ready */
#define USART_BUSY_IN_RX    1   /**< @brief USART busy in reception */
#define USART_BUSY_IN_TX    2   /**< @brief USART busy in transmission */
/** @} */

/**
 * @defgroup USART_AppEvent USART possible application events
 * @{
 */
#define USART_EVENT_TX_CMPLT    0   /**< @brief Transmission completed event */
#define USART_EVENT_RX_CMPLT    1   /**< @brief Reception completed event */
#define USART_EVENT_CTS         2   /**< @brief Clear to send event */
#define USART_EVENT_IDLE        3   /**< @brief IDLE event */
#define USART_EVENT_PE          4   /**< @brief Parity error event */
#define USART_ERROR_FE          5   /**< @brief Framing error event */
#define USART_ERROR_NF          6   /**< @brief Noise detected flag event */
#define USART_ERROR_ORE         7   /**< @brief Overrun error event */
/** @} */

/**
 * @brief Configuration structure for USARTx peripheral.
 */
typedef struct
{
    uint8_t USART_Mode;             /**< Possible values from @ref USART_Mode */
    uint32_t USART_Baud;            /**< Possible values from @ref USART_Baudrate */
    uint8_t USART_NoOfStopBits;     /**< Possible values from @ref USART_StopBits */
    uint8_t USART_WordLength;       /**< Possible values from @ref USART_WLength */
    uint8_t USART_ParityControl;    /**< Possible values from @ref USART_Parity */
    uint8_t USART_HWFlowControl;    /**< Possible values from @ref USART_FlowCtl */
}USART_Config_t;

/**
 * @brief Handle structure for USARTx peripheral.
 */
typedef struct
{
    USART_RegDef_t* pUSARTx;        /**< Base address of the USARTx peripheral */
    USART_Config_t USART_Config;    /**< USARTx peripheral configuration settings */
    uint8_t* pTxBuffer;             /**< To store the app. Tx buffer address */
    uint8_t* pRxBuffer;             /**< To store the app. Rx buffer address */
    uint32_t TxLen;                 /**< To store Tx len */
    uint32_t RxLen;                 /**< To store Rx len */
    uint8_t TxBusyState;            /**< To store busy state in transmission */
    uint8_t RxBusyState;            /**< To store busy state in reception */
}USART_Handle_t;

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to initialize USART peripheral.
 * @param[in] pUSART_Handle handle structure for the USART peripheral.
 * @return void
 */
void USART_Init(USART_Handle_t* pUSART_Handle);

/**
 * @brief Function to reset all register of a USART peripheral.
 * @param[in] pUSARTx the base address of the USARTx peripheral.
 * @return void
 */
void USART_DeInit(USART_RegDef_t* pUSARTx);

/**
 * @brief Function to control the peripheral clock of the USART peripheral.
 * @param[in] pUSARTx the base address of the USARTx peripheral.
 * @param[in] en_or_di for enable or disable.
 * @return void
 */
void USART_PerClkCtrl(USART_RegDef_t* pUSARTx, uint8_t en_or_di);

/**
 * @brief Function to send data.
 * @param[in] pUSART_Handle handle structure for the USART peripheral.
 * @param[in] pTxBuffer buffer with the data to send.
 * @param[in] len length of the data to send.
 * @return void
 * @note blocking call.
 */
void USART_SendData(USART_Handle_t* pUSART_Handle, uint8_t* pTxBuffer, uint32_t len);

/**
 * @brief Function to receive data.
 * @param[in] pUSART_Handle handle structure for the USART peripheral.
 * @param[out] pRxBuffer buffer to store the received data.
 * @param[in] len length of the data to receive.
 * @return void
 * @note blocking call.
 */
void USART_ReceiveData(USART_Handle_t* pUSART_Handle, uint8_t* pRxBuffer, uint32_t len);

/**
 * @brief Function to send data.
 * @param[in] pUSART_Handle handle structure for the USART peripheral.
 * @param[in] pTxBuffer buffer with the data to send.
 * @param[in] len length of the data to send.
 * @return @ref USART_AppState.
 */
uint8_t USART_SendDataIT(USART_Handle_t* pUSART_Handle, uint8_t* pTxBuffer, uint32_t len);

/**
 * @brief Function to receive data.
 * @param[in] pUSART_Handle handle structure for the USART peripheral.
 * @param[out] pRxBuffer buffer to store the received data.
 * @param[in] len length of the data to receive.
 * @return @ref USART_AppState.
 */
uint8_t USART_ReceiveDataIT(USART_Handle_t* pUSART_Handle, uint8_t* pRxBuffer, uint32_t len);

/**
 * @brief Function to set the baud rate of the USART peripheral.
 * @param[in] pUSARTx structure for managing registers of the USART peripheral.
 * @param[in] baudrate possible values of baud rate.
 * @return void
 */
void USART_SetBaudRate(USART_RegDef_t* pUSARTx, uint32_t baudrate);

/**
 * @brief Function to configure the IRQ number of the USART peripheral.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] en_or_di for enable or disable.
 * @return void.
 */
void USART_IRQConfig(uint8_t IRQNumber, uint8_t en_or_di);

/**
 * @brief Function to configure the IRQ number of the USART peripheral.
 * @param[in] IRQNumber number of the interrupt.
 * @param[in] IRQPriority priority of the interrupt.
 * @return void.
 */
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/**
 * @brief Function to handle the interrupt of the USART peripheral.
 * @param[in] pUSART_Handle handle structure to USART peripheral.
 * @return void.
 */
void USART_IRQHandling(USART_Handle_t* pUSART_Handle);

/**
 * @brief Function enable the USART peripheral.
 * @param[in] pUSARTx the base address of the USARTx peripheral.
 * @param[in] en_or_di for enable or disable.
 * @return void.
 */
void USART_Enable(USART_RegDef_t* pUSARTx, uint8_t en_or_di);

/**
 * @brief Function returns the status of a given flag.
 * @param[in] pUSARTx the base address of the USARTx peripheral.
 * @param[in] flagname the name of the flag.
 * @return flag status: FLAG_SET or FLAG_RESET.
 */
uint8_t USART_GetFlagStatus(USART_RegDef_t* pUSARTx, uint32_t flagname);

/**
 * @brief Function clear a flag.
 * @param[in] pUSARTx the base address of the USARTx peripheral.
 * @param[in] status_flagname name of the flag status.
 * @return void.
 */
void USART_ClearFlag(USART_RegDef_t* pUSARTx, uint16_t status_flagname);

/**
 * @brief Function for application callback.
 * @param[in] pUSART_Handle handle structure to USART peripheral.
 * @param[in] app_event @ref USART_AppEvent.
 * @return void.
 */
void USART_ApplicationEventCallback(USART_Handle_t* pUSART_Handle, uint8_t app_event);

#endif /* USART_DRIVER_H */
