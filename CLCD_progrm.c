#include "STD_Types.h"
#include "BIT_MATHS.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_priavate.h"




void CLCD_voidSendCommand(u8 Copy_u8Command){
#if CLCD_MODE == EIGHT_BIT_MODE
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
#elif
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	DIO_u8SetPortValue(CLCD_DATA0_PIN,Copy_u8Command);
	DIO_u8SetPortValue(CLCD_DATA1_PIN,Copy_u8Command);
	DIO_u8SetPortValue(CLCD_DATA2_PIN,Copy_u8Command);
	DIO_u8SetPortValue(CLCD_DATA3_PIN,Copy_u8Command);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

#else
#error "Your Configuration is Wrong"
#endif

}
void CLCD_voidSendData(u8 Copy_u8Data){
#if CLCD_MODE == EIGHT_BIT_MODE

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
#elif
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	DIO_u8SetPortValue(CLCD_DATA0_PIN,Copy_u8Data);
	DIO_u8SetPortValue(CLCD_DATA1_PIN,Copy_u8Data);
	DIO_u8SetPortValue(CLCD_DATA2_PIN,Copy_u8Data);
	DIO_u8SetPortValue(CLCD_DATA3_PIN,Copy_u8Data);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

#else
#error "Your Configuration is Wrong"
#endif


}

void CLCD_voidInit(){
#if CLCD_MODE == EIGHT_BIT_MODE

	_delay_ms(40);

	/*Function Set*/
	CLCD_voidSendCommand(0b00111000);

	/*Display ON/OFF Control*/
	CLCD_voidSendCommand(0b00001100);

	/*Display Clear*/
	CLCD_voidSendCommand(1);

#elif CLCD_MODE == FOUR_BIT_MODE
	_delay_ms(40);

	/*Function Set*/
	CLCD_voidSendCommand(0b00100000);
	CLCD_voidSendCommand(0b00100000);
	CLCD_voidSendCommand(0b10000000);
	/*Display ON/OFF Control*/
	CLCD_voidSendCommand(0);
	CLCD_voidSendCommand(0b11000000);

	/*Display Clear*/
	CLCD_voidSendCommand(0);
	CLCD_voidSendCommand(0b00010000);

#else
#error "Your Configuration is Wrong"
#endif
}


void CLCD_voidSendSting(const char*Copy_pcString){
	//	/* Local loop index */
	//	u8 u8Index = 0;
	u8 iteration=0;
	//	while (pu8StringCpy[u8Index] != '\0')
	while( Copy_pcString[iteration] != '\0' )
	{

		/* Write Character on LCD */
		CLCD_voidSendData(Copy_pcString[iteration]);

		iteration++;

		_delay_ms(2);

	}




}

void CLCD_voidgoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos){
	u8 Local_u8Adress;
	if(Copy_u8XPos==0){
		Local_u8Adress=Copy_u8YPos;
	}
	if(Copy_u8XPos==1){
		Local_u8Adress=Copy_u8YPos+0x40;
	}

	CLCD_voidSendCommand(Local_u8Adress+128);



}

void CLCD_voidWriteSpecialcharacters(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos){
	u8 Local_u8Address=0;
	u8 Local_u8Iterrator;
	Local_u8Address = Copy_u8PatternNumber*8;
	CLCD_voidSendCommand(Local_u8Address+64);
	for(Local_u8Iterrator=0;Local_u8Iterrator<8;Local_u8Iterrator++){
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterrator]);
	}
	CLCD_voidgoToXY(Copy_u8XPos,Copy_u8YPos);
	CLCD_voidSendData(Copy_u8PatternNumber);
}


void CLCD_voidWriteNumber(u32 Copy_u32Number){

	u8 Local_u8Digit1,Local_u8Digit2,Local_u8Digit3,Local_u8Digit4;

	/*write digit1*/
	if(Copy_u32Number<10){
		CLCD_voidSendData(Copy_u32Number+'0');
	}
	/*write digit2*/
	else if(Copy_u32Number<100){

		Local_u8Digit1 = Copy_u32Number/10;
		CLCD_voidSendData(Local_u8Digit1+'0');

		Local_u8Digit2 = Copy_u32Number%10;
		CLCD_voidSendData(Local_u8Digit2+'0');
	}
	/*write digit3*/
	else if(Copy_u32Number<1000){
		Local_u8Digit1 = Copy_u32Number/100;
		CLCD_voidSendData(Local_u8Digit1+'0');

		Local_u8Digit2 = Copy_u32Number%100;
		Local_u8Digit2 = Local_u8Digit2/10;
		CLCD_voidSendData(Local_u8Digit2+'0');


		Local_u8Digit3 = Copy_u32Number%100;
		Local_u8Digit3 = Local_u8Digit3%10;
		CLCD_voidSendData(Local_u8Digit3+'0');
	}
	/*write digit4*/
	else if(Copy_u32Number<10000){

		Local_u8Digit1 = Copy_u32Number/1000;
		CLCD_voidSendData(Local_u8Digit1+'0');

		Local_u8Digit2 = Copy_u32Number%1000;
		Local_u8Digit2 = Local_u8Digit2/100;
		CLCD_voidSendData(Local_u8Digit2+'0');


		Local_u8Digit3 = Copy_u32Number%100;
		Local_u8Digit3 = Local_u8Digit3/10;
		CLCD_voidSendData(Local_u8Digit3+'0');

		Local_u8Digit4 = Copy_u32Number%10;
		CLCD_voidSendData(Local_u8Digit4+'0');
	}
}





