/********************************************************************************************************//**
* @file flash_driver.c
*
* @brief File containing the APIs for configuring the FLASH peripheral.
*
* Public Functions:
*       - uint8_t Flash_EraseSector(uint8_t sector)
*       - uint8_t Flash_WriteMemoryByte(uint32_t address, uint8_t data)
*       - uint8_t Flash_WriteMemoryHalfWord(uint32_t address, uint16_t data)
*       - uint8_t Flash_WriteMemoryWord(uint32_t address, uint32_t data)
*       - uint8_t Flash_WriteMemoryDoubleWord(uint32_t address, uint64_t data)
*       - uint8_t Flash_EnRWProtection(uint8_t sectors, uint8_t protection_mode)
*       - uint8_t Flash_DisRWProtection(void)
*       - void    Flash_Unlock(void)
*       - void    Flash_Lock(void)
*       - void    Flash_OPTUnlock(void)
*       - void    Flash_OPTLock(void)
*       - void    Flash_SetPSIZE(flash_psize_t psize)
*       - uint8_t Flash_Busy(void)
*       - void    Flash_GetOBCfg(OPT_Cfg_t* OPTCfg)
*       - uint8_t Flash_SetLatency(uint8_t latency)
*
* @note
*       For further information about functions refer to the corresponding header file.
**/

#include <stdint.h>
#include "flash_driver.h"

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

uint8_t Flash_EraseSector(uint8_t sector){

    /* Check no flash memory operation is ongoing */
    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    /* Unlock Flash to perform erase operation */
    Flash_Unlock();

    if(sector != 0xFF){
        /* Set Sector Erase bit in Flash Control Register */
        FLASHINTR->CR |= (1 << FLASH_CR_SER);
        /* Select the sector to be erased in the SNB bit in Flash Control Register */
        FLASHINTR->CR &= ~(0x0F << FLASH_CR_SNB); /* Clear the SNB bits */
        FLASHINTR->CR |= ((0x07 & sector) << FLASH_CR_SNB);
    }
    else{
        /* Set Mass Erase bit in Flash Control Register */
        FLASHINTR->CR |= (1 << FLASH_CR_MER);
    }
    /* Set the STRT bit in Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_STRT);

    /* Wait for flash memory operation is finished */
    while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

    /* Lock Flash Control Register */
    Flash_Lock();

    return 0;
}

uint8_t Flash_WriteMemoryByte(uint32_t address, uint8_t data){

    /* check no flash memory operation is ongoing */
    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    /* Set PSIZE bits in the Flash Control Register */
    Flash_SetPSIZE(FLASH_PSIZE_BYTE);

    /* Set Programming bit in the Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_PG);

    /* Write data in flash memory */
    *(uint8_t*)address = data;

    /* Wait for flash memory operation is finished */
    while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

    /*Check for any error */
    if(FLASHINTR->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) | 
      (1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
        return 1;
    }

    return 0;
}

uint8_t Flash_WriteMemoryHalfWord(uint32_t address, uint16_t data){

    /* check no flash memory operation is ongoing */
    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    /* Set PSIZE bits in the Flash Control Register */
    Flash_SetPSIZE(FLASH_PSIZE_HALFWORD);

    /* Set Programming bit in the Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_PG);

    /* Write data in flash memory */
    *(uint16_t*)address = data;

    /* Wait for flash memory operation is finished */
    while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

    /*Check for any error */
    if(FLASHINTR->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) | 
      (1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
        return 1;
    }

    return 0;
}

uint8_t Flash_WriteMemoryWord(uint32_t address, uint32_t data){

    /* check no flash memory operation is ongoing */
    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    /* Set PSIZE bits in the Flash Control Register */
    Flash_SetPSIZE(FLASH_PSIZE_WORD);

    /* Set Programming bit in the Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_PG);

    /* Write data in flash memory */
    *(uint32_t*)address = data;

    /* Wait for flash memory operation is finished */
    while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

    /*Check for any error */
    if(FLASHINTR->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) | 
      (1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
        return 1;
    }

    return 0;
}

uint8_t Flash_WriteMemoryDoubleWord(uint32_t address, uint64_t data){

    /* check no flash memory operation is ongoing */
    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    /* Set PSIZE bits in the Flash Control Register */
    Flash_SetPSIZE(FLASH_PSIZE_DOUBLEWORD);

    /* Set Programming bit in the Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_PG);

    /* Write data in flash memory */
    *(uint32_t*)address = (uint32_t)data;
    *(uint32_t*)(address + 4) = (uint32_t)(data >> 32);

    /* Wait for flash memory operation is finished */
    while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

    /*Check for any error */
    if(FLASHINTR->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) | 
      (1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
        return 1;
    }

    return 0;
}

uint8_t Flash_EnRWProtection(uint8_t sectors, uint8_t protection_mode){

    if(protection_mode == 1){
        /* Check no flash memory operation is ongoing */
        if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
            return 1;
        }

        /* Unlock Flash to perform erase operation */
        Flash_OPTUnlock();

        /* Set write protection on sectors */
        /* Reset SPRMOD bit in OPTCR register */
        FLASHINTR->OPTCR &= ~(1 << FLASH_OPTCR_SPRMOD);
        /* Set nWRP byte in OPTCR register (0 is protection active) */
        FLASHINTR->OPTCR &= ~(sectors << FLASH_OPTCR_NWRP);

        /* Set the STRT bit in Flash Control Register */
        FLASHINTR->CR |= (1 << FLASH_CR_STRT);

        /* Wait for flash memory operation is finished */
        while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

        /* Lock Flash Control Register */
        Flash_OPTLock();
    }
    else if(protection_mode == 2){
        /* Check no flash memory operation is ongoing */
        if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
            return 1;
        }

        /* Unlock Flash to perform erase operation */
        Flash_OPTUnlock();

        /* Set read/write protection on sectors */
        /* Set SPRMOD bit in OPTCR register */
        FLASHINTR->OPTCR |= (1 << FLASH_OPTCR_SPRMOD);
        /* Clear nWRP byte in OPTCR register */
        FLASHINTR->OPTCR &= ~(0xFF << FLASH_OPTCR_NWRP);
        /* Set nWRP byte in OPTCR register (1 is protection active) */
        FLASHINTR->OPTCR |= (sectors << FLASH_OPTCR_NWRP);

        /* Set the STRT bit in Flash Control Register */
        FLASHINTR->CR |= (1 << FLASH_CR_STRT);

        /* Wait for flash memory operation is finished */
        while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

        /* Lock Flash Control Register */
        Flash_OPTLock();
    }
    else{
        return 1;
    }

    return 0;
}

uint8_t Flash_DisRWProtection(void){

    /* Check no flash memory operation is ongoing */
    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    /* Unlock Flash to perform erase operation */
    Flash_OPTUnlock();

    /* Set read/write protection on sectors */
    /* Reset SPRMOD bit in OPTCR register */
    FLASHINTR->OPTCR &= ~(1 << FLASH_OPTCR_SPRMOD);
    /* Set nWRP byte in OPTCR register (1 is disabled) */
    FLASHINTR->OPTCR |= (0xFF << FLASH_OPTCR_NWRP);

    /* Set the STRT bit in Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_STRT);

    /* Wait for flash memory operation is finished */
    while(FLASHINTR->SR & (1 << FLASH_SR_BSY));

    /* Lock Flash Control Register */
    Flash_OPTLock();

    return 0;
}

void Flash_Unlock(void){

    /* Write KEY1 and KEY2 in Flash Key Register */
    FLASHINTR->KEYR = 0x45670123;
    FLASHINTR->KEYR = 0xCDEF89AB;
}

void Flash_Lock(void){

    /* Set Lock bit in Flash Control Register */
    FLASHINTR->CR |= (1 << FLASH_CR_LOCK);
}

void Flash_OPTUnlock(void){

    /* Write KEY1 and KEY2 in Flash Option Key Register */
    FLASHINTR->OPTKEYR = 0x08192A3B;
    FLASHINTR->OPTKEYR = 0x4C5D6E7F;
}

void Flash_OPTLock(void){

    /* Set Lock bit in Flash Option Control Register */
    FLASHINTR->OPTCR |= (1 << FLASH_OPTCR_OPTLOCK);
}

void Flash_SetPSIZE(flash_psize_t psize){

    /* Set PSIZE bits in the Flash Control Register */
    FLASHINTR->CR &= (0x07 << FLASH_CR_PSIZE);
    FLASHINTR->CR |= (psize << FLASH_CR_PSIZE);
}

uint8_t Flash_Busy(void){

    if(FLASHINTR->SR & (1 << FLASH_SR_BSY)){
        return 1;
    }

    return 0;
}

void Flash_GetOBCfg(OPT_Cfg_t* OPTCfg){

    /* Unlock Option Byte Flash area */
    Flash_OPTUnlock();

    /* Get Option Byte configuration */
    /* Get Not Write Protect byte */
    OPTCfg->nWRP = (uint16_t)((FLASHINTR->OPTCR & (0xFFFF << FLASH_OPTCR_NWRP)) >> 16);
    /*Get Read Protect byte */
    OPTCfg->RDP = (uint8_t)((FLASHINTR->OPTCR & (0xFF << FLASH_OPTCR_RDP)) >> 8);
    /* Get User Option bits */
    OPTCfg->user = (uint8_t)(FLASHINTR->OPTCR & 0xE0);
    /* Get BOR bits */
    OPTCfg->BOR = (uint8_t)(FLASHINTR->OPTCR & 0x0C);

    /* Lock Option Byte Flash area */
    Flash_OPTLock();
}

uint8_t Flash_SetLatency(uint8_t latency){

    /* Check value is allowed */
    if(latency > 0x0F){
        return 1;
    }

    /* Clear and set latency */
    FLASHINTR->ACR &= ~(0x0F << FLASH_ACR_LATENCY);
    FLASHINTR->ACR |= (latency << FLASH_ACR_LATENCY);

    return 0;
}
