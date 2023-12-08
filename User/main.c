#include <string.h>
#include "stm32f10x.h" // Device header
#include "system.h"
#include "delay.h"
#include "serial.h"
#include "pwm.h"
#include "key.h"
#include "defs.h"


int main(void)
{
    // 初始化
    System_Init();
    Serial_Init();
    PWM_Init();
    Key_Init();
    
    while (1)
    {
        uint8_t KeyNum = Key_GetNum();
        if (Serial_RxFlag == 1)
        {
            Serial_SendString(Serial_RxPacket);
            Serial_RxFlag = 0;
        }

        // for (int i = 0; i <= 100; i++) {
        //     PWM_SetDuty(light_num, i);
        //     Delay_ms(10);
        // }
        // for (int i = 0; i <= 100; i++) {
        //     PWM_SetDuty(light_num, 100 - i);
        //     Delay_ms(10);
        // }
    }
}
