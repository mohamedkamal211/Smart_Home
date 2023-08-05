
#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_


#define TCCR0               *((volatile u8*)0x53)
#define TCCR0_WGM00         6
#define TCCR0_WGM01         3
#define TCCR0_CS02          2
#define TCCR0_CS01          1
#define TCCR0_CS00          0

#define OCR0                *((volatile u8*)0x5C)

#define TIMSK               *((volatile u8*)0x59)
#define TIMSK_OCIE0         1


#define TCCR1A               *((volatile u8*)0x4F)
#define TCCR1A_WGM10         0
#define TCCR1A_WGM11         1
#define TCCR1A_COM1A1        7
#define TCCR1A_COM1A0        6


#define TCCR1B               *((volatile u8*)0x4E)
#define TCCR1B_WGM13         4
#define TCCR1B_WGM12         3





#define ICR1                 *((volatile u16*)0x46)
#define OCR1A                *((volatile u16*)0x4A)


#endif
