#ifndef __DEFS_H
#define __DEFS_H

// 通用 General
// 日志模式
#define DEBUG (1)
// 芯片速度
#define SPEED GPIO_Speed_50MHz
// 灯源频率
#define FREQ (4000)
// 调节最小值
#define MIN_VALUE (0)
// 调节最大值
#define MAX_VALUE (255)

// PWM Freq = CK_PSC / (PSC + 1) / (ARR + 1) = 72M / 256 / 70 = 4017.86kHz
// 时钟分频 1分频
#define CLOCK_DIVISION TIM_CKD_DIV1
// 计数模式 向上计数
#define COUNTER_MODE TIM_CounterMode_Up
// ARR
#define ARR MAX_VALUE
// PSC
#define PSC (72000000 / (ARR + 1) / FREQ)
// 重复计数器
#define REPETITION_COUNTER (0)
// 输出模式
#define OC_MODE TIM_OCMode_PWM1
// 输出极性
#define OC_POLARITY TIM_OCPolarity_High
// 脉冲初始值
#define PULSE (0x00)


// 输入 T1~T12
// 模式 上拉输入
#define T_MODE GPIO_Mode_IPU
// GPIOC
#define T1 GPIO_Pin_14
#define T2 GPIO_Pin_15
// GPIOA
#define T3 GPIO_Pin_4
#define T4 GPIO_Pin_5
// GPIOB
#define T5 GPIO_Pin_5
#define T6 GPIO_Pin_4
#define T7 GPIO_Pin_3
// GPIOA
#define T8 GPIO_Pin_15
// GPIOB
#define T9 GPIO_Pin_15  // 预留
#define T10 GPIO_Pin_14 // 预留
#define T11 GPIO_Pin_13 // 预留
#define T12 GPIO_Pin_12 // 预留

// 输出 X1~X12
// 模式 复用推挽输出
#define X_MODE GPIO_Mode_AF_PP
// GPIOA
#define X1 GPIO_Pin_0
#define X2 GPIO_Pin_1
#define X3 GPIO_Pin_2
#define X4 GPIO_Pin_3
// GPIOB
#define X5 GPIO_Pin_9
#define X6 GPIO_Pin_8
#define X7 GPIO_Pin_7
#define X8 GPIO_Pin_6
// GPIOA
#define X9 GPIO_Pin_11
#define X10 GPIO_Pin_10
#define X11 GPIO_Pin_9
#define X12 GPIO_Pin_8
// GPIOA
#define X13 GPIO_Pin_6
#define X14 GPIO_Pin_7
// GPIOB
#define X15 GPIO_Pin_0
#define X16 GPIO_Pin_1

// 通信 USART3
// 接收 RX
#define RX_MODE GPIO_Mode_IPU
#define RX GPIO_Pin_11
// 发送 TX
#define TX_MODE GPIO_Mode_AF_PP
#define TX GPIO_Pin_10
// 缓冲区长度
#define RX_PACKET_LEN (256)
// 波特率
#define BAUD_RATE (9600)
// 硬件流控制
#define HARDWARE_FLOW_CONTROL USART_HardwareFlowControl_None
// 校验
#define PARITY USART_Parity_No
// 停止位
#define STOP_BITS USART_StopBits_1
// 数据位长度
#define WORD_LENGTH USART_WordLength_8b

// 按键
// 外部中断模式
#define EXTI_MODE EXTI_Mode_Interrupt
// 外部触发方式
#define EXTI_TRIGGER EXTI_Trigger_Falling

#endif
