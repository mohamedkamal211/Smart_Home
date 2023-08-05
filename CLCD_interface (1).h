
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidInit();
void CLCD_voidSendSting(const char*Copy_pcString);
void CLCD_voidgoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);
void CLCD_voidWriteSpecialcharacters(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos);
void CLCD_voidWriteNumber(u32 Copy_u32Number);

#endif
