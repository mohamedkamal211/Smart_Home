#include "STD_Types.h"
#include "BIT_MATHS.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "KPD_interface.h"
#include "CLCD_interface.h"
#include "USART_interface.h"
#include "ADC_interface.h"
#include "TIMER0_interface.h"

#include <util/delay.h>


int main(){
	PORT_voidInit();
	CLCD_voidInit();
	USART_voidInit();
	ADC_voidInit();
	Timer1_voidInit();
	u8 Local_u8Key[4];
	u8 arr[] = {1,2,3,4};
	u8 Local_u8Counter = 0;
	u8 Local_u8Data;
	u8 Local_u8Reading;
	Timer_voidSetICR1(20000);


	while(1){

		if(Local_u8Counter == 0){

			CLCD_voidgoToXY(0,3);
			CLCD_voidSendSting("Welcome");
			_delay_ms(3000);
			Local_u8Counter++;

		}
		if(Local_u8Counter == 1){
			CLCD_voidSendCommand(1);
			CLCD_voidgoToXY(0,0);
			CLCD_voidSendSting("Enter ID: ");
			for(u8 i=0;i<4;i++){
				do{
					Local_u8Key[i] = KPD_u8GetPressedKey();
				}while(Local_u8Key[i] == 0xff);
				if(Local_u8Key[i] == arr[i]){

					CLCD_voidgoToXY(1,i);
					CLCD_voidWriteNumber(Local_u8Key[i]);
				}
				if(i == 3){
					_delay_ms(300);
					Local_u8Counter++;
					break;
				}

			}
			for(int j=0;j<3;j++){
				if(Local_u8Counter == 2){

					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,0);
					CLCD_voidSendSting("Enter Pass: ");
					for(u8 i=0;i<4;i++){
						do{
							Local_u8Key[i] = KPD_u8GetPressedKey();
						}while(Local_u8Key[i] == 0xff);
						if(Local_u8Key[i] == arr[3-i]){

							CLCD_voidgoToXY(1,i);
							CLCD_voidWriteNumber(Local_u8Key[i]);
							_delay_ms(100);
							CLCD_voidgoToXY(1,i);
							CLCD_voidSendSting(" ");
							CLCD_voidgoToXY(1,i);
							CLCD_voidSendData('*');
							if(i == 3){
								_delay_ms(300);
								Local_u8Counter++;
								break;
							}

						}
						else if(Local_u8Key[i] != arr[3-i]){
							//
							CLCD_voidgoToXY(1,i);
							CLCD_voidWriteNumber(Local_u8Key[i]);
							_delay_ms(100);
							CLCD_voidgoToXY(1,i);
							CLCD_voidSendSting(" ");
							CLCD_voidgoToXY(1,i);
							CLCD_voidSendData('*');
							if(i == 3){
								if(j == 2){
									CLCD_voidSendCommand(1);
									CLCD_voidgoToXY(0,0);
									CLCD_voidSendSting("You are not User");
								}

								_delay_ms(300);
								CLCD_voidSendCommand(1);
								CLCD_voidgoToXY(0,0);
								CLCD_voidSendSting("Wrong Pass!");
								_delay_ms(2000);


							}
						}


					}
				}
				if(Local_u8Counter == 3){

					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,2);
					CLCD_voidSendSting("Welcome to");
					CLCD_voidgoToXY(1,2);
					CLCD_voidSendSting("Smart home");
					_delay_ms(2000);
					Local_u8Counter++;
				}

				if(Local_u8Counter == 4){
					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,0);
					CLCD_voidSendSting("Choose Options:");
					CLCD_voidgoToXY(1,0);
					CLCD_voidSendSting("from 1 to 8");
					_delay_ms(1000);
					Local_u8Counter++;

				}

				if(Local_u8Counter == 5){

					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,0);
					CLCD_voidSendSting("1-Open the Light");
					CLCD_voidgoToXY(1,0);
					CLCD_voidSendSting("2-Close the Light");
					_delay_ms(1000);
					Local_u8Counter++;

				}
				if(Local_u8Counter == 6){

					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,0);
					CLCD_voidSendSting("3-Play music");
					CLCD_voidgoToXY(1,0);
					CLCD_voidSendSting("4-Open the fan");
					_delay_ms(1000);
					Local_u8Counter++;

				}
				if(Local_u8Counter == 7){

					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,0);
					CLCD_voidSendSting("5-Close The fan");
					CLCD_voidgoToXY(1,0);
					CLCD_voidSendSting("6-Adjust the fan");
					_delay_ms(1000);
					Local_u8Counter++;

				}
				if(Local_u8Counter == 8){

					CLCD_voidSendCommand(1);
					CLCD_voidgoToXY(0,0);
					CLCD_voidSendSting("7-Open The door");
					CLCD_voidgoToXY(1,0);
					CLCD_voidSendSting("8-Close the door");
					_delay_ms(1000);
					Local_u8Counter++;

				}


			}

		}

		Local_u8Data = USART_u8Reading();
		if(Local_u8Data > '0'){
			if(Local_u8Data == '1'){
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);

			}
			else if(Local_u8Data == '2'){
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);

			}
			else if(Local_u8Data == '3'){
				for(u8 i=1;i<100;i++){
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
					_delay_us(50*i);
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
					_delay_us(1000*i);


				}
			}
			else if(Local_u8Data == '4'){
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
			}
			else if(Local_u8Data == '5'){
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
			}


			else if(Local_u8Data == '6'){
			    ADC_u8StartConversionSync(0,&Local_u8Reading);
				u8 Voltage = (u16)((u32)(Local_u8Reading*5000UL))/256UL;
				u8 Temp = Voltage/10;
				CLCD_voidSendCommand(1);
				CLCD_voidgoToXY(0,0);
				CLCD_voidSendSting("Temp= ");
				CLCD_voidgoToXY(0,5);
				CLCD_voidWriteNumber(Local_u8Reading);
				CLCD_voidgoToXY(0,7);
				CLCD_voidSendData('C');
				if(Temp > 15){
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
				}
				else{
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
				}
			}
			else if(Local_u8Data == '7'){

				for(u8 i=750;i<2500;i++){
					Timer_voidSetOCR1A(i);
					_delay_ms(10);
				}
			}

		}


	}


}






