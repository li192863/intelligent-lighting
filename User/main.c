#include "stm32f10x.h" // Device header
#include "system.h"


int main(void)
{
    // 初始化
    System_Init();
    while (1)
    {
        System_MainLoop();
    }
}
