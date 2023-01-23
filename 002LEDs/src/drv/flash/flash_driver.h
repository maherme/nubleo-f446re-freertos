/********************************************************************************************************//**
* @file flash_driver.h
*
* @brief Header file containing the prototypes of the APIs for configuring the FLASH peripheral.
*
* Public Functions:
*       - uint8_t Flash_Erase(uint8_t sector, uint8_t num_sectors)
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
*/

#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stdint.h>
#include "stm32f446xx.h"

/** @brief Maximum number of sectors of the Flash memory */
#define MAX_NUM_SECTOR  8

/**
 * @brief List of allowed PSIZE values for FLASH CR register.
 */
typedef enum{
    FLASH_PSIZE_BYTE        = 0x00, /**< Supply voltage from 1.7V to 3.6V */
    FLASH_PSIZE_HALFWORD    = 0x01, /**< Supply voltage from 2.1V to 3.6V */
    FLASH_PSIZE_WORD        = 0x02, /**< Supply voltage from 2.7V to 3.6V */
    FLASH_PSIZE_DOUBLEWORD  = 0x03  /**< Supply voltage from 2.7V to 3.6V with external Vpp 8V to 9V */
}flash_psize_t;

/**
 * @brief Configuration Option structure.
 */
typedef struct{
    uint16_t nWRP;   /**< Not Write Protect */
    uint8_t  RDP;    /**< Read Protect */
    uint8_t  user;   /**< User configuration */
    uint8_t  BOR;    /**< BOR reset level */
}OPT_Cfg_t;

/***********************************************************************************************************/
/*                                       APIs Supported                                                    */
/***********************************************************************************************************/

/**
 * @brief Function to erase a sector of the FLASH.
 * @param[in] sector is the selected sector of the flash to be erased, 0xFF means mass erase.
 * @return 0 if success.
 * @return 1 if fail.
 */
uint8_t Flash_EraseSector(uint8_t sector);

/**
 * @brief Function to program a byte in a flash memory address.
 * @param[in] address is the memory address to be programmed.
 * @param[in] data is the data to be stored in address.
 * @return 0 if success.
 * @return 1 if fail.
 * @note This function must be used when the device voltage range is from 1.7V to 3.6V.
 */
uint8_t Flash_WriteMemoryByte(uint32_t address, uint8_t data);

/**
 * @brief Function to program a half word in a flash memory address.
 * @param[in] address is the memory address to be programmed.
 * @param[in] data is the data to be stored in address.
 * @return 0 if success.
 * @return 1 if fail.
 * @note This function must be used when the device voltage range is from 2.1V to 3.6V.
 */
uint8_t Flash_WriteMemoryHalfWord(uint32_t address, uint16_t data);

/**
 * @brief Function to program a word in a flash memory address.
 * @param[in] address is the memory address to be programmed.
 * @param[in] data is the data to be stored in address.
 * @return 0 if success.
 * @return 1 if fail.
 * @note This function must be used when the device voltage range is from 2.7V to 3.6V.
 */
uint8_t Flash_WriteMemoryWord(uint32_t address, uint32_t data);

/**
 * @brief Function to program a double word in a flash memory address.
 * @param[in] address is the memory address to be programmed.
 * @param[in] data is the data to be stored in address.
 * @return 0 if success.
 * @return 1 if fail.
 * @note This function must be used when the device voltage range is from 2.7V to 3.6V
 *       with external Vpp in the range 8V to 9V.
 */
uint8_t Flash_WriteMemoryDoubleWord(uint32_t address, uint64_t data);

/**
 * @brief Function to enable the read/write protection of flash sectors.
 * @param[in] sectors is the value of the nWRP byte to set in the OPTCR register.
 * @param[in] protection_mode is 1 for write or 2 for read/write.
 * @return 0 if success.
 * @return 1 if fail.
 */
uint8_t Flash_EnRWProtection(uint8_t sectors, uint8_t protection_mode);

/**
 * @brief Function to disable the read/write protection of flash sectors.
 * @return 0 if success.
 * @return 1 if fail.
 */
uint8_t Flash_DisRWProtection(void);

/**
 * @brief Function to unlock the flash programming/erase protection.
 * @return void.
 */
void Flash_Unlock(void);

/**
 * @brief Function to lock up the flash programming/erase protection.
 * @return void.
 */
void Flash_Lock(void);

/**
 * @brief Function to unlock the flash programming/erase option byte protection.
 * @return void.
 */
void Flash_OPTUnlock(void);

/**
 * @brief Function to lock up the flash programming/erase option byte protection.
 * @return void.
 */
void Flash_OPTLock(void);

/**
 * @brief Function to set the PSIZE according to the supply voltage.
 * @param[in] psize is the value to store in the PSIZE bit in FLASH CR.
 * @return void.
 * @note Be aware that the PSIZE need to be set according to the supply voltage range.
 */
void Flash_SetPSIZE(flash_psize_t psize);

/**
 * @brief Function to check if a flash operation is ongoing.
 * @return 0 if Flash is not busy.
 * @return 1 if Flash is busy.
 */
uint8_t Flash_Busy(void);

/**
 * @brief Function for getting the Option Byte configuration.
 * @param[out] OPTCfg is a pointer to the struct for storing the OB configuration.
 * @return void.
 */
void Flash_GetOBCfg(OPT_Cfg_t* OPTCfg);

/**
 * @brief Function for setting the latency of the flash.
 * @param[in] latency is the latency value to be set.
 * @return 0 is OK.
 * @return 1 is fail.
 */
uint8_t Flash_SetLatency(uint8_t latency);

#endif
