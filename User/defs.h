#ifndef __DEFS_H
#define __DEFS_H

// 通用 General
// 日志模式
#define DEBUG (1)
// 芯片速度
#define SPEED GPIO_Speed_50MHz
// 灯源频率
#define FREQ (4000)
// 占空比最小值
#define MIN_VALUE (0)
// 占空比最大值
#define MAX_VALUE (127)
// 占空比调节最小值
#define MIN_DUTY (0)
// 占空比调节最大值
#define MAX_DUTY (127)
// 占空比调节档次
#define GEAR_COUNT (8)

// PWM Freq = CK_PSC / (PSC + 1) / (ARR + 1) = 72M / 128 / 140 = 4017.86kHz
// 时钟分频 1分频
#define CLOCK_DIVISION TIM_CKD_DIV1
// 计数模式 向上计数
#define COUNTER_MODE TIM_CounterMode_Up
// ARR
#define ARR MAX_VALUE
// PSC
#define PSC (72000000 / (ARR + 1) / FREQ)  // 72M / 128 / 4k = 140
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
#define T1_PORT GPIOC
#define T1_PIN GPIO_Pin_14
#define T2_PORT GPIOC
#define T2_PIN GPIO_Pin_15
// GPIOA
#define T3_PORT GPIOA
#define T3_PIN GPIO_Pin_4
#define T4_PORT GPIOA
#define T4_PIN GPIO_Pin_5
// GPIOB
#define T5_PORT GPIOB
#define T5_PIN GPIO_Pin_5
#define T6_PORT GPIOB
#define T6_PIN GPIO_Pin_4
#define T7_PORT GPIOB
#define T7_PIN GPIO_Pin_3
// GPIOA
#define T8_PORT GPIOA
#define T8_PIN GPIO_Pin_15
// GPIOB
#define T9_PORT GPIOB
#define T9_PIN GPIO_Pin_15  // 预留
#define T10_PORT GPIOB
#define T10_PIN GPIO_Pin_14 // 预留
#define T11_PORT GPIOB
#define T11_PIN GPIO_Pin_13 // 预留
#define T12_PORT GPIOB
#define T12_PIN GPIO_Pin_12 // 预留

// 输出 X1~X16
// 模式 复用推挽输出
#define X_MODE GPIO_Mode_AF_PP
// GPIOA
#define X1_PORT GPIOA
#define X1_PIN GPIO_Pin_0
#define X2_PORT GPIOA
#define X2_PIN GPIO_Pin_1
#define X3_PORT GPIOA
#define X3_PIN GPIO_Pin_2
#define X4_PORT GPIOA
#define X4_PIN GPIO_Pin_3
// GPIOB
#define X5_PORT GPIOB
#define X5_PIN GPIO_Pin_9
#define X6_PORT GPIOB
#define X6_PIN GPIO_Pin_8
#define X7_PORT GPIOB
#define X7_PIN GPIO_Pin_7
#define X8_PORT GPIOB
#define X8_PIN GPIO_Pin_6
// GPIOA
#define X9_PORT GPIOA
#define X9_PIN GPIO_Pin_11
#define X10_PORT GPIOA
#define X10_PIN GPIO_Pin_10
#define X11_PORT GPIOA
#define X11_PIN GPIO_Pin_9
#define X12_PORT GPIOA
#define X12_PIN GPIO_Pin_8
// GPIOA
#define X13_PORT GPIOA
#define X13_PIN GPIO_Pin_6
#define X14_PORT GPIOA
#define X14_PIN GPIO_Pin_7
// GPIOB
#define X15_PORT GPIOB
#define X15_PIN GPIO_Pin_0
#define X16_PORT GPIOB
#define X16_PIN GPIO_Pin_1

// 通信 USART3
// 接收 RX
#define RX_MODE GPIO_Mode_IPU
#define RX_PIN GPIO_Pin_11
// 发送 TX
#define TX_MODE GPIO_Mode_AF_PP
#define TX_PIN GPIO_Pin_10
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
// 接收缓冲区长度
#define RX_PACKET_LEN (256)
// 发送缓冲区长度
#define TX_PACKET_LEN (256)
// 信息包头
#define PACKET_HEAD (0xFF)
// 信息结束
#define PACKET_ENDS (0xFD)
// 信息包尾
#define PACKET_TAIL (0xFE)

// 按键
// 外部中断模式
#define EXTI_MODE EXTI_Mode_Interrupt
// 外部触发方式
#define EXTI_TRIGGER EXTI_Trigger_Falling

// 存储 Flash
// 存储单位 以Byte为单位
#define STORE_UNIT (2)
// 存储区缓存大小 以HalfWord为单位（16位）
#define STORE_MAX_LEN (1024 / (STORE_UNIT))
// 存储区起始地址
#define STORE_START_ADDRESS (0x0800FC00)
// 选项位区
#define FLAG_START (0)
#define FLAG_LEN (8)
#define FLAG_EFFECTIVE (0x6666)
// 占空比区
#define DUTY_START ((FLAG_START) + (FLAG_LEN))
#define DUTY_LEN (16)
#define DUTY_1 (MAX_DUTY)
#define DUTY_2 (MAX_DUTY)
#define DUTY_3 (MAX_DUTY)
#define DUTY_4 (MAX_DUTY)
#define DUTY_5 (MAX_DUTY)
#define DUTY_6 (MAX_DUTY)
#define DUTY_7 (MAX_DUTY)
#define DUTY_8 (MAX_DUTY)
#define DUTY_9 (MAX_DUTY)
#define DUTY_10 (MAX_DUTY)
#define DUTY_11 (MAX_DUTY)
#define DUTY_12 (MAX_DUTY)
#define DUTY_13 (MAX_DUTY)
#define DUTY_14 (MAX_DUTY)
#define DUTY_15 (MAX_DUTY)
#define DUTY_16 (MAX_DUTY)
// 存储区实际缓存大小 以HalfWord为单位（16位）
#define STORE_LEN ((DUTY_START) + (DUTY_LEN))

#endif
