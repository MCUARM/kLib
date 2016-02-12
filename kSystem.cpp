#include "kSystem.h"

static void kSystem_Default_IRQ_Handler(void);

extern void (* const g_pfnVectors[])(void);

__attribute__ ((aligned (512)))
static void (* kSystem_isr_vector[])(void) = {
		  (void (*)())g_pfnVectors[0],
		  kSystem_Default_IRQ_Handler,             /*!< Reset Handler                               */
		  kSystem_Default_IRQ_Handler,               /*!< NMI Handler                                 */
		  kSystem_Default_IRQ_Handler,         /*!< Hard Fault Handler                          */
		  kSystem_Default_IRQ_Handler,         /*!< MPU Fault Handler                           */
		  kSystem_Default_IRQ_Handler,          /*!< Bus Fault Handler                           */
		  kSystem_Default_IRQ_Handler,        /*!< Usage Fault Handler                         */
		  0,0,0,0,                   /*!< Reserved                                    */
		  kSystem_Default_IRQ_Handler,               /*!< SVCall Handler                              */
		  kSystem_Default_IRQ_Handler,          /*!< Debug Monitor Handler                       */
		  0,                         /*!< Reserved                                    */
		  kSystem_Default_IRQ_Handler,            /*!< PendSV Handler                              */
		  kSystem_Default_IRQ_Handler,           /*!< SysTick Handler                             */

		  /*----------External Exceptions---------------------------------------------*/
		  kSystem_Default_IRQ_Handler,           /*!<  0: Window WatchDog                         */
		  kSystem_Default_IRQ_Handler,            /*!<  1: PVD through EXTI Line detection         */
		  kSystem_Default_IRQ_Handler,     /*!<  2: Tamper and TimeStamps through the EXTI line*/
		  kSystem_Default_IRQ_Handler,       /*!<  3: RTC Wakeup through the EXTI line        */
		  kSystem_Default_IRQ_Handler,          /*!<  4: FLASH                                   */
		  kSystem_Default_IRQ_Handler,          /*!<  5: RCC                                     */
		  kSystem_Default_IRQ_Handler,          /*!<  6: EXTI Line0                              */
		  kSystem_Default_IRQ_Handler,          /*!<  7: EXTI Line1                              */
		  kSystem_Default_IRQ_Handler,          /*!<  8: EXTI Line2                              */
		  kSystem_Default_IRQ_Handler,          /*!<  9: EXTI Line3                              */
		  kSystem_Default_IRQ_Handler,          /*!< 10: EXTI Line4                              */
		  kSystem_Default_IRQ_Handler,   /*!< 11: DMA1 Stream 0                           */
		  kSystem_Default_IRQ_Handler,   /*!< 12: DMA1 Stream 1                           */
		  kSystem_Default_IRQ_Handler,   /*!< 13: DMA1 Stream 2                           */
		  kSystem_Default_IRQ_Handler,   /*!< 14: DMA1 Stream 3                           */
		  kSystem_Default_IRQ_Handler,   /*!< 15: DMA1 Stream 4                           */
		  kSystem_Default_IRQ_Handler,   /*!< 16: DMA1 Stream 5                           */
		  kSystem_Default_IRQ_Handler,   /*!< 17: DMA1 Stream 6                           */
		  kSystem_Default_IRQ_Handler,            /*!< 18: ADC1, ADC2 and ADC3s                    */
		  kSystem_Default_IRQ_Handler,        /*!< 19: CAN1 TX                                 */
		  kSystem_Default_IRQ_Handler,       /*!< 20: CAN1 RX0                                */
		  kSystem_Default_IRQ_Handler,       /*!< 21: CAN1 RX1                                */
		  kSystem_Default_IRQ_Handler,       /*!< 22: CAN1 SCE                                */
		  kSystem_Default_IRQ_Handler,        /*!< 23: External Line[9:5]s                     */
		  kSystem_Default_IRQ_Handler,  /*!< 24: TIM1 Break and TIM9                     */
		  kSystem_Default_IRQ_Handler,  /*!< 25: TIM1 Update and TIM10                   */
		  kSystem_Default_IRQ_Handler,/*!< 26: TIM1 Trigger and Commutation and TIM11*/
		  kSystem_Default_IRQ_Handler,        /*!< 27: TIM1 Capture Compare                    */
		  kSystem_Default_IRQ_Handler,           /*!< 28: TIM2                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 29: TIM3                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 30: TIM4                                    */
		  kSystem_Default_IRQ_Handler,        /*!< 31: I2C1 Event                              */
		  kSystem_Default_IRQ_Handler,        /*!< 32: I2C1 Error                              */
		  kSystem_Default_IRQ_Handler,        /*!< 33: I2C2 Event                              */
		  kSystem_Default_IRQ_Handler,        /*!< 34: I2C2 Error                              */
		  kSystem_Default_IRQ_Handler,           /*!< 35: SPI1                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 36: SPI2                                    */
		  kSystem_Default_IRQ_Handler,         /*!< 37: USART1                                  */
		  kSystem_Default_IRQ_Handler,         /*!< 38: USART2                                  */
		  kSystem_Default_IRQ_Handler,         /*!< 39: USART3                                  */
		  kSystem_Default_IRQ_Handler,      /*!< 40: External Line[15:10]s                   */
		  kSystem_Default_IRQ_Handler,      /*!< 41: RTC Alarm (A and B) through EXTI Line   */
		  kSystem_Default_IRQ_Handler,    /*!< 42: USB OTG FS Wakeup through EXTI line     */
		  kSystem_Default_IRQ_Handler, /*!< 43: TIM8 Break and TIM12                    */
		  kSystem_Default_IRQ_Handler,  /*!< 44: TIM8 Update and TIM13                   */
		  kSystem_Default_IRQ_Handler,/*!< 45:TIM8 Trigger and Commutation and TIM14*/
		  kSystem_Default_IRQ_Handler,        /*!< 46: TIM8 Capture Compare                    */
		  kSystem_Default_IRQ_Handler,   /*!< 47: DMA1 Stream7                            */
		  kSystem_Default_IRQ_Handler,           /*!< 48: FSMC                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 49: SDIO                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 50: TIM5                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 51: SPI3                                    */
		  kSystem_Default_IRQ_Handler,          /*!< 52: UART4                                   */
		  kSystem_Default_IRQ_Handler,          /*!< 53: UART5                                   */
		  kSystem_Default_IRQ_Handler,       /*!< 54: TIM6 and DAC1&2 underrun errors         */
		  kSystem_Default_IRQ_Handler,           /*!< 55: TIM7                                    */
		  kSystem_Default_IRQ_Handler,   /*!< 56: DMA2 Stream 0                           */
		  kSystem_Default_IRQ_Handler,   /*!< 57: DMA2 Stream 1                           */
		  kSystem_Default_IRQ_Handler,   /*!< 58: DMA2 Stream 2                           */
		  kSystem_Default_IRQ_Handler,   /*!< 59: DMA2 Stream 3                           */
		  kSystem_Default_IRQ_Handler,   /*!< 60: DMA2 Stream 4                           */
		  kSystem_Default_IRQ_Handler,            /*!< 61: Ethernet                                */
		  kSystem_Default_IRQ_Handler,       /*!< 62: Ethernet Wakeup through EXTI line       */
		  kSystem_Default_IRQ_Handler,        /*!< 63: CAN2 TX                                 */
		  kSystem_Default_IRQ_Handler,       /*!< 64: CAN2 RX0                                */
		  kSystem_Default_IRQ_Handler,       /*!< 65: CAN2 RX1                                */
		  kSystem_Default_IRQ_Handler,       /*!< 66: CAN2 SCE                                */
		  kSystem_Default_IRQ_Handler,         /*!< 67: USB OTG FS                              */
		  kSystem_Default_IRQ_Handler,   /*!< 68: DMA2 Stream 5                           */
		  kSystem_Default_IRQ_Handler,   /*!< 69: DMA2 Stream 6                           */
		  kSystem_Default_IRQ_Handler,   /*!< 70: DMA2 Stream 7                           */
		  kSystem_Default_IRQ_Handler,         /*!< 71: USART6                                  */
		  kSystem_Default_IRQ_Handler,        /*!< 72: I2C3 event                              */
		  kSystem_Default_IRQ_Handler,        /*!< 73: I2C3 error                              */
		  kSystem_Default_IRQ_Handler, /*!< 74: USB OTG HS End Point 1 Out              */
		  kSystem_Default_IRQ_Handler,  /*!< 75: USB OTG HS End Point 1 In               */
		  kSystem_Default_IRQ_Handler,    /*!< 76: USB OTG HS Wakeup through EXTI          */
		  kSystem_Default_IRQ_Handler,         /*!< 77: USB OTG HS                              */
		  kSystem_Default_IRQ_Handler,           /*!< 53: DCMI                                    */
		  kSystem_Default_IRQ_Handler,           /*!< 53: CRYP crypto                             */
		  kSystem_Default_IRQ_Handler,       /*!< 53: Hash and Rng                            */
		  kSystem_Default_IRQ_Handler             /*!< 53: FPU                                     */

		};


k_System kSystem;



k_System::k_System(void)
{
	this->timerReady = 0;
	SysTick->LOAD = 0xFFFFFF;
	// enable SystemTick
	SysTick->CTRL |= 1;

	this->init();


	uint32_t reg = (uint32_t)kSystem_isr_vector - SRAM_BASE;
	reg |= (1<<29);

	SCB->VTOR = reg;


}
void k_System::setIRQHandler(unsigned char channel,void (*IRQHandler_function_pointer)(void))
{
	if(channel > 14 && channel < 98)
	{
		kSystem_isr_vector[channel] = IRQHandler_function_pointer;
	}
}

static void kSystem_Default_IRQ_Handler(void)
{
	while(1);
}

unsigned int k_System::coreCLK(void)
{
	unsigned int clock=0;
	unsigned int temp;

	//get clock source
	switch(RCC->CFGR & 0x00000003)
	{
		case 0:	//HSI
			clock = HSI_VALUE;
		break;
		case 1: //HSE
			clock = HSE_VALUE;
		break;
		case 2: //PLL

			//get PLL source
			if(RCC->PLLCFGR & (1<<22)) clock = HSE_VALUE; // HSE
			else clock = HSI_VALUE; // HSI

			//N multi
			temp = RCC->PLLCFGR & 0x00007FC0;
			temp = temp >> 6;

			clock *= temp;

			//M division
			temp = RCC->PLLCFGR & 0x0000003F;

			clock /= temp;

			//P division
			temp = RCC->PLLCFGR & 0x00030000;
			temp = temp >> 16;
			temp = 2*(temp+1);

			clock /= temp;

		break;
	}

	//get AHB prescaler
	temp = RCC->CFGR & 0x000000F0;
	temp = temp >> 4;

	if(temp & 0x00000008)
	{
		// get prescaler
		temp &= 0x00000007;
		temp +=1;
		if(temp > 4) temp +=1;

		// divide clock by 2 ( using shift)

		clock = clock >> temp;
	}


	return clock;
}
unsigned int k_System::APB1_CLK(void)
{
	unsigned int HCLK = this->coreCLK();

	// get APB1 prescaler
	unsigned int pres = RCC->CFGR & (7<<10);
	pres = pres >> 10;

	if(pres < 4) return HCLK;

	pres -= 3;
	HCLK = HCLK >> pres;

	return HCLK;
}
unsigned int k_System::APB2_CLK(void)
{
	unsigned int HCLK = this->coreCLK();

	// get APB1 prescaler
	unsigned int pres = RCC->CFGR & (7<<13);
	pres = pres >> 13;

	if(pres < 4) return HCLK;

	pres -= 3;
	HCLK = HCLK >> pres;

	return HCLK;
}
unsigned int k_System::APB1_Timer_CLK(void)
{
	unsigned int HCLK = this->coreCLK();

	// get APB1 prescaler
	unsigned int pres = RCC->CFGR & (7<<10);
	pres = pres >> 10;

	if(pres < 4) return HCLK;

	pres -= 2;
	HCLK = HCLK >> pres;

	return HCLK;
}
unsigned int k_System::APB2_Timer_CLK(void)
{
	unsigned int HCLK = this->coreCLK();

	// get APB1 prescaler
	unsigned int pres = RCC->CFGR & (7<<13);
	pres = pres >> 13;

	// if statement true HCLK is not divided
	if(pres < 4) return HCLK;

	pres -= 2;
	HCLK = HCLK >> pres;

	return HCLK;
}

unsigned int k_System::systemTimerCLK()
{
	return (this->coreCLK() >> 3);
}
void k_System::init(void)
{
	this->SecondInTimerTicks = this->systemTimerCLK();
}

void k_System::waitTicks(unsigned short int ticks)
{
	int beg = SysTick->VAL;
	int end = beg-ticks;
	if(beg==end) return;
	if(end < 0)
	{
		end += 0x00FFFFFF;
		while((int)SysTick->VAL <= beg || (int)SysTick->VAL > end);
	}else
	{
		while((int)SysTick->VAL <= beg && (int)SysTick->VAL > end);
	}
}
void k_System::waitus(unsigned short int microseconds)
{
	unsigned long long ticks = this->SecondInTimerTicks;
	ticks *= microseconds;
	ticks/=1000000;

	while(ticks)
	{
		if(ticks > 0xFFFF)
		{
			ticks -= 0xFFFF;
			this->waitTicks(0xFFFF);
		}else
		{
			this->waitTicks((unsigned short int)ticks);
			ticks = 0;
		}
	}
}
void k_System::waitms(unsigned short int miliseconds)
{
	unsigned long long ticks = this->SecondInTimerTicks;
	ticks *=miliseconds;
	ticks/=1000;

	while(ticks)
	{
		if(ticks > 0xFFFF)
		{
			ticks -= 0xFFFF;
			this->waitTicks(0xFFFF);
		}else
		{
			this->waitTicks((unsigned short int)ticks);
			ticks = 0;
		}
	}
}
void k_System::wait(unsigned short int seconds)
{
	unsigned long long ticks = this->SecondInTimerTicks*seconds;

	while(ticks)
	{
		if(ticks > 0xFFFF)
		{
			ticks -= 0xFFFF;
			this->waitTicks(0xFFFF);
		}else
		{
			this->waitTicks((unsigned short int)ticks);
			ticks = 0;
		}
	}
}
