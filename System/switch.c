#include "stm32f10x.h" // Device header
#include "defs.h"
#include "key.h"

const uint16_t KeyMapping[][SWITCH_LEN] =
    {
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
    };

/**
 * @brief  获取按键对应的映射
 * @param KeyNum 按键值
 * @retval 无
 */
const uint16_t *Switch_GetKeyMapping(uint8_t KeyNum)
{
    return KeyMapping[KeyNum - 1];
}

/**
 * @brief  获取该组灯的状态
 * @param KeyNum 按键值
 * @param Switches 各个灯状态
 * @retval 该组灯状态 1开启 0关闭
 */
uint16_t Switch_GetGroupStatus(uint8_t KeyNum, uint16_t Switches[])
{
    const uint16_t *mask = Switch_GetKeyMapping(KeyNum);
    for (int i = 0; i < SWITCH_LEN; i++)
    {
        // 跳过不受控制的灯
        if (mask[i] == 0)
        {
            continue;
        }
        // 若有任意一灯开启则视为该组灯为开启状态
        if (Switches[i] != 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief  返回仲裁结果
 * @param KeyNum 按键值
 * @param Switches 各个灯状态
 * @retval KeyNum对应的该组灯应当关闭或开启 1开启 0关闭
 */
uint16_t Switch_Arbitration(uint8_t KeyNum, uint16_t Switches[])
{
    uint16_t status = Switch_GetGroupStatus(KeyNum, Switches);
    return !status;
}
