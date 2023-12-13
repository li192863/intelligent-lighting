#include <math.h>
#include "stm32f10x.h"                  // Device header
#include "defs.h"

/**
  * @brief  PWM初始化
  * @retval 无
  */
void PWM_Init(void)
{
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    // 初始化引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X1_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X1_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X2_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X2_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X3_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X3_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X4_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X4_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X5_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X5_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X6_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X6_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X7_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X7_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X8_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X8_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X9_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X9_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X10_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X10_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X11_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X11_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X12_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X12_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X13_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X13_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X14_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X14_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X15_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X15_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = X_MODE; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = X16_PIN;
    GPIO_InitStruct.GPIO_Speed = SPEED;
    GPIO_Init(X16_PORT, &GPIO_InitStruct);

    // 使用定时器内部时钟源
    TIM_InternalClockConfig(TIM1);
    TIM_InternalClockConfig(TIM2);
    TIM_InternalClockConfig(TIM3);
    TIM_InternalClockConfig(TIM4);
    
    // 初始化时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = CLOCK_DIVISION; // 不分频
    TIM_TimeBaseInitStruct.TIM_CounterMode = COUNTER_MODE; // 向上计数
    TIM_TimeBaseInitStruct.TIM_Period = ARR;
    TIM_TimeBaseInitStruct.TIM_Prescaler = PSC;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = REPETITION_COUNTER;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
    TIM_TimeBaseInitStruct.TIM_ClockDivision = CLOCK_DIVISION;
    TIM_TimeBaseInitStruct.TIM_CounterMode = COUNTER_MODE;
    TIM_TimeBaseInitStruct.TIM_Period = ARR;
    TIM_TimeBaseInitStruct.TIM_Prescaler = PSC;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = REPETITION_COUNTER;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    TIM_TimeBaseInitStruct.TIM_ClockDivision = CLOCK_DIVISION;
    TIM_TimeBaseInitStruct.TIM_CounterMode = COUNTER_MODE;
    TIM_TimeBaseInitStruct.TIM_Period = ARR;
    TIM_TimeBaseInitStruct.TIM_Prescaler = PSC;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = REPETITION_COUNTER;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    TIM_TimeBaseInitStruct.TIM_ClockDivision = CLOCK_DIVISION;
    TIM_TimeBaseInitStruct.TIM_CounterMode = COUNTER_MODE;
    TIM_TimeBaseInitStruct.TIM_Period = ARR;
    TIM_TimeBaseInitStruct.TIM_Prescaler = PSC;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = REPETITION_COUNTER;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

    // 初始化输出比较单元    
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = OC_MODE;
    TIM_OCInitStruct.TIM_OCPolarity = OC_POLARITY;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = PULSE; // CCR
    TIM_OC1Init(TIM1, &TIM_OCInitStruct);
    TIM_OC2Init(TIM1, &TIM_OCInitStruct);
    TIM_OC3Init(TIM1, &TIM_OCInitStruct);
    TIM_OC4Init(TIM1, &TIM_OCInitStruct);
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = OC_MODE;
    TIM_OCInitStruct.TIM_OCPolarity = OC_POLARITY;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = PULSE; // CCR
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    TIM_OC2Init(TIM2, &TIM_OCInitStruct);
    TIM_OC3Init(TIM2, &TIM_OCInitStruct);
    TIM_OC4Init(TIM2, &TIM_OCInitStruct);
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = OC_MODE;
    TIM_OCInitStruct.TIM_OCPolarity = OC_POLARITY;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = PULSE; // CCR
    TIM_OC1Init(TIM3, &TIM_OCInitStruct);
    TIM_OC2Init(TIM3, &TIM_OCInitStruct);
    TIM_OC3Init(TIM3, &TIM_OCInitStruct);
    TIM_OC4Init(TIM3, &TIM_OCInitStruct);
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = OC_MODE;
    TIM_OCInitStruct.TIM_OCPolarity = OC_POLARITY;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = PULSE; // CCR
    TIM_OC1Init(TIM4, &TIM_OCInitStruct);
    TIM_OC2Init(TIM4, &TIM_OCInitStruct);
    TIM_OC3Init(TIM4, &TIM_OCInitStruct);
    TIM_OC4Init(TIM4, &TIM_OCInitStruct);
    // 开启定时器
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1,ENABLE); // 高级定时器
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

/**
 * @brief  设置第i个输出得占空比
 * @param i 第i个输出 1 ~ 16
 * @param duty 占空比 * MAX_VALUE
 * @retval 无
 */
void PWM_SetDuty(uint8_t i, uint16_t duty)
{
    uint16_t Compare = duty; // duty * (ARR + 1) / (MAX_VALUE) == duty * 1.004
    if (i == 1)
    {
        TIM_SetCompare1(TIM2, Compare); // TIM2CH1
    }
    else if (i == 2)
    {
        TIM_SetCompare2(TIM2, Compare); // TIM2CH2
    }
    else if (i == 3)
    {
        TIM_SetCompare3(TIM2, Compare); // TIM2CH3
    }
    else if (i == 4)
    {
        TIM_SetCompare4(TIM2, Compare); // TIM2CH4
    }
    else if (i == 5)
    {
        TIM_SetCompare4(TIM4, Compare); // TIM4CH4
    }
    else if (i == 6)
    {
        TIM_SetCompare3(TIM4, Compare); // TIM4CH3
    }
    else if (i == 7)
    {
        TIM_SetCompare2(TIM4, Compare); // TIM4CH2
    }
    else if (i == 8)
    {
        TIM_SetCompare1(TIM4, Compare); // TIM4CH1
    }
    else if (i == 9)
    {
        TIM_SetCompare4(TIM1, Compare); // TIM1CH4
    }
    else if (i == 10)
    {
        TIM_SetCompare3(TIM1, Compare); // TIM1CH3
    }
    else if (i == 11)
    {
        TIM_SetCompare2(TIM1, Compare); // TIM1CH2
    }
    else if (i == 12)
    {
        TIM_SetCompare1(TIM1, Compare); // TIM1CH1
    }
    else if (i == 13)
    {
        TIM_SetCompare1(TIM3, Compare); // TIM3CH1
    }
    else if (i == 14)
    {
        TIM_SetCompare2(TIM3, Compare); // TIM3CH2
    }
    else if (i == 15)
    {
        TIM_SetCompare3(TIM3, Compare); // TIM3CH3
    }
    else if (i == 16)
    {
        TIM_SetCompare4(TIM3, Compare); // TIM3CH4
    }
}
