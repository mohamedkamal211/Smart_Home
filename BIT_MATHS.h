#ifndef BIT_MATH
#define BIT_MATH

		#define SET_BIT(BYTE,Bit_NO) (BYTE) |= (1<<(Bit_NO))
		#define CLR_BIT(BYTE,Bit_NO) (BYTE) &= ~(1<<(Bit_NO))
		#define TOGGEL_BIT(BYTE,Bit_NO) (BYTE) ^= 1<<(Bit_NO)
		#define GET_BIT(BYTE,Bit_NO) ((BYTE>>Bit_NO)&(0x01))
		
		#define SET_BYTE(Byte) (Byte |=(0xFF))
		#define CLEAR_BYTE(Byte) (Byte &=(0x00))
		#define TOGGEL_BYTE(BYTE) (BYTE = ~ BYTE)
		#define SET_NIBBLE_HIGH(Byte) (Byte |=(0xF0))
		#define SET_NIBBLE_LOW(Byte) (Byte |=(0x0F))
		#define CLEAR_NIBBLE_HIGH(Byte) (Byte &=(0x0F))
		#define CLEAR_NIBBLE_LOW(Byte) (Byte &=(0xF0))
		
		
		#define BIT_CONC(P7,P6,P5,P4,P3,P2,P1,P0)  CONC_HELP(P7,P6,P5,P4,P3,P2,P1,P0)
		#define CONC_HELP(P7,P6,P5,P4,P3,P2,P1,P0)  0b##P7##P6##P5##P4##P3##P2##P1##P0
		
#endif
