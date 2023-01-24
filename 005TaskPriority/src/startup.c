/********************************************************************************************************//**
* @file startup.c
*
* @brief File containing the interrupt vector table and initialize process of the microcontroller.
*
* @note
*       These file is for the specific STM32F446xx microcontroller.
*/

#include <stdint.h>

/** @brief SRAM start address */
#define SRAM_START      0x20000000U
/** @brief Size of SRAM memory (128 KB) */
#define SRAM_SIZE       (128U * 1024U)
/** @brief SRAM end address */
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))
/** @brief Stack start address */
#define STACK_START     SRAM_END

/** @brief Used for storing the end of the text section in the linker script */
extern uint32_t _etext;
/** @brief Used for storing the start of the data section in the linker script */
extern uint32_t _sdata;
/** @brief Used for defining the end of the data section in the linker script */
extern uint32_t _edata;
/** @brief Used to initialize data section of the linker script */
extern uint32_t _la_data;
/** @brief Used for storing the start of the bss section in the linker script */
extern uint32_t _sbss;
/** @brief Used for storing the end of the bss section in the linker script */
extern uint32_t _ebss;

/** @brief Main function */
int main(void);
/** @brief Function for calling constructors and other library initialization which is 
 *  necessary before calling main.
 */
void __libc_init_array(void);

/** @brief Handler function for reset exception */
void Reset_Handler(void);
/** @brief Handler function for NMI exception */
void NMI_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for hard fault excepction */
void HardFault_Handler(void)            __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for memory manage exception */
void MemManage_Handler(void)            __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for bus fault exception */
void BusFault_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for usage fault exception */
void UsageFault_Handler(void)           __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for supervisor call exception */
void SVC_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for debug monitor exception */
void DebugMonitor_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for PendSV exception */
void PendSV_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for systick interrupt */
void SysTick_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for WWDG interrupt */
void WWDG_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for PVD interrupt */
void PVD_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TAMP STAMP interrupt */
void TAMP_STAMP_Handler(void)           __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for RCT wake up interrupt */
void RTC_WKUP_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for FLASH interrupt */
void FLASH_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for RCC interrupt */
void RCC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line 0 */
void EXTI0_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line 1 */
void EXTI1_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line 2 */
void EXTI2_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line 3 */
void EXTI3_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line 4 */
void EXTI4_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 0 interrupt */
void DMA1_Stream0_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 1 interrupt */
void DMA1_Stream1_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 2 interrupt */
void DMA1_Stream2_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 3 interrupt */
void DMA1_Stream3_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 4 interrupt */
void DMA1_Stream4_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 5 interrupt */
void DMA1_Stream5_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 6 interrupt */
void DMA1_Stream6_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for ADC interrupt */
void ADC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN1 transmission interrupt */
void CAN1_TX_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN1 reception 0 interrupt */
void CAN1_RX0_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN1 reception 1 interrupt */
void CAN1_RX1_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN1 SCE interrupt */
void CAN1_SCE_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line from 5 to 9 */
void EXTI9_5_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM1 Break interrupt and TIM9 global interrupt */
void TIM1_BRK_TIM9_Handler(void)        __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM1 Update interrupt and TIM10 global interrupt */
void TIM1_UP_TIM10_Handler(void)        __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
void TIM1_TRG_COM_TIM11_Handler(void)   __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM1 Capture compare interrupt */
void TIM1_CC_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM2 global interrupt */
void TIM2_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM3 global interrupt */
void TIM3_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM4 global interrupt */
void TIM4_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for I2C1 event interrupt */
void I2C1_EV_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for I2C1 error interrupt */
void I2C1_ER_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for I2C2 event interrupt */
void I2C2_EV_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for I2C2 error interrupt */
void I2C2_ER_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SPI1 interrupt */
void SPI1_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SPI2 interrupt */
void SPI2_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USART1 interrupt */
void USART1_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USART2 interrupt */
void USART2_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USART3 interrupt */
void USART3_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for external interrupt line from 10 to 15 */
void EXTI15_10_Handler(void)            __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for RTC Alarms (A and B) through EXTI line interrupt */
void RTC_Alarm_Handler(void)            __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USB On-The-Go FS Wakeup through EXTI line interrupt */
void OTG_FS_WKUP_Handler(void)          __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM8 break interrupt and TIM12 global interrupt */
void TIM8_BRK_TIM12_Handler(void)       __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM8 Update interrupt and TIM13 global interrupt */
void TIM8_UP_TIM13_Handler(void)        __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM8 Trigger and Commutation interrupts and TIM14 global interrupt */
void TIM8_TRG_COM_TIM14_Handler(void)   __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM8 Capture compare interrupt */
void TIM8_CC_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA1 stream 7 interrupt */
void DMA1_Stream7_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for FMC global interrupt */
void FMC_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SDIO global interrupt */
void SDIO_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM5 global interrupt */
void TIM5_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SPI3 interrupt */
void SPI3_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for UART4 interrupt */
void UART4_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for UART5 interrupt */
void UART5_Handler(void)                __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts */
void TIM6_DAC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for TIM7 global interrupt */
void TIM7_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 0 interrupt */
void DMA2_Stream0_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 1 interrupt */
void DMA2_Stream1_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 2 interrupt */
void DMA2_Stream2_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 3 interrupt */
void DMA2_Stream3_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 4 interrupt */
void DMA2_Stream4_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN2 transmission interrupt */
void CAN2_TX_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN2 reception 0 interrupt */
void CAN2_RX0_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN2 reception 1 interrupt */
void CAN2_RX1_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for CAN2 SCE interrupt */
void CAN2_SCE_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USB On The Go FS global interrupt */
void OTG_FS_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 5 interrupt */
void DMA2_Stream5_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 6 interrupt */
void DMA2_Stream6_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DMA2 stream 7 interrupt */
void DMA2_Stream7_Handler(void)         __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USART6 interrupt */
void USART6_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for I2C3 event interrupt */
void I2C3_EV_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for I2C3 error interrupt */
void I2C3_ER_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USB On The Go HS End Point 1 Out global interrupt */
void OTG_HS_EP1_OUT_Handler(void)       __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USB On The Go HS End Point 1 In global interrupt */
void OTG_HS_EP1_IN_Handler(void)        __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USB On The Go HS Wakeup through EXTI interrupt */
void OTG_HS_WKUP_Handler(void)          __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for USB On The Go HS global interrupt */
void OTG_HS_Handler(void)               __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for DCMI global interrupt */
void DCMI_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for FPU global interrupt */
void FPU_Handler(void)                  __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SPI4 interrupt */
void SPI4_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SAI1 interrupt */
void SAI1_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SAI2 interrupt */
void SAI2_Handler(void)                 __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for QuadSPI interrupt */
void QuadSPI_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for HDMI CEC interrupt */
void HDMI_CEC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for SPDIF Rx interrupt */
void SPDIF_Rx_Handler(void)             __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for FMPI2C1 interrupt */
void FMPI2C1_Handler(void)              __attribute__((weak, alias("Default_Handler")));
/** @brief Handler function for FMPI2C1 interrupt */
void FMPI2C1_error_Handler(void)        __attribute__((weak, alias("Default_Handler")));

/** @brief Array for managing the ISR vector */
uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMonitor_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_Handler,
    (uint32_t)PVD_Handler,
    (uint32_t)TAMP_STAMP_Handler,
    (uint32_t)RTC_WKUP_Handler,
    (uint32_t)FLASH_Handler,
    (uint32_t)RCC_Handler,
    (uint32_t)EXTI0_Handler,
    (uint32_t)EXTI1_Handler,
    (uint32_t)EXTI2_Handler,
    (uint32_t)EXTI3_Handler,
    (uint32_t)EXTI4_Handler,
    (uint32_t)DMA1_Stream0_Handler,
    (uint32_t)DMA1_Stream1_Handler,
    (uint32_t)DMA1_Stream2_Handler,
    (uint32_t)DMA1_Stream3_Handler,
    (uint32_t)DMA1_Stream4_Handler,
    (uint32_t)DMA1_Stream5_Handler,
    (uint32_t)DMA1_Stream6_Handler,
    (uint32_t)ADC_Handler,
    (uint32_t)CAN1_TX_Handler,
    (uint32_t)CAN1_RX0_Handler,
    (uint32_t)CAN1_RX1_Handler,
    (uint32_t)CAN1_SCE_Handler,
    (uint32_t)EXTI9_5_Handler,
    (uint32_t)TIM1_BRK_TIM9_Handler,
    (uint32_t)TIM1_UP_TIM10_Handler,
    (uint32_t)TIM1_TRG_COM_TIM11_Handler,
    (uint32_t)TIM1_CC_Handler,
    (uint32_t)TIM2_Handler,
    (uint32_t)TIM3_Handler,
    (uint32_t)TIM4_Handler,
    (uint32_t)I2C1_EV_Handler,
    (uint32_t)I2C1_ER_Handler,
    (uint32_t)I2C2_EV_Handler,
    (uint32_t)I2C2_ER_Handler,
    (uint32_t)SPI1_Handler,
    (uint32_t)SPI2_Handler,
    (uint32_t)USART1_Handler,
    (uint32_t)USART2_Handler,
    (uint32_t)USART3_Handler,
    (uint32_t)EXTI15_10_Handler,
    (uint32_t)RTC_Alarm_Handler,
    (uint32_t)OTG_FS_WKUP_Handler,
    (uint32_t)TIM8_BRK_TIM12_Handler,
    (uint32_t)TIM8_UP_TIM13_Handler,
    (uint32_t)TIM8_TRG_COM_TIM14_Handler,
    (uint32_t)TIM8_CC_Handler,
    (uint32_t)DMA1_Stream7_Handler,
    (uint32_t)FMC_Handler,
    (uint32_t)SDIO_Handler,
    (uint32_t)TIM5_Handler,
    (uint32_t)SPI3_Handler,
    (uint32_t)UART4_Handler,
    (uint32_t)UART5_Handler,
    (uint32_t)TIM6_DAC_Handler,
    (uint32_t)TIM7_Handler,
    (uint32_t)DMA2_Stream0_Handler,
    (uint32_t)DMA2_Stream1_Handler,
    (uint32_t)DMA2_Stream2_Handler,
    (uint32_t)DMA2_Stream3_Handler,
    (uint32_t)DMA2_Stream4_Handler,
    0,
    0,
    (uint32_t)CAN2_TX_Handler,
    (uint32_t)CAN2_RX0_Handler,
    (uint32_t)CAN2_RX1_Handler,
    (uint32_t)CAN2_SCE_Handler,
    (uint32_t)OTG_FS_Handler,
    (uint32_t)DMA2_Stream5_Handler,
    (uint32_t)DMA2_Stream6_Handler,
    (uint32_t)DMA2_Stream7_Handler,
    (uint32_t)USART6_Handler,
    (uint32_t)I2C3_EV_Handler,
    (uint32_t)I2C3_ER_Handler,
    (uint32_t)OTG_HS_EP1_OUT_Handler,
    (uint32_t)OTG_HS_EP1_IN_Handler,
    (uint32_t)OTG_HS_WKUP_Handler,
    (uint32_t)OTG_HS_Handler,
    (uint32_t)DCMI_Handler,
    0,
    0,
    (uint32_t)FPU_Handler,
    0,
    0,
    (uint32_t)SPI4_Handler,
    0,
    0,
    (uint32_t)SAI1_Handler,
    0,
    0,
    0,
    (uint32_t)SAI2_Handler,
    (uint32_t)QuadSPI_Handler,
    (uint32_t)HDMI_CEC_Handler,
    (uint32_t)SPDIF_Rx_Handler,
    (uint32_t)FMPI2C1_Handler,
    (uint32_t)FMPI2C1_error_Handler,
};

/** @brief Default handler for not configured interrupt */
void Default_Handler(void){
    while(1);
}

void Reset_Handler(void){
    /* copy .data section to SRAM */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t*)&_sdata; /* sram */
    uint8_t *pSrc = (uint8_t*)&_la_data; /* flash */

    for(uint32_t i = 0; i < size; i++){
        *pDst++ = *pSrc++;
    }

    /* init the .bss section to zero in SRAM */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i = 0; i < size; i++){
        *pDst++ = 0;
    }

    __libc_init_array();

    main();
}
