# 智慧照明芯片程序

## 项目介绍

本项目为智慧照明芯片程序，使用STM32F103C8T6芯片为载体。

该程序实现功能为：按键按下控制灯的亮灭，上位机（树莓派）发送指定命令可控制灯的亮灭。

### 下载

```shell
git clone https://github.com/li192863/intelligent-lighting.git
```

### 配置

配置文件为`./User/defs.h`，除过部分引脚定义不可更改外，其余配置均可自行更改。

### 引脚

![image-20231215132851666](.github/STM32F103C8T6引脚定义)

`Tn`引脚为输入引脚，`Xn`引脚为输出引脚，`USART`引脚为通信引脚。

### 配置

通用配置如下：

```c
// 通用 General
// 日志模式，开启DEBUG模式下会回显更多提示消息，若不开启则没有
#define DEBUG (1)
// 芯片速度
#define SPEED GPIO_Speed_50MHz
// 灯源频率
#define FREQ (1000)
// 占空比实际最小值
#define MIN_VALUE (0)
// 占空比实际最大值
#define MAX_VALUE (127)
// 占空比调节最小值
#define MIN_DUTY (8)
// 占空比调节最大值
#define MAX_DUTY (119)
```

## 硬件模块

### 按键`key.c`

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

`T1`~`T12`为输入引脚，其中`T1`~`T8`连接开关，连接按键式开关（点击后回弹至高电平），`T9`~`T12`预留使用，后期可连接传感器，配置外部中断。

### 调光`pwm.c`

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

`X1`~`X16`为输出引脚，均可输出PWM波，且频率可调。

### 通信`serial.c`

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

使用`USART3`与上位机（树莓派）进行通讯，通信格式为`FF<message>FDFE`，开启`DEBUG`模式下可回显消息。

### 存储`store.c`

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
// 开关状态区
#define SWITCH_START ((FLAG_START) + (FLAG_LEN))
#define SWITCH_LEN (16)
#define SWITCH_1 (1)
#define SWITCH_2 (1)
#define SWITCH_3 (1)
#define SWITCH_4 (1)
#define SWITCH_5 (1)
#define SWITCH_6 (1)
#define SWITCH_7 (1)
#define SWITCH_8 (1)
#define SWITCH_9 (1)
#define SWITCH_10 (1)
#define SWITCH_11 (1)
#define SWITCH_12 (1)
#define SWITCH_13 (1)
#define SWITCH_14 (1)
#define SWITCH_15 (1)
#define SWITCH_16 (0) // 备用
// 占空比区
#define DUTY_START ((SWITCH_START) + (SWITCH_LEN))
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
#define DUTY_16 (MIN_DUTY) // 备用
// 存储区实际缓存大小 以HalfWord为单位（16位）
#define STORE_LEN ((DUTY_START) + (DUTY_LEN))
```

Flash存储的信息如下：FLAG（8个半字）、SWITCH（16个半字）、DUTY（16个半字），存储的信息起始地址为`0x0x0800FC00`。

Flash首次加载时，会判断FLAG的第一个半字是否为`0x6666`，如果是，则判断存储信息有效、加载存储信息，否则则加载默认配置。Flash加载的配置信息主要有**各个灯的开启/关闭状态**，以及**各个灯的PWM波占空比**（以128为分母）。芯片上电后，以这些信息设置灯的开关状态和PWM波占空比。

注意`SWITCH`和`KEY`的区别，每个`SWITCH`对应一个灯，每一个`KEY`对应多个`SWITCH`。

注意在系统运行时，灯光亮度信息和开关信息实时更新至Flash当中。

## 系统模块

### 命令`command.c`

命令定义如下：

```C
/**
 * 命令 命令为16进制形式，数量最多256-3=253条，长度最长为256-4=252B
 * 为方便描述命令格式，约定<cn> -> HEX(cmd num), <ln> -> HEX(light num), <kn> -> HEX(key num), <n> -> HEX(num)
 */
enum Command {
  // 不进行任何操作 仅做占位使用
  NOP,
  // 查看状态 <cn> 0x01
  STATUS,
  // 设置当前某灯亮度，仅限内部调试使用 <cn><ln><n> 0x02017f
  SET_CURRENT_DUTY,
  // 获取当前亮度 <cn><ln> 0x0301
  GET_CURRENT_DUTY,
  // 设置某灯亮度，并同时修改当前亮度为此值 <cn><ln><n> 0x04017f
  SET_STORED_DUTY,
  // 获取设置亮度 <cn><ln> 0x0501
  GET_STORED_DUTY,
  // 设置开关 <cn><ln><n> 0x060101
  SET_SWITCH,
  // 获取开关 <cn><ln> 0x0701
  GET_SWITCH,
  // 开启某灯 <cn><ln> 0x0801
  ON,
  // 关闭某灯 <cn><ln> 0x0901
  OFF,
  // 开启/关闭某灯 <cn><ln> 0x0A01
  TURN,
  // 全部开启 <cn> 0x0B
  ALL_ON,
  // 全部关闭 <cn> 0x0C
  ALL_OFF,
  // 模拟按键按下 <cn><kn> 0x0D01
  KEY_PRESSED,
  // 重置系统 <cn> 0x0E
  MY_RESET
};
```

提供给上位机消息如上。注意消息为16进制，故如果使用串口调试助手，常用消息如下：

* 获取当前灯光信息：`FF01FDFE`
* 设置15号灯PWM波占空比为30/128：`FF040F30FDFE`
* 全部开启：`FF0BFDFE`

注意`SET_CURRENT_DUTY`不会将灯光信息存储到Flash当中，一般使用`SET_STORED_DUTY`来调节亮度，即调节亮度时会写入亮度信息到Flash当中。

### 开关`switch.c`

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

`KeyMapping[i][j]`表示按键`i`是否控制`j`灯，1表示控制，0表示不控制。

按键策略为：如果按键控制一组灯，那么该组灯只要有一个一个亮，则判定这组灯处于开启状态，按键按下后，这组灯将全部处于关闭状态。

### 执行`execute.c`

封装执行命令的相关函数。

### 存储 `my_flash.c`

封装供`store.c`使用的相关函数。

### 延时`delay.c`

封装延时相关函数。

### 系统`system.c`

封装主函数。