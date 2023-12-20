#ifndef __EXECUTE_H
#define __EXECUTE_H

void Execute_Status(void);

void Execute_SetDuties(uint16_t Duties[], int Len);
void Execute_SetMaskedDuties(uint16_t Mask[], int Len, uint16_t Duty);
void Execute_SetDuty(uint8_t i, uint16_t Duty);
uint16_t* Execute_GetDuties(int *Len);
uint16_t Execute_GetDuty(uint8_t i);

void Execute_On(uint8_t i);
void Execute_Off(uint8_t i);
void Execute_AllOn(void);
void Execute_AllOff(void);

void Execute_KeyPressed(uint8_t KeyNum);
void Execute_Reset(void);

#endif
