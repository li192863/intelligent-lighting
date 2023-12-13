#include "stm32f10x.h"                  // Device header
#include "my_flash.h"
#include "defs.h"

uint16_t Store_Data[STORE_LEN];

/**
 * @brief  加载初始化配置
 * @retval 无
 */
void Store_LoadDefaultConfig(void)
{
    // 选项
    uint16_t flags[FLAG_LEN] =
    {
        FLAG_EFFECTIVE
    };
    for (int i = 0; i < FLAG_LEN; i++)
    {
        Store_Data[FLAG_START + i] = flags[i];
    }

    // 开关
    uint16_t switches[SWITCH_LEN] =
    {
        SWITCH_1,
        SWITCH_2,
        SWITCH_3,
        SWITCH_4,
        SWITCH_5,
        SWITCH_6,
        SWITCH_7,
        SWITCH_8,
        SWITCH_9,
        SWITCH_10,
        SWITCH_11,
        SWITCH_12,
        SWITCH_13,
        SWITCH_14,
        SWITCH_15,
        SWITCH_16
    };
    for (int i = 0; i < SWITCH_LEN; i++) {
        Store_Data[SWITCH_START + i] = switches[i];
    }

    // 亮度
    uint16_t duties[DUTY_LEN] =
    {
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
    for (int i = 0; i < STORE_LEN; i++)
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
    for (int i = 0; i < STORE_LEN; i++)
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
    for (int i = 0; i < STORE_LEN; i++)
    {
        Store_Data[i] = 0;
    }
    Store_Write();
}

/**
 * @brief  写入占空比信息
 * @param duties 占空比数组
 * @param len 占空比数组长度
 * @retval 无
 */
void Store_WriteDuties(uint16_t duties[], int len)
{
    for (int i = 0; i < len && i < DUTY_LEN; i++) {
        Store_Data[DUTY_START + i] = duties[i];
    }
    Store_Write();
}

/**
 * @brief  写入占空比信息
 * @param mask 掩码数组，值为非0的表示被选择，值为0的不被选择
 * @param len 掩码数组的长度（将依次按序设置）
 * @param value 掩码处设置的值
 * @retval 无
 */
void Store_WriteMaskedDuties(uint16_t mask[], int len, uint16_t value)
{
    for (int i = 0; i < len && i < DUTY_LEN; i++) {
        if (mask[i]) {
            Store_Data[DUTY_LEN + i] = value;
        }
    }
    Store_Write();
}

/**
 * @brief  读取占空比信息
 * @retval 指向占空比数组的指针
 */
uint16_t* Store_ReadDuties(void)
{
    return Store_Data + DUTY_START;
}

/**
 * @brief  写入占空比信息，注意：仅SET_DUTY才可调用此函数
 * @param i 第i个灯 1 ~ 16
 * @param duty 占空比
 * @retval 无
 */
void Store_WriteDuty(uint8_t i, uint16_t duty)
{
    if (i >= 1 && i <= DUTY_LEN)
    {
        Store_Data[DUTY_START + i - 1] = duty;
        Store_Write();
    }
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

/**
 * @brief  写入开关信息
 * @param switches 开关数组
 * @param len 开关数组长度
 * @retval 无
 */
void Store_WriteSwitches(uint16_t switches[], int len)
{
    for (int i = 0; i < len && i < SWITCH_LEN; i++) {
        Store_Data[SWITCH_START + i] = switches[i];
    }
    Store_Write();
}

/**
 * @brief  写入开关信息
 * @param mask 掩码数组，值为非0的表示被选择，值为0的不被选择
 * @param len 掩码数组的长度（将依次按序设置）
 * @param value 掩码处设置的值
 * @retval 无
 */
void Store_WriteMaskedSwitches(uint16_t mask[], int len, uint16_t value)
{
    for (int i = 0; i < len && i < SWITCH_LEN; i++) {
        if (mask[i]) {
            Store_Data[SWITCH_START + i] = value;
        }
    }
    Store_Write();
}

/**
 * @brief  读取开关信息
 * @retval 指向开关数组的指针
 */
uint16_t* Store_ReadSwitches(void)
{
    return Store_Data + SWITCH_START;
}

/**
 * @brief  写入开关信息
 * @param i 第i个灯 1 ~ 16
 * @param switch_ 开关信息
 * @retval 无
 */
void Store_WriteSwitch(uint8_t i, uint16_t switch_)
{
    if (i >= 1 && i <= SWITCH_LEN)
    {
        Store_Data[SWITCH_START + i - 1] = switch_;
        Store_Write();
    }
}

/**
 * @brief  读取开关信息
 * @param  i 第i个灯 1 ~ 16
 * @retval 开关信息
 */
uint16_t Store_ReadSwitch(uint8_t i)
{
    return Store_Data[SWITCH_START + i - 1];
}
