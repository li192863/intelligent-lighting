#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "defs.h"
#include "pwm.h"
#include "store.h"
#include "switch.h"

/**
 * @brief  获取状态
 * @retval 无
 */
void Execute_Status(void)
{
    Store_PrintStoreData();
}

/**
 * @brief  设置存储占空比，占空比值不会被存储
 * @param i 第i个灯 1 ~ 16
 * @param Duty 占空比 0 ~ 127
 * @retval 无
 */
void Execute_SetCurrentDuty(uint8_t i, uint16_t Duty)
{
    // 保护硬件
    Duty = Duty < MIN_DUTY ? MIN_DUTY : Duty;
    Duty = Duty > MAX_DUTY ? MAX_DUTY : Duty;
    PWM_SetDuty(i, Duty);
}

/**
 * @brief  获取当前占空比，此占空比为真实占空比，非存储的占空比
 * @param i 第i个灯 1 ~ 16
 * @retval 无
 */
uint16_t Execute_GetCurrentDuty(uint8_t i)
{
    uint16_t switch_ = Store_ReadSwitch(i);
    uint16_t duty = switch_ ? Store_ReadDuty(i) : MIN_DUTY;
    return duty;
}

/**
 * @brief  设置当前占空比，占空比值将被存储
 * @param i 第i个灯 1 ~ 16
 * @param Duty 占空比 0 ~ 127
 * @retval 无
 */
void Execute_SetStoredDuty(uint8_t i, uint16_t Duty)
{
    // 保护硬件
    Duty = Duty < MIN_DUTY ? MIN_DUTY : Duty;
    Duty = Duty > MAX_DUTY ? MAX_DUTY : Duty;
    PWM_SetDuty(i, Duty);
    Store_WriteDuty(i, Duty);
}

/**
 * @brief  获取存储占空比，此占空比为存储的占空比，非真实占空比
 * @param i 第i个灯 1 ~ 16
 * @retval 无
 */
uint16_t Execute_GetStoredDuty(uint8_t i)
{
    return Store_ReadDuty(i);
}

/**
 * @brief  设置第i个灯的开关状态
 * @param i 第i个灯 1 ~ 16
 * @param switch_ 开关信息
 * @retval 无
 */
void Execute_SetSwitch(uint8_t i, uint8_t switch_)
{
    Store_WriteSwitch(i, switch_);
    uint16_t duty = switch_ ? Store_ReadDuty(i) : MIN_DUTY;
    PWM_SetDuty(i, duty);
}

/**
 * @brief  获取第i个灯的开关状态
 * @param i 第i个灯 1 ~ 16
 * @retval 开关信息 1开启0关闭
 */
uint8_t Execute_GetSwitch(uint8_t i)
{
    return Store_ReadSwitch(i);
}

/**
 * @brief  打开第i个灯，开关状态将被存储，占空比值以上次设置值为准
 * @param i 第i个灯 1 ~ 16
 * @retval 无
 */
void Execute_On(uint8_t i)
{
    // 设置占空比，占空比值以上次设置值为准
    Store_WriteSwitch(i, 1);
    PWM_SetDuty(i, Store_ReadDuty(i));
}

/**
 * @brief  关闭第i个灯，开关状态将被存储，占空比值为最小占空比
 * @param i 第i个灯 1 ~ 16
 * @retval 无
 */
void Execute_Off(uint8_t i)
{
    // 设置占空比，占空比值为最小占空比
    Store_WriteSwitch(i, 0);
    PWM_SetDuty(i, MIN_DUTY);
}

/**
 * @brief  打开/关闭第i个灯，开关状态将被存储，打开后占空比值以上次设置值为准，关闭后占空比值为最小占空比
 * @param i 第i个灯 1 ~ 16
 * @retval 无
 */
void Execute_Turn(uint8_t i)
{
    uint16_t switch_ = Store_ReadSwitch(i);
    if (switch_ != 0)
    {
        Execute_Off(i);
    }
    else
    {
        Execute_On(i);
    }
}

/**
 * @brief  打开一批灯，开关状态将被存储，占空比值以上次设置值为准
 * @param  Mask 掩码数组，值为1的表示被选择，值为0的不被选择
 * @param  Len 掩码数组的长度（将依次按序设置）
 * @retval 无
 */
void Execute_OnBatch(uint16_t Mask[], int Len)
{
    // 存储开关值
    Store_WriteMaskedSwitches(Mask, Len, 1);
    // 读取duties值
    uint16_t *duties = Store_ReadDuties();
    // 设置占空比，占空比值以上次设置值为准
    for (int i = 0; i < Len; i++) {
        if (Mask[i]) {
            // 不必对duties检查，不必存储duties值
            PWM_SetDuty(i + 1, duties[i]); // 若使用Execute_SetDuty则将进行频繁写入
        }
    }
}

/**
 * @brief  关闭一批灯，开关状态将被存储，占空比值为最小占空比
 * @param  Mask 掩码数组，值为1的表示被选择，值为0的不被选择
 * @param  Len 开关数组的长度（将依次按序设置）
 * @retval 无
 */
void Execute_OffBatch(uint16_t Mask[], int Len) {
    // 存储开关值
    Store_WriteMaskedSwitches(Mask, Len, 0);
    // 设置占空比，占空比值为最小占空比
    for (int i = 0; i < Len; i++) {
        if (Mask[i]) {
            // 不必对duties检查，不必存储duties值
            PWM_SetDuty(i + 1, MIN_DUTY); // 不可使用Execute_SetDuty！
        }
    }
}

/**
 * @brief  全部开启
 * @retval 无
 */
void Execute_AllOn(void)
{
    // 设置开关值
    uint16_t mask[SWITCH_LEN];
    for (int i = 0; i < SWITCH_LEN; i++)
    {
        // 备用开关打开无影响
        mask[i] = 1;
    }
    // 全部开启
    Execute_OnBatch(mask, SWITCH_LEN);
}

/**
 * @brief  全部关闭
 * @retval 无
 */
void Execute_AllOff(void)
{
    // 设置开关值
    uint16_t mask[SWITCH_LEN];
    for (int i = 0; i < SWITCH_LEN; i++)
    {
        // 备用开关关闭无影响
        mask[i] = 1;
    }
    // 全部关闭
    Execute_OffBatch(mask, SWITCH_LEN);
}

/**
 * @brief  按键按下
 * @param KeyNum 按键值
 * @retval 无
 */
void Execute_KeyPressed(uint8_t KeyNum)
{
    // 对于KeyNum == 0的情况直接跳过
    if (KeyNum != 0)
    {
        // 读取开关信息
        uint16_t *switches = Store_ReadSwitches();
        // 获取仲裁结果
        uint16_t turnOn = Switch_Arbitration(KeyNum, switches);
        // 执行打开或关闭
        if (turnOn)
        {
            Execute_OnBatch(Switch_GetKeyMapping(KeyNum), SWITCH_LEN);
        }
        else
        {
            Execute_OffBatch(Switch_GetKeyMapping(KeyNum), SWITCH_LEN);
        }
    }
}

/**
 * @brief  重置系统
 * @retval 无
 */
void Execute_Reset(void)
{
    Store_Clear();
    printf("System reset has completed!\r\n ");
    // 重新启动
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}
