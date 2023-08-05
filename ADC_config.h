
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_





#define TIME_OUT                                 50000
/* options:

            * AVCC
            * AREF
            * INT_VOLTAGE_REF(2.56)      */

#define ADC_VOLTAGE_REFRENCE                     AVCC


/* options:

            * SINGLE_CONVERSION
            * FREE_RUNNING               */

#define ADC_CONVERSION_MODE                      SINGLE_CONVERSION

/* options:
            *DEVISION_BY_2
            *DEVISION_BY_4
            *DEVISION_BY_8
            *DEVISION_BY_16
            *DEVISION_BY_32
            *DEVISION_BY_64
            *DIVISION_BY_128             */

#define ADC_PRESCALER                            DIVISION_BY_128


/* options:
            *LEFT_ADJUST
            *RIGHT_ADJUST                */

#define ADC_ADJUST                               LEFT_ADJUST

/* options:
            *EIGHT_BIT
            *TEN_BIT                     */

#define ADC_RESOLUTION                            EIGHT_BIT







#endif
