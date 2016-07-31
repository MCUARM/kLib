#include "kPWM.h"

const kPWM_out * kPWM::out = (kPWM_out*)SRAM1_BASE;
const kPWM_in  * kPWM::in  = (kPWM_in *)SRAM1_BASE;


void kPWM_calculatePWM(kPWM_EXTI_data_storage & EXTIx_data,unsigned char channel)
{
	// get timer value
	EXTIx_data.SysTick_val = SysTick->VAL;
	EXTIx_data.kSystem_timer_val = kSystem_ms_downcounter;

	// check if rising or falling edge occurred
	if( (EXTI->RTSR & (1<<channel))) // rising edge
	{
		// disable rising edge trigger
		EXTI->RTSR &= ~(1<<channel);

		// update incoming pwm time
		EXTIx_data.last_update_kSystem_timer_value = EXTIx_data.last_kSystem_timer_value - EXTIx_data.kSystem_timer_val;

		// save current timers values
		EXTIx_data.last_kSystem_timer_value = EXTIx_data.kSystem_timer_val;
		EXTIx_data.last_SysTick_value = EXTIx_data.SysTick_val;

		// enable falling edge trigger
		EXTI->FTSR |= (1<<channel);
	}else 	// falling edge occurred
	{
		// disable falling edge trigger
		EXTI->FTSR &= ~(1<<channel);

		// calculate pwm width
		// get miliseconds
		EXTIx_data.temp_ms = EXTIx_data.last_kSystem_timer_value - EXTIx_data.kSystem_timer_val;


		// get microseconds
		if(EXTIx_data.temp_ms)
		{
			EXTIx_data.temp_ms--;
			// SysTick overflows
			EXTIx_data.temp_us = EXTIx_data.last_SysTick_value + (SysTick->LOAD+1);
		}
		// change units to microseconds
		EXTIx_data.temp_ms *= 1000;

		EXTIx_data.temp_us -= EXTIx_data.SysTick_val;
		EXTIx_data.temp_us *= 1000;
		EXTIx_data.temp_us /= (SysTick->LOAD+1);

		// collect data
		EXTIx_data.temp_ms += EXTIx_data.temp_us;

		// update signal value
		EXTIx_data.pwm_input_register = EXTIx_data.temp_ms;

		// enable rising edge trigger
		EXTI->RTSR |= (1<<channel);
	}

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<channel);

}

kPWM_EXTI_data_storage EXTI0_data;
void kPWM_EXTI0_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTI0_data,0);
}

kPWM_EXTI_data_storage EXTI1_data;
void kPWM_EXTI1_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTI1_data,1);
}

kPWM_EXTI_data_storage EXTI2_data;
void kPWM_EXTI2_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTI2_data,2);
}

kPWM_EXTI_data_storage EXTI3_data;
void kPWM_EXTI3_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTI3_data,3);
}

kPWM_EXTI_data_storage EXTI4_data;
void kPWM_EXTI4_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTI4_data,4);
}


kPWM_EXTI_data_storage EXTI5_data;
kPWM_EXTI_data_storage EXTI6_data;
kPWM_EXTI_data_storage EXTI7_data;
kPWM_EXTI_data_storage EXTI8_data;
kPWM_EXTI_data_storage EXTI9_data;
void kPWM_EXTI9_5_IRQ_Handler(void)
{
	if(EXTI->PR & (1<<5))
	{
		kPWM_calculatePWM(EXTI5_data,5);
	}
	if(EXTI->PR & (1<<6))
	{
		kPWM_calculatePWM(EXTI6_data,6);
	}
	if(EXTI->PR & (1<<7))
	{
		kPWM_calculatePWM(EXTI7_data,7);
	}
	if(EXTI->PR & (1<<8))
	{
		kPWM_calculatePWM(EXTI8_data,8);
	}
	if(EXTI->PR & (1<<9))
	{
		kPWM_calculatePWM(EXTI9_data,9);
	}
}

kPWM_EXTI_data_storage EXTI10_data;
kPWM_EXTI_data_storage EXTI11_data;
kPWM_EXTI_data_storage EXTI12_data;
kPWM_EXTI_data_storage EXTI13_data;
kPWM_EXTI_data_storage EXTI14_data;
kPWM_EXTI_data_storage EXTI15_data;
void kPWM_EXTI15_10_IRQ_Handler(void)
{
	if(EXTI->PR & (1<<10))
	{
		kPWM_calculatePWM(EXTI10_data,10);
	}
	if(EXTI->PR & (1<<11))
	{
		kPWM_calculatePWM(EXTI11_data,11);
	}
	if(EXTI->PR & (1<<12))
	{
		kPWM_calculatePWM(EXTI12_data,12);
	}
	if(EXTI->PR & (1<<13))
	{
		kPWM_calculatePWM(EXTI13_data,13);
	}
	if(EXTI->PR & (1<<14))
	{
		kPWM_calculatePWM(EXTI14_data,14);
	}
	if(EXTI->PR & (1<<15))
	{
		kPWM_calculatePWM(EXTI15_data,15);
	}
}



kPWM::kPWM(void)
{

}

kPWM::kPWMHardware::kPWMHardware(void)
{

}


kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (unsigned int pwmHard)
{
	unsigned char pin;
	GPIO_TypeDef * gpio;
	unsigned char gpio_alternate_function;
	unsigned int temp;

	// decode pin number
	pin = ((unsigned char)pwmHard) & 0x0F;

	// decode alternate function
	gpio_alternate_function = ((unsigned char)pwmHard);
	gpio_alternate_function = gpio_alternate_function >> 4;

	// decode gpio
	temp = pwmHard & 0x00000F00;
	temp = temp << 2;
	gpio = (GPIO_TypeDef*)(AHB1PERIPH_BASE | temp);

	// make sure gpio clock is enabled
	temp = temp >> 10;
	RCC->AHB1ENR |= (1 << temp);

	//set proper gpio alternate function
	//calculate either AFH or AFL register pointer
	temp = (uint32_t)gpio->AFR + ((pin >> 3)*4);
	// clear bits
	*((uint32_t*)temp) &= ~(0x0000000F << ((pin & 0x07) << 2));
	// set new alternate function
	*((uint32_t*)temp) |= ((uint32_t)gpio_alternate_function << ((pin & 0x07) << 2));

	//set gpio output type to push-pull
	gpio->OTYPER &= ~(1<<pin);

	//set gpio mode to alternate function mode
	pin *=2;
	gpio->MODER &= ~(3<<pin);
	gpio->MODER |=  (2<<pin);

	//set gpio output speed to medium
	gpio->OSPEEDR &= ~(3<<pin);
	gpio->OSPEEDR |= (1<<pin);

	//set no pull resistors
	gpio->PUPDR &= ~(3<<pin);


	// decode output register
	pwmHard = pwmHard >> 12;
	this->output = (uint32_t*)(PERIPH_BASE | pwmHard);

	// decode timer base address
	this->tim = (TIM_TypeDef*)(((uint32_t)this->output) & 0xFFFFFF00);


	//make sure timer clock is enabled
	// get proper RCC register
	pwmHard = pwmHard >> 8;
	temp = ((pwmHard & 0x00000100) >> 6) + ((unsigned int)&RCC->APB1ENR);
	// get proper register bit
	pwmHard = (pwmHard & 0x000000FF) >> 2;
	// enable clock
	*((uint32_t*)temp) |= (1<<pwmHard);

	// make sure timer is stopped
	this->tim->CR1 &= ~(1);

	// if it is TIM1 or TIM8 set global output enable
	if(this->tim == TIM1 || this->tim == TIM8) this->tim->BDTR |= (1<<15);

	// setup output compare
	// calculate OC number
	temp = ((unsigned int)this->output) & 0x000000FF;
	temp -= 0x34;
	temp = temp >> 2;

	// setup OCx
	switch(temp)
	{
		case 0:
			tim->CCMR1 &= ~(7<<4);
			tim->CCMR1 |= ((6<<4) | (1<<3));
		break;
		case 1:
			tim->CCMR1 &= ~(7<<12);
			tim->CCMR1 |= ((6<<12) | (1<<11));
		break;
		case 2:
			tim->CCMR2 &= ~(7<<4);
			tim->CCMR2 |= ((6<<4) | (1<<3));
		break;
		case 3:
			tim->CCMR2 &= ~(7<<12);
			tim->CCMR2 |= ((6<<12) | (1<<11));
		break;
	}

	//enable channel
	this->tim->CCER |= (1<<(temp*4));

	return (*this);
}



void kPWM::run(unsigned short int resolution, unsigned int tick_freq)
{

	unsigned int timer_clock;
	unsigned int prescaler;

	// check if timer is APB2 or APB1 peripheral
	if( ((uint32_t)this->hardware.tim) & 0x00010000)
	{
		// timer is connected to APB2 bus
		timer_clock = kSystem.APB2_Timer_CLK();

	}else
	{
		// timer is connected to APB1 bus
		timer_clock = kSystem.APB1_Timer_CLK();
	}

	this->hardware.tim->CR1 &= ~((15<<3)+1);
	this->hardware.tim->ARR = (uint32_t)resolution-1;

	if(tick_freq)
	{
		prescaler = timer_clock/tick_freq;

		if(prescaler)
		{
			prescaler -=1;
			this->hardware.tim->PSC = (uint16_t)prescaler;

			this->hardware.tim->CR1 |=1;
		}

	}



}
void kPWM::kPWMHardware::setupInputModeHardware(unsigned int hard_code)
{
	uint32_t temp;

	// decode pin number
	unsigned char pin = hard_code & 0x0F;
	// decode port number
	unsigned char port = hard_code & 0xF0;
	port = port >> 4;
	// get gpio address
	temp = ((uint32_t)port) << 10;
	GPIO_TypeDef * gpio = ((GPIO_TypeDef*)(AHB1PERIPH_BASE | temp));



	//make sure gpio clock is enabled
	RCC->AHB1ENR |= (1<<port);

	//make sure pin is in input state
	gpio->MODER &= ~(3<<(pin*2));



	// get SYSCFG->EXTICR shift bits number
	hard_code = hard_code >> 8;
	temp = hard_code & 0x000000FF;
	// get proper SYSCFG->EXTICR address (saved in hard_code)
	hard_code = hard_code >> 8;
	hard_code |= ((uint32_t)SYSCFG);

	// make sure SYSCFG clock is enabled
	RCC->APB2ENR |= (1<<14);

	// setup SYSCFG->EXTICR
	// clear proper bits
	*((uint32_t*)hard_code) &= ~(((uint32_t)0x0F) << temp);
	// save new value
	*((uint32_t*)hard_code) |=  (((uint32_t)port) << temp);


	// enable EXTI interrupt handling
	EXTI->IMR |= (1<<pin);
	// enable EXTI rising edge detection
	EXTI->RTSR |= (1<<pin);



}

kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI0::kPWM_EXTI0_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI0_data;

	kSystem.setIRQHandler(6,kPWM_EXTI0_IRQ_Handler);
	kSystem.enableInterrupt(6,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI1::kPWM_EXTI1_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI1_data;

	kSystem.setIRQHandler(7,kPWM_EXTI1_IRQ_Handler);
	kSystem.enableInterrupt(7,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI2::kPWM_EXTI2_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI2_data;

	kSystem.setIRQHandler(8,kPWM_EXTI2_IRQ_Handler);
	kSystem.enableInterrupt(8,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI3::kPWM_EXTI3_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI3_data;

	kSystem.setIRQHandler(9,kPWM_EXTI3_IRQ_Handler);
	kSystem.enableInterrupt(9,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI4::kPWM_EXTI4_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI4_data;

	kSystem.setIRQHandler(10,kPWM_EXTI4_IRQ_Handler);
	kSystem.enableInterrupt(10,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI5::kPWM_EXTI5_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI5_data;

	kSystem.setIRQHandler(23,kPWM_EXTI9_5_IRQ_Handler);
	kSystem.enableInterrupt(23,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI6::kPWM_EXTI6_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI6_data;

	kSystem.setIRQHandler(23,kPWM_EXTI9_5_IRQ_Handler);
	kSystem.enableInterrupt(23,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI7::kPWM_EXTI7_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI7_data;

	kSystem.setIRQHandler(23,kPWM_EXTI9_5_IRQ_Handler);
	kSystem.enableInterrupt(23,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI8::kPWM_EXTI8_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI8_data;

	kSystem.setIRQHandler(23,kPWM_EXTI9_5_IRQ_Handler);
	kSystem.enableInterrupt(23,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI9::kPWM_EXTI9_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI9_data;

	kSystem.setIRQHandler(23,kPWM_EXTI9_5_IRQ_Handler);
	kSystem.enableInterrupt(23,0,0);

	return (*this);
}

kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI10::kPWM_EXTI10_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI10_data;

	kSystem.setIRQHandler(40,kPWM_EXTI15_10_IRQ_Handler);
	kSystem.enableInterrupt(40,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI11::kPWM_EXTI11_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI11_data;

	kSystem.setIRQHandler(40,kPWM_EXTI15_10_IRQ_Handler);
	kSystem.enableInterrupt(40,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI12::kPWM_EXTI12_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI12_data;

	kSystem.setIRQHandler(40,kPWM_EXTI15_10_IRQ_Handler);
	kSystem.enableInterrupt(40,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI13::kPWM_EXTI13_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI13_data;

	kSystem.setIRQHandler(40,kPWM_EXTI15_10_IRQ_Handler);
	kSystem.enableInterrupt(40,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI14::kPWM_EXTI14_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI14_data;

	kSystem.setIRQHandler(40,kPWM_EXTI15_10_IRQ_Handler);
	kSystem.enableInterrupt(40,0,0);

	return (*this);
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI15::kPWM_EXTI15_Pin & pwmHard)
{
	this->setupInputModeHardware((uint32_t)pwmHard);
	// register input buffer
	this->EXTI_data = &EXTI15_data;

	kSystem.setIRQHandler(40,kPWM_EXTI15_10_IRQ_Handler);
	kSystem.enableInterrupt(40,0,0);

	return (*this);
}
kPWM::operator unsigned int()
{
	return (unsigned int)this->hardware.EXTI_data->pwm_input_register;
}
