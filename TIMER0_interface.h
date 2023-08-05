
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


void Timer_voidInit(void);


u8 Timer_u8SetcallBack(void(*Copy_pvCallbackFunc)(void));

void Timer1_voidInit(void);
void Timer_voidSetICR1(u16 Copy_u16ICR1Val);
void Timer_voidSetOCR1A(u16 Copy_u16OCR1Val);


#endif
