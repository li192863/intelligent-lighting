#include "stm32f10x.h"                  // Device header

/**
 * @brief 读取指定地址内容
 * @param Address 地址
 * @retval 地址处内容
*/
uint32_t MyFlash_ReadWord(uint32_t Address) {
    return *((__IO uint32_t *) (Address));
}

/**
 * @brief 读取指定地址内容
 * @param Address 地址
 * @retval 地址处内容
*/
uint16_t MyFlash_ReadHalfWord(uint32_t Address)
{
    return *((__IO uint16_t *) (Address));
}

/**
 * @brief 读取指定地址内容
 * @param Address 地址
 * @retval 地址处内容
*/
uint8_t MyFlash_ReadByte(uint32_t Address)
{
    return *((__IO uint8_t *) (Address));
}

/**
 * @brief 擦除全部页的内容
 * @retval 无
*/
void MyFlash_EraseAllPages(void)
{
    FLASH_Unlock();
    FLASH_EraseAllPages();
    FLASH_Lock();
}

/**
 * @brief 擦除指定页的内容
 * @param PageAddress 地址
 * @retval 无
*/
void MyFlash_ErasePage(uint32_t PageAddress)
{
    FLASH_Unlock();
    FLASH_ErasePage(PageAddress);
    FLASH_Lock();
}

/**
 * @brief 向指定地址写入内容
 * @param Address 地址
 * @param Data 数据
 * @retval 无
*/
void MyFlash_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Unlock();
    FLASH_ProgramWord(Address, Data);
    FLASH_Lock();
}

/**
 * @brief 向指定地址写入内容
 * @param Address 地址
 * @param Data 数据
 * @retval 无
*/
void MyFlash_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
    FLASH_Unlock();
    FLASH_ProgramHalfWord(Address, Data);
    FLASH_Lock();
}
