/********************************************************************************************************//**
* @file rcc_driver.c
*
* @brief File containing the APIs for configuring the RCC peripheral.
*
* Public Functions:
*       - uint32_t RCC_GetPCLK1Value(void)
*       - uint32_t RCC_GetPCLK2Value(void)
*       - uint32_t RCC_GetPLLOutputClock(void)
*       - uint8_t  RCC_SetSystemClock(RCC_Config_t RCC_Config)
*       - uint8_t RCC_SetMCO1Clk(RCC_Config_t RCC_Config)
*       - uint8_t RCC_SetMCO2Clk(RCC_Config_t RCC_Config)
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include <stdint.h>
#include "stm32f446xx.h"
#include "rcc_driver.h"

/** @brief Frequency of 8 MHz */
#define FREQ_8MHZ    8000000
/** @brief Frequency of 16 MHz */
#define FREQ_16MHZ   16000000

/** @brief Possible AHB prescaler values */
static uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
/** @brief Possible APB prescaler values */
static uint8_t APB_PreScaler[4] = {2, 4, 8, 16};
/** @brief Possible PLLP prescaler values */
static uint8_t PLLP_PreScaler[4] = {2, 4, 6, 8};

/***********************************************************************************************************/
/*                                       Static Function Prototypes                                        */
/***********************************************************************************************************/

/**
 * @brief Function for configuring the PLL.
 * @param[in] RCC_Config is the configuration struct.
 * @return void.
 */
static void RCC_PLLConfig(RCC_Config_t RCC_Config);

/**
 * @brief Function for configuring the PLLI2S.
 * @param[in] RCC_Config is the configuration struct.
 * @return void.
 */
static void RCC_PLLI2SConfig(RCC_Config_t RCC_Config);

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

uint32_t RCC_GetPCLK1Value(void){

    uint32_t pclk1, systemclk, clksrc;
    uint8_t temp;
    uint8_t ahbp, apb1p;

    /* Check for SWS */
    clksrc = ((RCC->CFGR >> RCC_CFGR_SWS) & 0x3);

    if(clksrc == 0){
        /* clk is HSI */
        systemclk = FREQ_16MHZ;
    }
    else if(clksrc == 1){
        /* clk is HSE */
        systemclk = FREQ_8MHZ;
    }
    else if(clksrc == 2){
        /* clk is PLL */
        systemclk = RCC_GetPLLOutputClock();
    }
    else{
        /* do nothing */
    }

    /* AHB prescaler */
    temp = ((RCC->CFGR >> RCC_CFGR_HPRE) & 0xF);

    if(temp < 8){
        ahbp = 1;
    }
    else{
        ahbp = AHB_PreScaler[temp-8];
    }

    /* APB1 prescaler */
    temp = ((RCC->CFGR >> RCC_CFGR_PPRE1) & 0x7);

    if(temp < 4){
        apb1p = 1;
    }
    else{
        apb1p = APB_PreScaler[temp-4];
    }

    pclk1 = (systemclk/ahbp)/apb1p;

    return pclk1;
}

uint32_t RCC_GetPCLK2Value(void){

    uint32_t pclk2, systemclk, clksrc;
    uint8_t temp;
    uint8_t ahbp, apb2p;

    /* Check for SWS */
    clksrc = ((RCC->CFGR >> RCC_CFGR_SWS) & 0x3);

    if(clksrc == 0){
        /* clk is HSI */
        systemclk = FREQ_16MHZ;
    }
    else if(clksrc == 1){
        /* clk is HSE */
        systemclk = FREQ_8MHZ;
    }
    else if(clksrc == 2){
        /* clk is PLL */
        systemclk = RCC_GetPLLOutputClock();
    }
    else{
        /* do nothing */
    }

    /* AHB prescaler */
    temp = ((RCC->CFGR >> RCC_CFGR_HPRE) & 0xF);

    if(temp < 8){
        ahbp = 1;
    }
    else{
        ahbp = AHB_PreScaler[temp-8];
    }

    /* APB2 prescaler */
    temp = ((RCC->CFGR >> RCC_CFGR_PPRE2) & 0x7);

    if(temp < 4){
        apb2p = 1;
    }
    else{
        apb2p = APB_PreScaler[temp-4];
    }

    pclk2 = (systemclk/ahbp)/apb2p;

    return pclk2;
}

uint32_t RCC_GetPLLOutputClock(void){

    uint8_t pllm = 0;
    uint16_t plln = 0;
    uint8_t pllp = 0;
    uint32_t pll_clock = 0;

    pllm = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLM) & 0x3F);
    plln = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x01FF);
    pllp = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLP) & 0x03);

    if((uint8_t)(RCC->PLLCFGR >> RCC_PLLCFGR_PLLSRC) & 0x01){
        /* HSE oscillator clock selected as PLL clock input */
        pll_clock = ((uint32_t)(FREQ_8MHZ*plln)/pllm)/PLLP_PreScaler[pllp];
    }
    else{
        /* HSI clock selected as PLL clock input */
        pll_clock = ((uint32_t)(FREQ_16MHZ*plln)/pllm)/PLLP_PreScaler[pllp];
    }

    return pll_clock;
}

uint8_t RCC_SetSystemClock(RCC_Config_t RCC_Config){

    /* Check clk_source is a valid value */
    if(RCC_Config.clk_source > RCC_CLK_SOURCE_PLL_R){
        return 1;
    }

    /* Set prescaler values */
    /* Clear and set AHB prescaler */
    RCC->CFGR &= ~(0x0F << RCC_CFGR_HPRE);
    RCC->CFGR |= (RCC_Config.ahb_presc << RCC_CFGR_HPRE);
    /* Clear and set APB1 prescaler */
    RCC->CFGR &= ~(0x07 << RCC_CFGR_PPRE1);
    RCC->CFGR |= (RCC_Config.apb1_presc << RCC_CFGR_PPRE1);
    /* Clear and set APB2 prescaler */
    RCC->CFGR &= ~(0x07 << RCC_CFGR_PPRE2);
    RCC->CFGR |= (RCC_Config.apb2_presc << RCC_CFGR_PPRE2);

    /* Clear the RCC_CFGR_SW bits before setting */
    RCC->CFGR &= ~(0x03 << RCC_CFGR_SW);

    if(RCC_Config.clk_source == RCC_CLK_SOURCE_HSI){
        /* Enable HSI source */
        RCC->CR |= (1 << RCC_CR_HSION);
        /* Wait unitl source is ready */
        while(!(RCC->CR & (1 << RCC_CR_HSIRDY)));
        /* Disable HSE source */
        RCC->CR &= ~(1 << RCC_CR_HSEON);
    }
    else if(RCC_Config.clk_source == RCC_CLK_SOURCE_HSE){
        /* Set HSE mode */
        if(RCC_Config.hse_mode == RCC_HSE_BYPASS){
            RCC->CR |= (1 << RCC_CR_HSEBYP);
        }
        else{
            RCC->CR &= ~(1 << RCC_CR_HSEBYP);
        }
        /* Enable HSE source */
        RCC->CR |= (1 << RCC_CR_HSEON);
        /* Wait until source is ready */
        while(!(RCC->CR & (1 << RCC_CR_HSERDY)));
        /* Switch to HSE source clock */
        RCC->CFGR |= (0x01 << RCC_CFGR_SW);
        /* Disable HSI source */
        RCC->CR &= ~(1 << RCC_CR_HSION);
    }
    else{
        /* Configure PLL */
        RCC_PLLConfig(RCC_Config);
        /* Enable PLL source */
        RCC->CR |= (1 << RCC_CR_PLLON);
        /* Wait until source is ready */
        while(!(RCC->CR & (1 << RCC_CR_PLLRDY)));
        if(RCC_Config.clk_source == RCC_CLK_SOURCE_PLL_P){
            /* Switch to PLL source clock */
            RCC->CFGR |= (0x02 << RCC_CFGR_SW);
        }
        else if(RCC_Config.clk_source == RCC_CLK_SOURCE_PLL_R){
            /* Switch to PLL_R source clock */
            RCC->CFGR |= (0x03 << RCC_CFGR_SW);
        }
        else{
            return 1;
        }
    }

    return 0;
}

uint8_t RCC_SetMCO1Clk(RCC_Config_t RCC_Config){

    /* Check if division factor and input source are correct */
    if((RCC_Config.mco1_presc > MCO_P_5) || (RCC_Config.mco1_source > MCO1_PLL)){
        return 1;
    }

    /* Clear and set prescaler value */
    RCC->CFGR &= ~(0x07 << RCC_CFGR_MCO1PRE);
    RCC->CFGR |= (RCC_Config.mco1_presc << RCC_CFGR_MCO1PRE);
    /* Clear and set source value */
    RCC->CFGR &= ~(0x03 << RCC_CFGR_MCO1);
    RCC->CFGR |= (RCC_Config.mco1_source << RCC_CFGR_MCO1);
    /* Check and enable source value */
    if(RCC_Config.mco1_source == MCO1_HSI){
        /* Enable HSI source */
        RCC->CR |= (1 << RCC_CR_HSION);
    }
    else if(RCC_Config.mco1_source == MCO1_LSE){
        /* Disalbe backup protection */
        PWR_PCLK_EN();
        PWR->CR |= (1 << PWR_CR_DBP);
        /* Set LSE bypass */
        if(RCC_Config.lse_bypass == RCC_LSE_BYPASS){
            RCC->BDCR |= (1 << RCC_BDCR_LSEBYP);
        }
        else{
            RCC->BDCR &= ~(1 << RCC_BDCR_LSEBYP);
        }
        /* Enable LSE source */
        RCC->BDCR |= (1 << RCC_BDCR_LSEON);
    }
    else if(RCC_Config.mco1_source == MCO1_HSE){
        /* Set HSE mode */
        if(RCC_Config.hse_mode == RCC_HSE_BYPASS){
            RCC->CR |= (1 << RCC_CR_HSEBYP);
        }
        else{
            RCC->CR &= ~(1 << RCC_CR_HSEBYP);
        }
        /* Enable HSE source */
        RCC->CR |= (1 << RCC_CR_HSEON);
    }
    else{
        /* Configure PLL */
        RCC_PLLConfig(RCC_Config);
        /* Enable PLL */
        RCC->CR |= (1 << RCC_CR_PLLON);
    }

    return 0;
}

uint8_t RCC_SetMCO2Clk(RCC_Config_t RCC_Config){

    /* Check if division factor is correct */
    if(RCC_Config.mco2_presc > MCO_P_5){
        return 1;
    }

    /* Clear and set prescaler value */
    RCC->CFGR &= ~(0x07 << RCC_CFGR_MCO2PRE);
    RCC->CFGR |= (RCC_Config.mco2_presc << RCC_CFGR_MCO2PRE);
    /* Clear and set source value */
    RCC->CFGR &= ~(0x03 << RCC_CFGR_MCO2);
    RCC->CFGR |= (RCC_Config.mco2_source << RCC_CFGR_MCO2);
    /* Check and enable source value */
    if(RCC_Config.mco2_source == MCO2_SYSCLK){
        /* Do nothing */
    }
    else if(RCC_Config.mco2_source == MCO2_PLLI2S){
        /* Configure PLLI2S */
        RCC_PLLI2SConfig(RCC_Config);
        /* Enable PLLI2S */
        RCC->CR |= (1 << RCC_CR_PLLI2SON);
    }
    else if(RCC_Config.mco2_source == MCO2_HSE){
        /* Set HSE mode */
        if(RCC_Config.hse_mode == RCC_HSE_BYPASS){
            RCC->CR |= (1 << RCC_CR_HSEBYP);
        }
        else{
            RCC->CR &= ~(1 << RCC_CR_HSEBYP);
        }
        /* Enable HSE source */
        RCC->CR |= (1 << RCC_CR_HSEON);
    }
    else{
        /* Configure PLL */
        RCC_PLLConfig(RCC_Config);
        /* Enable PLL */
        RCC->CR |= (1 << RCC_CR_PLLON);
    }

    return 0;
}

/***********************************************************************************************************/
/*                                       Static Function Definitions                                       */
/***********************************************************************************************************/

static void RCC_PLLConfig(RCC_Config_t RCC_Config){

    /* Clear and set R prescaler division factor */
    RCC->PLLCFGR &= ~(0x07 << RCC_PLLCFGR_PLLR);
    RCC->PLLCFGR |= (RCC_Config.pll_r << RCC_PLLCFGR_PLLR);
    /* Clear and set Q prescaler division factor */
    RCC->PLLCFGR &= ~(0x0F << RCC_PLLCFGR_PLLQ);
    RCC->PLLCFGR |= (RCC_Config.pll_q << RCC_PLLCFGR_PLLQ);
    /* Clear and set P prescaler division factor */
    RCC->PLLCFGR &= ~(0x03 << RCC_PLLCFGR_PLLP);
    RCC->PLLCFGR |= (RCC_Config.pll_p << RCC_PLLCFGR_PLLP);
    /* Clear and set N prescaler multiplication value */
    RCC->PLLCFGR &= ~(0x01FF << RCC_PLLCFGR_PLLN);
    RCC->PLLCFGR |= (RCC_Config.pll_n << RCC_PLLCFGR_PLLN);
    /* Clear and set M prescaler division factor */
    RCC->PLLCFGR &= ~(0x3F << RCC_PLLCFGR_PLLM);
    RCC->PLLCFGR |= (RCC_Config.pll_m << RCC_PLLCFGR_PLLM);
    /* Clear and set input source for PLL */
    RCC->PLLCFGR &= ~(0x01 << RCC_PLLCFGR_PLLSRC);
    RCC->PLLCFGR |= (RCC_Config.pll_source << RCC_PLLCFGR_PLLSRC);

    /* Enable input source for PLL */
    if(RCC_Config.pll_source == PLL_SOURCE_HSI){
        /* Enable HSI source */
        RCC->CR |= (1 << RCC_CR_HSION);
    }
    else if(RCC_Config.pll_source == PLL_SOURCE_HSE){
        /* Set HSE mode */
        if(RCC_Config.hse_mode == RCC_HSE_BYPASS){
            RCC->CR |= (1 << RCC_CR_HSEBYP);
        }
        else{
            RCC->CR &= ~(1 << RCC_CR_HSEBYP);
        }
        /* Enable HSE source */
        RCC->CR |= (1 << RCC_CR_HSEON);
    }
    else{
        /* do nothing */
    }
}

static void RCC_PLLI2SConfig(RCC_Config_t RCC_Config){

    /* Clear and set R prescaler division factor */
    RCC->PLLI2SCFGR &= ~(0x07 << RCC_PLLI2SCFGR_PLLI2SR);
    RCC->PLLI2SCFGR |= (RCC_Config.plli2s_r << RCC_PLLI2SCFGR_PLLI2SR);
    /* Clear and set Q prescaler division factor */
    RCC->PLLI2SCFGR &= ~(0x0F << RCC_PLLI2SCFGR_PLLI2SQ);
    RCC->PLLI2SCFGR |= (RCC_Config.plli2s_q << RCC_PLLI2SCFGR_PLLI2SQ);
    /* Clear and set P prescaler division factor */
    RCC->PLLI2SCFGR &= ~(0x03 << RCC_PLLI2SCFGR_PLLI2SP);
    RCC->PLLI2SCFGR |= (RCC_Config.plli2s_p << RCC_PLLI2SCFGR_PLLI2SP);
    /* Clear and set N prescaler multiplication value */
    RCC->PLLI2SCFGR &= ~(0x01FF << RCC_PLLI2SCFGR_PLLI2SN);
    RCC->PLLI2SCFGR |= (RCC_Config.plli2s_n << RCC_PLLI2SCFGR_PLLI2SN);
    /* Clear and set M prescaler division factor */
    RCC->PLLI2SCFGR &= ~(0x3F << RCC_PLLI2SCFGR_PLLI2SM);
    RCC->PLLI2SCFGR |= (RCC_Config.plli2s_m << RCC_PLLI2SCFGR_PLLI2SM);
    /* Clear and set input source for PLLI2S */
    RCC->PLLCFGR &= ~(0x01 << RCC_PLLCFGR_PLLSRC);
    RCC->PLLCFGR |= (RCC_Config.pll_source << RCC_PLLCFGR_PLLSRC);

    /* Enable input source for PLLI2S */
    if(RCC_Config.pll_source == PLL_SOURCE_HSI){
        /* Enable HSI source */
        RCC->CR |= (1 << RCC_CR_HSION);
    }
    else if(RCC_Config.pll_source == PLL_SOURCE_HSE){
        /* Set HSE mode */
        if(RCC_Config.hse_mode == RCC_HSE_BYPASS){
            RCC->CR |= (1 << RCC_CR_HSEBYP);
        }
        else{
            RCC->CR &= ~(1 << RCC_CR_HSEBYP);
        }
        /* Enable HSE source */
        RCC->CR |= (1 << RCC_CR_HSEON);
    }
    else{
        /* do nothing */
    }
}
