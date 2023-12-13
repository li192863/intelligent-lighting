#include <stdio.h>
#include <stdarg.h>
#include "stm32f10x.h"
#include "defs.h"

uint8_t Serial_RxPacket[RX_PACKET_LEN];
uint8_t Serial_RxFlag = 0;

static uint8_t RxState = 0;
static uint8_t pRxPacket = 0;

/**
  * @brief  串口初始化
  * @retval 无
  */
void Serial_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 初始化引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = TX_MODE;
    GPIO_InitStructure.GPIO_Pin = TX_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = RX_MODE;
    GPIO_InitStructure.GPIO_Pin = RX_PIN;
    GPIO_InitStructure.GPIO_Speed = SPEED;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 初始化USART
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = BAUD_RATE; // 波特率
    USART_InitStruct.USART_HardwareFlowControl = HARDWARE_FLOW_CONTROL;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = PARITY; // 不校验
    USART_InitStruct.USART_StopBits = STOP_BITS;
    USART_InitStruct.USART_WordLength = WORD_LENGTH;
    USART_Init(USART3, &USART_InitStruct);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    
    // 开启USART
    USART_Cmd(USART3, ENABLE);
}

/**
  * @brief  串口发送字节
  * @param Byte 待发送字节
  * @retval 无
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART3, Byte);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

/**
  * @brief  串口发送数组
  * @param Array 待发送数组
  * @param Length 数组长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}

/**
  * @brief  串口发送字符串
  * @param String 待发送字符串
  * @retval 无
  */
void Serial_SendString(char *String)
{
    uint16_t i;
    for (i = 0; String[i]; i++)
    {
        Serial_SendByte(String[i]);
    }
}

/**
  * @brief  串口计算幂函数
  * @param X 底数
  * @param Y 指数
  * @retval 结果X^Y
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t i, Result = 1;
    for (i = 0; i < Y; i++)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  串口发送数字
  * @param Number 数字
  * @param Length 数字长度
  * @retval 无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  串口输出字符
  * @param ch 字符
  * @param f 文件
  * @retval 字符
  */
int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

/**
  * @brief  串口打印函数
  * @param format 格式化字符串
  * @retval 无
  */
void Serial_Printf(char *format, ...)
{
    char String[TX_PACKET_LEN];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

/**
  * @brief  获取串口接收到的数据
  * @retval 字符串/char[]数组/uint8_t[]数组
  */
uint8_t* Serial_Get(void)
{
    // 检查是否接收完成
    if (Serial_RxFlag == 1)
    {
        // 在调试模式下打印字符串
        if (DEBUG) {
            printf("[DEBUG]: Recive data ");
            for (int i = 0; i < pRxPacket; i++)
            {
                printf("%02X ", Serial_RxPacket[i]);
            }
            printf("\r\n");
        }
        // 重新开启接收
        Serial_RxFlag = 0;
        return Serial_RxPacket;
    }
    return NULL;
}

/**
  * @brief  USART3中断处理函数
  * @retval 无
  */
void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART3);
        if (RxState == 0)  // 等待包头状态
        {
            if (RxData == PACKET_HEAD && Serial_RxFlag == 0)
            {
                RxState = 1;
                pRxPacket = 0;
            }
        }
        else if (RxState == 1)  // 接收数据状态
        {
            if (RxData == PACKET_ENDS)
            {
                RxState = 2;
            }
            else
            {
                Serial_RxPacket[pRxPacket++] = RxData;
            }
            
            
        }
        else if (RxState == 2)  // 等待包尾状态
        {
            if (RxData == PACKET_TAIL)
            {
                RxState = 0;
                Serial_RxPacket[pRxPacket] = '\0';
                Serial_RxFlag = 1;
            }
        }
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}
