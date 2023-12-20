#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "defs.h"
#include "serial.h"
#include "pwm.h"
#include "key.h"
#include "store.h"
#include "execute.h"
#include "command.h"

/**
 * @brief  初始化JTAG调试功能，NVIC初始化
 * @retval 无
 */
void System_PreInit(void)
{
    // 关闭JTAG调试端口，因为其影响输出PA15/PB3/PB4输出
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    // 初始化NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/**
 * @brief  根据配置初始化
 * @retval 无
 */
void System_PostInit(void)
{
    // 根据存储值启动
    Command_Start();

    // 检测是否发生了独立看门狗复位
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
    {
        if (DEBUG)
        {
            printf("[DEBUG]: Independent Watchdog reset detected!\r\n");
        }
        RCC_ClearFlag();
    }

    // 开启独立看门狗
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_128);
    IWDG_SetReload(3124); // 10000ms = 10s
    IWDG_ReloadCounter(); // 喂狗
    IWDG_Enable();

    printf("[INFO ]: Program started!\r\n");
}

/**
 * @brief  初始化系统
 * @retval 无
 */
void System_Init(void)
{
    // 初始化预处理
    System_PreInit(); // 初始化JTAG，初始化NVIC

    // 初始化硬件
    Serial_Init(); // 初始化串口
    Store_Init(); // 初始化存储
    PWM_Init(); // 初始化PWM波
    Key_Init(); // 初始化按键

    // 初始化后处理
    System_PostInit();
}

/**
 * @brief  系统主循环
 * @retval 无
 */
void System_MainLoop(void)
{
    // 执行喂狗
    IWDG_ReloadCounter(); // 喂狗
    // 执行按键
    Command_KeyPressed(Key_GetNum());
    // 执行命令
    uint8_t *cmd = Serial_Get();
    if (cmd != NULL)
    {
        Command_Execute(cmd);
    }
}
