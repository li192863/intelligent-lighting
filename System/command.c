#include <stdio.h>
#include "stm32f10x.h"                  // Device header
#include "defs.h"
#include "execute.h"

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

/**
 * @brief  按键按下
 * @param KeyNum 按键值
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
    for (int i = 0; i < DUTY_LEN; i++)
    {
        uint8_t switch_ = Execute_GetSwitch(i + 1);
        uint16_t duty = switch_ ? Execute_GetStoredDuty(i + 1) : MIN_DUTY;
        Execute_SetCurrentDuty(i + 1, duty);
    }
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
    case STATUS:
        Execute_Status();
        break;
    // <cn><ln><n>
    case SET_CURRENT_DUTY:
        // Deprecated, do NOT use this function to avoid unsatisfying results.
        // 编写这个函数的目的是配合开关使用，使用命令方式传入会产生不符合预期的结果
        // Execute_SetCurrentDuty(Bytes[1], Bytes[2]);
        break;
    // <cn><ln>
    case GET_CURRENT_DUTY:
        printf("%4d\r\n", Execute_GetCurrentDuty(Bytes[1]));
        break;
    // <cn><ln><n>
    case SET_STORED_DUTY:
        Execute_SetStoredDuty(Bytes[1], Bytes[2]);
        break;
    // <cn><ln>
    case GET_STORED_DUTY:
        printf("%4d\r\n", Execute_GetStoredDuty(Bytes[1]));
        break;
    // <cn><ln><n>
    case SET_SWITCH:
        Execute_SetSwitch(Bytes[1], Bytes[2]);
        break;
    // <cn><ln>
    case GET_SWITCH:
        printf("%4d\r\n", Execute_GetSwitch(Bytes[1]));
        break;
    // <cn><ln>
    case ON:
        Execute_On(Bytes[1]);
        break;
    // <cn><ln>
    case OFF:
        Execute_Off(Bytes[1]);
        break;
    // <cn><ln>
    case TURN:
        Execute_Turn(Bytes[1]);
        break;
    // <cn>
    case ALL_ON:
        Execute_AllOn();
        break;
    // <cn>
    case ALL_OFF:
        Execute_AllOff();
        break;
    // <cn><kn>
    case KEY_PRESSED:
        Execute_KeyPressed(Bytes[1]);
        break;
    // <cn>
    case MY_RESET:
        Execute_Reset();
        break;
    default:
        break;
    }
}
