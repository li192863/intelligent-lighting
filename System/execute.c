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
 * @brief  设置当前占空比，占空比值不会被存储，所有灯
 * @param  Duties 占空比数组
 * @param  Len 占空比数组长度
 * @retval 无
 */
static void Execute_SetCurrentDuties(uint16_t Duties[], int Len)
{
    for (int i = 0; i < Len; i++)
    {
        PWM_SetDuty(i + 1, Duties[i]);
    }
}

/**
 * @brief  设置当前占空比，占空比值不会被存储，掩码灯
 * @param  Mask 掩码数组，值为1的表示被选择，值为0的不被选择
 * @param  Len 掩码数组的长度（将依次按序设置）
 * @param  Duty 占空比 0 ~ 127
 * @retval 无
 */
static void Execute_SetCurrentMaskedDuties(uint16_t Mask[], int Len, uint16_t Duty)
{
    for (int i = 0; i < Len; i++)
    {
        if (Mask[i]) {
            PWM_SetDuty(i + 1, Duty);
        }
    }
}

/**
 * @brief  设置当前占空比，占空比值不会被存储，单个灯
 * @param  i 第i个灯 1 ~ 16
 * @param  Duty 占空比 0 ~ 127
 * @retval 无
 */
static void Execute_SetCurrentDuty(uint8_t i, uint16_t Duty)
{
    // 保护硬件
    Duty = Duty <= MIN_DUTY ? MIN_DUTY : Duty;
    Duty = Duty > MAX_DUTY ? MAX_DUTY : Duty;
    PWM_SetDuty(i, Duty);
}

/**
 * @brief  设置当前占空比，所有灯
 * @param  Duties 占空比数组
 * @param  Len 占空比数组长度
 * @retval 无
 */
void Execute_SetDuties(uint16_t Duties[], int Len)
{
    Execute_SetCurrentDuties(Duties, Len);
    Store_WriteDuties(Duties, Len);
}

/**
 * @brief  设置当前占空比，掩码灯
 * @param  Mask 掩码数组，值为1的表示被选择，值为0的不被选择
 * @param  Len 掩码数组的长度（将依次按序设置）
 * @param  Duty 占空比 0 ~ 127
 * @retval 无
 */
void Execute_SetMaskedDuties(uint16_t Mask[], int Len, uint16_t Duty)
{
    Execute_SetCurrentMaskedDuties(Mask, Len, Duty);
    Store_WriteMaskedDuties(Mask, Len, Duty);
}

/**
 * @brief  设置当前占空比，单个灯
 * @param  i 第i个灯 1 ~ 16
 * @param  Duty 占空比 0 ~ 127
 * @retval 无
 */
void Execute_SetDuty(uint8_t i, uint16_t Duty)
{
    Execute_SetCurrentDuty(i, Duty);
    Store_WriteDuty(i, Duty);
}

/**
 * @brief  读取占空比信息，所有灯
 * @param  Len 指向长度的指针，若为NULL则不做处理
 * @retval 指向占空比数组的指针
 */
uint16_t* Execute_GetDuties(int *Len)
{
    return Store_ReadDuties(Len);
}

/**
 * @brief  获取存储占空比，单个灯
 * @param  i 第i个灯 1 ~ 16
 * @retval 无
 */
uint16_t Execute_GetDuty(uint8_t i)
{
    return Store_ReadDuty(i);
}

/**
 * @brief  打开第i个灯，最大亮度
 * @param  i 第i个灯 1 ~ 16
 * @retval 无
 */
void Execute_On(uint8_t i)
{
    Execute_SetDuty(i, MAX_DUTY);
}

/**
 * @brief  关闭第i个灯，最小亮度
 * @param  i 第i个灯 1 ~ 16
 * @retval 无
 */
void Execute_Off(uint8_t i)
{
    Execute_SetDuty(i, MIN_DUTY);
}

/**
 * @brief  全部开启
 * @retval 无
 */
void Execute_AllOn(void)
{
    uint16_t Duties[DUTY_LEN];
    for (int i = 0; i < DUTY_LEN; i++) {
        Duties[i] = MAX_VALUE;
    }
    Execute_SetDuties(Duties, DUTY_LEN);
}

/**
 * @brief  全部关闭
 * @retval 无
 */
void Execute_AllOff(void)
{
    uint16_t Duties[DUTY_LEN];
    for (int i = 0; i < DUTY_LEN; i++) {
        Duties[i] = MIN_VALUE;
    }
    Execute_SetDuties(Duties, DUTY_LEN);
}

/**
 * @brief  按键按下
 * @param  KeyNum 按键值
 * @retval 无
 */
void Execute_KeyPressed(uint8_t KeyNum)
{
    // 对于KeyNum == 0的情况直接跳过
    if (KeyNum != 0)
    {
        int len;
        uint16_t *mask = Switch_GetKeyMask(KeyNum);
        uint16_t *duties = Execute_GetDuties(&len);
        uint16_t nextDuty = Switch_GetNextDuty(duties, mask, len);
        Execute_SetMaskedDuties(mask, len, nextDuty);
    }
}

/**
 * @brief  重置系统，包括Flash存储等一同清除
 * @retval 无
 */
void Execute_DeepReset(void)
{
    Store_Clear();
    if (DEBUG)
    {
        printf("[DEBUG]: System reset has completed!\r\n ");
    }
    // 重新启动
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}

/**
 * @brief  普通重置系统，即不删除缓存数据
 * @retval 无
 */
void Execute_Restart(void)
{
    // 重新启动
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}
