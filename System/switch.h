#ifndef __SWITCH_H
#define __SWITCH_H

uint16_t* Switch_GetKeyMapping(uint8_t KeyNum);
uint16_t Switch_GetGroupStatus(uint8_t KeyNum, uint16_t switches[]);
uint16_t Switch_Arbitration(uint8_t KeyNum, uint16_t switches[]);

#endif
