#include "STD_Types.h"
#include "BIT_MATHS.h"

#include "DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"
#include <util/delay.h>


u8 KPD_u8GetPressedKey(void){
	u8 Local_u8PressedKey = KPD_NOT_PRESSED_KEY;
	u8 KPDARR[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL;
	u8 Local_u8ColumnIdx,Local_u8RowIdx,Local_u8StatePin;
	u8 KPD_COLUMN[COLUMN_NUM] = {KPD_COLUMN0,KPD_COLUMN1,KPD_COLUMN2,KPD_COLUMN3};
	u8 KPD_ROW[ROW_NUM] = {KPD_ROW0,KPD_ROW1,KPD_ROW2,KPD_ROW3};

	for(Local_u8ColumnIdx = 0;Local_u8ColumnIdx<COLUMN_NUM;Local_u8ColumnIdx++){
		/*Activate Column Current*/
		DIO_u8SetPinValue(KPD_PORT,KPD_COLUMN[Local_u8ColumnIdx],DIO_u8PIN_LOW);
		for(Local_u8RowIdx = 0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++){
			//Read Row Pins
			DIO_u8GetPinValue(KPD_PORT,KPD_ROW[Local_u8RowIdx],&Local_u8StatePin);
			//Check if switch is pressed
			if(DIO_u8PIN_LOW == Local_u8StatePin){
				Local_u8PressedKey = KPDARR[Local_u8RowIdx][Local_u8ColumnIdx];
				//polling(busy waiting until key is released
				while(DIO_u8PIN_LOW == Local_u8StatePin){
					DIO_u8GetPinValue(KPD_PORT,KPD_ROW[Local_u8RowIdx],&Local_u8StatePin);
				}
				return Local_u8PressedKey;
			}

		}

		//Deactivate Columns Current
		DIO_u8SetPinValue(KPD_PORT,KPD_COLUMN[Local_u8ColumnIdx],DIO_u8PIN_HIGH);
	}

	return Local_u8PressedKey;
}


