#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "defs.h"
#include "execute.h"
#include "serial.h"

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
    COMMAND_RESET,
    // 普通重置系统 <cn> 0x0A
    COMMAND_RESTART
};

/**
 * 发送的消息
 * 消息为字符串形式，字符串中的数字为16进制
 * 为方便描述消息格式，约定<mn> -> msg num <str> -> string content
 */
enum Message {
    // 不进行任何操作 仅做占位使用
    MESSAGE_NOP,
    // 操作成功 <mn> 1
    MESSAGE_SUCCESS,
    // 操作失败 <mn> 2
    MESSAGE_ERROR
};

/**
 * @brief  按键按下
 * @param  KeyNum 按键值
 * @retval 无
 */
void Command_KeyPressed(uint8_t KeyNum)
{
    Execute_KeyPressed(KeyNum);
}

/**
 * @brief  启动系统
 * @retval 无
 */
void Command_Start(void)
{
    int len = 0;
    uint16_t *duties = Execute_GetDuties(&len);
    Execute_SetDuties(duties, len);
}

/**
 * @brief  发送成功信息
 * @retval 无
 */
void Command_SendSuccess(void)
{
    printf("%d\r\n", MESSAGE_SUCCESS);
}

/**
 * @brief  发送字符串
 * @param  Info 信息内容
 * @retval 无
 */
void Command_SendString(char* Info)
{
    printf("%d %s\r\n", MESSAGE_SUCCESS, Info);
}

/**
 * @brief  发送10进制数字
 * @param  Num 数字
 * @retval 无
 */
void Command_SendNum(int Num)
{
    printf("%d %d\r\n", MESSAGE_SUCCESS, Num);
}

/**
 * @brief  发送16进制数字
 * @param  HexNum 数字
 * @retval 无
 */
void Command_SendHexNum(int HexNum)
{
    printf("%d %x\r\n", MESSAGE_SUCCESS, HexNum);
}

/**
 * @brief  发送失败信息
 * @retval 无
 */
void Command_SendError(void)
{
    printf("%d\r\n", MESSAGE_ERROR);
}

/**
* @brief  执行指定命令
* @param Bytes 数组
* @retval 无
*/
void Command_Execute(uint8_t Bytes[])
{
    uint8_t cmd = Bytes[0];
    switch (cmd)
    {
    // <cn>
    case COMMAND_STATUS:
        Command_SendString(Execute_Status());
        break;
    // <cn><ln><n>
    case COMMAND_SET_DUTY:
        Execute_SetDuty(Bytes[1], Bytes[2]);
        Command_SendSuccess();
        break;
    // <cn><ln>
    case COMMAND_GET_DUTY:
        Command_SendHexNum(Execute_GetDuty(Bytes[1]));
        break;
    // <cn><ln>
    case COMMAND_ON:
        Execute_On(Bytes[1]);
        Command_SendSuccess();
        break;
    // <cn><ln>
    case COMMAND_OFF:
        Execute_Off(Bytes[1]);
        Command_SendSuccess();
        break;
    // <cn>
    case COMMAND_ALL_ON:
        Execute_AllOn();
        Command_SendSuccess();
        break;
    // <cn>
    case COMMAND_ALL_OFF:
        Execute_AllOff();
        Command_SendSuccess();
        break;
    // <cn><kn>
    case COMMAND_KEY_PRESSED:
        Execute_KeyPressed(Bytes[1]);
        Command_SendString(Execute_Status());
        break;
    // <cn>
    case COMMAND_RESET:
        Execute_Reset();
        break;
    // <cn>
    case COMMAND_RESTART:
        Execute_Restart();
        break;
    default:
        break;
    }
}
