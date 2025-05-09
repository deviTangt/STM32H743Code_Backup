#ifndef _AD7705_H_
#define _AD7705_H_

void AD7705_CalibSelf(uint8_t _ch);
void AD7705_Init(void);
void AD7705_WriteByte(uint8_t data);
uint16_t AD7705_ReadAdc(uint8_t _ch);
void AD7705_ResetHard(void);	
void AD7705_SyncSPI(void);
uint8_t AD7705_ReadByte(void);
uint16_t AD7705_Read2Byte(void);
uint32_t AD7705_Read3Byte(void);

#endif