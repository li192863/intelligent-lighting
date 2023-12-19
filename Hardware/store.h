#ifndef __STORE_H
#define __STORE_H

extern uint16_t Store_Data[];

void Store_Init(void);
void Store_Write(void);
void Store_Read(void);
void Store_Clear(void);
void Store_PrintStoreData(void);

void Store_WriteDuties(uint16_t Duties[], int Len);
void Store_WriteMaskedDuties(uint16_t Mask[], int Len, uint16_t Duty);
uint16_t* Store_ReadDuties(void);
void Store_WriteDuty(uint8_t i, uint16_t Duty);
uint16_t Store_ReadDuty(uint8_t i);
void Store_WriteSwitches(uint16_t Switches[], int Len);
void Store_WriteMaskedSwitches(uint16_t Mask[], int Len, uint16_t Switch);
uint16_t* Store_ReadSwitches(void);
void Store_WriteSwitch(uint8_t i, uint16_t Switch);
uint16_t Store_ReadSwitch(uint8_t i);

#endif
