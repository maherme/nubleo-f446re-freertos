/********************************************************************************************************//**
* @file stm32f446xx.h
*
* @brief File containing macros definition and structures for configuring the microcontroller.
*
* @note
*       These file is for the specific STM32F446xx microcontroller.
*/

#ifndef STM32F446XX_H
#define STM32F446XX_H

#include "cmsis_m4.h"
#include <stdint.h>

/***********************************************************************************************************/
/*                          Generic macros                                                                 */
/***********************************************************************************************************/

/**
 * @name Some Generic Macros.
 * @{
 */
#define ENABLE              1           /**< @brief Enable value */
#define DISABLE             0           /**< @brief Disable value */
#define SET                 ENABLE      /**< @brief Set value */
#define RESET               DISABLE     /**< @brief Reset value */
#define GPIO_PIN_SET        SET         /**< @brief Set value for GPIO PIN */
#define GPIO_PIN_RESET      RESET       /**< @brief Reset value for GPIO PIN */
#define FLAG_SET            SET         /**< @brief Set value for a flag */
#define FLAG_RESET          RESET       /**< @brief Reset value for a flag */
/** @} */

/***********************************************************************************************************/
/*                          ARM Cortex M4 Processor Specific Registers                                     */
/***********************************************************************************************************/

/**
 * @name ARM Cortex M4 Processor Specific Registers.
 * @{
 */
#define NVIC_ISER0      ((volatile uint32_t*)0xE000E100)        /**< @brief NVIC ISER0 Register Addr */
#define NVIC_ISER1      ((volatile uint32_t*)0xE000E104)        /**< @brief NVIC ISER1 Register Addr */
#define NVIC_ISER2      ((volatile uint32_t*)0xE000E108)        /**< @brief NVIC ISER2 Register Addr */
#define NVIC_ISER3      ((volatile uint32_t*)0xE000E10C)        /**< @brief NVIC ISER3 Register Addr */

#define NVIC_ICER0      ((volatile uint32_t*)0xE000E180)        /**< @brief NVIC ICER0 Register Addr */
#define NVIC_ICER1      ((volatile uint32_t*)0xE000E184)        /**< @brief NVIC ICER1 Register Addr */
#define NVIC_ICER2      ((volatile uint32_t*)0xE000E188)        /**< @brief NVIC ICER2 Register Addr */
#define NVIC_ICER3      ((volatile uint32_t*)0xE000E18C)        /**< @brief NVIC ICER3 Register Addr */

#define NVIC_PR_BASEADDR    ((volatile uint32_t*)0xE000E400)    /**< @brief NVIC Priority Register Addr */

#define DBGMCU_BASEADDR     0xE0042000                          /**< @brief Debug Peripheral Base Addr */

#define NO_PR_BITS_IMPLEMENTED  4 /**< @brief Numb of priority bits implemented in the Priority Register */
/** @} */

/***********************************************************************************************************/
/*                          Memory and Bus Base Address Definition                                         */
/***********************************************************************************************************/

/**
 * @name Base and End Addresses of Memories.
 * @{
 */
#define FLASH_BASEADDR      0x08000000U     /**< @brief Base addr of flash memory, size 512KB */
#define FLASH_ENDADDR       0x081FFFFFU     /**< @brief End addr of the total flash memory */
#define SRAM1_BASEADDR      0x20000000U     /**< @brief Base addr of system RAM first block, size 112KB */
#define SRAM1_ENDADDR       0x2001BFFFU     /**< @brief End addr of the total SRAM1 memory */
#define SRAM2_BASEADDR      0x2001C000U     /**< @brief Base addr of system RAM second block, size 16KB */
#define SRAM2_ENDADDR       0x2001FFFFU     /**< @brief End addr of the total SRAM2 memory */
#define SRAM                SRAM1_BASEADDR  /**< @brief Base addr of the SRAM memory, size 128KB */
#define ROM                 0x1FFF0000U     /**< @brief Base addr of system memory or ROM, size 30KB */
#define BKPSRAM_ENDADDR     0x40024FFFU     /**< @brief End addr of the total backup SRAM, size 4KB */
#define OTP_BASEADDR        0x1FFF7800      /**< @brief Base addr of One-time programmable bytes */
#define OTP_SECTOR_SIZE     32              /**< @brief Size of OTP sector in bytes */
/** @} */

/**
 * @name Base Addresses of AHBx and APBx Bus Peripheral.
 * @{
 */
#define PERIPH_BASEADDR     0x40000000U     /**< @brief Base addr of peripherals */
#define APB1_BASEADDR       PERIPH_BASEADDR /**< @brief Base addr of peripheral connected to APB1 bus */
#define APB2_BASEADDR       0x40010000U     /**< @brief Base addr of peripheral connected to APB2 bus */
#define AHB1_BASEADDR       0x40020000U     /**< @brief Base addr of peripheral connected to AHB1 bus */
#define AHB2_BASEADDR       0x50000000U     /**< @brief Base addr of peripheral connected to AHB2 bus */
#define AHB3_BASEADDR       0xA0000000U     /**< @brief Base addr of peripheral connected to AHB3 bus */
/** @} */

/***********************************************************************************************************/
/*                          Peripheral Base Address Definition                                             */
/***********************************************************************************************************/

/**
 * @name Base addresses of peripheral connected to AHB1 bus.
 * @{
*/
#define GPIOA_BASEADDR      (AHB1_BASEADDR + 0x0000)    /**< @brief Base address of GPIOA */
#define GPIOB_BASEADDR      (AHB1_BASEADDR + 0x0400)    /**< @brief Base address of GPIOB */
#define GPIOC_BASEADDR      (AHB1_BASEADDR + 0x0800)    /**< @brief Base address of GPIOC */
#define GPIOD_BASEADDR      (AHB1_BASEADDR + 0x0C00)    /**< @brief Base address of GPIOD */
#define GPIOE_BASEADDR      (AHB1_BASEADDR + 0x1000)    /**< @brief Base address of GPIOE */
#define GPIOF_BASEADDR      (AHB1_BASEADDR + 0x1400)    /**< @brief Base address of GPIOF */
#define GPIOG_BASEADDR      (AHB1_BASEADDR + 0x1800)    /**< @brief Base address of GPIOG */
#define GPIOH_BASEADDR      (AHB1_BASEADDR + 0x1C00)    /**< @brief Base address of GPIOH */
#define CRC_BASEADDR        (AHB1_BASEADDR + 0x3000)    /**< @brief Base address of CRC */
#define RCC_BASEADDR        (AHB1_BASEADDR + 0x3800)    /**< @brief Base address of RCC */
#define FLASHINTR_BASEADDR  (AHB1_BASEADDR + 0x3C00)    /**< @brief Base address of flash interface regist */
#define BKPSRAM_BASEADDR    (AHB1_BASEADDR + 0x4000)    /**< @brief Base address of BKPSRAM */
#define DMA1_BASEADDR       (AHB1_BASEADDR + 0x6000)    /**< @brief Base address of DMA1 */
#define DMA1_STR0_BASEADDR  (AHB1_BASEADDR + 0x6010)    /**< @brief Base address of DMA1 stream 0 */
#define DMA1_STR1_BASEADDR  (AHB1_BASEADDR + 0x6028)    /**< @brief Base address of DMA1 stream 1 */
#define DMA1_STR2_BASEADDR  (AHB1_BASEADDR + 0x6040)    /**< @brief Base address of DMA1 stream 2 */
#define DMA1_STR3_BASEADDR  (AHB1_BASEADDR + 0x6058)    /**< @brief Base address of DMA1 stream 3 */
#define DMA1_STR4_BASEADDR  (AHB1_BASEADDR + 0x6070)    /**< @brief Base address of DMA1 stream 4 */
#define DMA1_STR5_BASEADDR  (AHB1_BASEADDR + 0x6088)    /**< @brief Base address of DMA1 stream 5 */
#define DMA1_STR6_BASEADDR  (AHB1_BASEADDR + 0x60A0)    /**< @brief Base address of DMA1 stream 6 */
#define DMA1_STR7_BASEADDR  (AHB1_BASEADDR + 0x60B8)    /**< @brief Base address of DMA1 stream 7 */
#define DMA2_BASEADDR       (AHB1_BASEADDR + 0x6400)    /**< @brief Base address of DMA2 */
#define DMA2_STR0_BASEADDR  (AHB1_BASEADDR + 0x6410)    /**< @brief Base address of DMA2 stream 0 */
#define DMA2_STR1_BASEADDR  (AHB1_BASEADDR + 0x6428)    /**< @brief Base address of DMA2 stream 1 */
#define DMA2_STR2_BASEADDR  (AHB1_BASEADDR + 0x6440)    /**< @brief Base address of DMA2 stream 2 */
#define DMA2_STR3_BASEADDR  (AHB1_BASEADDR + 0x6458)    /**< @brief Base address of DMA2 stream 3 */
#define DMA2_STR4_BASEADDR  (AHB1_BASEADDR + 0x6470)    /**< @brief Base address of DMA2 stream 4 */
#define DMA2_STR5_BASEADDR  (AHB1_BASEADDR + 0x6488)    /**< @brief Base address of DMA2 stream 5 */
#define DMA2_STR6_BASEADDR  (AHB1_BASEADDR + 0x64A0)    /**< @brief Base address of DMA2 stream 6 */
#define DMA2_STR7_BASEADDR  (AHB1_BASEADDR + 0x64B8)    /**< @brief Base address of DMA2 stream 7 */
#define USBOTGHS_BASEADDR   (AHB1_BASEADDR + 0x40000)   /**< @brief Base address of USB OTG HS */
/** @} */

/**
 * @name Base addresses of peripheral connected to APB1 bus.
 * @{
 */
#define TIM2_BASEADDR       (APB1_BASEADDR + 0x0000)    /**< @brief Base address of TIM2 */
#define TIM3_BASEADDR       (APB1_BASEADDR + 0x0400)    /**< @brief Base address of TIM3 */
#define TIM4_BASEADDR       (APB1_BASEADDR + 0x0800)    /**< @brief Base address of TIM4 */
#define TIM5_BASEADDR       (APB1_BASEADDR + 0x0C00)    /**< @brief Base address of TIM5 */
#define TIM6_BASEADDR       (APB1_BASEADDR + 0x1000)    /**< @brief Base address of TIM6 */
#define TIM7_BASEADDR       (APB1_BASEADDR + 0x1400)    /**< @brief Base address of TIM7 */
#define TIM12_BASEADDR      (APB1_BASEADDR + 0x1800)    /**< @brief Base address of TIM12 */
#define TIM13_BASEADDR      (APB1_BASEADDR + 0x1C00)    /**< @brief Base address of TIM13 */
#define TIM14_BASEADDR      (APB1_BASEADDR + 0x2000)    /**< @brief Base address of TIM14 */
#define RTCBKP_BASEADDR     (APB1_BASEADDR + 0x2800)    /**< @brief Base address of RTC and BKP registers */
#define WWDG_BASEADDR       (APB1_BASEADDR + 0x2C00)    /**< @brief Base address of WWDG */
#define IWDG_BASEADDR       (APB1_BASEADDR + 0x3000)    /**< @brief Base address of IWDG */
#define SPI2_I2S2_BASEADDR  (APB1_BASEADDR + 0x3800)    /**< @brief Base address of SPI2 / I2S2 */
#define SPI3_I2S3_BASEADDR  (APB1_BASEADDR + 0x3C00)    /**< @brief Base address of SPI3 / I2S3 */
#define SPDIF_RX_BASEADDR   (APB1_BASEADDR + 0x4000)    /**< @brief Base address of SPDIF-RX */
#define USART2_BASEADDR     (APB1_BASEADDR + 0x4400)    /**< @brief Base address of USART2 */
#define USART3_BASEADDR     (APB1_BASEADDR + 0x4800)    /**< @brief Base address of USART3 */
#define UART4_BASEADDR      (APB1_BASEADDR + 0x4C00)    /**< @brief Base address of UART4 */
#define UART5_BASEADDR      (APB1_BASEADDR + 0x5000)    /**< @brief Base address of UART5 */
#define I2C1_BASEADDR       (APB1_BASEADDR + 0x5400)    /**< @brief Base address of I2C1 */
#define I2C2_BASEADDR       (APB1_BASEADDR + 0x5800)    /**< @brief Base address of I2C2 */
#define I2C3_BASEADDR       (APB1_BASEADDR + 0x5C00)    /**< @brief Base address of I2C3 */
#define CAN1_BASEADDR       (APB1_BASEADDR + 0x6400)    /**< @brief Base address of CAN1 */
#define CAN2_BASEADDR       (APB1_BASEADDR + 0x6800)    /**< @brief Base address of CAN2 */
#define HDMI_CEC_BASEADDR   (APB1_BASEADDR + 0x6C00)    /**< @brief Base address of HDMI-CEC */
#define PWR_BASEADDR        (APB1_BASEADDR + 0x7000)    /**< @brief Base address of PWR */
#define DAC_BASEADDR        (APB1_BASEADDR + 0x7400)    /**< @brief Base address of DAC */
/** @} */

/**
 * @name Base addresses of peripheral connected to AHB2 bus.
 * @{
 */
#define USBOTGFS_BASEADDR   (AHB2_BASEADDR + 0x0000)    /**< @brief Base address of USB OTG FS */
#define DCMI_BASEADDR       (AHB2_BASEADDR + 0x50000)   /**< @brief Base address of DCMI */
/** @} */

/**
 * @name Base addresses of peripheral connected to APB2 bus.
 * @{
 */
#define TIM1_BASEADDR       (APB2_BASEADDR + 0x0000)    /**< @brief Base address of TIM1 */
#define TIM8_BASEADDR       (APB2_BASEADDR + 0x0400)    /**< @brief Base address of TIM8 */
#define USART1_BASEADDR     (APB2_BASEADDR + 0x1000)    /**< @brief Base address of USART1 */
#define USART6_BASEADDR     (APB2_BASEADDR + 0x1400)    /**< @brief Base address of USART6 */
#define ADC1_2_3_BASEADDR   (APB2_BASEADDR + 0x2000)    /**< @brief Base address of ADC1 - ADC2 - ADC3 */
#define SDMMC_BASEADDR      (APB2_BASEADDR + 0x2C00)    /**< @brief Base address of SDMMC */
#define SPI1_BASEADDR       (APB2_BASEADDR + 0x3000)    /**< @brief Base address of SPI1 */
#define SPI4_BASEADDR       (APB2_BASEADDR + 0x3400)    /**< @brief Base address of SPI4 */
#define SYSCFG_BASEADDR     (APB2_BASEADDR + 0x3800)    /**< @brief Base address of SYSCFG */
#define EXTI_BASEADDR       (APB2_BASEADDR + 0x3C00)    /**< @brief Base address of EXTI */
#define TIM9_BASEADDR       (APB2_BASEADDR + 0x4000)    /**< @brief Base address of TIM9 */
#define TIM10_BASEADDR      (APB2_BASEADDR + 0x4400)    /**< @brief Base address of TIM10 */
#define TIM11_BASEADDR      (APB2_BASEADDR + 0x4800)    /**< @brief Base address of TIM11 */
#define SAI1_BASEADDR       (APB2_BASEADDR + 0x5800)    /**< @brief Base address of SAI1 */
#define SAI2_BASEADDR       (APB2_BASEADDR + 0x5C00)    /**< @brief Base address of SAI2 */
/** @} */

/**
 * @name Base addresses of peripheral connected to AHB3 bus.
 * @{
 */
#define FMC_BASEADDR        (AHB3_BASEADDR + 0x0000)    /**< @brief Base addr of FMC control register */
#define QUADSPI_BASEADDR    (AHB3_BASEADDR + 0x1000)    /**< @brief Base addr of QUADSPI register */
/** @} */

/***********************************************************************************************************/
/*                          Peripheral Register Definition Structures                                      */
/***********************************************************************************************************/

/**
 * @brief Peripheral register definition structure for GPIO.
 */
typedef struct
{
    volatile uint32_t MODER;    /**< @brief GPIO port mode register                      Addr offset 0x00 */
    volatile uint32_t OTYPER;   /**< @brief GPIO port output type register               Addr offset 0x04 */
    volatile uint32_t OSPEEDER; /**< @brief GPIO port output speed register              Addr offset 0x08 */
    volatile uint32_t PUPDR;    /**< @brief GPIO port pull-up/pull-down register         Addr offset 0x0C */
    volatile uint32_t IDR;      /**< @brief GPIO port input data register                Addr offset 0x10 */
    volatile uint32_t ODR;      /**< @brief GPIO port output data register               Addr offset 0x14 */
    volatile uint32_t BSRR;     /**< @brief GPIO port bit set/reset register             Addr offset 0x18 */
    volatile uint32_t LCKR;     /**< @brief GPIO port configuration lock register        Addr offset 0x1C */
    volatile uint32_t AFR[2];   /**< @brief GPIO alternate funct low register AFR[0]  Addr offset 0x20<br> */
                                /**< @brief GPIO alternate function high register AFR[1] Addr offset 0x24 */
}GPIO_RegDef_t;

/**
 * @brief Peripheral register definition structure for RCC.
 */
typedef struct
{
    volatile uint32_t CR;           /**< @brief RCC clock control register                   Addr off 0x00 */
    volatile uint32_t PLLCFGR;      /**< @brief RCC PLL configuration register               Addr off 0x04 */
    volatile uint32_t CFGR;         /**< @brief RCC clock configuration register             Addr off 0x08 */
    volatile uint32_t CIR;          /**< @brief RCC clock interrupt register                 Addr off 0x0C */
    volatile uint32_t AHB1RSTR;     /**< @brief RCC AHB1 peripheral reset register           Addr off 0x10 */
    volatile uint32_t AHB2RSTR;     /**< @brief RCC AHB2 peripheral reset register           Addr off 0x14 */
    volatile uint32_t AHB3RSTR;     /**< @brief RCC AHB3 peripheral reset register           Addr off 0x18 */
    uint32_t RESERVED0;             /**< @brief Reserved                                     Addr off 0x1C */
    volatile uint32_t APB1RSTR;     /**< @brief RCC APB1 peripheral reset register           Addr off 0x20 */
    volatile uint32_t APB2RSTR;     /**< @brief RCC APB2 peripheral reset register           Addr off 0x24 */
    uint32_t RESERVED1;             /**< @brief Reserved                                     Addr off 0x28 */
    uint32_t RESERVED2;             /**< @brief Reserved                                     Addr off 0x2C */
    volatile uint32_t AHB1ENR;      /**< @brief RCC AHB1 peripheral clock enable register    Addr off 0x30 */
    volatile uint32_t AHB2ENR;      /**< @brief RCC AHB2 peripheral clock enable register    Addr off 0x34 */
    volatile uint32_t AHB3ENR;      /**< @brief RCC AHB3 peripheral clock enable register    Addr off 0x38 */
    uint32_t RESERVED3;             /**< @brief Reserved                                     Addr off 0x3C */
    volatile uint32_t APB1ENR;      /**< @brief RCC APB1 peripheral clock enable register    Addr off 0x40 */
    volatile uint32_t APB2ENR;      /**< @brief RCC APB2 peripheral clock enable register    Addr off 0x44 */
    uint32_t RESERVED4;             /**< @brief Reserved                                     Addr off 0x48 */
    uint32_t RESERVED5;             /**< @brief Reserved                                     Addr off 0x4C */
    volatile uint32_t AHB1LPENR;    /**< @brief RCC AHB1 peri clk en in low power mode reg   Addr off 0x50 */
    volatile uint32_t AHB2LPENR;    /**< @brief RCC AHB2 peri clk en in low power mode reg   Addr off 0x54 */
    volatile uint32_t AHB3LPENR;    /**< @brief RCC AHB3 peri clk en in low power mode reg   Addr off 0x58 */
    uint32_t RESERVED6;             /**< @brief Reserved                                     Addr off 0x5C */
    volatile uint32_t APB1LPENR;    /**< @brief RCC APB1 peri clk en in low power mode reg   Addr off 0x60 */
    volatile uint32_t APB2LPENR;    /**< @brief RCC APB2 peri clk en in low power mode reg   Addr off 0x64 */
    uint32_t RESERVED7;             /**< @brief Reserved                                     Addr off 0x68 */
    uint32_t RESERVED8;             /**< @brief Reserved                                     Addr off 0x6C */
    volatile uint32_t BDCR;         /**< @brief RCC Backup domain control register           Addr off 0x70 */
    volatile uint32_t CSR;          /**< @brief RCC clock control & status register          Addr off 0x74 */
    uint32_t RESERVED9;             /**< @brief Reserved                                     Addr off 0x78 */
    uint32_t RESERVED10;            /**< @brief Reserved                                     Addr off 0x7C */
    volatile uint32_t SSCGR;        /**< @brief RCC spread spectrum clk generation reg       Addr off 0x80 */
    volatile uint32_t PLLI2SCFGR;   /**< @brief RCC PLLI2S configuration register            Addr off 0x84 */
    volatile uint32_t PLLSAICFGR;   /**< @brief RCC PLL configuration register               Addr off 0x88 */
    volatile uint32_t DCKCFGR;      /**< @brief RCC dedicated clock configuration register   Addr off 0x8C */
    volatile uint32_t CKGATENR;     /**< @brief RCC clocks gated enable register             Addr off 0x90 */
    volatile uint32_t DCKCFGR2;     /**< @brief RCC dedicated clocks configuration reg 2     Addr off 0x94 */
}RCC_RegDef_t;

/**
 * @brief Peripheral register definition structure for PWR.
 */
typedef struct
{
    volatile uint32_t CR;           /**< @brief PWR power control register          Address offset 0x00 */
    volatile uint32_t CSR;          /**< @brief PWR power control/status register   Address offset 0x04 */
}PWR_RegDef_t;

/**
 * @brief Peripheral register definition structure for EXTI.
 */
typedef struct
{
    volatile uint32_t IMR;      /**< @brief Interrupt mask register              Address offset 0x00 */
    volatile uint32_t EMR;      /**< @brief Event mask register                  Address offset 0x04 */
    volatile uint32_t RTSR;     /**< @brief Rising trigger selection register    Address offset 0x08 */
    volatile uint32_t FTSR;     /**< @brief Falling trigger selection register   Address offset 0x0C */
    volatile uint32_t SWIER;    /**< @brief Software interrupt event register    Address offset 0x10 */
    volatile uint32_t PR;       /**< @brief Pending register                     Address offset 0x14 */
}EXTI_RegDef_t;

/**
 * @brief Peripheral register definition structure for SYSCFG.
 */
typedef struct
{
    volatile uint32_t MEMRMP;       /**< @brief SYSCFG memory remap register            Addr offset 0x00 */
    volatile uint32_t PMC;          /**< @brief SYSCFG peripheral mode config register  Addr offset 0x04 */
    volatile uint32_t EXTICR[4];    /**< @brief SYSCFG ext int cfg reg 1 EXTICR[0]  Addr offset 0x08<br> */
                                    /**< @brief SYSCFG ext int cfg reg 2 EXTICR[1]  Addr offset 0x0C<br> */
                                    /**< @brief SYSCFG ext int cfg reg 3 EXTICR[2]  Addr offset 0x10<br> */
                                    /**< @brief SYSCFG ext int cfg reg 4 EXTICR[3]  Addr offset 0x14 */
    uint32_t RESERVED0;             /**< @brief Reserved                                Addr offset 0x18 */
    uint32_t RESERVED1;             /**< @brief Reserved                                Addr offset 0x1C */
    volatile uint32_t CMPCR;        /**< @brief Compensation cell control register      Addr offset 0x20 */
    uint32_t RESERVED2;             /**< @brief Reserved                                Addr offset 0x24 */
    uint32_t RESERVED3;             /**< @brief Reserved                                Addr offset 0x28 */
    volatile uint32_t CFGR;         /**< @brief SYSCFG configuration register           Addr offset 0x2C */
}SYSCFG_RegDef_t;

/**
 * @brief Peripheral register definition structure for SPI.
 */
typedef struct
{
    volatile uint32_t CR1;          /**< @brief SPI control register 1          Address offset 0x00 */
    volatile uint32_t CR2;          /**< @brief SPI control register 2          Address offset 0x04 */
    volatile uint32_t SR;           /**< @brief SPI status register             Address offset 0x08 */
    volatile uint32_t DR;           /**< @brief SPI data register               Address offset 0x0C */
    volatile uint32_t CRCPR;        /**< @brief SPI CRC polynomial register     Address offset 0x10 */
    volatile uint32_t RXCRCR;       /**< @brief SPI RX CRC register             Address offset 0x14 */
    volatile uint32_t TXCRCR;       /**< @brief SPI TX CRC register             Address offset 0x18 */
    volatile uint32_t I2SCFGR;      /**< @brief SPI_I2S configuration register  Address offset 0x1C */
    volatile uint32_t I2SPR;        /**< @brief SPI_I2S prescaler register      Address offset 0x20 */
}SPI_RegDef_t;

/**
 * @brief Peripheral register definition structure for I2C.
 */
typedef struct
{
    volatile uint32_t CR1;          /**< @brief I2C control register 1          Address offset 0x00 */
    volatile uint32_t CR2;          /**< @brief I2C control register 2          Address offset 0x04 */
    volatile uint32_t OAR1;         /**< @brief I2C own address register 1      Address offset 0x08 */
    volatile uint32_t OAR2;         /**< @brief I2C own address register 2      Address offset 0x0C */
    volatile uint32_t DR;           /**< @brief I2C data register               Address offset 0x10 */
    volatile uint32_t SR1;          /**< @brief I2C status register 1           Address offset 0x14 */
    volatile uint32_t SR2;          /**< @brief I2C status register 2           Address offset 0x18 */
    volatile uint32_t CCR;          /**< @brief I2C clock control register      Address offset 0x1C */
    volatile uint32_t TRISE;        /**< @brief I2C TRISE register              Address offset 0x20 */
    volatile uint32_t FLTR;         /**< @brief I2C FLTR register               Address offset 0x24 */
}I2C_RegDef_t;

/**
 * @brief Peripheral register definition structure for USART.
 */
typedef struct
{
    volatile uint32_t SR;       /**< @brief USART status register                Address offset 0x00 */
    volatile uint32_t DR;       /**< @brief USART data register                  Address offset 0x04 */
    volatile uint32_t BRR;      /**< @brief USART baud rate register             Address offset 0x08 */
    volatile uint32_t CR1;      /**< @brief USART control register 1             Address offset 0x0C */
    volatile uint32_t CR2;      /**< @brief USART control register 2             Address offset 0x10 */
    volatile uint32_t CR3;      /**< @brief USART control register 3             Address offset 0x14 */
    volatile uint32_t GTPR;     /**< @brief USART guard time and prescaler reg   Address offset 0x18 */
}USART_RegDef_t;

/**
 * @brief Peripheral register definition structure for CRC.
 */
typedef struct
{
    volatile uint32_t DR;           /**< @brief CRC data register               Address offset 0x00 */
    volatile uint32_t IDR;          /**< @brief CRC independent data register   Address offset 0x04 */
    volatile uint32_t CR;           /**< @brief CRC control register            Address offset 0x08 */
}CRC_RegDef_t;

/**
 * @brief Peripheral register definition structure for DBG.
 */
typedef struct
{
    volatile uint32_t IDCODE;   /**< @brief Debug MCU ID code register          Address offset 0x00 */
    volatile uint32_t CR;       /**< @brief Debug MCU configuration register    Address offset 0x04 */
    volatile uint32_t APB1_FZ;  /**< @brief Debug MCU APB1 freeze register      Address offset 0x08 */
    volatile uint32_t APB2_FZ;  /**< @brief Debug MCU APB2 freeze register      Address offset 0x0C */
}DBG_RegDef_t;

/**
 * @brief Peripheral register definition structure for FLASH Interface.
 */
typedef struct
{
    volatile uint32_t ACR;          /**< @brief Flash access control register   Address offset 0x00 */
    volatile uint32_t KEYR;         /**< @brief Flash key register              Address offset 0x04 */
    volatile uint32_t OPTKEYR;      /**< @brief Flash option key register       Address offset 0x08 */
    volatile uint32_t SR;           /**< @brief Flash status register           Address offset 0x0C */
    volatile uint32_t CR;           /**< @brief Flash control register          Address offset 0x10 */
    volatile uint32_t OPTCR;        /**< @brief Flash option control register   Address offset 0x14 */
}FLASHINTR_RegDef_t;

/**
 * @brief Peripheral register definition structure for TIM.
 */
typedef struct
{
    volatile uint32_t CR1;          /**< @brief Control register 1                  Address offset 0x00 */
    volatile uint32_t CR2;          /**< @brief Control register 2                  Address offset 0x04 */
    volatile uint32_t SMCR;         /**< @brief Slave mode control register         Address offset 0x08 */
    volatile uint32_t DIER;         /**< @brief DMA/Interrupt enable register       Address offset 0x0C */
    volatile uint32_t SR;           /**< @brief Status resgister                    Address offset 0x10 */
    volatile uint32_t EGR;          /**< @brief Event generation register           Address offset 0x14 */
    volatile uint32_t CCMR1;        /**< @brief Capture compare mode register 1     Address offset 0x18 */
    volatile uint32_t CCMR2;        /**< @brief Capture compare mode register 2     Address offset 0x1C */
    volatile uint32_t CCER;         /**< @brief Capture compare enable register     Address offset 0x20 */
    volatile uint32_t CNT;          /**< @brief Counter                             Address offset 0x24 */
    volatile uint32_t PSC;          /**< @brief Prescaler                           Address offset 0x28 */
    volatile uint32_t ARR;          /**< @brief Auto-reload register                Address offset 0x2C */
    volatile uint32_t RCR;          /**< @brief Repetition counter register         Address offset 0x30 */
    volatile uint32_t CCR1;         /**< @brief Capture compare register 1          Address offset 0x34 */
    volatile uint32_t CCR2;         /**< @brief Capture compare register 2          Address offset 0x38 */
    volatile uint32_t CCR3;         /**< @brief Capture compare register 3          Address offset 0x3C */
    volatile uint32_t CCR4;         /**< @brief Capture compare register 4          Address offset 0x40 */
    volatile uint32_t BDTR;         /**< @brief Break and dead-time register        Address offset 0x44 */
    volatile uint32_t DCR;          /**< @brief DMA control register                Address offset 0x48 */
    volatile uint32_t DMAR;         /**< @brief DMA address for full transfer       Address offset 0x4C */
    volatile uint32_t OR;           /**< @brief Option register                     Address offset 0x50 */
}TIM_RegDef_t;

/**
 * @brief Peripheral register definition structure for DMA.
 */
typedef struct
{
    volatile uint32_t LISR;         /**< @brief Low interrupt status register       Address offset 0x00 */
    volatile uint32_t HISR;         /**< @brief High interrupt status register      Address offset 0x04 */
    volatile uint32_t LIFCR;        /**< @brief Low interrupt flag clear register   Address offset 0x08 */
    volatile uint32_t HIFCR;        /**< @brief High interrupt flag clear register  Address offset 0x0C */
}DMA_RegDef_t;

/**
 * @brief Peripheral register definition structure for DMA stream
 */
typedef struct
{
    volatile uint32_t CR;           /**< @brief Configuration register     Address offset 0x10 */
    volatile uint32_t NDTR;         /**< @brief Number of data register    Address offset 0x14 */
    volatile uint32_t PAR;          /**< @brief Peripheral addr register   Address offset 0x18 */
    volatile uint32_t M0AR;         /**< @brief Memory 0 address register  Address offset 0x1C */
    volatile uint32_t M1AR;         /**< @brief Memory 1 address register  Address offset 0x20 */
    volatile uint32_t FCR;          /**< @brief FIFO control register      Address offset 0x24 */
}DMA_Stream_RegDef_t;

/**
 * @brief Peripheral register definition structure for RTC
 */
typedef struct
{
    volatile uint32_t TR;           /**< @brief Time register                       Address offset 0x00 */
    volatile uint32_t DR;           /**< @brief Date register                       Address offset 0x04 */
    volatile uint32_t CR;           /**< @brief Control register                    Address offset 0x08 */
    volatile uint32_t ISR;          /**< @brief Initialization and status register  Address offset 0x0C */
    volatile uint32_t PRER;         /**< @brief Prescaler register                  Address offset 0x10 */
    volatile uint32_t WUTR;         /**< @brief Wakeup timer register               Address offset 0x14 */
    volatile uint32_t CALIBR;       /**< @brief Calibration register                Address offset 0x18 */
    volatile uint32_t ALRMAR;       /**< @brief Alarm A register                    Address offset 0x1C */
    volatile uint32_t ALRMBR;       /**< @brief Alarm B register                    Address offset 0x20 */
    volatile uint32_t WPR;          /**< @brief Write protection register           Address offset 0x24 */
    volatile uint32_t SSR;          /**< @brief Sub second register                 Address offset 0x28 */
    volatile uint32_t SHIFTR;       /**< @brief Shift control register              Address offset 0x2C */
    volatile uint32_t TSTR;         /**< @brief Time stamp time register            Address offset 0x30 */
    volatile uint32_t TSDR;         /**< @brief Time stamp date register            Address offset 0x34 */
    volatile uint32_t TSSSR;        /**< @brief Timestamp sub second register       Address offset 0x38 */
    volatile uint32_t CALR;         /**< @brief Calibration register                Address offset 0x3C */
    volatile uint32_t TAFCR;        /**< @brief Tamper and alt function conf reg    Address offset 0x40 */
    volatile uint32_t ALRMASSR;     /**< @brief Alarm A sub second register         Address offset 0x44 */
    volatile uint32_t ALRMBSSR;     /**< @brief Alarm B sub second register         Address offset 0x48 */
    volatile uint32_t RESERVED;     /**< @brief Reserved                            Address offset 0x4C */
    volatile uint32_t BKPxR[20];    /**< @brief Backup register x                   Address offset 0x50 */
}RTC_RegDef_t;

/***********************************************************************************************************/
/*                          Bit Position Definition of Peripheral Register                                 */
/***********************************************************************************************************/

/**
 * @name Bit position definitions SPI control register 1.
 * @{
 */
#define SPI_CR1_CPHA        0   /**< @brief Clock phase offset */
#define SPI_CR1_CPOL        1   /**< @brief Clock polarity offset */
#define SPI_CR1_MSTR        2   /**< @brief Master selection offset */
#define SPI_CR1_BR          3   /**< @brief Baud rate control offset */
#define SPI_CR1_SPE         6   /**< @brief SPI enable offset */
#define SPI_CR1_LSB_FIRST   7   /**< @brief Frame format offset */
#define SPI_CR1_SSI         8   /**< @brief Internal slave select offset */
#define SPI_CR1_SSM         9   /**< @brief Software slave management offset */
#define SPI_CR1_RXONLY      10  /**< @brief Receive only mode enable offset */
#define SPI_CR1_DFF         11  /**< @brief Data frame format offset */
#define SPI_CR1_CRC_NEXT    12  /**< @brief CRC transfer next offset */
#define SPI_CR1_CRC_EN      13  /**< @brief Hardware CRC calculation enable offset */
#define SPI_CR1_BIDI_OE     14  /**< @brief Output enable in bidirectional mode offset */
#define SPI_CR1_BIDI_MODE   15  /**< @brief Bidirectional data mode enable offset */
/** @} */

/**
 * @name Bit position definition SPI control register 2.
 * @{
 */
#define SPI_CR2_RXDMAEN     0   /**< @brief Rx buffer DMA enable offset */
#define SPI_CR2_TXDMAEN     1   /**< @brief Tx buffer DMA enable offset */
#define SPI_CR2_SSOE        2   /**< @brief SS output enable offset */
#define SPI_CR2_FRF         4   /**< @brief Frame format offset */
#define SPI_CR2_ERRIE       5   /**< @brief Error interrupt enable offset */
#define SPI_CR2_RXNEIE      6   /**< @brief Rx buffer not empty interrupt enable offset*/
#define SPI_CR2_TXEIE       7   /**< @brief Tx buffer empty interrupt enable offset */
/** @} */

/**
 * @name Bit position definition SPI status register.
 * @{
 */
#define SPI_SR_RXNE         0   /**< @brief Receive buffer not empty */
#define SPI_SR_TXE          1   /**< @brief Transmit buffer empty offset */
#define SPI_SR_CHSIDE       2   /**< @brief Channel side offset */
#define SPI_SR_UDR          3   /**< @brief Underrun flag offset */
#define SPI_SR_CRCERR       4   /**< @brief CRC error flag offset */
#define SPI_SR_MODF         5   /**< @brief Mode fault offset */
#define SPI_SR_OVR          6   /**< @brief Overrun flag offset */
#define SPI_SR_BSY          7   /**< @brief Busy flag offset */
#define SPI_SR_FRE          8   /**< @brief Frame error offset */
/** @} */

/**
 * @name Bit position definition I2C control register 1.
 * @{
 */
#define I2C_CR1_PE          0   /**< @brief Peripheral enable offset */
#define I2C_CR1_SMBUS       1   /**< @brief SMBus mode offset */
#define I2C_CR1_SMBTYPE     3   /**< @brief SMBus type offset */
#define I2C_CR1_ENARP       4   /**< @brief ARP enable offset */
#define I2C_CR1_ENPEC       5   /**< @brief PEC enable offset */
#define I2C_CR1_ENGC        6   /**< @brief General call enable offset */
#define I2C_CR1_NOSTRETCH   7   /**< @brief Clock stretching disable (Slave mode) offset */
#define I2C_CR1_START       8   /**< @brief Start generation offset */
#define I2C_CR1_STOP        9   /**< @brief Stop generation offset */
#define I2C_CR1_ACK         10  /**< @brief Acknowledge enable offset */
#define I2C_CR1_POS         11  /**< @brief Acknowledge/PEC Position (for data reception) offset */
#define I2C_CR1_PEC         12  /**< @brief Packet error checking offset */
#define I2C_CR1_ALERT       13  /**< @brief SMBus alert offset */
#define I2C_CR1_SWRST       15  /**< @brief Software reset offset */
/** @} */

/**
 * @name Bit position definition I2C control register 2.
 * @{
 */
#define I2C_CR2_FREQ        0   /**< @brief Peripheral clock frequency offset */
#define I2C_CR2_ITERREN     8   /**< @brief Error interrupt enable offset */
#define I2C_CR2_ITEVTEN     9   /**< @brief Event interrupt enable offset */
#define I2C_CR2_ITBUFEN     10  /**< @brief Buffer interrupt enable offset */
#define I2C_CR2_DMAEN       11  /**< @brief DMA requests enable offset */
#define I2C_CR2_LAST        12  /**< @brief DMA last transfer offset */
/** @} */

/**
 * @name Bit position definition I2C status register 1.
 * @{
 */
#define I2C_SR1_SB          0  /**< @brief Start bit (Master mode) offset */
#define I2C_SR1_ADDR        1  /**< @brief Address sent (master mode)/matched (slave mode) offset */
#define I2C_SR1_BTF         2  /**< @brief Byte transfer finished offset */
#define I2C_SR1_ADD10       3  /**< @brief 10-bit header sent (Master mode) offset */
#define I2C_SR1_STOPF       4  /**< @brief Stop detection (slave mode) offset */
#define I2C_SR1_RXNE        6  /**< @brief Data register not empty (receivers) offset */
#define I2C_SR1_TXE         7  /**< @brief Data register empty (transmitters) offset */
#define I2C_SR1_BERR        8  /**< @brief Bus error offset */
#define I2C_SR1_ARLO        9  /**< @brief Arbitration lost (master mode) offset */
#define I2C_SR1_AF          10 /**< @brief Acknowledge failure offset */
#define I2C_SR1_OVR         11 /**< @brief Overrun/Underrun offset*/
#define I2C_SR1_PECERR      12 /**< @brief PEC Error in reception offset */
#define I2C_SR1_TIMEOUT     14 /**< @brief Timeout or Tlow error offset */
#define I2C_SR1_SMBALERT    15 /**< @brief SMBus alert offset */
/** @} */

/**
 * @name Bit position definition I2C status register 2.
 * @{
 */
#define I2C_SR2_MSL         0   /**< @brief Master/slave offset */
#define I2C_SR2_BUSY        1   /**< @brief Bus busy offset */
#define I2C_SR2_TRA         2   /**< @brief Transmitter/receiver offset */
#define I2C_SR2_GENCALL     4   /**< @brief General call address (Slave mode) offset */
#define I2C_SR2_SMBDEFAULT  5   /**< @brief SMBus device default address (Slave mode) offset */
#define I2C_SR2_SMBHOST     6   /**< @brief SMBus host header (Slave mode) offset */
#define I2C_SR2_DUALF       7   /**< @brief Dual flag (Slave mode) offset */
#define I2C_SR2_PEC         8   /**< @brief Packet error checking register offset */
/** @} */

/**
 * @name Bit position definition I2C clock control register.
 * @{
 */
#define I2C_CCR_CCR         0  /**< @brief Clock control register in Fm/Sm mode (Master mode) offset */
#define I2C_CCR_DUTY        14 /**< @brief Fm mode duty cycle offset */
#define I2C_CCR_FS          15 /**< @brief I2C master mode selection offset */
/** @} */

/**
 * @name Bit position definition USART control register 1.
 * @{
 */
#define USART_CR1_SBK       0   /**< @brief Send break offset */
#define USART_CR1_RWU       1   /**< @brief Receiver wakeup offset */
#define USART_CR1_RE        2   /**< @brief Receiver enable offset */
#define USART_CR1_TE        3   /**< @brief Transmitter enable offset */
#define USART_CR1_IDLEIE    4   /**< @brief IDLE interrupt enable offset */
#define USART_CR1_RXNEIE    5   /**< @brief RXNE interrupt enable offset */
#define USART_CR1_TCIE      6   /**< @brief Transmission complete interrupt enable offset */
#define USART_CR1_TXEIE     7   /**< @brief TXE interrupt enable offset */
#define USART_CR1_PEIE      8   /**< @brief PE interrupt enable offset */
#define USART_CR1_PS        9   /**< @brief Parity selection offset */
#define USART_CR1_PCE       10  /**< @brief Parity control enable offset */
#define USART_CR1_WAKE      11  /**< @brief Wakeup method offset */
#define USART_CR1_M         12  /**< @brief Word length offset */
#define USART_CR1_UE        13  /**< @brief USART enable offset */
#define USART_CR1_OVER8     15  /**< @brief Oversampling mode offset */
/** @} */

/**
 * @name Bit position definition USART control register 2.
 * @{
 */
#define USART_CR2_ADD       0  /**< @brief Address of the USART node offset */
#define USART_CR2_LBDL      5  /**< @brief LIN break detection length offset */
#define USART_CR2_LBDIE     6  /**< @brief LIN break detection interrupt enable offset */
#define USART_CR2_LBCL      8  /**< @brief Last bit clock pulse offset */
#define USART_CR2_CPHA      9  /**< @brief Clock phase offset */
#define USART_CR2_CPOL      10 /**< @brief Clock polarity offset */
#define USART_CR2_CLKEN     11 /**< @brief Clock enable offset */
#define USART_CR2_STOP      12 /**< @brief STOP bits offset */
#define USART_CR2_LINEN     14 /**< @brief LIN mode enable offset */
/** @} */

/**
 * @name Bit position definition USART control register 3.
 * @{
 */
#define USART_CR3_EIE       0  /**< @brief Error interrupt enable offset */
#define USART_CR3_IREN      1  /**< @brief IrDA mode enable offset */
#define USART_CR3_IRLP      2  /**< @brief IrDA low-power offset */
#define USART_CR3_HDSEL     3  /**< @brief Half-duplex selection offset */
#define USART_CR3_NACK      4  /**< @brief Smartcard NACK enable offset */
#define USART_CR3_SCEN      5  /**< @brief Smartcard mode enable offset */
#define USART_CR3_DMAR      6  /**< @brief DMA enable receiver offset */
#define USART_CR3_DMAT      7  /**< @brief DMA enable transmitter offset */
#define USART_CR3_RTSE      8  /**< @brief RTS enable offset */
#define USART_CR3_CTSE      9  /**< @brief CTS enable offset */
#define USART_CR3_CTSIE     10 /**< @brief CTS interrupt enable offset */
#define USART_CR3_ONEBIT    11 /**< @brief One sample bit method enable offset */
/** @} */

/**
 * @name Bit position definition USART status register.
 * @{
 */
#define USART_SR_PE         0   /**< @brief Parity error offset */
#define USART_SR_FE         1   /**< @brief Framing error offset */
#define USART_SR_NF         2   /**< @brief Noise detected flag offset */
#define USART_SR_ORE        3   /**< @brief Overrun error offset */
#define USART_SR_IDLE       4   /**< @brief IDLE line detected offset */
#define USART_SR_RXNE       5   /**< @brief Read data register not empty offset */
#define USART_SR_TC         6   /**< @brief Transmission complete offset */
#define USART_SR_TXE        7   /**< @brief Transmit data register empty offset */
#define USART_SR_LBD        8   /**< @brief LIN break detection flag offset */
#define USART_SR_CTS        9   /**< @brief CTS flag offset */
/** @} */

/**
 * @name Bit position definition CRC control register.
 * @{
 */
#define CRC_CR_RESET        0   /**< @brief Reset bit offset */
/** @} */

/**
 * @name Bit position definition FLASH access control register.
 * @{
 */
#define FLASH_ACR_LATENCY   0  /**< @brief Latency offset */
#define FLASH_ACR_PRFTEN    8  /**< @brief Prefetch enable offset */
#define FLASH_ACR_ICEN      9  /**< @brief Instruction cache enable offset */
#define FLASH_ACR_DCEN      10 /**< @brief Data cache enable offset */
#define FLASH_ACR_ICRST     11 /**< @brief Instruction cache reset offset */
#define FLASH_ACR_DCRST     12 /**< @brief Data cache reset offset */
/** @} */

/**
 * @name Bit position definition FLASH_KEYR.
 * @{
 */
#define FLASH_KEYR          0   /**< @brief FPEC key offset */
/** @} */

/**
 * @name Bit position definition FLASH_OPTKEYR.
 * @{
 */
#define FLASH_OPTKEYR       0   /**< @brief Option byte key offset */
/** @} */

/**
 * @name Bit position definition FLASH status register.
 * @{
 */
#define FLASH_SR_EOP        0  /**< @brief End of operation offset */
#define FLASH_SR_OPERR      1  /**< @brief Operation error offset */
#define FLASH_SR_WRPERR     4  /**< @brief Write protection error offset */
#define FLASH_SR_PGAERR     5  /**< @brief Programming alignment error offset */
#define FLASH_SR_PGPERR     6  /**< @brief Programming parallelism error offset */
#define FLASH_SR_PGSERR     7  /**< @brief Programming sequence error offset */
#define FLASH_SR_RDERR      8  /**< @brief Read Protection Error (pcrop) offset */
#define FLASH_SR_BSY        16 /**< @brief Busy offset */
/** @} */

/**
 * @name Bit position definition FLASH control register.
 * @{
 */
#define FLASH_CR_PG         0  /**< @brief Programming offset */
#define FLASH_CR_SER        1  /**< @brief Sector erase offset */
#define FLASH_CR_MER        2  /**< @brief Mass erase offset */
#define FLASH_CR_SNB        3  /**< @brief Sector number offset */
#define FLASH_CR_PSIZE      8  /**< @brief Program size offset */
#define FLASH_CR_STRT       16 /**< @brief Start offset */
#define FLASH_CR_EOPIE      24 /**< @brief End of operation interrupt enable offset */
#define FLASH_CR_ERRIE      25 /**< @brief Error interrupt enable offset */
#define FLASH_CR_LOCK       31 /**< @brief Lock offset */
/** @} */

/**
 * @name Bit position definition FLASH option control register.
 * @{
 */
#define FLASH_OPTCR_OPTLOCK     0  /**< @brief Option lock offset */
#define FLASH_OPTCR_OPTSTRT     1  /**< @brief Option start offset */
#define FLASH_OPTCR_BOR_LEV     2  /**< @brief BOR reset level offset */
#define FLASH_OPTCR_WDG_SW      5  /**< @brief User option byte (WDG_SW) offset */
#define FLASH_OPTCR_NRST_STOP   6  /**< @brief User option byte (nRST_STOP) offset */
#define FLASH_OPTCR_NRST_STDBY  7  /**< @brief User option byte (nRST_STDBY) offset */
#define FLASH_OPTCR_RDP         8  /**< @brief Read protect offset */
#define FLASH_OPTCR_NWRP        16 /**< @brief Not write protect offset */
#define FLASH_OPTCR_SPRMOD      31 /**< @brief Selection of Protection Mode of nWRPi bits offset */
/** @} */

/**
 * @name Bit position definition RCC clock control register.
 * @{
 */
#define RCC_CR_HSION       0   /**< @brief Internal high-speed clock enable */
#define RCC_CR_HSIRDY      1   /**< @brief Internal high-speed clock ready flag */
#define RCC_CR_HSITRIM     3   /**< @brief Internal high-speed clock trimming */
#define RCC_CR_HSICAL      8   /**< @brief Internal high-speed clock calibration */
#define RCC_CR_HSEON       16  /**< @brief HSE clock enable.*/
#define RCC_CR_HSERDY      17  /**< @brief HSE clock ready flag */
#define RCC_CR_HSEBYP      18  /**< @brief HSE clock bypass */
#define RCC_CR_CSSON       19  /**< @brief Clock security system enable */
#define RCC_CR_PLLON       24  /**< @brief Main PLL enable */
#define RCC_CR_PLLRDY      25  /**< @brief Main PLL clock ready flag */
#define RCC_CR_PLLI2SON    26  /**< @brief PLLI2S enable */
#define RCC_CR_PLLI2SRDY   27  /**< @brief PLLI2S clock ready flag */
#define RCC_CR_PLLSAION    28  /**< @brief PLLSAI enable */
#define RCC_CR_PLLSAIRDY   29  /**< @brief PLLSAI clock ready flag */
/** @}*/

/**
 * @name Bit position definition RCC PLL configuration register.
 * @{
 */
#define RCC_PLLCFGR_PLLM    0   /**< @brief Division factor for the main PLL input clock */
#define RCC_PLLCFGR_PLLN    6   /**< @brief Main PLL multiplication factor for VCO */
#define RCC_PLLCFGR_PLLP    16  /**< @brief Main PLL division factor for main system clock */
#define RCC_PLLCFGR_PLLSRC  22  /**< @brief Main PLL and audio PLL entry clock source */
#define RCC_PLLCFGR_PLLQ    24  /**< @brief Main PLL division factor for USB OTG FS */
#define RCC_PLLCFGR_PLLR    28  /**< @brief Main PLL div factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks */
/** @}*/

/**
 * @name Bit position definition RCC clock configuration register.
 * @{
 */
#define RCC_CFGR_SW         0   /**< @brief System clock switch */
#define RCC_CFGR_SWS        2   /**< @brief System clock switch status */
#define RCC_CFGR_HPRE       4   /**< @brief AHB prescaler */
#define RCC_CFGR_PPRE1      10  /**< @brief APB Low speed prescaler (APB1) */
#define RCC_CFGR_PPRE2      13  /**< @brief APB High speed prescaler (APB2) */
#define RCC_CFGR_RTCPRE     16  /**< @brief HSE division factor for RTC clock */
#define RCC_CFGR_MCO1       21  /**< @brief Microcontroller clock output 1 */
#define RCC_CFGR_MCO1PRE    24  /**< @brief MCO1 prescaler */
#define RCC_CFGR_MCO2PRE    27  /**< @brief MCO2 prescaler */
#define RCC_CFGR_MCO2       30  /**< @brief Microcontroller clock output 2 */
/** @} */

/**
 * @name Bit position definition RCC backup domain control register.
 * @{
 */
#define RCC_BDCR_LSEON      0   /**< @brief External low speed oscillator enable */
#define RCC_BDCR_LSERDY     1   /**< @brief External low speed oscillator ready */
#define RCC_BDCR_LSEBYP     2   /**< @brief External low speed oscillator bypass */
#define RCC_BDCR_LSEMOD     3   /**< @brief External low speed oscillator mode */
#define RCC_BDCR_RTCSEL     8   /**< @brief RTC clock source selection */
#define RCC_BDCR_RTCEN      15  /**< @brief RTC clock enable */
#define RCC_BDCR_BDRST      16  /**< @brief Backup domain software reset */
/**@}*/

/**
 * @name Bit position definition RCC PLLI2S configuration register.
 * @{
 */
#define RCC_PLLI2SCFGR_PLLI2SM  0   /**< @brief Division factor for the PLLI2S input clock */
#define RCC_PLLI2SCFGR_PLLI2SN  6   /**< @brief PLLI2S multiplication factor for VCO */
#define RCC_PLLI2SCFGR_PLLI2SP  16  /**< @brief PLLI2S division factor for SPDIF-Rx clock */
#define RCC_PLLI2SCFGR_PLLI2SQ  24  /**< @brief PLLI2S division factor for SAI1 clock.*/
#define RCC_PLLI2SCFGR_PLLI2SR  28  /**< @brief PLLI2S division factor for I2S clock */
/** @} */

/**
 * @name Bit position definition PWR power control register.
 * @{
 */
#define PWR_CR_LPDS         0   /**< @brief Low-power deepsleep */
#define PWR_CR_PDDS         1   /**< @brief Power-down deepsleep */
#define PWR_CR_CWUF         2   /**< @brief Clear wakeup flag */
#define PWR_CR_CSBF         3   /**< @brief Clear standby flag */
#define PWR_CR_PVDE         4   /**< @brief Power voltage detector enable */
#define PWR_CR_PLS          5   /**< @brief PVD level selection */
#define PWR_CR_DBP          8   /**< @brief Disable backup domain write protection */
#define PWR_CR_FPDS         9   /**< @brief Flash power-down in Stop  mode */
#define PWR_CR_LPUDS        10  /**< @brief Low-power regulator in deepsleep under-drive mode */
#define PWR_CR_MRUDS        11  /**< @brief Main regulator in deepsleep under-drive mode */
#define PWR_CR_ADCDC1       13  /**< @brief Watch Reference Manual */
#define PWR_CR_VOS          14  /**< @brief Regulator voltage scaling output selection */
#define PWR_CR_ODEN         16  /**< @brief Over-drive enable */
#define PWR_CR_ODSWEN       17  /**< @brief Over-drive switching enabled */
#define PWR_CR_UDEN         18  /**< @brief Under-drive enable in stop mode */
#define PWR_CR_FMSSR        20  /**< @brief Flash memory stop while system run */
#define PWR_CR_FISSR        21  /**< @brief Flash interface stop while system run */
/** @} */

/**
 * @name Bit position definition power controller control status register
 * @{
 */
#define PWR_CSR_WUF         0   /**< @brief Wakeup flag */
#define PWR_CSR_SBF         1   /**< @brief Standby flag */
#define PWR_CSR_PVDO        2   /**< @brief PVD output */
#define PWR_CSR_BRR         3   /**< @brief Backup regulator ready */
#define PWR_CSR_EWUP2       7   /**< @brief Enable WKUP2 pin */
#define PWR_CSR_EWUP1       8   /**< @brief Enable WKUP1 pin */
#define PWR_CSR_BRE         9   /**< @brief Backup regulator enable */
#define PWR_CSR_VOSRDY      14  /**< @brief Regulator voltage scaling output selection ready bit */
#define PWR_CSR_ODRDY       16  /**< @brief Over-drive mode ready */
#define PWR_CSR_ODSWRDY     17  /**< @brief Over-drive mode switching ready */
#define PWR_CSR_UDRDY       18  /**< @brief Under-drive ready flag */
/** @} */

/**
 * @name Bit position definition TIM control register 1.
 * @{
 */
#define TIM_CR1_CEN         0   /**< @brief Counter enable */
#define TIM_CR1_UDIS        1   /**< @brief Update disable */
#define TIM_CR1_URS         2   /**< @brief Update request source */
#define TIM_CR1_OPM         3   /**< @brief One-pulse mode */
#define TIM_CR1_ARPE        7   /**< @brief Auto-reload preload enable */
/** @} */

/**
 * @name Bit position definition TIM control register 2.
 * @{
 */
#define TIM_CR2_MMS         4   /**< @brief Master mode selection */
/** @} */

/**
 * @name Bit position definition TIM DMA/Interrupt enable register.
 * @{
 */
#define TIM_DIER_UIE        0   /**< @brief Update interrupt enable */
#define TIM_DIER_CC1IE      1   /**< @brief Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE      2   /**< @brief Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE      3   /**< @brief Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE      4   /**< @brief Capture/Compare 4 interrupt enable */
#define TIM_DIER_UDE        8   /**< @brief Update DMA request enable */
/** @} */

/**
 * @name Bit position definition TIM status register.
 * @{
 */
#define TIM_SR_UIF          0   /**< @brief Update interrupt flag */
#define TIM_SR_CC1IF        1   /**< @brief Capture/Compare 1 interrupt flag */
#define TIM_SR_CC2IF        2   /**< @brief Capture/Compare 2 interrupt flag */
#define TIM_SR_CC3IF        3   /**< @brief Capture/Compare 3 interrupt flag */
#define TIM_SR_CC4IF        4   /**< @brief Capture/Compare 4 interrupt flag */
/** @} */

/**
 * @name Bit position definition TIM event generation register.
 * @{
 */
#define TIM_EGR_UG          0   /**< @brief Update generation */
/** @} */

/**
 * @name Bit position definition TIM capture/compare mode register 1.
 * @{
 */
#define TIM_CCMR1_CC1S      0   /**< @brief Capture/compare 1 selection */
#define TIM_CCMR1_IC1PSC    2   /**< @brief Input capture 1 prescaler */
#define TIM_CCMR1_IC1F      4   /**< @brief Input capture 1 filter */
#define TIM_CCMR1_CC2S      8   /**< @brief Capture/compare 2 selection */
#define TIM_CCMR1_IC2PSC    10  /**< @brief Input capture 2 prescaler */
#define TIM_CCMR1_IC2F      12  /**< @brief Input capture 2 filter */
#define TIM_CCMR1_OC1PE     3   /**< @brief Output compare 1 preload enable */
#define TIM_CCMR1_OC1M      4   /**< @brief Output compare 1 mode */
#define TIM_CCMR1_OC2PE     11  /**< @brief Output compare 2 preload enable */
#define TIM_CCMR1_OC2M      12  /**< @brief Output compare 2 mode */
/** @} */

/**
 * @name Bit position definition TIM capture/compare mode register 2.
 * @{
 */
#define TIM_CCMR2_CC3S      0   /**< @brief Capture/compare 3 selection */
#define TIM_CCMR2_IC3PSC    2   /**< @brief Input capture 3 prescaler */
#define TIM_CCMR2_IC3F      4   /**< @brief Input capture 3 filter */
#define TIM_CCMR2_CC4S      8   /**< @brief Capture/compare 4 selection */
#define TIM_CCMR2_IC4PSC    10  /**< @brief Input capture 4 prescaler */
#define TIM_CCMR2_IC4F      12  /**< @brief Input capture 4 filter */
#define TIM_CCMR2_OC3PE     3   /**< @brief Output compare 3 preload enable */
#define TIM_CCMR2_OC3M      4   /**< @brief Output compare 3 mode */
#define TIM_CCMR2_OC4PE     11  /**< @brief Output compare 4 preload enable */
#define TIM_CCMR2_OC4M      12  /**< @brief Output compare 4 mode */
/** @} */

/**
 * @name Bit position definition TIM capture/compare enable register.
 * @{
 */
#define TIM_CCER_CC1E       0   /**< @brief Capture/compare 1 enable */
#define TIM_CCER_CC1P       1   /**< @brief Capture/compare 1 polarity */
#define TIM_CCER_CC2E       4   /**< @brief Capture/compare 2 enable */
#define TIM_CCER_CC2P       5   /**< @brief Capture/compare 2 polarity */
#define TIM_CCER_CC3E       8   /**< @brief Capture/compare 3 enable */
#define TIM_CCER_CC3P       9   /**< @brief Capture/compare 3 polarity */
#define TIM_CCER_CC4E       12  /**< @brief Capture/compare 4 enable */
#define TIM_CCER_CC4P       13  /**< @brief Capture/compare 4 polarity */
/** @{ */

/**
 * @name Bit position definition TIM counter register.
 * @{
 */
#define TIM_CNT             0   /**< @brief Counter value */
/** @} */

/**
 * @name Bit position definition TIM prescaler register.
 * @{
 */
#define TIM_PSC             0   /**< @brief Prescaler value */
/** @} */

/**
 * @name Bit position definition TIM auto-reload register.
 * @{
 */
#define TIM_ARR             0   /**< @brief Auto-reload value */
/** @} */

/**
 * @name Bit position definition DMA low interrupt status register
 * @{
 */
#define DMA_LISR_FEIF0      0   /**< @brief Stream0 FIFO error interrupt flag */
#define DMA_LISR_DMEIF0     2   /**< @brief Stream0 direct mode error interrupt flag */
#define DMA_LISR_TEIF0      3   /**< @brief Stream0 transfer error interrupt flag */
#define DMA_LISR_HTIF0      4   /**< @brief Stream0 half transfer interrupt flag */
#define DMA_LISR_TCIF0      5   /**< @brief Stream0 transfer complete interrupt flag */
#define DMA_LISR_FEIF1      6   /**< @brief Stream1 FIFO error interrupt flag */
#define DMA_LISR_DMEIF1     8   /**< @brief Stream1 direct mode error interrupt flag */
#define DMA_LISR_TEIF1      9   /**< @brief Stream1 transfer error interrupt flag */
#define DMA_LISR_HTIF1      10  /**< @brief Stream1 half transfer interrupt flag */
#define DMA_LISR_TCIF1      11  /**< @brief Stream1 transfer complete interrupt flag */
#define DMA_LISR_FEIF2      16  /**< @brief Stream2 FIFO error interrupt flag */
#define DMA_LISR_DMEIF2     18  /**< @brief Stream2 direct mode error interrupt flag */
#define DMA_LISR_TEIF2      19  /**< @brief Stream2 transfer error interrupt flag */
#define DMA_LISR_HTIF2      20  /**< @brief Stream2 half transfer interrupt flag */
#define DMA_LISR_TCIF2      21  /**< @brief Stream2 transfer complete interrupt flag */
#define DMA_LISR_FEIF3      22  /**< @brief Stream3 FIFO error interrupt flag */
#define DMA_LISR_DMEIF3     24  /**< @brief Stream3 direct mode error interrupt flag */
#define DMA_LISR_TEIF3      25  /**< @brief Stream3 transfer error interrupt flag */
#define DMA_LISR_HTIF3      26  /**< @brief Stream3 half transfer interrupt flag */
#define DMA_LISR_TCIF3      27  /**< @brief Stream3 transfer complete interrupt flag */
/** @} */

/**
 * @name Bit position definition DMA high interrupt status register
 * @{
 */
#define DMA_HISR_FEIF4      0   /**< @brief Stream4 FIFO error interrupt flag */
#define DMA_HISR_DMEIF4     2   /**< @brief Stream4 direct mode error interrupt flag */
#define DMA_HISR_TEIF4      3   /**< @brief Stream4 transfer error interrupt flag */
#define DMA_HISR_HTIF4      4   /**< @brief Stream4 half transfer interrupt flag */
#define DMA_HISR_TCIF4      5   /**< @brief Stream4 transfer complete interrupt flag */
#define DMA_HISR_FEIF5      6   /**< @brief Stream5 FIFO error interrupt flag */
#define DMA_HISR_DMEIF5     8   /**< @brief Stream5 direct mode error interrupt flag */
#define DMA_HISR_TEIF5      9   /**< @brief Stream5 transfer error interrupt flag */
#define DMA_HISR_HTIF5      10  /**< @brief Stream5 half transfer interrupt flag */
#define DMA_HISR_TCIF5      11  /**< @brief Stream5 transfer complete interrupt flag */
#define DMA_HISR_FEIF6      16  /**< @brief Stream6 FIFO error interrupt flag */
#define DMA_HISR_DMEIF6     18  /**< @brief Stream6 direct mode error interrupt flag */
#define DMA_HISR_TEIF6      19  /**< @brief Stream6 transfer error interrupt flag */
#define DMA_HISR_HTIF6      20  /**< @brief Stream6 half transfer interrupt flag */
#define DMA_HISR_TCIF6      21  /**< @brief Stream6 transfer complete interrupt flag */
#define DMA_HISR_FEIF7      22  /**< @brief Stream7 FIFO error interrupt flag */
#define DMA_HISR_DMEIF7     24  /**< @brief Stream7 direct mode error interrupt flag */
#define DMA_HISR_TEIF7      25  /**< @brief Stream7 transfer error interrupt flag */
#define DMA_HISR_HTIF7      26  /**< @brief Stream7 half transfer interrupt flag */
#define DMA_HISR_TCIF7      27  /**< @brief Stream7 transfer complete interrupt flag */
/** @} */

/**
 * @name Bit position definition DMA low interrupt flat clear register
 * @{
 */
#define DMA_LIFCR_CFEIF0    0   /**< @brief Stream0 clear FIFO error interrupt flag */
#define DMA_LIFCR_CDMEIF0   2   /**< @brief Stream0 clear direct mode error interrupt flag */
#define DMA_LIFCR_CTEIF0    3   /**< @brief Stream0 clear transfer error interrupt flag */
#define DMA_LIFCR_CHTIF0    4   /**< @brief Stream0 clear half transfer interrupt flag */
#define DMA_LIFCR_CTCIF0    5   /**< @brief Stream0 clear transfer complete interrupt flag */
#define DMA_LIFCR_CFEIF1    6   /**< @brief Stream1 clear FIFO error interrupt flag */
#define DMA_LIFCR_CDMEIF1   8   /**< @brief Stream1 clear direct mode error interrupt flag */
#define DMA_LIFCR_CTEIF1    9   /**< @brief Stream1 clear transfer error interrupt flag */
#define DMA_LIFCR_CHTIF1    10  /**< @brief Stream1 clear half transfer interrupt flag */
#define DMA_LIFCR_CTCIF1    11  /**< @brief Stream1 clear transfer complete interrupt flag */
#define DMA_LIFCR_CFEIF2    16  /**< @brief Stream2 clear FIFO error interrupt flag */
#define DMA_LIFCR_CDMEIF2   18  /**< @brief Stream2 clear direct mode error interrupt flag */
#define DMA_LIFCR_CTEIF2    19  /**< @brief Stream2 clear transfer error interrupt flag */
#define DMA_LIFCR_CHTIF2    20  /**< @brief Stream2 clear half transfer interrupt flag */
#define DMA_LIFCR_CTCIF2    21  /**< @brief Stream2 clear transfer complete interrupt flag */
#define DMA_LIFCR_CFEIF3    22  /**< @brief Stream3 clear FIFO error interrupt flag */
#define DMA_LIFCR_CDMEIF3   24  /**< @brief Stream3 clear direct mode error interrupt flag */
#define DMA_LIFCR_CTEIF3    25  /**< @brief Stream3 clear transfer error interrupt flag */
#define DMA_LIFCR_CHTIF3    26  /**< @brief Stream3 clear half transfer interrupt flag */
#define DMA_LIFCR_CTCIF3    27  /**< @brief Stream3 clear transfer complete interrupt flag */
/** @} */

/**
 * @name Bit position definition DMA high interrupt status register
 * @{
 */
#define DMA_HIFCR_CFEIF4    0   /**< @brief Stream4 clear FIFO error interrupt flag */
#define DMA_HIFCR_CDMEIF4   2   /**< @brief Stream4 clear direct mode error interrupt flag */
#define DMA_HIFCR_CTEIF4    3   /**< @brief Stream4 clear transfer error interrupt flag */
#define DMA_HIFCR_CHTIF4    4   /**< @brief Stream4 clear half transfer interrupt flag */
#define DMA_HIFCR_CTCIF4    5   /**< @brief Stream4 clear transfer complete interrupt flag */
#define DMA_HIFCR_CFEIF5    6   /**< @brief Stream5 clear FIFO error interrupt flag */
#define DMA_HIFCR_CDMEIF5   8   /**< @brief Stream5 clear direct mode error interrupt flag */
#define DMA_HIFCR_CTEIF5    9   /**< @brief Stream5 clear transfer error interrupt flag */
#define DMA_HIFCR_CHTIF5    10  /**< @brief Stream5 clear half transfer interrupt flag */
#define DMA_HIFCR_CTCIF5    11  /**< @brief Stream5 clear transfer complete interrupt flag */
#define DMA_HIFCR_CFEIF6    16  /**< @brief Stream6 clear FIFO error interrupt flag */
#define DMA_HIFCR_CDMEIF6   18  /**< @brief Stream6 clear direct mode error interrupt flag */
#define DMA_HIFCR_CTEIF6    19  /**< @brief Stream6 clear transfer error interrupt flag */
#define DMA_HIFCR_CHTIF6    20  /**< @brief Stream6 clear half transfer interrupt flag */
#define DMA_HIFCR_CTCIF6    21  /**< @brief Stream6 clear transfer complete interrupt flag */
#define DMA_HIFCR_CFEIF7    22  /**< @brief Stream7 clear FIFO error interrupt flag */
#define DMA_HIFCR_CDMEIF7   24  /**< @brief Stream7 clear direct mode error interrupt flag */
#define DMA_HIFCR_CTEIF7    25  /**< @brief Stream7 clear transfer error interrupt flag */
#define DMA_HIFCR_CHTIF7    26  /**< @brief Stream7 clear half transfer interrupt flag */
#define DMA_HIFCR_CTCIF7    27  /**< @brief Stream7 clear transfer complete interrupt flag */
/** @} */

/**
 * @name Bit position definition DMA stream configuration register
 * @{
 */
#define DMA_SCR_EN          0   /**< @brief Stream enable */
#define DMA_SCR_DMEIE       1   /**< @brief Direct mode error interrupt enable */
#define DMA_SCR_TEIE        2   /**< @brief Transfer error interrupt enable */
#define DMA_SCR_HTIE        3   /**< @brief Half transfer interrupt enable */
#define DMA_SCR_TCIE        4   /**< @brief Transfer complete interrupt enable */
#define DMA_SCR_PFCTRL      5   /**< @brief Peripheral flow control */
#define DMA_SCR_DIR         6   /**< @brief Data transfer direction */
#define DMA_SCR_CIRC        8   /**< @brief Circular mode */
#define DMA_SCR_PINC        9   /**< @brief Peripheral increment mode */
#define DMA_SCR_MINC        10  /**< @brief Memory increment mode */
#define DMA_SCR_PSIZE       11  /**< @brief Peripheral data size */
#define DMA_SCR_MSIZE       13  /**< @brief Memory data size */
#define DMA_SCR_PINCOS      15  /**< @brief Peripheral increment offset size */
#define DMA_SCR_PL          16  /**< @brief Priority level */
#define DMA_SCR_DBM         18  /**< @brief Double-buffer mode */
#define DMA_SCR_CT          19  /**< @brief Current target */
#define DMA_SCR_PBURST      21  /**< @brief Peripheral burst transfer configuration */
#define DMA_SCR_MBURST      23  /**< @brief Memory burst transfer configuration */
#define DMA_SCR_CHSEL       25  /**< @brief Channel selection */
/** @} */

/**
 * @name Bit position definition DMA stream number of data register
 * @{
 */
#define DMA_SNDTR_NDT       0   /**< @brief Number of data items to transfer */
/** @} */

/**
 * @name Bit position definition DMA stream peripheral address register
 * @{
 */
#define DMA_SPAR_PAR        0   /**< @brief Peripheral address */
/** @} */

/**
 * @name Bit position definition DMA stream memory 0 address register
 * @{
 */
#define DMA_SM0AR_M0A       0   /**< @brief Memory 0 address */
/** @} */

/**
 * @name Bit position definition DMA stream memory 1 address register
 * @{
 */
#define DMA_SM1AR_M1A       0   /**< @brief Memory 1 address */
/** @} */

/**
 * @name Bit position definition DMA stream FIFO control register
 * @{
 */
#define DMA_SFCR_FTH        0   /**< @brief FIFO threshold selection */
#define DMA_SFCR_DMDIS      2   /**< @brief Direct mode disable */
#define DMA_SFCR_FS         3   /**< @brief FIFO status */
#define DMA_SFCR_FEIE       7   /**< @brief FIFO error interrupt enable */
/** @} */

/**
 * @name Bit position definition RTC time register
 * @{
 */
#define RTC_TR_SU           0   /**< @brief Seconds units in BCD format */
#define RTC_TR_ST           4   /**< @brief Seconds tens in BCD format */
#define RTC_TR_MNU          8   /**< @brief Minute units in BCD format */
#define RTC_TR_MNT          12  /**< @brief Minute tens in BCD format */
#define RTC_TR_HU           16  /**< @brief Hours units in BCD format */
#define RTC_TR_HT           20  /**< @brief Hours tens in BCD format */
#define RTC_TR_PM           22  /**< @brief AM/PM notation */
/** @} */

/**
 * @name Bit position definition RTC date register
 * @{
 */
#define RTC_DR_DU           0   /**< @brief Date units in BCD format */
#define RTC_DR_DT           4   /**< @brief Date tens in BCD format */
#define RTC_DR_MU           8   /**< @brief Month units in BCD format */
#define RTC_DR_MT           12  /**< @brief Month tens in BCD format */
#define RTC_DR_WDU          13  /**< @brief Week day units */
#define RTC_DR_YU           16  /**< @brief Year units in BCD format */
#define RTC_DR_YT           20  /**< @brief Year tens in BCD format */
/** @} */

/**
 * @name Bit position definition RTC control register
 * @{
 */
#define RTC_CR_WUCKSEL      0   /**< @brief Wakeup clock selection */
#define RTC_CR_TSEDGE       3   /**< @brief Timestamp event active edge */
#define RTC_CR_REFCKON      4   /**< @brief Reference clock detection enable */
#define RTC_CR_BYPSHAD      5   /**< @brief Bypass the shadow registers */
#define RTC_CR_FMT          6   /**< @brief Hour format */
#define RTC_CR_DCE          7   /**< @brief Coarse digital calibration enable */
#define RTC_CR_ALRAE        8   /**< @brief Alarm A enable */
#define RTC_CR_ALRBE        9   /**< @brief Alarm B enable */
#define RTC_CR_WUTE         10  /**< @brief Wakeup timer enable */
#define RTC_CR_TSE          11  /**< @brief Time stamp enable */
#define RTC_CR_ALRAIE       12  /**< @brief Alarm A interrupt enable */
#define RTC_CR_ALRBIE       13  /**< @brief Alarm B interrupt enable */
#define RTC_CR_WUTIE        14  /**< @brief Wakeup timer interrupt enable */
#define RTC_CR_TSIE         15  /**< @brief Timestamp interrupt enable */
#define RTC_CR_ADD1H        16  /**< @brief Add 1hour */
#define RTC_CR_SUB1H        17  /**< @brief Subtract 1hour */
#define RTC_CR_BKP          18  /**< @brief Backup */
#define RTC_CR_COSEL        19  /**< @brief Calibration output selection */
#define RTC_CR_POL          20  /**< @brief Output polarity */
#define RTC_CR_OSEL         21  /**< @brief Output selection */
#define RTC_CR_COE          23  /**< @brief Calibration output enable */
/** @} */

/**
 * @name Bit position definition RTC initialization and status register
 * @{
 */
#define RTC_ISR_ALRAWF      0   /**< @brief Alarm A write flag */
#define RTC_ISR_ALRBWF      1   /**< @brief Alarm B write flag */
#define RTC_ISR_WUTWF       2   /**< @brief Wakeup timer write flag */
#define RTC_ISR_SHPF        3   /**< @brief Shift operation pending */
#define RTC_ISR_INITS       4   /**< @brief Initialization status flag */
#define RTC_ISR_RSF         5   /**< @brief Registers synchronization flag */
#define RTC_ISR_INITF       6   /**< @brief Initialization flag */
#define RTC_ISR_INIT        7   /**< @brief Initialization mode */
#define RTC_ISR_ALRAF       8   /**< @brief Alarm A flag */
#define RTC_ISR_ALRBF       9   /**< @brief Alarm B flag */
#define RTC_ISR_WUTF        10  /**< @brief Wakeup timer flag */
#define RTC_ISR_TSF         11  /**< @brief Timestamp flag */
#define RTC_ISR_TSOVF       12  /**< @brief Timestamp overflow flag */
#define RTC_ISR_TAMP1F      13  /**< @brief Tamper detection flag */
#define RTC_ISR_TAMP2F      14  /**< @brief Tamper2 detection flag */
#define RTC_ISR_RECALPF     16  /**< @brief Recalibration pending flag */
/** @} */

/**
 * @name Bit position definition RTC prescaler register
 * @{
 */
#define RTC_PRER_PREDIV_S   0   /**< @brief Synchronous prescaler factor */
#define RTC_PRER_PREDIV_A   16  /**< @brief Asynchronous prescaler factor */
/** @} */

/**
 * @name Bit position definition RTC alarm x register
 * @{
 */
#define RTC_ALRMxR_SU       0   /**< @brief Second units in BCD format */
#define RTC_ALRMxR_ST       4   /**< @brief Second tens in BCD format */
#define RTC_ALRMxR_MSK1     7   /**< @brief Alarm x seconds mask */
#define RTC_ALRMxR_MNU      8   /**< @brief Minute units in BCD format */
#define RTC_ALRMxR_MNT      12  /**< @brief Minute tens in BCD format */
#define RTC_ALRMxR_MSK2     15  /**< @brief Alarm x minutes mask */
#define RTC_ALRMxR_HU       16  /**< @brief Hour units in BCD format */
#define RTC_ALRMxR_HT       20  /**< @brief Hour tens in BCD format */
#define RTC_ALRMxR_PM       22  /**< @brief AM/PM notation */
#define RTC_ALRMxR_MSK3     23  /**< @brief Alarm x hours mask */
#define RTC_ALRMxR_DU       24  /**< @brief Date units or day in BCD format */
#define RTC_ALRMxR_DT       28  /**< @brief Date tens in BCD format */
#define RTC_ALRMxR_WDSEL    30  /**< @brief Week day selection */
#define RTC_ALRMxR_MSK4     31  /**< @brief Alarm x date mask */
/** @} */

/***********************************************************************************************************/
/*          Peripheral definitions (peripheral base addresses typecasted to xxx_RegDef_t)                  */
/***********************************************************************************************************/

/**
 * @name Peripheral Base Addresses Typecasted to xxx_RegDef_t.
 * @{
 */
#define GPIOA       ((GPIO_RegDef_t*)GPIOA_BASEADDR)        /**< @brief GPIOA base addr reg definition */
#define GPIOB       ((GPIO_RegDef_t*)GPIOB_BASEADDR)        /**< @brief GPIOB base addr reg definition */
#define GPIOC       ((GPIO_RegDef_t*)GPIOC_BASEADDR)        /**< @brief GPIOC base addr reg definition */
#define GPIOD       ((GPIO_RegDef_t*)GPIOD_BASEADDR)        /**< @brief GPIOD base addr reg definition */
#define GPIOE       ((GPIO_RegDef_t*)GPIOE_BASEADDR)        /**< @brief GPIOE base addr reg definition */
#define GPIOF       ((GPIO_RegDef_t*)GPIOF_BASEADDR)        /**< @brief GPIOF base addr reg definition */
#define GPIOG       ((GPIO_RegDef_t*)GPIOG_BASEADDR)        /**< @brief GPIOG base addr reg definition */
#define GPIOH       ((GPIO_RegDef_t*)GPIOH_BASEADDR)        /**< @brief GPIOH base addr reg definition */
#define GPIOI       ((GPIO_RegDef_t*)GPIOI_BASEADDR)        /**< @brief GPIOI base addr reg definition */

#define RCC         ((RCC_RegDef_t*)RCC_BASEADDR)           /**< @brief RCC base addr reg definition */

#define PWR         ((PWR_RegDef_t*)PWR_BASEADDR)           /**< @brief PWR base addr reg definition */

#define EXTI        ((EXTI_RegDef_t*)EXTI_BASEADDR)         /**< @brief EXTI base addr reg definition */

#define SYSCFG      ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)     /**< @brief SYSCFG base addr reg definition */

#define SPI1        ((SPI_RegDef_t*)SPI1_BASEADDR)          /**< @brief SPII base addr reg definition */
#define SPI2        ((SPI_RegDef_t*)SPI2_I2S2_BASEADDR)     /**< @brief SPI2 base addr reg definition */
#define SPI3        ((SPI_RegDef_t*)SPI3_I2S3_BASEADDR)     /**< @brief SPI3 base addr reg definition */
#define SPI4        ((SPI_RegDef_t*)SPI4_BASEADDR)          /**< @brief SPI4 base addr reg definition */

#define I2C1        ((I2C_RegDef_t*)I2C1_BASEADDR)          /**< @brief I2C1 base addr reg definition */
#define I2C2        ((I2C_RegDef_t*)I2C2_BASEADDR)          /**< @brief I2C2 base addr reg definition */
#define I2C3        ((I2C_RegDef_t*)I2C3_BASEADDR)          /**< @brief I2C3 base addr reg definition */

#define USART1      ((USART_RegDef_t*)USART1_BASEADDR)      /**< @brief USART1 base addr reg definition */
#define USART2      ((USART_RegDef_t*)USART2_BASEADDR)      /**< @brief USART2 base addr reg definition */
#define USART3      ((USART_RegDef_t*)USART3_BASEADDR)      /**< @brief USART3 base addr reg definition */
#define UART4       ((USART_RegDef_t*)UART4_BASEADDR)       /**< @brief USART4 base addr reg definition */
#define UART5       ((USART_RegDef_t*)UART5_BASEADDR)       /**< @brief USART5 base addr reg definition */
#define USART6      ((USART_RegDef_t*)USART6_BASEADDR)      /**< @brief USART6 base addr reg definition */

#define CRC         ((CRC_RegDef_t*)CRC_BASEADDR)           /**< @brief CRC base addr reg definition */

#define DBGMCU      ((DBG_RegDef_t*)DBGMCU_BASEADDR)        /**< @brief DBGMCU base addr reg definition */

#define FLASHINTR   ((FLASHINTR_RegDef_t*)FLASHINTR_BASEADDR)   /**< @brief FLASHINTR base addr reg defini */

#define TIM1        ((TIM_RegDef_t*)TIM1_BASEADDR)          /**< @brief TIM1 base addr reg definition */
#define TIM2        ((TIM_RegDef_t*)TIM2_BASEADDR)          /**< @brief TIM2 base addr reg definition */
#define TIM3        ((TIM_RegDef_t*)TIM3_BASEADDR)          /**< @brief TIM3 base addr reg definition */
#define TIM4        ((TIM_RegDef_t*)TIM4_BASEADDR)          /**< @brief TIM4 base addr reg definition */
#define TIM5        ((TIM_RegDef_t*)TIM5_BASEADDR)          /**< @brief TIM5 base addr reg definition */
#define TIM6        ((TIM_RegDef_t*)TIM6_BASEADDR)          /**< @brief TIM6 base addr reg definition */
#define TIM7        ((TIM_RegDef_t*)TIM7_BASEADDR)          /**< @brief TIM7 base addr reg definition */
#define TIM8        ((TIM_RegDef_t*)TIM8_BASEADDR)          /**< @brief TIM8 base addr reg definition */
#define TIM9        ((TIM_RegDef_t*)TIM9_BASEADDR)          /**< @brief TIM9 base addr reg definition */
#define TIM10       ((TIM_RegDef_t*)TIM10_BASEADDR)         /**< @brief TIM10 base addr reg definition */
#define TIM11       ((TIM_RegDef_t*)TIM11_BASEADDR)         /**< @brief TIM11 base addr reg definition */
#define TIM12       ((TIM_RegDef_t*)TIM12_BASEADDR)         /**< @brief TIM12 base addr reg definition */
#define TIM13       ((TIM_RegDef_t*)TIM13_BASEADDR)         /**< @brief TIM13 base addr reg definition */
#define TIM14       ((TIM_RegDef_t*)TIM14_BASEADDR)         /**< @brief TIM14 base addr reg definition */

#define DMA1        ((DMA_RegDef_t*)DMA1_BASEADDR)          /**< @brief DMA1 base addr reg definition */
#define DMA1_STR0   ((DMA_Stream_RegDef_t*)DMA1_STR0_BASEADDR)  /**< @brief DMA1 str0 base addr reg def */
#define DMA1_STR1   ((DMA_Stream_RegDef_t*)DMA1_STR1_BASEADDR)  /**< @brief DMA1 str1 base addr reg def */
#define DMA1_STR2   ((DMA_Stream_RegDef_t*)DMA1_STR2_BASEADDR)  /**< @brief DMA1 str2 base addr reg def */
#define DMA1_STR3   ((DMA_Stream_RegDef_t*)DMA1_STR3_BASEADDR)  /**< @brief DMA1 str3 base addr reg def */
#define DMA1_STR4   ((DMA_Stream_RegDef_t*)DMA1_STR4_BASEADDR)  /**< @brief DMA1 str4 base addr reg def */
#define DMA1_STR5   ((DMA_Stream_RegDef_t*)DMA1_STR5_BASEADDR)  /**< @brief DMA1 str5 base addr reg def */
#define DMA1_STR6   ((DMA_Stream_RegDef_t*)DMA1_STR6_BASEADDR)  /**< @brief DMA1 str6 base addr reg def */
#define DMA1_STR7   ((DMA_Stream_RegDef_t*)DMA1_STR7_BASEADDR)  /**< @brief DMA1 str7 base addr reg def */
#define DMA2        ((DMA_RegDef_t*)DMA2_BASEADDR)          /**< @brief DMA2 base addr reg definition */
#define DMA2_STR0   ((DMA_Stream_RegDef_t*)DMA2_STR0_BASEADDR)  /**< @brief DMA2 str0 base addr reg def */
#define DMA2_STR1   ((DMA_Stream_RegDef_t*)DMA2_STR1_BASEADDR)  /**< @brief DMA2 str1 base addr reg def */
#define DMA2_STR2   ((DMA_Stream_RegDef_t*)DMA2_STR2_BASEADDR)  /**< @brief DMA2 str2 base addr reg def */
#define DMA2_STR3   ((DMA_Stream_RegDef_t*)DMA2_STR3_BASEADDR)  /**< @brief DMA2 str3 base addr reg def */
#define DMA2_STR4   ((DMA_Stream_RegDef_t*)DMA2_STR4_BASEADDR)  /**< @brief DMA2 str4 base addr reg def */
#define DMA2_STR5   ((DMA_Stream_RegDef_t*)DMA2_STR5_BASEADDR)  /**< @brief DMA2 str5 base addr reg def */
#define DMA2_STR6   ((DMA_Stream_RegDef_t*)DMA2_STR6_BASEADDR)  /**< @brief DMA2 str6 base addr reg def */
#define DMA2_STR7   ((DMA_Stream_RegDef_t*)DMA2_STR7_BASEADDR)  /**< @brief DMA2 str7 base addr reg def */

#define PWR         ((PWR_RegDef_t*)PWR_BASEADDR)               /**< @brief PWR base addr reg def */

#define RTC         ((RTC_RegDef_t*)RTCBKP_BASEADDR)            /**< @brief RTC base addr reg definition */
/** @} */

/***********************************************************************************************************/
/*                          Peripheral macros                                                              */
/***********************************************************************************************************/

/**
 * @name Clock enable macros for GPIOx peripheral.
 * @{
 */
#define GPIOA_PCLK_EN()     (RCC->AHB1ENR |= (1 << 0))  /**< @brief Clock enable for GPIOA */
#define GPIOB_PCLK_EN()     (RCC->AHB1ENR |= (1 << 1))  /**< @brief Clock enable for GPIOB */
#define GPIOC_PCLK_EN()     (RCC->AHB1ENR |= (1 << 2))  /**< @brief Clock enable for GPIOC */
#define GPIOD_PCLK_EN()     (RCC->AHB1ENR |= (1 << 3))  /**< @brief Clock enable for GPIOD */
#define GPIOE_PCLK_EN()     (RCC->AHB1ENR |= (1 << 4))  /**< @brief Clock enable for GPIOE */
#define GPIOF_PCLK_EN()     (RCC->AHB1ENR |= (1 << 5))  /**< @brief Clock enable for GPIOF */
#define GPIOG_PCLK_EN()     (RCC->AHB1ENR |= (1 << 6))  /**< @brief Clock enable for GPIOG */
#define GPIOH_PCLK_EN()     (RCC->AHB1ENR |= (1 << 7))  /**< @brief Clock enable for GPIOH */
/** @} */

/**
 * @name Clock enable macros for I2Cx peripheral.
 * @{
 */
#define I2C1_PCLK_EN()      (RCC->APB1ENR |= (1 << 21)) /**< @brief Clock enable for I2C1 */
#define I2C2_PCLK_EN()      (RCC->APB1ENR |= (1 << 22)) /**< @brief Clock enable for I2C2 */
#define I2C3_PCLK_EN()      (RCC->APB1ENR |= (1 << 23)) /**< @brief Clock enable for I2C3 */
/** @} */

/**
 * @name Clock enable macros for SPIx peripheral.
 * @{
 */
#define SPI1_PCLK_EN()      (RCC->APB2ENR |= (1 << 12)) /**< @brief Clock enable for SPI1 */
#define SPI2_PCLK_EN()      (RCC->APB1ENR |= (1 << 14)) /**< @brief Clock enable for SPI2 */
#define SPI3_PCLK_EN()      (RCC->APB1ENR |= (1 << 15)) /**< @brief Clock enable for SPI3 */
#define SPI4_PCLK_EN()      (RCC->APB2ENR |= (1 << 13)) /**< @brief Clock enable for SPI4 */
/** @} */

/**
 * @name Clock enable macros for USARTx / UARTx peripheral.
 * @{
 */
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1 << 4))  /**< @brief Clock enable for USART1 */
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1 << 17)) /**< @brief Clock enable for USART2 */
#define USART3_PCLK_EN()    (RCC->APB1ENR |= (1 << 18)) /**< @brief Clock enable for USART3 */
#define UART4_PCLK_EN()     (RCC->APB1ENR |= (1 << 19)) /**< @brief Clock enable for UART4 */
#define UART5_PCLK_EN()     (RCC->APB1ENR |= (1 << 20)) /**< @brief Clock enable for UART5 */
#define USART6_PCLK_EN()    (RCC->APB2ENR |= (1 << 5))  /**< @brief Clock enable for USART6 */
/** @} */

/**
 * @name Clock enable macros for SYSCFG peripheral.
 * @{
 */
#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1 << 14)) /**< @brief Clock enable for SYSCFG */
/** @} */

/**
 * @name Clock enable macros for CRC peripheral.
 * @{
 */
#define CRC_PCLK_EN()       (RCC->AHB1ENR |= (1 << 12)) /**< @brief Clock enable for CRC */
/** @} */

/**
 * @name Clock enable macros for TIM peripheral.
 * @{
 */
#define TIM1_PCLK_EN()      (RCC->APB2ENR |= (1 << 0))  /**< @brief Clock enable for TIM1 */
#define TIM2_PCLK_EN()      (RCC->APB1ENR |= (1 << 0))  /**< @brief Clock enable for TIM2 */
#define TIM3_PCLK_EN()      (RCC->APB1ENR |= (1 << 1))  /**< @brief Clock enable for TIM3 */
#define TIM4_PCLK_EN()      (RCC->APB1ENR |= (1 << 2))  /**< @brief Clock enable for TIM4 */
#define TIM5_PCLK_EN()      (RCC->APB1ENR |= (1 << 3))  /**< @brief Clock enable for TIM5 */
#define TIM6_PCLK_EN()      (RCC->APB1ENR |= (1 << 4))  /**< @brief Clock enable for TIM6 */
#define TIM7_PCLK_EN()      (RCC->APB1ENR |= (1 << 5))  /**< @brief Clock enable for TIM7 */
#define TIM8_PCLK_EN()      (RCC->APB2ENR |= (1 << 1))  /**< @brief Clock enable for TIM8 */
#define TIM9_PCLK_EN()      (RCC->APB2ENR |= (1 << 16)) /**< @brief Clock enable for TIM9 */
#define TIM10_PCLK_EN()     (RCC->APB2ENR |= (1 << 17)) /**< @brief Clock enable for TIM10 */
#define TIM11_PCLK_EN()     (RCC->APB2ENR |= (1 << 18)) /**< @brief Clock enable for TIM11 */
#define TIM12_PCLK_EN()     (RCC->APB1ENR |= (1 << 6))  /**< @brief Clock enable for TIM12 */
#define TIM13_PCLK_EN()     (RCC->APB1ENR |= (1 << 7))  /**< @brief Clock enable for TIM13 */
#define TIM14_PCLK_EN()     (RCC->APB1ENR |= (1 << 8))  /**< @brief Clock enable for TIM14 */
/** @} */

/**
 * @name Clock enable macros for PWR peripheral.
 * @{
 */
#define PWR_PCLK_EN()       (RCC->APB1ENR |= (1 << 28)) /**< @brief Clock enable for PWR */
/** @} */

/**
 * @name Clock enable macros for DMA peripheral
 * @{
 */
#define DMA1_PCLK_EN()      (RCC->AHB1ENR |= (1 << 21)) /**< @brief Clock enable for DMA1 */
#define DMA2_PCLK_EN()      (RCC->AHB1ENR |= (1 << 22)) /**< @brief Clock enable for DMA2 */
/** @} */

/**
 * @name Clock enable macros for RTC peripheral
 * @{
 */
#define RTC_PCLK_EN()       (RCC->BDCR |= (1 << 15))    /**< @brief clock enable for RTC */
/** @} */

/**
 * @name Clock disable macros for GPIOx peripheral.
 * @{
 */
#define GPIOA_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 0)) /**< @brief Clock disable for GPIOA */
#define GPIOB_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 1)) /**< @brief Clock disable for GPIOB */
#define GPIOC_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 2)) /**< @brief Clock disable for GPIOC */
#define GPIOD_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 3)) /**< @brief Clock disable for GPIOD */
#define GPIOE_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 4)) /**< @brief Clock disable for GPIOE */
#define GPIOF_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 5)) /**< @brief Clock disable for GPIOF */
#define GPIOG_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 6)) /**< @brief Clock disable for GPIOG */
#define GPIOH_PCLK_DI()     (RCC->AHB1ENR &= ~(1 << 7)) /**< @brief Clock disable for GPIOH */
/** @} */

/**
 * @name Clock disable macros for I2Cx peripheral.
 * @{
 */
#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 21)) /**< @brief Clock disable for I2C1 */
#define I2C2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 22)) /**< @brief Clock disable for I2C2 */
#define I2C3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 23)) /**< @brief Clock disable for I2C3 */
/** @} */

/**
 * @name Clock disable macros for SPIx peripheral.
 * @{
 */
#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 12)) /**< @brief Clock disable for SPI1 */
#define SPI2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 14)) /**< @brief Clock disable for SPI2 */
#define SPI3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 15)) /**< @brief Clock disable for SPI3 */
#define SPI4_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 13)) /**< @brief Clock disable for SPI4 */
/** @} */

/**
 * @name Clock disable macros for USARTx / UARTx peripheral.
 * @{
 */
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 4))     /**< @brief Clock disable for USART1 */
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 17))    /**< @brief Clock disable for USART2 */
#define USART3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 18))    /**< @brief Clock disable for USART3 */
#define UART4_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 19))    /**< @brief Clock disable for UART4 */
#define UART5_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 20))    /**< @brief Clock disable for UART5 */
#define USART6_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 5))     /**< @brief Clock disable for USART6 */
/** @} */

/**
 * @name Clock disable macros for SYSCFG peripheral.
 * @{
 */
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14))    /**< @brief Clock disable for SYSCFG */
/** @} */

/**
 * @name Clock disable macros for CRC peripheral.
 * @{
 */
#define CRC_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 12))    /**< @brief Clock disable for CRC */
/** @} */

/**
 * @name Clock disable macros for TIM peripheral.
 * @{
 */
#define TIM1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 0))     /**< @brief Clock disable for TIM1 */
#define TIM2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 0))     /**< @brief Clock disable for TIM2 */
#define TIM3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 1))     /**< @brief Clock disable for TIM3 */
#define TIM4_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 2))     /**< @brief Clock disable for TIM4 */
#define TIM5_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 3))     /**< @brief Clock disable for TIM5 */
#define TIM6_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 4))     /**< @brief Clock disable for TIM6 */
#define TIM7_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 5))     /**< @brief Clock disable for TIM7 */
#define TIM8_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 8))     /**< @brief Clock disable for TIM8 */
#define TIM9_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 16))    /**< @brief Clock disable for TIM9 */
#define TIM10_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 17))    /**< @brief Clock disable for TIM10 */
#define TIM11_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 18))    /**< @brief Clock disable for TIM11 */
#define TIM12_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 6))     /**< @brief Clock disable for TIM12 */
#define TIM13_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 7))     /**< @brief Clock disable for TIM13 */
#define TIM14_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 8))     /**< @brief Clock disable for TIM14 */
/** @} */

/**
 * @name Clock disable macros for PWR peripheral.
 * @{
 */
#define PWR_PCLK_DI()       (RCC->APB1ENR &= ~(1 << 28))    /**< @brief Clock disable for PWR */
/** @} */

/**
 * @name Clock disable macros for DMA peripheral
 * @{
 */
#define DMA1_PCLK_DI()      (RCC->AHB1ENR &= ~(1 << 21))    /**< @brief Clock disable for DMA1 */
#define DMA2_PCLK_DI()      (RCC->AHB1ENR &= ~(1 << 22))    /**< @brief Clock disable for DMA2 */
/** @} */

/**
 * @name Clock disable macros for RTC peripheral
 * @{
 */
#define RTC_PCLK_DI()       (RCC->BDCR &= ~(1 << 15))       /**< @brief clock disable for RTC */
/** @} */

/**
 * @name Reset macros GPIOx peripheral.
 * @{
 */
/** @brief Reset macro for GPIOA */
#define GPIOA_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
/** @brief Reset macro for GPIOB */
#define GPIOB_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
/** @brief Reset macro for GPIOC */
#define GPIOC_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
/** @brief Reset macro for GPIOD */
#define GPIOD_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
/** @brief Reset macro for GPIOE */
#define GPIOE_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
/** @brief Reset macro for GPIOF */
#define GPIOF_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
/** @brief Reset macro for GPIOG */
#define GPIOG_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
/** @brief Reset macro for GPIOH */
#define GPIOH_REG_RESET()   do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)
/** @} */

/**
 * @brief This macro returns a code between 0 to 7 for a given GPIO base address(x).
 */
#define GPIO_BASEADDR_TO_CODE(x)    ((x == GPIOA) ? 0 :\
                                    (x == GPIOB) ? 1 :\
                                    (x == GPIOC) ? 2 :\
                                    (x == GPIOD) ? 3 :\
                                    (x == GPIOE) ? 4 :\
                                    (x == GPIOF) ? 5 :\
                                    (x == GPIOG) ? 6 :\
                                    (x == GPIOH) ? 7 : 0)

/**
 * @name Reset macros SPIx peripheral.
 * @{
 */
/** @brief Reset macro for SPI1 */
#define SPI1_REG_RESET()    do{(RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12));}while(0)
/** @brief Reset macro for SPI2 */
#define SPI2_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14));}while(0)
/** @brief Reset macro for SPI3 */
#define SPI3_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15));}while(0)
/** @brief Reset macro for SPI4 */
#define SPI4_REG_RESET()    do{(RCC->APB2RSTR |= (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13));}while(0)
/** @} */

/**
 * @name Reset macros I2Cx peripheral.
 * @{
 */
/** @brief Reset macro for I2C1 */
#define I2C1_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21));}while(0)
/** @brief Reset macro for I2C2 */
#define I2C2_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22));}while(0)
/** @brief Reset macro for I2C3 */
#define I2C3_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23));}while(0)
/** @} */

/**
 * @name Reset macros USARTx peripheral.
 * @{
 */
/** @brief Reset macro for USART1 */
#define USART1_REG_RESET()  do{(RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4));}while(0)
/** @brief Reset macro for USART2 */
#define USART2_REG_RESET()  do{(RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17));}while(0)
/** @brief Reset macro for USART3 */
#define USART3_REG_RESET()  do{(RCC->APB1RSTR |= (1 << 18)); (RCC->APB1RSTR &= ~(1 << 18));}while(0)
/** @brief Reset macro for UART4 */
#define UART4_REG_RESET()   do{(RCC->APB1RSTR |= (1 << 19)); (RCC->APB1RSTR &= ~(1 << 19));}while(0)
/** @brief Reset macro for UART5 */
#define UART5_REG_RESET()   do{(RCC->APB1RSTR |= (1 << 20)); (RCC->APB1RSTR &= ~(1 << 20));}while(0)
/** @brief Reset macro for USART6 */
#define USART6_REG_RESET()  do{(RCC->APB2RSTR |= (1 << 5)); (RCC->APB2RSTR &= ~(1 << 5));}while(0)
/** @} */

/**
 * @name Reset macros CRC peripheral.
 * @{
 */
/** @brief Reset macro for CRC */
#define CRC_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 12)); (RCC->AHB1RSTR &= ~(1 << 12));}while(0)
/** @} */

/**
 * @name Reset macros TIM peripheral.
 * @{
 */
/** @brief Reset macro for TIM1 */
#define TIM1_REG_RESET()    do{(RCC->APB2RSTR |= (1 << 0)); (RCC->APB2RSTR &= ~(1 << 0));}while(0)
/** @brief Reset macro for TIM2 */
#define TIM2_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 0)); (RCC->APB1RSTR &= ~(1 << 0));}while(0)
/** @brief Reset macro for TIM3 */
#define TIM3_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 1)); (RCC->APB1RSTR &= ~(1 << 1));}while(0)
/** @brief Reset macro for TIM4 */
#define TIM4_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 2)); (RCC->APB1RSTR &= ~(1 << 2));}while(0)
/** @brief Reset macro for TIM5 */
#define TIM5_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 3)); (RCC->APB1RSTR &= ~(1 << 3));}while(0)
/** @brief Reset macro for TIM6 */
#define TIM6_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 4)); (RCC->APB1RSTR &= ~(1 << 4));}while(0)
/** @brief Reset macro for TIM7 */
#define TIM7_REG_RESET()    do{(RCC->APB1RSTR |= (1 << 5)); (RCC->APB1RSTR &= ~(1 << 5));}while(0)
/** @brief Reset macro for TIM8 */
#define TIM8_REG_RESET()    do{(RCC->APB2RSTR |= (1 << 1)); (RCC->APB2RSTR &= ~(1 << 1));}while(0)
/** @brief Reset macro for TIM9 */
#define TIM9_REG_RESET()    do{(RCC->APB2RSTR |= (1 << 16)); (RCC->APB2RSTR &= ~(1 << 16));}while(0)
/** @brief Reset macro for TIM10 */
#define TIM10_REG_RESET()   do{(RCC->APB2RSTR |= (1 << 17)); (RCC->APB2RSTR &= ~(1 << 17));}while(0)
/** @brief Reset macro for TIM11 */
#define TIM11_REG_RESET()   do{(RCC->APB2RSTR |= (1 << 18)); (RCC->APB2RSTR &= ~(1 << 18));}while(0)
/** @brief Reset macro for TIM12 */
#define TIM12_REG_RESET()   do{(RCC->APB1RSTR |= (1 << 6)); (RCC->APB1RSTR &= ~(1 << 6));}while(0)
/** @brief Reset macro for TIM13 */
#define TIM13_REG_RESET()   do{(RCC->APB1RSTR |= (1 << 7)); (RCC->APB1RSTR &= ~(1 << 7));}while(0)
/** @brief Reset macro for TIM14 */
#define TIM14_REG_RESET()   do{(RCC->APB1RSTR |= (1 << 8)); (RCC->APB1RSTR &= ~(1 << 8));}while(0)
/** @} */

/**
 * @name Reset macros DMA peripheral
 * @{
 */
/** @brief Reset macro for DMA1 */
#define DMA1_REG_RESET()    do{(RCC->AHB1RSTR |= (1 << 21)); (RCC->AHB1RSTR &= ~(1 << 21));}while(0)
/** @brief Reset macro for DMA2 */
#define DMA2_REG_RESET()    do{(RCC->AHB1RSTR |= (1 << 22)); (RCC->AHB1RSTR &= ~(1 << 22));}while(0)
/** @} */

/***********************************************************************************************************/
/*                          IRQ definitions                                                                */
/***********************************************************************************************************/

/**
 * @name IRQ (Interrupt Request) number.
 * @{
 */
#define IRQ_NO_EXTI0                6   /**< @brief Interrupt Num for EXTI0 */
#define IRQ_NO_EXTI1                7   /**< @brief Interrupt Num for EXTI1 */
#define IRQ_NO_EXTI2                8   /**< @brief Interrupt Num for EXTI2 */
#define IRQ_NO_EXTI3                9   /**< @brief Interrupt Num for EXTI3 */
#define IRQ_NO_EXTI4                10  /**< @brief Interrupt Num for EXTI4 */
#define IRQ_NO_DMA1_STREAM0         11  /**< @brief Interrupt Num for DMA1 Stream0 */
#define IRQ_NO_DMA1_STREAM1         12  /**< @brief Interrupt Num for DMA1 Stream1 */
#define IRQ_NO_DMA1_STREAM2         13  /**< @brief Interrupt Num for DMA1 Stream2 */
#define IRQ_NO_DMA1_STREAM3         14  /**< @brief Interrupt Num for DMA1 Stream3 */
#define IRQ_NO_DMA1_STREAM4         15  /**< @brief Interrupt Num for DMA1 Stream4 */
#define IRQ_NO_DMA1_STREAM5         16  /**< @brief Interrupt Num for DMA1 Stream5 */
#define IRQ_NO_DMA1_STREAM6         17  /**< @brief Interrupt Num for DMA1 Stream6 */
#define IRQ_NO_EXTI9_5              23  /**< @brief Interrupt Num for EXTI5 to EXTI9 */
#define IRQ_NO_EXTI15_10            40  /**< @brief Interrupt Num for EXTI10 to EXTI15 */
#define IRQ_NO_SPI1                 35  /**< @brief Interrupt Num for SPI1 */
#define IRQ_NO_SPI2                 36  /**< @brief Interrupt Num for SPI2 */
#define IRQ_NO_SPI3                 51  /**< @brief Interrupt Num for SPI3 */
#define IRQ_NO_SPI4                 84  /**< @brief Interrupt Num for SPI4 */
#define IRQ_NO_I2C1_EV              31  /**< @brief Interrupt Num for I2C1 EV */
#define IRQ_NO_I2C1_ER              32  /**< @brief Interrupt Num for I2C1 ER */
#define IRQ_NO_I2C2_EV              33  /**< @brief Interrupt Num for I2C2 EV */
#define IRQ_NO_I2C2_ER              34  /**< @brief Interrupt Num for I2C2 ER */
#define IRQ_NO_I2C3_EV              72  /**< @brief Interrupt Num for I2C3 EV */
#define IRQ_NO_I2C3_ER              73  /**< @brief Interrupt Num for I2C3 ER */
#define IRQ_NO_USART1               37  /**< @brief Interrupt Num for USART1 */
#define IRQ_NO_USART2               38  /**< @brief Interrupt Num for USART2 */
#define IRQ_NO_USART3               39  /**< @brief Interrupt Num for USART3 */
#define IRQ_NO_UART4                52  /**< @brief Interrupt Num for UART4 */
#define IRQ_NO_UART5                53  /**< @brief Interrupt Num for UART5 */
#define IRQ_NO_USART6               71  /**< @brief Interrupt Num for USART6 */
#define IRQ_NO_TIM1_BRK_TIM9        24  /**< @brief Interrupt Num for TIM1 BRK and TIM9 global */
#define IRQ_NO_TIM1_UP_TIM10        25  /**< @brief Interrupt Num for TIM1 UP and TIM10 global */
#define IRQ_NO_TIM1_TRG_COM_TIM11   26  /**< @brief Interrupt Num for TIM1 TRG and COM and TIM 11 global */
#define IRQ_NO_TIM1_CC              27  /**< @brief Interrupt Num for TIM1 Capture/Compare */
#define IRQ_NO_TIM2                 28  /**< @brief Interrupt Num for TIM2 */
#define IRQ_NO_TIM3                 29  /**< @brief Interrupt Num for TIM3 */
#define IRQ_NO_TIM4                 30  /**< @brief Interrupt Num for TIM4 */
#define IRQ_NO_TIM8_BRK_TIM12       43  /**< @brief Interrupt Num for TIM8 BRK and TIM12 global */
#define IRQ_NO_TIM8_UP_TIM13        44  /**< @brief Interrupt Num for TIM8 UP and TIM13 global */
#define IRQ_NO_TIM8_TRG_COM_TIM14   45  /**< @brief Interrupt Num for TIM8 TRG and COM and TIM14 global */
#define IRQ_NO_TIM8_CC              46  /**< @brief Interrupt Num for TIM8 Capture/Compare */
#define IRQ_DMA1_STREAM7            47  /**< @brief Interrupt Num for DMA1 Stream7 */
#define IRQ_NO_TIM5                 50  /**< @brief Interrupt Num for TIM5 */
#define IRQ_NO_TIM6_DAC             54  /**< @brief Interrupt Num for TIM6 or DAC */
#define IRQ_NO_TIM7                 55  /**< @brief Interrupt Num for TIM7 */
#define IRQ_DMA2_STREAM0            56  /**< @brief Interrupt Num for DMA2 Stream0 */
#define IRQ_DMA2_STREAM1            57  /**< @brief Interrupt Num for DMA2 Stream1 */
#define IRQ_DMA2_STREAM2            58  /**< @brief Interrupt Num for DMA2 Stream2 */
#define IRQ_DMA2_STREAM3            59  /**< @brief Interrupt Num for DMA2 Stream3 */
#define IRQ_DMA2_STREAM4            60  /**< @brief Interrupt Num for DMA2 Stream4 */
#define IRQ_DMA2_STREAM5            68  /**< @brief Interrupt Num for DMA2 Stream5 */
#define IRQ_DMA2_STREAM6            69  /**< @brief Interrupt Num for DMA2 Stream6 */
#define IRQ_DMA2_STREAM7            70  /**< @brief Interrupt Num for DMA2 Stream7 */
#define IRQ_RTC_ALARM               41  /**< @brief Interrupt Num for RTC alarm */
/** @} */

/**
 * @name IRQ priority.
 * @{
 */
#define NVIC_IRQ_PRIORITY0      0   /**< @brief Interrupt Priority 0 */
#define NVIC_IRQ_PRIORITY1      1   /**< @brief Interrupt Priority 1 */
#define NVIC_IRQ_PRIORITY2      2   /**< @brief Interrupt Priority 2 */
#define NVIC_IRQ_PRIORITY3      3   /**< @brief Interrupt Priority 3 */
#define NVIC_IRQ_PRIORITY4      4   /**< @brief Interrupt Priority 4 */
#define NVIC_IRQ_PRIORITY5      5   /**< @brief Interrupt Priority 5 */
#define NVIC_IRQ_PRIORITY6      6   /**< @brief Interrupt Priority 6 */
#define NVIC_IRQ_PRIORITY7      7   /**< @brief Interrupt Priority 7 */
#define NVIC_IRQ_PRIORITY8      8   /**< @brief Interrupt Priority 8 */
#define NVIC_IRQ_PRIORITY9      9   /**< @brief Interrupt Priority 9 */
#define NVIC_IRQ_PRIORITY10     10  /**< @brief Interrupt Priority 10 */
#define NVIC_IRQ_PRIORITY11     11  /**< @brief Interrupt Priority 11 */
#define NVIC_IRQ_PRIORITY12     12  /**< @brief Interrupt Priority 12 */
#define NVIC_IRQ_PRIORITY13     13  /**< @brief Interrupt Priority 13 */
#define NVIC_IRQ_PRIORITY14     14  /**< @brief Interrupt Priority 14 */
#define NVIC_IRQ_PRIORITY15     15  /**< @brief Interrupt Priority 15 */
/** @} */

#endif /* STM32F446XX_H */
