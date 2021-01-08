/*************************************************************************//**

*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


#define _debug_log_UART_					(1)

//#define LED_R							(PH0)
//#define LED_Y							(PH1)
//#define LED_G							(PH2)


#define SPI_LED0_CS_LOW					(PA6 = 0)
#define SPI_LED0_CS_HIGH				(PA6 = 1)
#define SPI_LED1_CS_LOW					(PA7 = 0)
#define SPI_LED1_CS_HIGH				(PA7 = 1)
#define SPI_LED2_CS_LOW					(PA11 = 0)
#define SPI_LED2_CS_HIGH				(PA11 = 1)
#define SPI_LED3_CS_LOW					(PF1 = 0)
#define SPI_LED3_CS_HIGH				(PF1 = 1)
#define SPI_LED4_CS_LOW					(PF0 = 0)
#define SPI_LED4_CS_HIGH				(PF0 = 1)

#define SPI_SNLED27351_POWERON		(PC14 = 1)
#define SPI_SNLED27351_POWERDOWN	(PC14 = 0)


#define SPI_LED_CLK_FREQ  				(200000)
#define SPI_LED_PORT  					(SPI0)
#define SPI_LED_TX_DMA_CH 				(12)
#define SPI_LED_RX_DMA_CH 				(13)
#define SPI_LED_PDMA_OPENED_CH   		((1 << SPI_LED_TX_DMA_CH) | (1 << SPI_LED_RX_DMA_CH))

extern volatile uint8_t SPI_LED_Num;

enum
{
	SPI_LED0 = 0,
	SPI_LED1 ,	
	SPI_LED2 ,	
	SPI_LED3 ,	
	SPI_LED4 ,		
};


typedef enum{

	flag_uart_rx = 0 ,
	flag_compare_error ,			
	flag_WDT ,	
	flag_UART_PDMA ,

	flag_SPI_LED_TX ,
	
	flag_DEFAULT	
}Flag_Index;

//volatile uint32_t BitFlag = 0;
extern volatile uint32_t BitFlag;
#define BitFlag_ON(flag)							(BitFlag|=flag)
#define BitFlag_OFF(flag)							(BitFlag&=~flag)
#define BitFlag_READ(flag)							((BitFlag&flag)?1:0)
#define ReadBit(bit)								(uint32_t)(1<<bit)

#define is_flag_set(idx)							(BitFlag_READ(ReadBit(idx)))
#define set_flag(idx,en)							( (en == 1) ? (BitFlag_ON(ReadBit(idx))) : (BitFlag_OFF(ReadBit(idx))))




void dump_buffer(uint8_t *pucBuff, int nBytes);

void  dump_buffer_hex(uint8_t *pucBuff, int nBytes);





/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
