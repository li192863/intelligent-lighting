#include <math.h>
#include "stm32f10x.h" // Device header
#include "defs.h"
#include "key.h"

const uint16_t KeyMapping[][DUTY_LEN] =
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
const uint16_t *Switch_GetKeyMask(uint8_t KeyNum)
{
    return KeyMapping[KeyNum - 1];
}

/**
 * @brief  根据当前占空比确定下一挡的占空比
 * @param  CurrentDuties 占空比数组
 * @param  Mask 掩码数组
 * @param  Len 数组长度
 * @retval 下一挡位的占空比
 */
uint16_t Switch_GetNextDuty(uint16_t CurrentDuties[], uint16_t Mask[], int Len)
{
    int dutySum = 0, count = 0;
    for (int i = 0; i < Len && i < DUTY_LEN; i++)
    {
        if (Mask[i]) {
            dutySum += CurrentDuties[i];
            count++;
        }
    }
    int nextGear = ((int) round(1.0 * (GEAR_COUNT - 1) * dutySum / count / MAX_DUTY) + 1) % GEAR_COUNT;
    int nextDuty = ((int) round(1.0 * MAX_DUTY * nextGear / (GEAR_COUNT - 1))) % (MAX_DUTY + 1);
    return nextDuty;
}
