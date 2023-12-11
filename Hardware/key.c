#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "defs.h"

/**
  * @brief  按键初始化
  * @retval 无
  */
void Key_Init(void)
{
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    // 初始化引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T1_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T1_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T2_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T2_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T3_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T3_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T4_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T4_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T5_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T5_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T6_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T6_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T7_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T7_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = T_MODE;
    GPIO_InitStructure.GPIO_Pin = T8_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(T8_PORT, &GPIO_InitStructure);
    
    // 预留T12~T15为外部中断输入
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 使能AFIO时钟

    // GPIO_InitStructure.GPIO_Mode = T_MODE;
    // GPIO_InitStructure.GPIO_Pin = T9;
    // GPIO_InitStructure.GPIO_Speed = SPEED;
    // GPIO_Init(T9_PORT, &GPIO_InitStructure);
    // GPIO_InitStructure.GPIO_Mode = T_MODE;
    // GPIO_InitStructure.GPIO_Pin = T10;
    // GPIO_InitStructure.GPIO_Speed = SPEED;
    // GPIO_Init(T10_PORT, &GPIO_InitStructure);
    // GPIO_InitStructure.GPIO_Mode = T_MODE;
    // GPIO_InitStructure.GPIO_Pin = T11;
    // GPIO_InitStructure.GPIO_Speed = SPEED;
    // GPIO_Init(T11_PORT, &GPIO_InitStructure);
    // GPIO_InitStructure.GPIO_Mode = T_MODE;
    // GPIO_InitStructure.GPIO_Pin = T12_PIN;
    // GPIO_InitStructure.GPIO_Speed = SPEED;
    // GPIO_Init(T12_PORT, &GPIO_InitStructure);

    // EXTI_InitTypeDef EXTI_InitStruct;
    // Line15: B15(T9)
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource15);
    // EXTI_InitStruct.EXTI_Line = EXTI_Line15; // 指定外部中断线
    // EXTI_InitStruct.EXTI_Mode = EXTI_MODE;
    // EXTI_InitStruct.EXTI_Trigger = EXTI_TRIGGER;
    // EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // EXTI_Init(&EXTI_InitStruct);

    // Line14: B14(T10)
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);
    // EXTI_InitStruct.EXTI_Line = EXTI_Line14; // 指定外部中断线
    // EXTI_InitStruct.EXTI_Mode = EXTI_MODE;
    // EXTI_InitStruct.EXTI_Trigger = EXTI_TRIGGER;
    // EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // EXTI_Init(&EXTI_InitStruct);

    // Line13: B13(T11)
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    // EXTI_InitStruct.EXTI_Line = EXTI_Line13; // 指定外部中断线
    // EXTI_InitStruct.EXTI_Mode = EXTI_MODE;
    // EXTI_InitStruct.EXTI_Trigger = EXTI_TRIGGER;
    // EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // EXTI_Init(&EXTI_InitStruct);

    // Line12: B12(T12_PIN)
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
    // EXTI_InitStruct.EXTI_Line = EXTI_Line12; // 指定外部中断线
    // EXTI_InitStruct.EXTI_Mode = EXTI_MODE;
    // EXTI_InitStruct.EXTI_Trigger = EXTI_TRIGGER;
    // EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    // EXTI_Init(&EXTI_InitStruct);
}

/**
  * @brief  获取按键
  * @retval 无
  */
uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;
    if (GPIO_ReadInputDataBit(T1_PORT, T1_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T1_PORT, T1_PIN) == 0);
        Delay_ms(20);
        KeyNum = 1;
    }
    if (GPIO_ReadInputDataBit(T2_PORT, T2_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T2_PORT, T2_PIN) == 0);
        Delay_ms(20);
        KeyNum = 2;
    }
    if (GPIO_ReadInputDataBit(T3_PORT, T3_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T3_PORT, T3_PIN) == 0);
        Delay_ms(20);
        KeyNum = 3;
    }
    if (GPIO_ReadInputDataBit(T4_PORT, T4_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T4_PORT, T4_PIN) == 0);
        Delay_ms(20);
        KeyNum = 4;
    }
    if (GPIO_ReadInputDataBit(T5_PORT, T5_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T5_PORT, T5_PIN) == 0);
        Delay_ms(20);
        KeyNum = 5;
    }
    if (GPIO_ReadInputDataBit(T6_PORT, T6_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T6_PORT, T6_PIN) == 0);
        Delay_ms(20);
        KeyNum = 6;
    }
    if (GPIO_ReadInputDataBit(T7_PORT, T7_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T7_PORT, T7_PIN) == 0);
        Delay_ms(20);
        KeyNum = 7;
    }
    if (GPIO_ReadInputDataBit(T8_PORT, T8_PIN) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(T8_PORT, T8_PIN) == 0);
        Delay_ms(20);
        KeyNum = 8;
    }

    // 预留T12~T15为外部中断输入
    // if (GPIO_ReadInputDataBit(GPIOB, T9) == 0)
    // {
    //     Delay_ms(20);
    //     while (GPIO_ReadInputDataBit(GPIOB, T9) == 0);
    //     Delay_ms(20);
    //     KeyNum = 9;
    // }
    // if (GPIO_ReadInputDataBit(GPIOB, T10) == 0)
    // {
    //     Delay_ms(20);
    //     while (GPIO_ReadInputDataBit(GPIOB, T10) == 0);
    //     Delay_ms(20);
    //     KeyNum = 10;
    // }
    // if (GPIO_ReadInputDataBit(GPIOB, T11) == 0)
    // {
    //     Delay_ms(20);
    //     while (GPIO_ReadInputDataBit(GPIOB, T11) == 0);
    //     Delay_ms(20);
    //     KeyNum = 11;
    // }
    // if (GPIO_ReadInputDataBit(GPIOB, T12_PIN) == 0)
    // {
    //     Delay_ms(20);
    //     while (GPIO_ReadInputDataBit(GPIOB, T12_PIN) == 0);
    //     Delay_ms(20);
    //     KeyNum = 12;
    // }
    if (DEBUG && KeyNum != 0)
    {
        printf("[DEBUG]: KeyNum %2d\r\n", KeyNum);
    }
    return KeyNum;
}

