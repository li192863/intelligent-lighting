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
  // 设置当前某灯亮度，<cn><ln><n> 0x02017f
  SET_DUTY,
  // 获取当前亮度 <cn><ln> 0x0301
  GET_DUTY,
  // 开启某灯 <cn><ln> 0x0401
  ON,
  // 关闭某灯 <cn><ln> 0x0501
  OFF,
  // 全部开启 <cn> 0x06
  ALL_ON,
  // 全部关闭 <cn> 0x07
  ALL_OFF,
  // 模拟按键按下 <cn><kn> 0x0801
  KEY_PRESSED,
  // 重置系统 <cn> 0x09
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
    int len = 0;
    uint16_t *duties = Execute_GetDuties(&len);
    Execute_SetDuties(duties, len);
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
    case SET_DUTY:
        Execute_SetDuty(Bytes[1], Bytes[2]);
        break;
    // <cn><ln>
    case GET_DUTY:
        printf("%4d\r\n", Execute_GetDuty(Bytes[1]));
        break;
    // <cn><ln>
    case ON:
        Execute_On(Bytes[1]);
        break;
    // <cn><ln>
    case OFF:
        Execute_Off(Bytes[1]);
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
