#ifndef __EXECUTE_H
#define __EXECUTE_H

void Execute_Status(void);

void Execute_SetCurrentDuty(uint8_t i, uint16_t Duty);
uint16_t Execute_GetCurrentDuty(uint8_t i);
void Execute_SetStoredDuty(uint8_t i, uint16_t Duty);
uint16_t Execute_GetStoredDuty(uint8_t i);

void Execute_SetSwitch(uint8_t i, uint8_t switch_);
uint8_t Execute_GetSwitch(uint8_t i);
void Execute_On(uint8_t i);
void Execute_Off(uint8_t i);
void Execute_Turn(uint8_t i);

void Execute_OnBatch(uint16_t Mask[], int Len);
void Execute_OffBatch(uint16_t Mask[], int Len);
void Execute_AllOn(void);
void Execute_AllOff(void);

void Execute_KeyPressed(uint8_t KeyNum);
void Execute_Reset(void);

#endif
