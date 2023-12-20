#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "my_flash.h"
#include "defs.h"

uint16_t Store_Data[STORE_MAX_LEN];

/**
 * @brief  加载初始化配置
 * @retval 无
 */
void Store_LoadDefaultConfig(void)
{
    // 选项
    uint16_t flags[FLAG_LEN] =
    {
        // 标志位
        FLAG_EFFECTIVE // 存储标志位
    };
    for (int i = 0; i < FLAG_LEN; i++)
    {
        Store_Data[FLAG_START + i] = flags[i];
    }

    // 亮度
    uint16_t duties[DUTY_LEN] =
    {
        // 亮度信息
        DUTY_1,
        DUTY_2,
        DUTY_3,
        DUTY_4,
        DUTY_5,
        DUTY_6,
        DUTY_7,
        DUTY_8,
        DUTY_9,
        DUTY_10,
        DUTY_11,
        DUTY_12,
        DUTY_13,
        DUTY_14,
        DUTY_15,
        DUTY_16
    };
    for (int i = 0; i < DUTY_LEN; i++) {
        Store_Data[DUTY_START + i] = duties[i];
    }
}

/**
 * @brief  存储配置信息，Store_Data -> Flash
 * @retval 无
 */
void Store_Write(void)
{
    MyFlash_ErasePage(STORE_START_ADDRESS);
    // 写入数据
    for (int i = 0; i < STORE_MAX_LEN; i++)
    {
        MyFlash_ProgramHalfWord(STORE_START_ADDRESS + i * STORE_UNIT, Store_Data[i]);
    }
}

/**
 * @brief  读取配置信息，Flash -> Store_Data
 * @retval 无
 */
void Store_Read(void)
{
    // 读取数据
    for (int i = 0; i < STORE_MAX_LEN; i++)
    {
        Store_Data[i] = MyFlash_ReadHalfWord(STORE_START_ADDRESS + i * STORE_UNIT);
    }
}

/**
 * @brief  存储初始化
 * @retval 无
 */
void Store_Init(void)
{
    if (MyFlash_ReadHalfWord(STORE_START_ADDRESS + FLAG_START) != FLAG_EFFECTIVE)
    {
        // 加载默认配置 defs -> Store_Data
        Store_LoadDefaultConfig();
        // 存储配置信息 Store_Data -> Flash
        Store_Write();
    }
    else
    {
        // 读取配置信息 Flash -> Store_Data
        Store_Read();
    }
}

/**
 * @brief  清除存储数据，包括存储标志位
 * @retval 无
 */
void Store_Clear(void)
{
    for (int i = 0; i < STORE_MAX_LEN; i++)
    {
        Store_Data[i] = 0;
    }
    Store_Write();
}

/**
 * @brief  打印信息
 * @retval 开关信息
 */
void Store_PrintStoreData(void)
{
    // 打印存储数据信息
    for (int i = 0; i < STORE_LEN; i++) {
        printf("%x ", Store_Data[i]);
    }
    printf("\r\n");

    // 调试模式下风格化
    if (DEBUG)
    {
        int len1 = FLAG_LEN, len2 = FLAG_LEN + DUTY_LEN;

        printf("[DEBUG]: FLAGS   ");
        int i = 0;
        while (i < len1) printf("%04x ", Store_Data[i++]);
        printf("\r\n");
        
        printf("[DEBUG]: DUTIES  ");
        while (i < len2) printf("%04x ", Store_Data[i++]);
        printf("\r\n");

        printf("[DEBUG]: CURRENT ");
        int j = len1;
        while (j < len2)
        {
            uint8_t luminance = (((int) Store_Data[j]) - MIN_DUTY) * 100 / (MAX_DUTY - MIN_DUTY);
            printf("%4d ", luminance);
            j++;
        }
        printf("\r\n");
    }
}

/**
 * @brief  写入占空比信息
 * @param  Duties 占空比数组
 * @param  Len 占空比数组长度
 * @retval 无
 */
void Store_WriteDuties(uint16_t Duties[], int Len)
{
    for (int i = 0; i < Len && i < DUTY_LEN; i++) {
        Store_Data[DUTY_START + i] = Duties[i];
    }
    Store_Write();
}

/**
 * @brief  写入占空比信息
 * @param  Mask 掩码数组，值为非0的表示被选择，值为0的不被选择
 * @param  Len 掩码数组的长度（将依次按序设置）
 * @param  Duty 掩码处设置的值
 * @retval 无
 */
void Store_WriteMaskedDuties(uint16_t Mask[], int Len, uint16_t Duty)
{
    for (int i = 0; i < Len && i < DUTY_LEN; i++) {
        if (Mask[i]) {
            Store_Data[DUTY_START + i] = Duty;
        }
    }
    Store_Write();
}

/**
 * @brief  写入占空比信息，注意：仅SET_DUTY才可调用此函数
 * @param  i 第i个灯 1 ~ 16
 * @param  Duty 占空比
 * @retval 无
 */
void Store_WriteDuty(uint8_t i, uint16_t Duty)
{
    if (i >= 1 && i <= DUTY_LEN)
    {
        Store_Data[DUTY_START + i - 1] = Duty;
        Store_Write();
    }
}

/**
 * @brief  读取占空比信息
 * @param  Len 指向长度的指针，若为NULL则不做处理
 * @retval 指向占空比数组的指针
 */
uint16_t* Store_ReadDuties(int *Len)
{
    if (Len != NULL)
    {
        *Len = DUTY_LEN;
    }
    return Store_Data + DUTY_START;
}

/**
 * @brief  读取占空比信息
 * @param  i 第i个灯 1 ~ 16
 * @retval 占空比
 */
uint16_t Store_ReadDuty(uint8_t i)
{
    return Store_Data[DUTY_START + i - 1];
}
