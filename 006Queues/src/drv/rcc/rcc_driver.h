/********************************************************************************************************//**
* @file rcc_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the RCC peripheral.
*
* Public Functions:
*       - uint32_t RCC_GetPCLK1Value(void)
*       - uint32_t RCC_GetPCLK2Value(void)
*       - uint32_t RCC_GetPLLOutputClock(void)
*       - uint8_t  RCC_SetSystemClock(RCC_Config_t RCC_Config)
*       - uint8_t RCC_SetMCO1Clk(RCC_Config_t RCC_Config)
*       - uint8_t RCC_SetMCO2Clk(RCC_Config_t RCC_Config)
*/

#ifndef RCC_DRIVER_H
#define RCC_DRIVER_H

#include <stdint.h>

/**
 * @defgroup Clk_Source Possible system clk input source values.
 * @{
 */
#define RCC_CLK_SOURCE_HSI      0   /**< @brief High Speed Internal source clock */
#define RCC_CLK_SOURCE_HSE      1   /**< @brief High Speed External source clock */
#define RCC_CLK_SOURCE_PLL_P    2   /**< @brief PLL_P source clock */
#define RCC_CLK_SOURCE_PLL_R    3   /**< @brief PLL_R source clock */
/**@}*/

/**
 * @defgroup HSE_Mode Possible modes for HSE input source.
 * @{
 */
#define RCC_HSE_BYPASS          0   /**< @brief Bypass mode for HSE source clock */
#define RCC_HSE_CRYSTAL         1   /**< @brief Crystal mode for HSE source clock */
/**@}*/

/**
 * @defgroup AHP_Presc Possible values of AHP prescaler.
 * @{
 */
#define AHB_NO_PRESC            0x00    /**< @brief AHB prescaler division factor to 1 */
#define AHB_PRESC_2             0x08    /**< @brief AHB prescaler division factor to 2 */
#define AHB_PRESC_4             0x09    /**< @brief AHB prescaler division factor to 4 */
#define AHB_PRESC_8             0x0A    /**< @brief AHB prescaler division factor to 8 */
#define AHB_PRESC_16            0x0B    /**< @brief AHB prescaler division factor to 16 */
#define AHB_PRESC_64            0x0C    /**< @brief AHB prescaler division factor to 64 */
#define AHB_PRESC_128           0x0D    /**< @brief AHB prescaler division factor to 128 */
#define AHB_PRESC_256           0x0E    /**< @brief AHB prescaler division factor to 256 */
#define AHB_PRESC_512           0x0F    /**< @brief AHB prescaler division factor to 512 */
/**@}*/

/**
 * @defgroup APB1_Presc Possible values of APB1 prescaler.
 * @{
 */
#define APB1_NO_PRESC           0x00    /**< @brief APB1 prescaler division factor to 1 */
#define APB1_PRESC_2            0x04    /**< @brief APB1 prescaler division factor to 2 */
#define APB1_PRESC_4            0x05    /**< @brief APB1 prescaler division factor to 4 */
#define APB1_PRESC_8            0x06    /**< @brief APB1 prescaler division factor to 8 */
#define APB1_PRESC_16           0x07    /**< @brief APB1 prescaler division factor to 16 */
/**@}*/

/**
 * @defgroup APB2_Presc Possible values of APB2 prescaler.
 * @{
 */
#define APB2_NO_PRESC           0x00    /**< @brief APB2 prescaler division factor to 1 */
#define APB2_PRESC_2            0x04    /**< @brief APB2 prescaler division factor to 2 */
#define APB2_PRESC_4            0x05    /**< @brief APB2 prescaler division factor to 4 */
#define APB2_PRESC_8            0x06    /**< @brief APB2 prescaler division factor to 8 */
#define APB2_PRESC_16           0x07    /**< @brief APB2 prescaler division factor to 16 */
/**@}*/

/**
 * @defgroup PLL_Source Possible PLL clk input source values.
 * @{
 */
#define PLL_SOURCE_HSI          0x00    /**< @brief HSI source clock for PLL */
#define PLL_SOURCE_HSE          0x01    /**< @brief HSE source clock for PLL */
/**@}*/

/**
 * @defgroup PLL_P Possible values of PLL P prescaler.
 * @{
 */
#define PLL_P_2                 0x00    /**< @brief PLL P prescaler division factor to 2 */
#define PLL_P_4                 0x01    /**< @brief PLL P prescaler division factor to 4 */
#define PLL_P_6                 0x02    /**< @brief PLL P prescaler division factor to 6 */
#define PLL_P_8                 0x03    /**< @brief PLL P prescaler division factor to 8 */
/**@}*/

/**
 * @defgroup MCO1_Source Possible MCO1 source values.
 * @{
 */
#define MCO1_HSI                0x00    /**< @brief HSI as input source of MCO1 */
#define MCO1_LSE                0x01    /**< @brief LSE as input source of MCO1 */
#define MCO1_HSE                0x02    /**< @brief HSE as input source of MCO1 */
#define MCO1_PLL                0x03    /**< @brief PLL as input source of MCO1 */
/**@}*/

/**
 * @defgroup MCO2_Source Possible MCO2 source values.
 * @{
 */
#define MCO2_SYSCLK             0x00    /**< @brief SYSCLK as input source of MCO2 */
#define MCO2_PLLI2S             0x01    /**< @brief PLLI2S as input source of MCO2 */
#define MCO2_HSE                0x02    /**< @brief HSE as input source of MCO2 */
#define MCO2_PLL                0x03    /**< @brief PLL as input source of MCO2 */
/**@}*/

/**
 * @defgroup MCO_Presc Possible values of MCO1 and MCO2 prescaler.
 * @{
 */
#define MCO_P_1                 0x00    /**< @brief MCO1 no prescaler division factor */
#define MCO_P_2                 0x04    /**< @brief MCO1 prescaler division factor to 2 */
#define MCO_P_3                 0x05    /**< @brief MCO1 prescaler division factor to 3 */
#define MCO_P_4                 0x06    /**< @brief MCO1 prescaler division factor to 4 */
#define MCO_P_5                 0x07    /**< @brief MCO1 prescaler division factor to 5 */
/**@}*/

/**
 * @defgroup LSE_Bypass Possible values of LSE Bypass.
 * @{
 */
#define RCC_LSE_BYPASS          0x00    /**< @brief Bypass mode for LSE source clock */
#define RCC_LSE_CRYSTAL         0x01    /**< @brief Crystal mode for LSE source clock */
/**@}*/

/**
 * @brief Configuration structure for RCC peripheral.
 */
typedef struct
{
    uint8_t clk_source;     /**< Possible values from @ref Clk_Source */
    uint8_t hse_mode;       /**< Possible values from @ref HSE_Mode */
    uint8_t ahb_presc;      /**< Possible values from @ref AHP_Presc */
    uint8_t apb1_presc;     /**< Possible values from @ref APB1_Presc */
    uint8_t apb2_presc;     /**< Possible values from @ref APB2_Presc */
    uint8_t pll_source;     /**< Possible values from @ref PLL_Source */
    uint8_t pll_r;          /**< Prescaler R value (2 <= pll_r <= 7) */
    uint8_t pll_q;          /**< Prescaler Q value (2 <= pll_q <= 15) */
    uint8_t pll_p;          /**< Possible values from @ref PLL_P */
    uint8_t pll_m;          /**< Division factor of PLL (2 <= pll_m <= 63 */
    uint16_t pll_n;         /**< Multiplication factor of PLL (50 <= pll_n <= 432) */
    uint8_t mco1_source;    /**< Possible values from @ref MCO1_Source */
    uint8_t mco1_presc;     /**< Possible values from @ref MCO_Presc */
    uint8_t mco2_source;    /**< Possible values from @ref MCO2_Source */
    uint8_t mco2_presc;     /**< Possible values from @ref MCO_Presc */
    uint8_t lse_bypass;     /**< Possible values from @ref LSE_Bypass */
    uint8_t plli2s_r;       /**< Prescaler R value (2 <= plli2s_r <= 7) */
    uint8_t plli2s_q;       /**< Prescaler Q value (2 <= plli2s_q <= 15) */
    uint8_t plli2s_p;       /**< Possible values from @ref PLL_P */
    uint8_t plli2s_m;       /**< Division factor of PLLI2S (2 <= plli2s_m <= 63) */
    uint16_t plli2s_n;      /**< Multiplication factor of PLL (50 <= plli2s_n <= 432) */
}RCC_Config_t;

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to calculate the PCLK1 clock value.
 * @return PCLK1 clock value.
 */
uint32_t RCC_GetPCLK1Value(void);

/**
 * @brief Function to calculate the PCLK2 clock value.
 * @return PCLK1 clock value.
 */
uint32_t RCC_GetPCLK2Value(void);

/**
 * @brief Function to calculate the PLL clock value.
 * @return PLL clock value.
 */
uint32_t RCC_GetPLLOutputClock(void);

/**
 * @brief Function to set the system clock and related prescaler values.
 * @param[in] RCC_Config is the configuration struct.
 * @return 0 is OK.
 * @return 1 is fail.
 */
uint8_t RCC_SetSystemClock(RCC_Config_t RCC_Config);

/**
 * @brief Function to configure the MCO1.
 * @param[in] RCC_Config is the configuration struct.
 * @return 0 is OK.
 * @return 1 is fail.
 */
uint8_t RCC_SetMCO1Clk(RCC_Config_t RCC_Config);

/**
 * @brief Function to configure the MCO2.
 * @param[in] RCC_Config is the configuration struct.
 * @return 0 is OK.
 * @return 1 is fail.
 */
uint8_t RCC_SetMCO2Clk(RCC_Config_t RCC_Config);

#endif /* RCC_DRIVER_H */
