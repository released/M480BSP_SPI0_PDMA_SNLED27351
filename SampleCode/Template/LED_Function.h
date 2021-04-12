/******************** (C) COPYRIGHT 2013 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2019/10
* AUTHOR:				SA1
* IC:						SNLED2735
* DESCRIPTION:	LED_Function.h
*____________________________________________________________________________
* REVISION	Date				User		Description

*____________________________________________________________________________
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS TIME TO MARKET.
* SONiX SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
* DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
* AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN 
* IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************/
#ifndef __LED_FUNCTION_H
#define __LED_FUNCTION_H

/*_____ I N C L U D E S ____________________________________________________*/

#include "NuMicro.h"



/*_____ D E F I N I T I O N S ______________________________________________*/
	/*--------Registers Page Define------------*/
		#define	LED_CONTROL_PAGE 	0X00
		#define	LED_PWM_PAGE 			0X01
		#define	FUNCTION_PAGE 		0X03
		#define	CURRENT_TUNE_PAGE 0X04
	//=====================================//		
	//        Registers Define             //	
	//=====================================//

	/*--------Function Register: address 0x00------------*/	
		#define	CONFIGURATION_REG 	0X00	
				#define	mskSW_SHUT_DOWN_MODE	(0x0<<0)	
				#define	mskSW_NORMAL_MODE			(0x1<<0)	
				
		#define	DRIVER_ID_REG 		0x11
				#define	SNLED2735_ID 	0x8A
				
		#define	PDU_REG 					0x13
				#define	mskSET_CA_CB_CHANNEL 	0xAA
				#define	mskCLR_CA_CB_CHANNEL 	0x00

		#define	SCAN_PHASE_REG 0x14
				#define	mskPHASE_12CHANNEL 	0x00
				#define	mskPHASE_11CHANNEL 	0x01
				#define	mskPHASE_10CHANNEL 	0x02
				#define	mskPHASE_9CHANNEL 	0x03
				#define	mskPHASE_8CHANNEL 	0x04
				#define	mskPHASE_7CHANNEL 	0x05
				#define	mskPHASE_6CHANNEL 	0x06
				#define	mskPHASE_5CHANNEL 	0x07
				#define	mskPHASE_4CHANNEL 	0x08
				#define	mskPHASE_3CHANNEL 	0x09
				#define	mskPHASE_2CHANNEL 	0x0A
				#define	mskPHASE_1CHANNEL 	0x0B
	
		#define	SLEW_RATE_CONTROL_MODE1_REG 	0x15
				#define	mskPWM_DELAY_PHASE_ENABLE 	0x04
				#define	mskPWM_DELAY_PHASE_DISABLE 	0x00

		#define	SLEW_RATE_CONTROL_MODE2_REG 	0x16
				#define	mskDRIVING_SINKING_CHHANNEL_SLEWRATE_ENABLE 	0xC0
				#define	mskDRIVING_SINKING_CHHANNEL_SLEWRATE_DISABLE 	0x00


		#define	SOFTWARE_SLEEP_REG 	0x1A
				#define	mskSLEEP_ENABLE 	0x02
				#define	mskSLEEP_DISABLE 	0x00
	
/*--------Function Register: Constant Current Control Reg------------*/
		#define	CONST_CURRENT_STEP_CB1		0x80
		#define	CONST_CURRENT_STEP_CB2		0x80
		#define	CONST_CURRENT_STEP_CB3		0x80
		#define	CONST_CURRENT_STEP_CB4		0x80
		#define	CONST_CURRENT_STEP_CB5		0x80
		#define	CONST_CURRENT_STEP_CB6		0x80
		#define	CONST_CURRENT_STEP_CB7		0x80
		#define	CONST_CURRENT_STEP_CB8		0x80
		#define	CONST_CURRENT_STEP_CB9		0x80
		#define	CONST_CURRENT_STEP_CB10		0x80
		#define	CONST_CURRENT_STEP_CB11		0x80
		#define	CONST_CURRENT_STEP_CB12		0x80
		
		
/*----------------------------------------------------------*/
/*											Frame1Page													*/
/*----------------------------------------------------------*/
			//=======================//
			// LED Control Registers //
			//=======================//
			#define	LED_CONTROL_ON_OFF_FIRST_ADDR		0x0
			#define	LED_CONTROL_ON_OFF_LAST_ADDR		0x17		
			#define	LED_CONTROL_ON_OFF_LENGTH				0x18
					
			#define	LED_CONTROL_PAGE_LENGTH		0x48							
		
			//=======================//
			// PWM Control Registers //
			//=======================//	
			#define	LED_PWM_FIRST_ADDR		0x00
			#define	LED_PWM_LAST_ADDR			0xBF						 	
			#define	LED_PWM_LENGTH				0xC0	
				
			//========================//
			// Current Tune Registers //
			//========================//	
			#define	LED_CURRENT_TUNE_FIRST_ADDR		0x00
			#define	LED_CURRENT_TUNE_LAST_ADDR		0x0B						 	
			#define	LED_CURRENT_TUNE_LENGTH				0x0C	


//==================================================================
//
//** Define LED number location based on SNLED2735 Demo Board
//
//==================================================================
#define LED_LAYOUT_TOTAL_LED_NUMBERS 64
#define			LED_RESERVED		255

#define			RGBLED_NUM1				0
#define			RGBLED_NUM2				1
#define			RGBLED_NUM3				2
#define			RGBLED_NUM4				3
#define			RGBLED_NUM5				4
#define			RGBLED_NUM6				5
#define			RGBLED_NUM7				6
#define			RGBLED_NUM8				7
#define			RGBLED_NUM9				8
#define			RGBLED_NUM10			9
#define			RGBLED_NUM11			10
#define			RGBLED_NUM12			11
#define			RGBLED_NUM13			12
#define			RGBLED_NUM14			13
#define			RGBLED_NUM15			14
#define			RGBLED_NUM16			15
#define			RGBLED_NUM17			16
#define			RGBLED_NUM18			17
#define			RGBLED_NUM19			18
#define			RGBLED_NUM20			19
#define			RGBLED_NUM21			20
#define			RGBLED_NUM22			21
#define			RGBLED_NUM23			22
#define			RGBLED_NUM24			23
#define			RGBLED_NUM25			24
#define			RGBLED_NUM26			25
#define			RGBLED_NUM27			26
#define			RGBLED_NUM28			27
#define			RGBLED_NUM29			28
#define			RGBLED_NUM30			29
#define			RGBLED_NUM31			30
#define			RGBLED_NUM32			31
#define			RGBLED_NUM33			32
#define			RGBLED_NUM34			33
#define			RGBLED_NUM35			34
#define			RGBLED_NUM36			35
#define			RGBLED_NUM37			36
#define			RGBLED_NUM38			37
#define			RGBLED_NUM39			38
#define			RGBLED_NUM40			39
#define			RGBLED_NUM41			40
#define			RGBLED_NUM42			41
#define			RGBLED_NUM43			42
#define			RGBLED_NUM44			43
#define			RGBLED_NUM45			44
#define			RGBLED_NUM46			45
#define			RGBLED_NUM47			46
#define			RGBLED_NUM48			47
#define			RGBLED_NUM49			48
#define			RGBLED_NUM50			49
#define			RGBLED_NUM51			50
#define			RGBLED_NUM52			51
#define			RGBLED_NUM53			52
#define			RGBLED_NUM54			53
#define			RGBLED_NUM55			54
#define			RGBLED_NUM56			55
#define			RGBLED_NUM57			56
#define			RGBLED_NUM58			57
#define			RGBLED_NUM59			58
#define			RGBLED_NUM60			59
#define			RGBLED_NUM61			60
#define			RGBLED_NUM62			61
#define			RGBLED_NUM63			62
#define			RGBLED_NUM64			63


//==================================================================
//
//** Define LED Control Bit Location based on SNLED2735 Datasheet
//
//==================================================================
#define			LED_OFF		0

//** Column 0
#define			LED_P_00				(0x01U<<0)
#define			LED_P_01				(0x01U<<1)
#define			LED_P_02				(0x01U<<2)
#define			LED_P_03				(0x01U<<3)
#define			LED_P_04				(0x01U<<4)
#define			LED_P_05				(0x01U<<5)
#define			LED_P_06				(0x01U<<6)
#define			LED_P_07				(0x01U<<7)
#define			LED_P_08				(0x01U<<0)
#define			LED_P_09				(0x01U<<1)
#define			LED_P_0A				(0x01U<<2)
#define			LED_P_0B				(0x01U<<3)
#define			LED_P_0C				(0x01U<<4)
#define			LED_P_0D				(0x01U<<5)
#define			LED_P_0E				(0x01U<<6)
#define			LED_P_0F				(0x01U<<7)

//** Column1
#define			LED_P_10				(0x01U<<0)
#define			LED_P_11				(0x01U<<1)
#define			LED_P_12				(0x01U<<2)
#define			LED_P_13				(0x01U<<3)
#define			LED_P_14				(0x01U<<4)
#define			LED_P_15				(0x01U<<5)
#define			LED_P_16				(0x01U<<6)
#define			LED_P_17				(0x01U<<7)
#define			LED_P_18				(0x01U<<0)
#define			LED_P_19				(0x01U<<1)
#define			LED_P_1A				(0x01U<<2)
#define			LED_P_1B				(0x01U<<3)
#define			LED_P_1C				(0x01U<<4)
#define			LED_P_1D				(0x01U<<5)
#define			LED_P_1E				(0x01U<<6)
#define			LED_P_1F				(0x01U<<7)

//** Column2
#define			LED_P_20				(0x01U<<0)
#define			LED_P_21				(0x01U<<1)
#define			LED_P_22				(0x01U<<2)
#define			LED_P_23				(0x01U<<3)
#define			LED_P_24				(0x01U<<4)
#define			LED_P_25				(0x01U<<5)
#define			LED_P_26				(0x01U<<6)
#define			LED_P_27				(0x01U<<7)
#define			LED_P_28				(0x01U<<0)
#define			LED_P_29				(0x01U<<1)
#define			LED_P_2A				(0x01U<<2)
#define			LED_P_2B				(0x01U<<3)
#define			LED_P_2C				(0x01U<<4)
#define			LED_P_2D				(0x01U<<5)
#define			LED_P_2E				(0x01U<<6)
#define			LED_P_2F				(0x01U<<7)

//** Column3
#define			LED_P_30				(0x01U<<0)
#define			LED_P_31				(0x01U<<1)
#define			LED_P_32				(0x01U<<2)
#define			LED_P_33				(0x01U<<3)
#define			LED_P_34				(0x01U<<4)
#define			LED_P_35				(0x01U<<5)
#define			LED_P_36				(0x01U<<6)
#define			LED_P_37				(0x01U<<7)
#define			LED_P_38				(0x01U<<0)
#define			LED_P_39				(0x01U<<1)
#define			LED_P_3A				(0x01U<<2)
#define			LED_P_3B				(0x01U<<3)
#define			LED_P_3C				(0x01U<<4)
#define			LED_P_3D				(0x01U<<5)
#define			LED_P_3E				(0x01U<<6)
#define			LED_P_3F				(0x01U<<7)

//** Column4
#define			LED_P_40				(0x01U<<0)
#define			LED_P_41				(0x01U<<1)
#define			LED_P_42				(0x01U<<2)
#define			LED_P_43				(0x01U<<3)
#define			LED_P_44				(0x01U<<4)
#define			LED_P_45				(0x01U<<5)
#define			LED_P_46				(0x01U<<6)
#define			LED_P_47				(0x01U<<7)
#define			LED_P_48				(0x01U<<0)
#define			LED_P_49				(0x01U<<1)
#define			LED_P_4A				(0x01U<<2)
#define			LED_P_4B				(0x01U<<3)
#define			LED_P_4C				(0x01U<<4)
#define			LED_P_4D				(0x01U<<5)
#define			LED_P_4E				(0x01U<<6)
#define			LED_P_4F				(0x01U<<7)

//** Column5
#define			LED_P_50				(0x01U<<0)
#define			LED_P_51				(0x01U<<1)
#define			LED_P_52				(0x01U<<2)
#define			LED_P_53				(0x01U<<3)
#define			LED_P_54				(0x01U<<4)
#define			LED_P_55				(0x01U<<5)
#define			LED_P_56				(0x01U<<6)
#define			LED_P_57				(0x01U<<7)
#define			LED_P_58				(0x01U<<0)
#define			LED_P_59				(0x01U<<1)
#define			LED_P_5A				(0x01U<<2)
#define			LED_P_5B				(0x01U<<3)
#define			LED_P_5C				(0x01U<<4)
#define			LED_P_5D				(0x01U<<5)
#define			LED_P_5E				(0x01U<<6)
#define			LED_P_5F				(0x01U<<7)

//** Column6
#define			LED_P_60				(0x01U<<0)
#define			LED_P_61				(0x01U<<1)
#define			LED_P_62				(0x01U<<2)
#define			LED_P_63				(0x01U<<3)
#define			LED_P_64				(0x01U<<4)
#define			LED_P_65				(0x01U<<5)
#define			LED_P_66				(0x01U<<6)
#define			LED_P_67				(0x01U<<7)
#define			LED_P_68				(0x01U<<0)
#define			LED_P_69				(0x01U<<1)
#define			LED_P_6A				(0x01U<<2)
#define			LED_P_6B				(0x01U<<3)
#define			LED_P_6C				(0x01U<<4)
#define			LED_P_6D				(0x01U<<5)
#define			LED_P_6E				(0x01U<<6)
#define			LED_P_6F				(0x01U<<7)

//** Column7
#define			LED_P_70				(0x01U<<0)
#define			LED_P_71				(0x01U<<1)
#define			LED_P_72				(0x01U<<2)
#define			LED_P_73				(0x01U<<3)
#define			LED_P_74				(0x01U<<4)
#define			LED_P_75				(0x01U<<5)
#define			LED_P_76				(0x01U<<6)
#define			LED_P_77				(0x01U<<7)
#define			LED_P_78				(0x01U<<0)
#define			LED_P_79				(0x01U<<1)
#define			LED_P_7A				(0x01U<<2)
#define			LED_P_7B				(0x01U<<3)
#define			LED_P_7C				(0x01U<<4)
#define			LED_P_7D				(0x01U<<5)
#define			LED_P_7E				(0x01U<<6)
#define			LED_P_7F				(0x01U<<7)

//** Column8
#define			LED_P_80				(0x01U<<0)
#define			LED_P_81				(0x01U<<1)
#define			LED_P_82				(0x01U<<2)
#define			LED_P_83				(0x01U<<3)
#define			LED_P_84				(0x01U<<4)
#define			LED_P_85				(0x01U<<5)
#define			LED_P_86				(0x01U<<6)
#define			LED_P_87				(0x01U<<7)
#define			LED_P_88				(0x01U<<0)
#define			LED_P_89				(0x01U<<1)
#define			LED_P_8A				(0x01U<<2)
#define			LED_P_8B				(0x01U<<3)
#define			LED_P_8C				(0x01U<<4)
#define			LED_P_8D				(0x01U<<5)
#define			LED_P_8E				(0x01U<<6)
#define			LED_P_8F				(0x01U<<7)

//** Column9
#define			LED_P_90				(0x01U<<0)
#define			LED_P_91				(0x01U<<1)
#define			LED_P_92				(0x01U<<2)
#define			LED_P_93				(0x01U<<3)
#define			LED_P_94				(0x01U<<4)
#define			LED_P_95				(0x01U<<5)
#define			LED_P_96				(0x01U<<6)
#define			LED_P_97				(0x01U<<7)
#define			LED_P_98				(0x01U<<0)
#define			LED_P_99				(0x01U<<1)
#define			LED_P_9A				(0x01U<<2)
#define			LED_P_9B				(0x01U<<3)
#define			LED_P_9C				(0x01U<<4)
#define			LED_P_9D				(0x01U<<5)
#define			LED_P_9E				(0x01U<<6)
#define			LED_P_9F				(0x01U<<7)

//** Column10
#define			LED_P_A0				(0x01U<<0)
#define			LED_P_A1				(0x01U<<1)
#define			LED_P_A2				(0x01U<<2)
#define			LED_P_A3				(0x01U<<3)
#define			LED_P_A4				(0x01U<<4)
#define			LED_P_A5				(0x01U<<5)
#define			LED_P_A6				(0x01U<<6)
#define			LED_P_A7				(0x01U<<7)
#define			LED_P_A8				(0x01U<<0)
#define			LED_P_A9				(0x01U<<1)
#define			LED_P_AA				(0x01U<<2)
#define			LED_P_AB				(0x01U<<3)
#define			LED_P_AC				(0x01U<<4)
#define			LED_P_AD				(0x01U<<5)
#define			LED_P_AE				(0x01U<<6)
#define			LED_P_AF				(0x01U<<7)

//** Column11
#define			LED_P_B0				(0x01U<<0)
#define			LED_P_B1				(0x01U<<1)
#define			LED_P_B2				(0x01U<<2)
#define			LED_P_B3				(0x01U<<3)
#define			LED_P_B4				(0x01U<<4)
#define			LED_P_B5				(0x01U<<5)
#define			LED_P_B6				(0x01U<<6)
#define			LED_P_B7				(0x01U<<7)
#define			LED_P_B8				(0x01U<<0)
#define			LED_P_B9				(0x01U<<1)
#define			LED_P_BA				(0x01U<<2)
#define			LED_P_BB				(0x01U<<3)
#define			LED_P_BC				(0x01U<<4)
#define			LED_P_BD				(0x01U<<5)
#define			LED_P_BE				(0x01U<<6)
#define			LED_P_BF				(0x01U<<7)


/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
		#define	ID_CHECK_PASS				0x01	
		#define	ID_CHECK_FAIL				0x00	
/*_____ F U N C T I O N S ____________________________________________*/

void SpiLED_TX_PDMA(uint8_t idx , uint8_t* Tx , uint16_t len);
void SpiLED_Init(void);

void LED_SNLED2735Init(uint8_t idx);
void LED_SW_SLEEP(uint8_t idx);

//void	LED_DriverNormalState(void);
//void	LED_DriverSWShutDownState(void);

void LED_SnledType4Fun1(uint8_t idx);
void LED_SnledType4Fun2(uint8_t idx);
void LED_SnledType4Fun3(uint8_t idx);
void LED_SnledType4Fun4(uint8_t idx)	;
void LED_SnledSetColor(uint8_t idx , uint8_t bPWM_R_Value , uint8_t bPWM_G_Value , uint8_t bPWM_B_Value);

void LED_SnledSetColor_init(uint8_t idx_start , uint8_t idx_end);
void LED_SnledSetColor_all_idx(uint8_t idx_start , uint8_t idx_end ,uint8_t bPWM_R_Value , uint8_t bPWM_G_Value , uint8_t bPWM_B_Value);

void LED_SnledSetSingleColor(uint8_t idx ,uint8_t bPWM_Index, uint8_t bPWM_R_Value , uint8_t bPWM_G_Value , uint8_t bPWM_B_Value);

extern const uint8_t b_tabLED_Location[];
extern const uint8_t b_tabLED_Control_Map[];
extern const uint8_t b_tabRedLED_PWM_Location[];
extern const uint8_t b_tabGreenLED_PWM_Location[];
extern const uint8_t b_tabBlueLED_PWM_Location[];

extern uint8_t 	b_arySPI_Tx_FIFO[];	
extern uint8_t 	b_arySPI_Rx_FIFO[];

#endif	/*__SN32F240b_LED_FUNCTION_H*/
