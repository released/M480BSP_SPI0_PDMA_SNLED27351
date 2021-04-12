# M480BSP_SPI0_PDMA_SNLED27351
 M480BSP_SPI0_PDMA_SNLED27351


update @ 2021/04/12

1. add LED rainbow behavior , refer to video (IMG_1526.MOV) in repo.

![caption](https://github.com/released/M480BSP_SPI0_PDMA_SNLED27351/blob/main/IMG_1526.gif)



update @ 2021/01/08

1. init SPI0 , to drive SNLED2735

		SPI0_LED_MOSI : PA.0
		
		SPI0_LED_MISO : PA.1	
		
		SPI0_LED_CLK : PA.2
	
		SPI0_LED_NSS0 : PA.6
		
		SPI0_LED_NSS1 : PA.7	
		
		SPI0_LED_NSS2 : PA.11

2. use terminal tool , to test LED function

digit A~C : follow SNLED2735 sample code behavior , with SNLED2735 EVM

digit D~G , Q : turn on EVM RGB LED , as full white , color R , color G , color B , LED off

