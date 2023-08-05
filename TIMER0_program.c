#include "STD_Types.h"
#include "BIT_MATHS.h"

#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_register.h"


void (*TIMER0_pvCallBackFunc)(void) = NULL;

void Timer_voidInit(void){

	SET_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);


	SET_BIT(TIMSK,TIMSK_OCIE0);

	OCR0 = 250;

	CLR_BIT(TCCR0,TCCR0_CS02);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS00);




}


u8 Timer_u8SetcallBack(void(*Copy_pvCallbackFunc)(void)){

	u8 Local_u8ErrorState = OK;
	if(Copy_pvCallbackFunc != NULL){

		TIMER0_pvCallBackFunc = Copy_pvCallbackFunc;

	}
	else{

		Local_u8ErrorState = NULL_POINTER;

	}


	return Local_u8ErrorState;
}
void Timer1_voidInit(void){
	//Set Fast PWM Non_Inverted Mode
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//Set Wave Form Generation For fast PWM
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
	SET_BIT(TCCR1A,TCCR1A_WGM11);

	//Set Prescaler as Divide By 8
	TCCR1B &= BIT_MASK;
	TCCR1B |= DIVIDE_BY_8;




}
void Timer_voidSetICR1(u16 Copy_u16ICR1Val){

	ICR1 = Copy_u16ICR1Val;

}
void Timer_voidSetOCR1A(u16 Copy_u16OCR1Val){

	OCR1A = Copy_u16OCR1Val;

}


void __vector_10(void)     __attribute__((signal));
void __vector_10(void){

	if(TIMER0_pvCallBackFunc != NULL){

		TIMER0_pvCallBackFunc();

	}

}
