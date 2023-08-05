
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT                        DIO_u8PORTB

#define KPD_COLUMN0                     DIO_u8PIN0
#define KPD_COLUMN1                     DIO_u8PIN1
#define KPD_COLUMN2                     DIO_u8PIN2
#define KPD_COLUMN3                     DIO_u8PIN3

#define KPD_ROW0                        DIO_u8PIN4
#define KPD_ROW1                        DIO_u8PIN5
#define KPD_ROW2                        DIO_u8PIN6
#define KPD_ROW3                        DIO_u8PIN7


#define KPD_NOT_PRESSED_KEY              0xff
#define KPD_ARR_VAL                      {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};


#endif
