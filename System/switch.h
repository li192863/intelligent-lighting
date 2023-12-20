#ifndef __SWITCH_H
#define __SWITCH_H

uint16_t* Switch_GetKeyMask(uint8_t KeyNum);
uint16_t Switch_GetNextDuty(uint16_t CurrentDuties[], uint16_t Mask[], int Len);

#endif
