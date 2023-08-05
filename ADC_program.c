#include "STD_Types.h"
#include "BIT_MATHS.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_register.h"


u8 ADC_u8BusyState = IDLE;
static u8 *ADC_pu8Reading = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;
static u8 *ADC_pu8ChainChannelArr=NULL;
static u8 ADC_u8ChainSize;
static u16 *ADC_pu16ChainResultArr=NULL;
static u8 ADC_u8ChainArrayIndex=0;
static u8 ADC_u8ISRSource;

void ADC_voidInit(void){

#if ADC_VOLTAGE_REFRENCE == AREF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	CLR_BIT(ADMUX,ADMUX_REFS0);
#elif ADC_VOLTAGE_REFRENCE == AVCC
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#elif ADC_VOLTAGE_REFRENCE == INT_VOLTAGE_REF
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#else
#error "Wrong ADC_VOLTAGE_REFRENCE configuration option"
#endif




#if ADC_ADJUST == LEFT_ADJUST
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_ADJUST == RIGHT_ADJUST
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong ADC_ADJUST configuration option"
#endif


	/*Set PreScaler*/
	ADCSRA &= BIT_MASKING_1;
	ADCSRA |= ADC_PRESCALER;





	/*Enable ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);




}
u8 ADC_u8StartConversionSync(u8 Copy_u8Channel,u8 *Copy_pu8Reading){

	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState = OK;
	if(ADC_u8BusyState == IDLE){
		/*Pass Channel to ADMUX*/
		ADC_u8BusyState = BUSY;
		ADMUX &= BIT_MASKING_2;
		ADMUX |= Copy_u8Channel;
		/*Start Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/*Polling (busy waiting until flag is raised)*/
		while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_u32Counter != TIME_OUT)){
			Local_u32Counter++;
		}
		if(Local_u32Counter == TIME_OUT){
			//Loop is broken because time out is reaching
			Local_u8ErrorState = NOK;
		}

		else{
			SET_BIT(ADCSRA,ADCSRA_ADIF);
#if ADC_RESOLUTION == EIGHT_BIT
			*Copy_pu8Reading = ADCH;
			ADC_u8BusyState = IDLE;

#elif ADC_RESOLUTION == TEN_BIT
			*Copy_pu8Reading = ADC;
			ADC_u8BusyState = IDLE;
#else
#error "Wrong ADC_RESOLUTION configuration option"

#endif

		}
	}
	else{
		Local_u8ErrorState = BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsync(u8 Copy_u8Channel,u8 *Copy_pu8Reading,void(*Copy_pvNotificationFunc)(void)){
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState == IDLE){
		if((Copy_pu8Reading == NULL ) || (Copy_pvNotificationFunc == NULL)){
			Local_u8ErrorState = NULL_POINTER;
		}
		else{
			ADC_u8BusyState = BUSY;
			/*Make ISR Source SINGLE_CHANNEL_ASYNCH*/
			ADC_u8ISRSource = SINGLE_CHANNEL_ASYNC;
			ADC_pu8Reading = Copy_pu8Reading;
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Pass Channel to ADMUX*/
			ADMUX &= BIT_MASKING_2;
			ADMUX |= Copy_u8Channel;
			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*Enable Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);



		}


	}
	else {
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
u8 ADC_u8StartChainConversionAsync(Chain_t *Copy_Chain){
	u8 Local_u8Errorstate = OK;
	if(Copy_Chain == NULL){

		Local_u8Errorstate = NULL_POINTER;
	}
	else{
		if(ADC_u8BusyState == IDLE){

			/*Make ADC Busy*/
			ADC_u8BusyState = BUSY;
			/*Make ISR Source CHAIN_CHANNEL_ASYNCH*/
			ADC_u8ISRSource = CHAIN_CHANNEL_ASYNC;
			/*Initialize Chain Channel Array*/
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;
			/*Initialize Chain Channel Result*/
			ADC_pu16ChainResultArr = Copy_Chain->Result;
			/*Initialize Chain Size*/
			ADC_u8ChainSize = Copy_Chain->Size;
			/*Initialize Notification Function*/
			ADC_pvCallBackNotificationFunc = Copy_Chain->NotificationFunc;
			/*Initialize Current Conversion Index*/
			ADC_u8ChainArrayIndex = 0;

			ADMUX &= BIT_MASKING_2;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainArrayIndex];

			SET_BIT(ADCSRA,ADCSRA_ADSC);

			SET_BIT(ADCSRA,ADCSRA_ADIE);




		}
		else{

			Local_u8Errorstate = BUSY_FUNC;

		}
	}


	return Local_u8Errorstate;
}

void __vector_16 (void)            __attribute__((signal));
void __vector_16 (void){

	if(ADC_u8ISRSource == SINGLE_CHANNEL_ASYNC){

#if ADC_RESOLUTION == EIGHT_BIT
		*ADC_pu8Reading = ADCH;
		ADC_u8BusyState = IDLE;

#elif ADC_RESOLUTION == TEN_BIT
		*ADC_pu8Reading = ADC;
		ADC_u8BusyState = IDLE;
#else
#error "Wrong ADC_RESOLUTION configuration option"

#endif

		ADC_pvCallBackNotificationFunc();

		CLR_BIT(ADCSRA,ADCSRA_ADIE);

	}
	else if(ADC_u8ISRSource == CHAIN_CHANNEL_ASYNC){

		//read the current conversion
		ADC_pu16ChainResultArr[ADC_u8ChainArrayIndex] = ADCH;
		//Increment Chain Index
		ADC_u8ChainArrayIndex++;
		//Check if Conversion finished or not
		if(ADC_u8ChainArrayIndex == ADC_u8ChainSize){
			//ADC is IDLE
			ADC_u8BusyState = IDLE;
			//Invoke Notification Function
			ADC_pvCallBackNotificationFunc();
			//Disable ADC Interrupt
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else {
			//Set New Channel
			ADMUX &= BIT_MASKING_2;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainArrayIndex];
			//Start Conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}



	}
}
s32 Mapping(s32 Copy_s32InputMin,s32 Copy_s32InputMax,s32 Copy_s32OutputMin,s32 Copy_s32OutputMax,s32 Copy_s32InputValue){

	u8 Local_u8Val;
	Local_u8Val = ((Copy_s32OutputMax-Copy_s32OutputMin)*(Copy_s32InputValue-Copy_s32InputMin)/(Copy_s32InputMax-Copy_s32InputMin))+Copy_s32OutputMin;
	return Local_u8Val;
}






