#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_



#define CLCD_DATA_PORT       DIO_u8PORTC

#define CLCD_CTRL_PORT       DIO_u8PORTD

#define CLCD_RS_PIN          DIO_u8PIN2
#define CLCD_RW_PIN          DIO_u8PIN3
#define CLCD_E_PIN           DIO_u8PIN4


#define CLCD_DATA0_PIN       DIO_u8PIN0
#define CLCD_DATA1_PIN       DIO_u8PIN1
#define CLCD_DATA2_PIN       DIO_u8PIN2
#define CLCD_DATA3_PIN       DIO_u8PIN3
#define CLCD_DATA4_PIN       DIO_u8PIN4
#define CLCD_DATA5_PIN       DIO_u8PIN5
#define CLCD_DATA6_PIN       DIO_u8PIN6
#define CLCD_DATA7_PIN       DIO_u8PIN7

/* Two mode you can use :
                            1-8_bit_mode
                            2-4_bit_mode
                                                */
#define CLCD_MODE            EIGHT_BIT_MODE





#endif


