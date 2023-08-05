#include "STD_Types.h"
#include "BIT_MATHS.h"

#include "GIE_interface.h"
#include "GIE_private.h"
#include "GIE_register.h"
#include "GIE_config.h"


void GIE_voidEnable(void){

	SET_BIT(SREG,SREG_I);

}
void GIE_voidDisable(void){

	CLR_BIT(SREG,SREG_I);

}

