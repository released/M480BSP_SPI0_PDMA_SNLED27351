/*_____ I N C L U D E S ____________________________________________________*/

#include	"project_config.h"
#include	"LED_Function.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
uint8_t 	b_arySPI_Tx_FIFO[192];	
uint8_t 	b_arySPI_Rx_FIFO[192];	

/*_____ D E F I N I T I O N S ______________________________________________*/
/*_____ M A C R O S ________________________________________________________*/
/*_____ F U N C T I O N S __________________________________________________*/


/*****************************************************************************
* Function		: LED_SNLED2735Init
* Description	: 
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/

void set_CS_Low(uint8_t idx)
{
//	SPI_LED_Num = idx;

	switch(idx)
	{
		case SPI_LED0:
			SPI_LED0_CS_LOW;		
			break;
		case SPI_LED1:
			SPI_LED1_CS_LOW;		
			break;
		case SPI_LED2:
			SPI_LED2_CS_LOW;		
			break;
		case SPI_LED3:
			SPI_LED3_CS_LOW;		
			break;
		case SPI_LED4:
			SPI_LED4_CS_LOW;		
			break;	
	}

}

void set_CS_High(uint8_t idx)
{
//	SPI_LED_Num = idx;
	
	switch(idx)
	{
		case SPI_LED0:
			SPI_LED0_CS_HIGH;		
			break;
		case SPI_LED1:
			SPI_LED1_CS_HIGH;		
			break;
		case SPI_LED2:
			SPI_LED2_CS_HIGH;		
			break;
		case SPI_LED3:
			SPI_LED3_CS_HIGH;		
			break;
		case SPI_LED4:
			SPI_LED4_CS_HIGH;		
			break;	
	}
}

/*	
	idx : SPI_LED0 ~ SPI_LED4
*/
void SpiLED_TX_PDMA(uint8_t idx , uint8_t* Tx , uint16_t len)
{
	uint32_t u32RegValue = 0;
	uint32_t u32Abort = 0;	

    PDMA_Open(PDMA, (1 << SPI_LED_TX_DMA_CH));

	//TX
    PDMA_SetTransferCnt(PDMA,SPI_LED_TX_DMA_CH, PDMA_WIDTH_8, len);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,SPI_LED_TX_DMA_CH, (uint32_t)Tx, PDMA_SAR_INC, (uint32_t)&SPI_LED_PORT->TX, PDMA_DAR_FIX);
    /* Set request source; set basic mode. */
	
    PDMA_SetTransferMode(PDMA,SPI_LED_TX_DMA_CH, PDMA_SPI0_TX, FALSE, 0);
	
    /* Single request type. SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,SPI_LED_TX_DMA_CH, PDMA_REQ_SINGLE, PDMA_BURST_128);
    /* Disable table interrupt */
    PDMA->DSCT[SPI_LED_TX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    SPI_TRIGGER_TX_PDMA(SPI_LED_PORT);

    while(1)
    {
        /* Get interrupt status */
        u32RegValue = PDMA_GET_INT_STATUS(PDMA);
        /* Check the DMA transfer done interrupt flag */
        if(u32RegValue & PDMA_INTSTS_TDIF_Msk)
        {
            /* Check the PDMA transfer done interrupt flags */
            if((PDMA_GET_TD_STS(PDMA) & (1 << SPI_LED_TX_DMA_CH)) == (1 << SPI_LED_TX_DMA_CH))
            {
                /* Clear the DMA transfer done flags */
                PDMA_CLR_TD_FLAG(PDMA,1 << SPI_LED_TX_DMA_CH);
                /* Disable SPI PDMA TX function */
                SPI_DISABLE_TX_PDMA(SPI_LED_PORT);

				while (SPI_IS_BUSY(SPI_LED_PORT));	//TIMER_Delay(TIMER0,500);
				set_CS_High(idx);
				
                break;
            }

            /* Check the DMA transfer abort interrupt flag */
            if(u32RegValue & PDMA_INTSTS_ABTIF_Msk)
            {
                /* Get the target abort flag */
                u32Abort = PDMA_GET_ABORT_STS(PDMA);
                /* Clear the target abort flag */
                PDMA_CLR_ABORT_FLAG(PDMA,u32Abort);
                break;
            }
        }
    }

}



void SpiLED_Init(void)
{

    /* Configure SPI_LED_PORT as a master, MSB first, 8-bit transaction, SPI Mode-0 timing, clock is 20MHz */
    SPI_Open(SPI_LED_PORT, SPI_MASTER, SPI_MODE_0, 8, SPI_LED_CLK_FREQ);

    SYS_UnlockReg();	
	
    SYS->GPA_MFPL &= ~( SYS_GPA_MFPL_PA6MFP_Msk);	
    SYS->GPA_MFPL |=  SYS_GPA_MFPL_PA6MFP_GPIO;	
	GPIO_SetMode(PA,BIT6,GPIO_MODE_OUTPUT);	

    SYS->GPA_MFPL &= ~( SYS_GPA_MFPL_PA7MFP_Msk);	
    SYS->GPA_MFPL |=  SYS_GPA_MFPL_PA7MFP_GPIO;	
	GPIO_SetMode(PA,BIT7,GPIO_MODE_OUTPUT);	

    SYS->GPA_MFPH &= ~( SYS_GPA_MFPH_PA11MFP_Msk);	
    SYS->GPA_MFPH |=  SYS_GPA_MFPH_PA11MFP_GPIO;	
	GPIO_SetMode(PA,BIT11,GPIO_MODE_OUTPUT);	

	#if 0	// remove temporary for debug
    SYS->GPF_MFPL &= ~( SYS_GPF_MFPL_PF1MFP_Msk);	
    SYS->GPF_MFPL |=  SYS_GPF_MFPL_PF1MFP_GPIO;	
	GPIO_SetMode(PF,BIT1,GPIO_MODE_OUTPUT);

    SYS->GPF_MFPL &= ~( SYS_GPF_MFPL_PF0MFP_Msk);	
    SYS->GPF_MFPL |=  SYS_GPF_MFPL_PF0MFP_GPIO;	
	GPIO_SetMode(PF,BIT0,GPIO_MODE_OUTPUT);	
	#endif

    SYS->GPC_MFPH &= ~( SYS_GPC_MFPH_PC14MFP_Msk);	
    SYS->GPC_MFPH |=  SYS_GPC_MFPH_PC14MFP_GPIO;	
	GPIO_SetMode(PC,BIT14,GPIO_MODE_OUTPUT);
	
    SYS_LockReg();	

//	SPI_SET_SUSPEND_CYCLE(SPI_LED_PORT,2);


	/*
		Schmitt trigger structure as input mode only.   
		Hardware power down the chip when pull to low. 
	*/
	SPI_SNLED27351_POWERON;
	
    CLK_SysTickDelay(2000);

}



void SPI_W_3BYTE(uint8_t idx ,uint8_t bPage, uint8_t bRegAddr, uint8_t bData)
{		
	volatile uint8_t bDummyRead;

    // /CS: active
	set_CS_Low(idx);

    SPI_WRITE_TX(SPI_LED_PORT, (0x20|bPage));
    SPI_WRITE_TX(SPI_LED_PORT, bRegAddr);
    SPI_WRITE_TX(SPI_LED_PORT, bData);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_LED_PORT));

    // /CS: de-active
    set_CS_High(idx);

    // skip first rx data
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);

}

void SPI_W_NBYTE(uint8_t idx ,uint8_t bPage, uint8_t bRegAddr, uint8_t blength)
{	
	volatile uint8_t	bDummyRead;
//	uint16_t i;
	
    // /CS: active
	set_CS_Low(idx);


//	while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_LED_PORT));
    while(SPI_IS_BUSY(SPI_LED_PORT));
	
    SPI_WRITE_TX(SPI_LED_PORT, (0x20|bPage));
    SPI_WRITE_TX(SPI_LED_PORT, bRegAddr);	

//	while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_LED_PORT));
    while(SPI_IS_BUSY(SPI_LED_PORT));

	//** For SYNC SPI FIFO
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);	

	#if 1
	SpiLED_TX_PDMA(idx,b_arySPI_Tx_FIFO,blength);


	#else

	for(i = 0;i < blength;i++)
	{
//		while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_LED_PORT));
    	while(SPI_IS_BUSY(SPI_LED_PORT));
		SPI_WRITE_TX(SPI_LED_PORT, b_arySPI_Tx_FIFO[i]);
		//** For SYNC SPI FIFO
		bDummyRead = SPI_READ_RX(SPI_LED_PORT);
	}
	while(SPI_IS_BUSY(SPI_LED_PORT));
	
    // /CS: de-active
	set_CS_High(idx);

	#endif
}

void SPI_R_NBYTE(uint8_t idx ,uint8_t bPage, uint8_t bRegAddr, uint8_t blength)
{	
	volatile uint8_t	bDummyRead;
	uint16_t i;
	
    // /CS: active
	set_CS_Low(idx);
	
	while(!SPI_GET_TX_FIFO_EMPTY_FLAG(SPI_LED_PORT));
    SPI_WRITE_TX(SPI_LED_PORT, (0xA0|bPage));
    SPI_WRITE_TX(SPI_LED_PORT, bRegAddr);	

	while(SPI_IS_BUSY(SPI_LED_PORT));
	//** For SYNC SPI FIFO
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);	
	bDummyRead = SPI_READ_RX(SPI_LED_PORT);		

	for(i = 0;i < blength;i++)
	{
    	SPI_WRITE_TX(SPI_LED_PORT, 0);		
		while(SPI_IS_BUSY(SPI_LED_PORT));
		while(SPI_GET_RX_FIFO_EMPTY_FLAG(SPI_LED_PORT));
		//** For SYNC SPI FIFO
		b_arySPI_Rx_FIFO[i] = SPI_READ_RX(SPI_LED_PORT);
	}

	while(SPI_IS_BUSY(SPI_LED_PORT));	

    // /CS: de-active
	set_CS_High(idx);

}

void LED_SNLED2735Init(uint8_t idx)
{
	volatile uint32_t i,j;
	
	/*
		Mode selection pin for I2C or SPI interface. Input only pin. 
		I2C mode: MSEL tie GND. 
		SPI mode: MSEL tie VDD. 
	*/
	
	
	//** Select to function page
	//** Setting LED driver to shutdown mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	//** Setting internal channel pulldown/pullup
	SPI_W_3BYTE(idx, FUNCTION_PAGE,PDU_REG, mskSET_CA_CB_CHANNEL);
	//** Select number of scan phase
	SPI_W_3BYTE(idx, FUNCTION_PAGE,SCAN_PHASE_REG, mskPHASE_12CHANNEL);
	//** Setting PWM Delay Phase
	SPI_W_3BYTE(idx, FUNCTION_PAGE,SLEW_RATE_CONTROL_MODE1_REG, mskPWM_DELAY_PHASE_ENABLE);
	//** Setting Driving/Sinking Channel Slew Rate
	SPI_W_3BYTE(idx, FUNCTION_PAGE,SLEW_RATE_CONTROL_MODE2_REG, mskDRIVING_SINKING_CHHANNEL_SLEWRATE_ENABLE);
	//** Setting Iref
	SPI_W_3BYTE(idx, FUNCTION_PAGE,SOFTWARE_SLEEP_REG, mskSLEEP_DISABLE);	

	//===========================================//
	//Set LED CONTROL PAGE (Page 0)   		       //
	//===========================================//	
	for( i = 0; i< LED_CONTROL_PAGE_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = 0;
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);

	//===========================================//
	//Set PWM PAGE (Page 1)    						       //
	//===========================================//		
	for( i = 0; i< LED_PWM_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = 0;
	}
	SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
	
	//===========================================//
	//Set CURRENT PAGE (Page 4)      				     //
	//===========================================//	
	b_arySPI_Tx_FIFO[0] = CONST_CURRENT_STEP_CB1;
	b_arySPI_Tx_FIFO[1] = CONST_CURRENT_STEP_CB2;
	b_arySPI_Tx_FIFO[2] = CONST_CURRENT_STEP_CB3;
	b_arySPI_Tx_FIFO[3] = CONST_CURRENT_STEP_CB4;
	b_arySPI_Tx_FIFO[4] = CONST_CURRENT_STEP_CB5;
	b_arySPI_Tx_FIFO[5] = CONST_CURRENT_STEP_CB6;
	b_arySPI_Tx_FIFO[6] = CONST_CURRENT_STEP_CB7;
	b_arySPI_Tx_FIFO[7] = CONST_CURRENT_STEP_CB8;
	b_arySPI_Tx_FIFO[8] = CONST_CURRENT_STEP_CB9;
	b_arySPI_Tx_FIFO[9] = CONST_CURRENT_STEP_CB10;
	b_arySPI_Tx_FIFO[10] = CONST_CURRENT_STEP_CB11;
	b_arySPI_Tx_FIFO[11] = CONST_CURRENT_STEP_CB12;
	SPI_W_NBYTE(idx, CURRENT_TUNE_PAGE, LED_CURRENT_TUNE_FIRST_ADDR, LED_CURRENT_TUNE_LENGTH);
	
	//===========================================//
	//Enable LEDs ON/OFF 						  		       //
	//===========================================//	
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = 0xFF;
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);

	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
}
	

/*****************************************************************************
* Function		: LED_CheckDriverID
* Description	: 
*-----------------------------------------------------------------------------
* Input(Global)	: 
* Input(Local)  : None
* Output(Global): None
* Return(Local)	: None
*****************************************************************************/
uint8_t LED_CheckDriverID(uint8_t idx)
{
	SPI_R_NBYTE(idx, FUNCTION_PAGE, DRIVER_ID_REG, 1);
	if(b_arySPI_Rx_FIFO[0]==SNLED2735_ID)
	{
		return ID_CHECK_PASS;
	}
	else
	{
		return ID_CHECK_FAIL;
	}
}

/*****************************************************************************
* Function		: LED_SW_SLEEP
* Description	: 
*-----------------------------------------------------------------------------
* Input(Global)	: 
* Input(Local)  : None
* Output(Global): None
* Return(Local)	: None
*****************************************************************************/
void LED_SW_SLEEP(uint8_t idx)
{
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	//** Write SW Sleep Register
	SPI_W_3BYTE(idx, FUNCTION_PAGE,SOFTWARE_SLEEP_REG, mskSLEEP_ENABLE);
    CLK_SysTickDelay(5000);
	
}


//** Application LED lookup Table 
//** User Could replace this table for different LED layout
const uint8_t b_tabLED_Location[64]=
{	
	//** CA1      //** CA2      //** CA3    	//** CA4      //** CA5      //** CA6      //** CA7      //** CA8      //** CA9      //** CA10     //** CA11     //** CA12     //** CA13     //** CA14     //** CA15     //** CA16 	
	RGBLED_NUM1,  RGBLED_NUM2,  RGBLED_NUM3,  RGBLED_NUM4,  RGBLED_NUM5,  RGBLED_NUM6,  RGBLED_NUM7,  RGBLED_NUM8, RGBLED_NUM9,   RGBLED_NUM10, RGBLED_NUM11, RGBLED_NUM12, RGBLED_NUM13, RGBLED_NUM14, RGBLED_NUM15, RGBLED_NUM16, 			
	RGBLED_NUM17, RGBLED_NUM18, RGBLED_NUM19, RGBLED_NUM20, RGBLED_NUM21, RGBLED_NUM22, RGBLED_NUM23, RGBLED_NUM24, RGBLED_NUM25, RGBLED_NUM26, RGBLED_NUM27, RGBLED_NUM28, RGBLED_NUM29, RGBLED_NUM30, RGBLED_NUM31, RGBLED_NUM32, 		
	RGBLED_NUM33, RGBLED_NUM34, RGBLED_NUM35, RGBLED_NUM36, RGBLED_NUM37, RGBLED_NUM38, RGBLED_NUM39, RGBLED_NUM40, RGBLED_NUM41, RGBLED_NUM42, RGBLED_NUM43, RGBLED_NUM44, RGBLED_NUM45, RGBLED_NUM46, RGBLED_NUM47, RGBLED_NUM48,		
	RGBLED_NUM49, RGBLED_NUM50, RGBLED_NUM51, RGBLED_NUM52, RGBLED_NUM53, RGBLED_NUM54, RGBLED_NUM55, RGBLED_NUM56, RGBLED_NUM57, RGBLED_NUM58, RGBLED_NUM59, RGBLED_NUM60, RGBLED_NUM61, RGBLED_NUM62, RGBLED_NUM63, RGBLED_NUM64		
};

//** Create a PWM Registers Look-up table 
//** Reference SNLED2735 Datasheet "CH3.6" about PWM register location
const uint8_t	b_tabRedLED_PWM_Location[64]=
{
//**CA1/ CA2 / CA3 / CA4 / CA5 / CA6 / CA7 / CA8 / CA9 /CA10 /CA11 /CA12 /CA13 /CA14 /CA15 /CA16 	
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 			
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 		
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 	
	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 	
};
//** Create a PWM Registers Look-up table 
//** Reference SNLED2735 Datasheet "CH3.6" about PWM register location
const uint8_t	b_tabGreenLED_PWM_Location[64]=
{
//**CA1/ CA2 / CA3 / CA4 / CA5 / CA6 / CA7 / CA8 / CA9 /CA10 /CA11 /CA12 /CA13 /CA14 /CA15 /CA16 	
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 			
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 		
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 	
	0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
};	
//** Create a PWM Registers Look-up table 
//** Reference SNLED2735 Datasheet "CH3.6" about PWM register location
const uint8_t	b_tabBlueLED_PWM_Location[64]=
{
//**CA1/ CA2 / CA3 / CA4 / CA5 / CA6 / CA7 / CA8 / CA9 /CA10 /CA11 /CA12 /CA13 /CA14 /CA15 /CA16 	
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 			
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 		
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 	
	0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
};

//** Create a LED control (ON/OFF) Registers Look-up table  
//** Reference SNLED2735 Datasheet "CH8.6" about LED ON/OFF bit location
const uint8_t	b_tabLED_Control_Map[24]=
{
	//** COLUMN 0 
  (LED_P_00|LED_P_01|LED_P_02|LED_P_03|LED_P_04|LED_P_05|LED_P_06|LED_P_07), 
  (LED_P_08|LED_P_09|LED_P_0A|LED_P_0B|LED_P_0C|LED_P_0D|LED_P_0E|LED_P_0F),
 
	//** COLUMN 1
  (LED_P_10|LED_P_11|LED_P_12|LED_P_13|LED_P_14|LED_P_15|LED_P_16|LED_P_17), 
  (LED_P_18|LED_P_19|LED_P_1A|LED_P_1B|LED_P_1C|LED_P_1D|LED_P_1E|LED_P_1F), 

	//** COLUMN 2
  (LED_P_20|LED_P_21|LED_P_22|LED_P_23|LED_P_24|LED_P_25|LED_P_26|LED_P_27), 
  (LED_P_28|LED_P_29|LED_P_2A|LED_P_2B|LED_P_2C|LED_P_2D|LED_P_2E|LED_P_2F), 

	//** COLUMN 3
  (LED_P_30|LED_P_31|LED_P_32|LED_P_33|LED_P_34|LED_P_35|LED_P_36|LED_P_37), 
  (LED_P_38|LED_P_39|LED_P_3A|LED_P_3B|LED_P_3C|LED_P_3D|LED_P_3E|LED_P_3F), 

	//** COLUMN 4
  (LED_P_40|LED_P_41|LED_P_42|LED_P_43|LED_P_44|LED_P_45|LED_P_46|LED_P_47), 
  (LED_P_48|LED_P_49|LED_P_4A|LED_P_4B|LED_P_4C|LED_P_4D|LED_P_4E|LED_P_4F), 

	//** COLUMN 5
  (LED_P_50|LED_P_51|LED_P_52|LED_P_53|LED_P_54|LED_P_55|LED_P_56|LED_P_57), 
  (LED_P_58|LED_P_59|LED_P_5A|LED_P_5B|LED_P_5C|LED_P_5D|LED_P_5E|LED_P_5F), 

	//** COLUMN 6
  (LED_P_60|LED_P_61|LED_P_62|LED_P_63|LED_P_64|LED_P_65|LED_P_66|LED_P_67), 
  (LED_P_68|LED_P_69|LED_P_6A|LED_P_6B|LED_P_6C|LED_P_6D|LED_P_6E|LED_P_6F), 

	//** COLUMN 7
  (LED_P_70|LED_P_71|LED_P_72|LED_P_73|LED_P_74|LED_P_75|LED_P_76|LED_P_77), 
  (LED_P_78|LED_P_79|LED_P_7A|LED_P_7B|LED_P_7C|LED_P_7D|LED_P_7E|LED_P_7F), 

	//** COLUMN 8
  (LED_P_80|LED_P_81|LED_P_82|LED_P_83|LED_P_84|LED_P_85|LED_P_86|LED_P_87), 
  (LED_P_88|LED_P_89|LED_P_8A|LED_P_8B|LED_P_8C|LED_P_8D|LED_P_8E|LED_P_8F), 

	//** COLUMN 9
  (LED_P_90|LED_P_91|LED_P_92|LED_P_93|LED_P_94|LED_P_95|LED_P_96|LED_P_97), 
  (LED_P_98|LED_P_99|LED_P_9A|LED_P_9B|LED_P_9C|LED_P_9D|LED_P_9E|LED_P_9F), 

	//** COLUMN A
  (LED_P_A0|LED_P_A1|LED_P_A2|LED_P_A3|LED_P_A4|LED_P_A5|LED_P_A6|LED_P_A7), 
  (LED_P_A8|LED_P_A9|LED_P_AA|LED_P_AB|LED_P_AC|LED_P_AD|LED_P_AE|LED_P_AF), 

	//** COLUMN B
  (LED_P_B0|LED_P_B1|LED_P_B2|LED_P_B3|LED_P_B4|LED_P_B5|LED_P_B6|LED_P_B7), 
  (LED_P_B8|LED_P_B9|LED_P_BA|LED_P_BB|LED_P_BC|LED_P_BD|LED_P_BE|LED_P_BF), 
};


void LED_PWMUpdate(volatile uint8_t bPWM_Index,volatile uint8_t bPWM_R_Value,volatile uint8_t bPWM_G_Value,volatile uint8_t bPWM_B_Value)
{
	volatile uint32_t  wLED_RedIndex, wLED_GreenIndex, wLED_BlueIndex;
	if(bPWM_Index != LED_RESERVED)
	{
		//** RGB LED placement on layout
		wLED_RedIndex 	= b_tabRedLED_PWM_Location[bPWM_Index];			
		wLED_GreenIndex = b_tabGreenLED_PWM_Location[bPWM_Index];		
		wLED_BlueIndex	=	b_tabBlueLED_PWM_Location[bPWM_Index];

		b_arySPI_Tx_FIFO[wLED_RedIndex]  = bPWM_R_Value  ;		
		b_arySPI_Tx_FIFO[wLED_GreenIndex] = bPWM_G_Value ;		
		b_arySPI_Tx_FIFO[wLED_BlueIndex] = bPWM_B_Value ;			
	}	
}



void LED_SnledType4Fun1(uint8_t idx)
{
	uint32_t i, j, count;
	uint8_t	bIndexPrevious, bIndexCurrent;
	
	#if 1
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = 0xFF;	// setting 1~64 RGB LED CTL on
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif
	

	//===============================//
	//Start R_LED Single light on Flow//
	//===============================//
	for( i = 0; i< LED_PWM_LENGTH ; i++)
	{
		for (j=0;j<LED_PWM_LENGTH;j++)
			b_arySPI_Tx_FIFO[j] = 0;
		if (i == 0)
		{
			b_arySPI_Tx_FIFO[0x9F] = 0;
			b_arySPI_Tx_FIFO[0xAF] = 0;
			b_arySPI_Tx_FIFO[0xBF] = 0;
			bIndexPrevious = bIndexCurrent = 0;
		}
		else
		{
			bIndexCurrent = i;
			bIndexPrevious = i-1;
		}
		
		if (((bIndexCurrent & 0xF0) == 0x00) || ((bIndexCurrent & 0xF0) == 0x30) || ((bIndexCurrent & 0xF0) == 0x60) || ((bIndexCurrent & 0xF0) == 0x90))
		{
			//Turn Off Previous RGB LED PWM value
			if ((bIndexCurrent == 0x30) || (bIndexCurrent == 0x60) || (bIndexCurrent == 0x90))
				b_arySPI_Tx_FIFO[bIndexPrevious-0x20] = 0;
			else
				b_arySPI_Tx_FIFO[bIndexPrevious] = 0x00;
			
			//Set RGB LED PWM value
			b_arySPI_Tx_FIFO[bIndexCurrent] = 0xFF;

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(100000);
		}
	}

	//===============================//
	//Start G_LED Single light on Flow//
	//===============================//
	for( i = 0; i< LED_PWM_LENGTH ; i++)
	{
		if (i == 0)
		{
			b_arySPI_Tx_FIFO[0x9F] = 0;
			b_arySPI_Tx_FIFO[0xAF] = 0;
			b_arySPI_Tx_FIFO[0xBF] = 0;
			bIndexPrevious = bIndexCurrent = 0;
		}
		else
		{
			bIndexCurrent = i;
			bIndexPrevious = i-1;
		}
		
		if (((bIndexCurrent & 0xF0) == 0x10) || ((bIndexCurrent & 0xF0) == 0x40) || ((bIndexCurrent & 0xF0) == 0x70) || ((bIndexCurrent & 0xF0) == 0xA0))
		{
			//Turn Off Previous RGB LED PWM value
			if ((bIndexCurrent == 0x40) || (bIndexCurrent == 0x70) || (bIndexCurrent == 0xA0))
				b_arySPI_Tx_FIFO[bIndexPrevious-0x20] = 0;
			else
				b_arySPI_Tx_FIFO[bIndexPrevious] = 0x00;
			
			//Set RGB LED PWM value
			b_arySPI_Tx_FIFO[bIndexCurrent] = 0xFF;

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(100000);
		}
	}

		//===============================//
	//Start B_LED Single light on Flow//
	//===============================//
	for( i = 0; i< LED_PWM_LENGTH ; i++)
	{
		if (i == 0)
		{
			b_arySPI_Tx_FIFO[0x9F] = 0;
			b_arySPI_Tx_FIFO[0xAF] = 0;
			b_arySPI_Tx_FIFO[0xBF] = 0;
			bIndexPrevious = bIndexCurrent = 0;
		}
		else
		{
			bIndexCurrent = i;
			bIndexPrevious = i-1;
		}
		
		if (((bIndexCurrent & 0xF0) == 0x20) || ((bIndexCurrent & 0xF0) == 0x50) || ((bIndexCurrent & 0xF0) == 0x80) || ((bIndexCurrent & 0xF0) == 0xB0))
		{
			//Turn Off Previous RGB LED PWM value
			if ((bIndexCurrent == 0x50) || (bIndexCurrent == 0x80) || (bIndexCurrent == 0xB0))
				b_arySPI_Tx_FIFO[bIndexPrevious-0x20] = 0;
			else
				b_arySPI_Tx_FIFO[bIndexPrevious] = 0x00;
			
			//Set RGB LED PWM value
			b_arySPI_Tx_FIFO[bIndexCurrent] = 0xFF;

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(100000);
		}
	}
	
	//===============================//
	//Start LED White light on Flow  //
	//===============================//
	
	count = 0;
	while(count<3)
	{
		for (i=0;i<=255;i++)
		{
			//Set RGB LED PWM value
			for (j=0;j<LED_PWM_LENGTH;j++)
				b_arySPI_Tx_FIFO[j] = i;
			
			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(1000);
		}
		
		for (i=0;i<=255;i++)
		{
			//Set RGB LED PWM value
			for (j=0;j<LED_PWM_LENGTH;j++)
				b_arySPI_Tx_FIFO[j] = 255-i;

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(1000);
		}
	count++;
	}
}

/*****************************************************************************
* Function		: LED_SnledType4Fun2 : Blink
* Description	: All LED of the Panel Blink 
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void LED_SnledType4Fun2(uint8_t idx)
{
	uint32_t i, j, count;
	uint8_t	bIndexPrevious, bIndexCurrent;
	uint8_t	bRed, bGreen, bBlue;
	
	#if 1
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = b_tabLED_Control_Map[i];	// setting 1~64 RGB LED CTL on
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif
	
	//===============================//
	//Start R_LED Single light on Flow//
	//===============================//
	for (i=0;i<LED_LAYOUT_TOTAL_LED_NUMBERS;i++)
	{
		for (j=0;j<LED_PWM_LENGTH;j++)
			b_arySPI_Tx_FIFO[j] = 0;
		if (i == 0)
		{
			LED_PWMUpdate(b_tabLED_Location[63],	0 ,0 ,0);
			bIndexPrevious = bIndexCurrent = 0;
		}
		else
		{
			bIndexCurrent = i;
			bIndexPrevious = i-1;
		}
		
		//Turn Off Previous RGB LED PWM value
		LED_PWMUpdate(b_tabLED_Location[bIndexPrevious],	0 ,0 ,0);
	
		//Set RGB LED PWM value
		bRed 	 = 0xFF;	//**  LED_R
		bGreen  = 0x00;	//**  LED_G	
		bBlue	 = 0x00;	//**  LED_B
	
		LED_PWMUpdate(b_tabLED_Location[bIndexCurrent],	bRed ,bGreen ,bBlue);

		//** Update LED Driver
		SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
		CLK_SysTickDelay(100000);
	}

	//===============================//
	//Start G_LED Single light on Flow//
	//===============================//
	for (i=0;i<LED_LAYOUT_TOTAL_LED_NUMBERS;i++)
	{
		if (i == 0)
		{
			LED_PWMUpdate(b_tabLED_Location[63],	0 ,0 ,0);
			bIndexPrevious = bIndexCurrent = 0;
		}
		else
		{
			bIndexCurrent = i;
			bIndexPrevious = i-1;
		}
		
		//Turn Off Previous RGB LED PWM value
		LED_PWMUpdate(b_tabLED_Location[bIndexPrevious],	0 ,0 ,0);
	
		//Set RGB LED PWM value
		bRed 	 = 0x00;	//**  LED_R
		bGreen  = 0xFF;	//**  LED_G	
		bBlue	 = 0x00;	//**  LED_B
	
		LED_PWMUpdate(b_tabLED_Location[bIndexCurrent],	bRed ,bGreen ,bBlue);

		//** Update LED Driver
		SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
		CLK_SysTickDelay(100000);
	}
	
	//===============================//
	//Start B_LED Single light on Flow//
	//===============================//
	for (i=0;i<LED_LAYOUT_TOTAL_LED_NUMBERS;i++)
	{
		if (i == 0)
		{
			LED_PWMUpdate(b_tabLED_Location[63],	0 ,0 ,0);
			bIndexPrevious = bIndexCurrent = 0;
		}
		else
		{
			bIndexCurrent = i;
			bIndexPrevious = i-1;
		}
		
		//Turn Off Previous RGB LED PWM value
		LED_PWMUpdate(b_tabLED_Location[bIndexPrevious],	0 ,0 ,0);
	
		//Set RGB LED PWM value
		bRed 	 = 0x00;	//**  LED_R
		bGreen  = 0x00;	//**  LED_G	
		bBlue	 = 0xFF;	//**  LED_B
	
		LED_PWMUpdate(b_tabLED_Location[bIndexCurrent],	bRed ,bGreen ,bBlue);

		//** Update LED Driver
		SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
		CLK_SysTickDelay(100000);
	}
	
	//===============================//
	//Start LED White light on Flow  //
	//===============================//
	
	count = 0;
	while(count<3)
	{
		for (i=0;i<=255;i++)
		{
			//Set RGB LED PWM value
			bRed 	 = i;	//**  LED_R
			bGreen  = i;	//**  LED_G	
			bBlue	 = i;	//**  LED_B
			for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
				LED_PWMUpdate(b_tabLED_Location[j],	bRed ,bGreen ,bBlue);

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(1000);
		}
		
		for (i=0;i<=255;i++)
		{
			//Set RGB LED PWM value
			bRed 	 = 255-i;	//**  LED_R
			bGreen  = 255-i;	//**  LED_G	
			bBlue	 = 255-i;	//**  LED_B
			for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
				LED_PWMUpdate(b_tabLED_Location[j],	bRed ,bGreen ,bBlue);

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(1000);
		}
	count++;
	}
}

void LED_SnledType4Fun3(uint8_t idx)	//gradient , white
{
	uint32_t i, j, count;
//	uint8_t	bIndexPrevious, bIndexCurrent;
	uint8_t	bRed, bGreen, bBlue;
	
	#if 1
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = b_tabLED_Control_Map[i];	// setting 1~64 RGB LED CTL on
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif
	
	//===============================//
	//Start LED White light on Flow  //
	//===============================//
	
	count = 0;
	while(count<1)
	{
		for (i=0;i<=255;i++)
		{
			//Set RGB LED PWM value
			bRed 	 = i;	//**  LED_R
			bGreen  = i;	//**  LED_G	
			bBlue	 = i;	//**  LED_B
			for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
				LED_PWMUpdate(b_tabLED_Location[j],	bRed ,bGreen ,bBlue);

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(60);
		}
		
		for (i=0;i<=255;i++)
		{
			//Set RGB LED PWM value
			bRed 	 = 255-i;	//**  LED_R
			bGreen  = 255-i;	//**  LED_G	
			bBlue	 = 255-i;	//**  LED_B
			for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
				LED_PWMUpdate(b_tabLED_Location[j],	bRed ,bGreen ,bBlue);

			//** Update LED Driver
			SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
			CLK_SysTickDelay(60);
		}
	count++;
	}
}

void LED_SnledType4Fun4(uint8_t idx)		// full white off
{
	uint32_t i, j;
//	uint8_t	bIndexPrevious, bIndexCurrent;
	uint8_t	bRed, bGreen, bBlue;
	
	#if 1
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = b_tabLED_Control_Map[i];	// setting 1~64 RGB LED CTL on
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif
	
	//===============================//
	//Start LED White light on Flow  //
	//===============================//

	//Set RGB LED PWM value
	bRed 	= 0x00;	//**  LED_R
	bGreen  	= 0x00;	//**  LED_G	
	bBlue	= 0x00;	//**  LED_B
	for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
		LED_PWMUpdate(b_tabLED_Location[j],	bRed ,bGreen ,bBlue);

	//** Update LED Driver
	SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
	CLK_SysTickDelay(60);


}


void LED_SnledSetColor(uint8_t idx , uint8_t bPWM_R_Value , uint8_t bPWM_G_Value , uint8_t bPWM_B_Value)
{
	uint32_t i, j;
//	uint8_t	bIndexPrevious, bIndexCurrent;
//	uint8_t	bRed, bGreen, bBlue;
	
	#if 1
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = b_tabLED_Control_Map[i];	// setting 1~64 RGB LED CTL on
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif
	
	//===============================//
	//Start LED White light on Flow  //
	//===============================//

	//Set RGB LED PWM value
//	bRed 	 = bPWM_R_Value;	//**  LED_R
//	bGreen  = bPWM_G_Value;	//**  LED_G	
//	bBlue	 = bPWM_B_Value;	//**  LED_B
	for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
		LED_PWMUpdate(b_tabLED_Location[j],	bPWM_R_Value ,bPWM_G_Value ,bPWM_B_Value);

	//** Update LED Driver
	SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
	CLK_SysTickDelay(60);


}

void LED_SnledSetColor_init(uint8_t idx_start , uint8_t idx_end)
{
	uint32_t i;
	uint8_t idx = 0 ;
	
	#if 1
	// System must go to SW shutdowm mode
	for( idx = idx_start; idx <= idx_end ; idx++)
		SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = b_tabLED_Control_Map[i];	// setting 1~64 RGB LED CTL on
	}
	for( idx = idx_start; idx <= idx_end ; idx++)
		SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	for( idx = idx_start; idx <= idx_end ; idx++)
		SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif

}

void LED_SnledSetColor_all_idx(uint8_t idx_start , uint8_t idx_end ,uint8_t bPWM_R_Value , uint8_t bPWM_G_Value , uint8_t bPWM_B_Value)
{
	uint32_t j;
	uint8_t idx = 0 ;
		
	for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
		LED_PWMUpdate(b_tabLED_Location[j],	bPWM_R_Value ,bPWM_G_Value ,bPWM_B_Value);

	//** Update LED Driver
	for( idx = idx_start; idx <= idx_end ; idx++)
		SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
	CLK_SysTickDelay(1);

}

/*
	bPWM_Index : RGBLED_NUM1 ~ RGBLED_NUM64
*/

void LED_SnledSetSingleColor(uint8_t idx ,uint8_t bPWM_Index, uint8_t bPWM_R_Value , uint8_t bPWM_G_Value , uint8_t bPWM_B_Value)
{
	uint32_t i;
//	uint8_t	bIndexPrevious, bIndexCurrent;
//	uint8_t	bRed, bGreen, bBlue;
	
	#if 1
	// System must go to SW shutdowm mode
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_SHUT_DOWN_MODE);
	
	//=====================================//
	//Set LED CTL Registers (Frame1Page) //
	//=====================================//
	for( i = 0; i< LED_CONTROL_ON_OFF_LENGTH ; i++)
	{
		b_arySPI_Tx_FIFO[i] = b_tabLED_Control_Map[i];	// setting 1~64 RGB LED CTL on
	}
	SPI_W_NBYTE(idx, LED_CONTROL_PAGE, LED_CONTROL_ON_OFF_FIRST_ADDR, LED_CONTROL_PAGE_LENGTH);
	
	//** Setting LED driver to normal mode 
	SPI_W_3BYTE(idx, FUNCTION_PAGE,CONFIGURATION_REG, mskSW_NORMAL_MODE);
	#endif
	
	//===============================//
	//Start LED White light on Flow  //
	//===============================//

	//Set RGB LED PWM value
//	bRed 	 = bPWM_R_Value;	//**  LED_R
//	bGreen  = bPWM_G_Value;	//**  LED_G	
//	bBlue	 = bPWM_B_Value;	//**  LED_B
//	for (j=0;j<LED_LAYOUT_TOTAL_LED_NUMBERS;j++)
//		LED_PWMUpdate(b_tabLED_Location[j],	bRed ,bGreen ,bBlue);
	LED_PWMUpdate(bPWM_Index,bPWM_R_Value ,bPWM_G_Value ,bPWM_B_Value);

	//** Update LED Driver
	SPI_W_NBYTE(idx, LED_PWM_PAGE, LED_PWM_FIRST_ADDR, LED_PWM_LENGTH);
	CLK_SysTickDelay(60);


}



