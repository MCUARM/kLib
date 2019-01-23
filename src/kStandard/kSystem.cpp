/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2018, project author Pawel Zalewski                           *
 *     All rights reserved.                                                        *
 *                                                                                 *
 ***********************************************************************************
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions  in  binary  form  must  reproduce the above copyright
 *      notice,  this  list  of conditions and the following disclaimer in the
 *      documentation  and/or  other materials provided with the distribution.
 *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its
 *      contributors  may  be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
 *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF
 *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */



#include "kSystem.h"

	// Private preprocessor definition
	#ifndef AIRCR_VECTKEY_MASK
		#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)
	#endif
	#ifndef NVIC_PriorityGroup_4
		#define NVIC_PriorityGroup_4 ((uint32_t)0x300)
	#endif




	#if(kLib_config_USE_MODULE == 1)

		kRegister kSystem_default_systemRegister;
		const char * kSystem_commands[2] = {kSystem_cmd_get_string,
											kSystem_cmd_info_string};
		kCommand kSystem_commander(kSystem_commands,2);

	#endif

	#if(kLib_config_USE_RTOS == 1)

		// FreeRTOS idle task
		void vApplicationIdleHook()
		{

		}

	#endif

	static void kSystem_Default_IRQ_Handler(void);
	extern void (* const g_pfnVectors[])(void);

	__attribute__ ((aligned (512)))
	void (* kSystem_isr_vector[])(void) = {
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


	unsigned int kSystem_ms_downcounter=0xFFFFFFFF;
	k_System kSystem;


static void kSystem_SysTick_Handler(void)
{
	kSystem_ms_downcounter--;
}


k_System::k_System(void)
{
	unsigned int tmp_reg;

	#if(kLib_config_USE_MODULE == 1)

		// setup system modules register
		this->pSystemRegister = &kSystem_default_systemRegister;
		// setup system module default name
		this->setName("system");
		// setup system commands list
		this->setCommands(&kSystem_commander);

	#endif

	kSystem_isr_vector[15] = kSystem_SysTick_Handler;




	// setup NVIC priority group model to recommended by FreeRTOS
	SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup_4;


	// init SysTick - is used as a main kSystem and FreeRTOS timer
	// setup to generate interrupt every 1ms

	// get one second value in system timer ticks
	this->SecondInTimerTicks = this->systemTimerCLK();
	this->usInTimerTicks = this->SecondInTimerTicks/1000000;

	// calculate system tick value
	tmp_reg = this->SecondInTimerTicks/1000;

	// setup load register (note - SysTick is counting down)
	SysTick->LOAD = tmp_reg - 1;
	// enable SystemTick timer and interrupt
	SysTick->CTRL |= 3;


	// change ISR vector table from FLASH to kSystem_isr_vector placed in SRAM
	// get RAM address
	uint32_t reg = (uint32_t)kSystem_isr_vector - SRAM_BASE;
	// add flag that RAM is used
	reg |= (1<<29);
	// set new address
	SCB->VTOR = reg;



	#if(kLib_config_USE_RTOS == 1)

		// allow FreeRTOS to control these interrupts
		kSystem_isr_vector[11] = (void (*)())g_pfnVectors[11]; // SVC_Handler
		kSystem_isr_vector[14] = (void (*)())g_pfnVectors[14]; // PendSV_Handler

	#endif





}
void k_System::setIRQHandler(unsigned char channel,void (*IRQHandler_function_pointer)(void))
{
	if(channel < 83)
	{
		kSystem_isr_vector[channel+16] = IRQHandler_function_pointer;
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
unsigned int k_System::getPeripheralClock(unsigned int * peripheral_address)
{
	unsigned int HCLK = this->coreCLK();
	unsigned char shift = 10;
	// if this is APB2 Peripheral add 3 bits to shift
	if(((unsigned int)peripheral_address) & 0x00010000)shift=13;
	// get APBx prescaler
	unsigned int pres = RCC->CFGR & (7<<shift);
	pres = pres >> 10;

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


void k_System::waitus(unsigned short int microseconds)
{
	// get actual counter values
	unsigned int SysTick_counter = SysTick->VAL;
	unsigned int end_ms_counter = kSystem_ms_downcounter;

	end_ms_counter -= (microseconds/1000);

	// use microseconds as temporary storage
	microseconds = microseconds % 1000;
	microseconds *= this->usInTimerTicks;
	microseconds = SysTick_counter - microseconds;

	if(microseconds > SysTick->LOAD)
	{
		end_ms_counter--;
		microseconds = 0xFFFFFFFF - microseconds;
		microseconds = SysTick->LOAD - microseconds;
	}

	while(!( microseconds >= SysTick->LOAD  && end_ms_counter >= kSystem_ms_downcounter));
}
void k_System::waitms(unsigned short int miliseconds)
{
	unsigned int end_ms_counter = kSystem_ms_downcounter - miliseconds;
	while(end_ms_counter < kSystem_ms_downcounter);
}
void k_System::wait(unsigned short int seconds)
{
	unsigned short int tmp;
	tmp = seconds/60;

	while(tmp)
	{
		this->waitms(60000);
		tmp--;
	}
	tmp = seconds % 60;
	tmp*=1000;
	this->waitms(tmp);
}
void k_System::enableInterrupt(unsigned char channel,unsigned char preemptionPriority, unsigned char subPriority)
{
  uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

  /* Check the parameters */
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(preemptionPriority));
  assert_param(IS_NVIC_SUB_PRIORITY(subPriority));


	/* Compute the Corresponding IRQ Priority --------------------------------*/
	tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
	tmppre = (0x4 - tmppriority);
	tmpsub = tmpsub >> tmppriority;

	tmppriority = preemptionPriority << tmppre;
	tmppriority |=  (uint8_t)(subPriority & tmpsub);

	tmppriority = tmppriority << 0x04;

	NVIC->IP[channel] = tmppriority;

	/* Enable the Selected IRQ Channels --------------------------------------*/
	NVIC->ISER[channel >> 0x05] = (uint32_t)0x01 << (channel & (uint8_t)0x1F);

}
void k_System::disableInterrupt(unsigned char channel)
{
	/* Disable the Selected IRQ Channels --------------------------------------*/
	NVIC->ICER[channel >> 0x05] = (uint32_t)0x01 << (channel & (uint8_t)0x1F);
}
unsigned int k_System::millis(void)
{
	return kSystem_ms_downcounter;
}
unsigned int k_System::micros(void)
{
	unsigned int res = kSystem_ms_downcounter*1000;
	unsigned int us = ((unsigned int)(SysTick->VAL))*1000;
	us /= SysTick->LOAD;
	return (res+us);
}
bool k_System::isTimePassed(unsigned int * system_milliseconds_time)
{
	return (bool)(*system_milliseconds_time >= kSystem_ms_downcounter);
}

#if (kLib_config_USE_MODULE == 1)

	kRegister * k_System::getSystemRegister(void)
	{
		return this->pSystemRegister;
	}
	void k_System::setSystemRegister(kRegister * reg)
	{
		this->pSystemRegister = reg;
	}
	char * k_System::processCommand(const char * cmd, char * response)
	{
		char cmd_nr = this->commands()->decode(cmd);
		char cmd_nr2;
		switch(cmd_nr)
		{
			case kSystem_cmd_get:

				cmd = kString::skipOneWord(cmd);
				if(!(*cmd)) return kString::copy("Wrong parameter",response);
				cmd_nr2 = this->commands()->decode(cmd);

				switch(cmd_nr2)
				{
					case kSystem_cmd_info:

						response = kString::copy(" kSystem\t ", response);
						response = kString::copy(this->getName(),response);
						response = kString::copy(" core clock @ ",response);
						response = kString::number((int)this->coreCLK(),response);
						response = kString::copy(" Hz",response);

					break;
					default:
						//unexpected parameter
						return kString::copy("Wrong parameter",response);

					break;
				}


			break;
			case kSystem_cmd_info:


			break;
			default:
				//unexpected command

				response = kString::copyOneWord(cmd,response);
				return kString::copy(": command not found",response);

			break;
		}

		return response;
	}

#endif

unsigned int* kPrivate::setupPeripheralOutput(unsigned int hardware_code)
{
	kPrivate::uintSplitter * pData = (kPrivate::uintSplitter *)&hardware_code;
	GPIO_TypeDef * gpio;
	unsigned int temp;
	unsigned char pin;
	unsigned char gpio_alternate_function;

	// get pin number
	pin = pData->ui8[0] & 0x0F;

	// decode alternate function
	gpio_alternate_function = (pData->ui8[1] & 0x0F);

	// decode gpio
	temp = hardware_code & 0x000000F0;
	gpio = (GPIO_TypeDef*)(AHB1PERIPH_BASE | (temp << 6));

	// make sure gpio clock is enabled
	temp = temp >> 4;
	RCC->AHB1ENR |= (1 << temp);

	//set proper gpio alternate function
	//calculate either AFH or AFL register pointer
	temp = (uint32_t)gpio->AFR + ((pin >> 3)*4);
	// clear bits (temporary setup to input mode
	*((uint32_t*)temp) &= ~(0x0000000F << ((pin & 0x07) << 2));
	// set new alternate function
	*((uint32_t*)temp) |= ((uint32_t)gpio_alternate_function << ((pin & 0x07) << 2));


	// set output type
	// use gpio_alternate_function as temporary storage
	gpio_alternate_function = pData->ui8[1] & 0x40;
	gpio_alternate_function = gpio_alternate_function >> 6;
	temp = gpio->OTYPER;
	// clear appropriate bit
	temp &= ~(1<<pin);
	// set new output type
	temp |= (((unsigned int)gpio_alternate_function)<<pin);
	gpio->OTYPER = temp;

	//set gpio mode
	temp = hardware_code & 0x00003000;
	temp = temp >> 12;
	pin *=2;
	// clear bits (temporary set to input mode)
	gpio->MODER &= ~(3<<pin);
	// set appropriate bits
	gpio->MODER |=  (temp<<pin);


	return kPrivate::getPeriheralAndEnableClock(hardware_code);
}
unsigned int* kPrivate::getPeriheralAndEnableClock(unsigned int hardware_code)
{
	kPrivate::uintSplitter * pData = (kPrivate::uintSplitter *)&hardware_code;
	unsigned char shift;
	unsigned char *pByte;
	unsigned int temp;
	// enable peripheral clock
	// get RCC_APBx_ENR address
	temp = (hardware_code & 0x00C00000) >> 22;
	// APB1 or APB2?
	temp |= (hardware_code & 0x00200000) >> 19;
	pByte = (unsigned char*)(temp | ((unsigned int)&RCC->APB1ENR));
	// get bit position (use pin as temporary storage)
	shift = pData->ui8[3] & 0x07;
	// enable clock
	*pByte |= (1<<shift);

	// get peripheral base address
	temp = hardware_code & 0x003F8000;
	hardware_code =  PERIPH_BASE | (temp >> 5);

	return (unsigned int*)hardware_code;
}
uint8_t kPrivate::getUserCode(uint32_t hardware_code)
{
	return (uint8_t)(hardware_code >> 27);
}
unsigned int* kPrivate::getSRAMbitBand(unsigned int * reg, unsigned char bit)
{
	return ((unsigned int*)(((unsigned int)0x22000000)+((0x000FFFFF&((unsigned int)reg))*32)+(((unsigned int)bit)*4)));
}
kPrivate::intBitBand* kPrivate::getSRAMbitBand(unsigned int * reg)
{
	return ((kPrivate::intBitBand*)(((unsigned int)0x22000000)+((0x000FFFFF&((unsigned int)reg))*32)));
}
unsigned int* kPrivate::getPeriphBitBand(unsigned int * reg, unsigned char bit)
{
	return ((unsigned int*)(((unsigned int)0x42000000)+((0x000FFFFF&((unsigned int)reg))*32)+(((unsigned int)bit)*4)));
}
kPrivate::intBitBand* kPrivate::getPeriphBitBand(unsigned int * reg)
{
	return ((kPrivate::intBitBand*)(((unsigned int)0x42000000)+((0x000FFFFF&((unsigned int)reg))*32)));
}
