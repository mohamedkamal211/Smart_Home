
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


typedef struct{
	u8*Channel;
	u16*Result;
	u8 Size;
	void(*NotificationFunc)(void);
}Chain_t;




void ADC_voidInit(void);

u8 ADC_u8StartConversionSync(u8 Copy_u8Channel,u8 *Copy_pu8Reading);
u8 ADC_u8StartConversionAsync(u8 Copy_u8Channel,u8 *Copy_pu8Reading,void(*Copy_pvNotificationFunc)(void));
u8 ADC_u8StartChainConversionAsync(Chain_t *Copy_Chain);
s32 Mapping(s32 Copy_s32InputMin,s32 Copy_s32InputMax,s32 Copy_s32OutputMin,s32 Copy_s32OutputMax,s32 Copy_s32InputValue);

#endif
