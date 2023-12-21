# 智慧照明芯片程序

## 项目介绍

本项目为智慧照明芯片程序，使用STM32F103C8T6芯片为载体。

该程序实现功能为：按键按下控制灯的明暗程度，并且可通过上位机（树莓派）使用串口发送指定命令进行控制。

### 下载

```shell
git clone https://github.com/li192863/intelligent-lighting-mcu.git
```

### 配置

配置文件为`./User/defs.h`，除过部分引脚定义不可更改外，其余配置均可更改。

### 引脚

引脚定义如下图所示：

![image-20231215132851666](.github/STM32F103C8T6引脚定义)

`Tn`引脚为输入引脚、共12路；

`Xn`引脚为输出引脚、共16路；

`USART`引脚为通信引脚、使用`USART3`。

### 配置

通用配置如下：

```c
// 通用 General
// 日志模式
#define DEBUG (0)
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
```

日志模式：非0值表示开启。开启状态下，会输出调试信息。

灯源频率：取决于硬件设备，这里取4kHz。

占空比最小值/占空比最大值：占空比可设置的最大值与最小值，最大值即Timer中比较寄存器的值。

占空比调节最小值/占空比调节最大值：为保护硬件，有时需要对占空比的调节范围进行控制，此时可通过该宏定义限制其最小值和最大值。

## 硬件模块

### 按键`key.c`

`T1` ~ `T12`为输入引脚，其中`T1` ~ `T8`连接开关，连接按键式开关（点击后回弹至高电平），`T9` ~ `T12`预留使用，后期可连接传感器，配置外部中断。

输入引脚定义如下：

```c
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
```

### 调光`pwm.c`

`X1` ~ `X16`为输出引脚，均可输出PWM波，且频率可调。

输出引脚定义如下：

```c
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
```

PWM波配置如下：

```c
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
```

`ARR`：自动重装器当中的值，此处设置为占空比最大值，即`127`。

### 通信`serial.c`

使用`USART3`与上位机（树莓派）进行通讯，通信格式为`FF<message>FDFE`，`DEBUG`模式下可回显消息。

通信配置如下：

```c
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
```

波特率：通信时的波特率；

信息包头：收到信息包头时判定为一个命令起始；

信息结束：收到信息结束时判定为一个命令结束；

信息包尾：收到信息包头时判定为一个命令终止。

### 存储`store.c`

Flash存储的信息如下：FLAG（8个半字）、SWITCH（16个半字）、DUTY（16个半字），存储的信息起始地址为`0x0x0800FC00`。

Flash首次加载时，会判断FLAG的第一个半字是否为`0x6666`，如果是，则判断存储信息有效、加载存储信息，否则则加载默认配置。

Flash加载的配置信息主要有标志信息（8×16bit）、**各个灯的PWM波占空比**（以128为分母、16×16bit）。芯片上电后，以这些信息将设置灯的PWM波占空比。

注意在系统运行时，更改灯光亮度信息将实时更新至Flash当中。

存储配置如下：

```c
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
```

`DUTY_x`：第`x`号灯的初始占空比，初始状态下或重置系统（`DEEP_RESET`）后，将以此作为初始占空比。

## 系统模块

### 命令`command.c`

上位机可发送的命令采用HEX模式，如果使用串口调试助手，常用消息如下：

* 获取当前灯光信息：`FF01FDFE`
* 设置15号灯PWM波占空比为30/128：`FF020F30FDFE`
* 全部开启：`FF07FDFE`

命令定义如下：

```C
/**
 * 接收的命令
 * 命令为16进制形式，数量最多256-3=253条，长度最长为256-4=252B
 * 为方便描述命令格式，约定<cn> -> HEX(cmd num), <ln> -> HEX(light num), <kn> -> HEX(key num), <n> -> HEX(num)
 */
enum Command {
    // 不进行任何操作 仅做占位使用
    COMMAND_NOP,
    // 查看状态 <cn> 0x01
    COMMAND_STATUS,
    // 设置当前某灯亮度，<cn><ln><n> 0x02017f
    COMMAND_SET_DUTY,
    // 获取当前亮度 <cn><ln> 0x0301
    COMMAND_GET_DUTY,
    // 开启某灯 <cn><ln> 0x0401
    COMMAND_ON,
    // 关闭某灯 <cn><ln> 0x0501
    COMMAND_OFF,
    // 全部开启 <cn> 0x06
    COMMAND_ALL_ON,
    // 全部关闭 <cn> 0x07
    COMMAND_ALL_OFF,
    // 模拟按键按下 <cn><kn> 0x0801
    COMMAND_KEY_PRESSED,
    // 重置系统 <cn> 0x09
    COMMAND_DEEP_RESET,
    // 普通重置系统 <cn> 0x0A
    COMMAND_RESTART
};
```

### 开关`switch.c`

`KeyMapping[i][j]`表示按键`i`是否控制`j`灯，`1`表示控制，`0`表示不控制。

按键策略为：按键按下，按键控制的相应灯亮度增加`1/GEAR_COUNT`。当达到最亮时，再按一次将变为`0`。

按键掩码如下：

```c
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
```

### 执行`execute.c`

封装执行命令的相关函数。凡是新定义的执行功能，需定义在此模块。

### 系统`system.c`

封装主函数。这里使用到了看门狗，若程序卡死/跑飞超过10s，则看门狗电路自动复位程序（`RESTART`）。