#include "STD_Types.h"
#include "BIT_MATHS.h"

#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"
#include "USART_register.h"

void USART_voidInit(void){
	u8 Local_u8UCRCValue=0;
	SET_BIT(Local_u8UCRCValue,UCSRC_URSEL);
	SET_BIT(Local_u8UCRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCRCValue,UCSRC_UCSZ0);
	UCSRC = Local_u8UCRCValue;

	//Enable Receive mode
	SET_BIT(UCSRB,UCSRB_RXEN);
	//Enable Transmission mode
	SET_BIT(UCSRB,UCSRB_TXEN);
	//Speed is 9600bps
	UBRRL = 51;

}

void USART_voidSend(u8 Copy_u8Data){
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR = Copy_u8Data;

}

u8 USART_u8Reading(void){
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}






