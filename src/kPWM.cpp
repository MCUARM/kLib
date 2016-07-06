#include "kPWM.h"

const kPWM_Timer1 * kPWM::Timer1 = (kPWM_Timer1 *)SRAM1_BASE;
const kPWM_Timer2 * kPWM::Timer2 = (kPWM_Timer2 *)SRAM1_BASE;
const kPWM_Timer3 * kPWM::Timer3 = (kPWM_Timer3 *)SRAM1_BASE;
const kPWM_Timer4 * kPWM::Timer4 = (kPWM_Timer4 *)SRAM1_BASE;
const kPWM_Timer5 * kPWM::Timer5 = (kPWM_Timer5 *)SRAM1_BASE;
const kPWM_Timer9 * kPWM::Timer9 = (kPWM_Timer9 *)SRAM1_BASE;
const kPWM_Timer10 * kPWM::Timer10 = (kPWM_Timer10 *)SRAM1_BASE;
const kPWM_Timer11 * kPWM::Timer11 = (kPWM_Timer11 *)SRAM1_BASE;

const kPWM_EXTI0 * kPWM::EXTI0 = (kPWM_EXTI0 *)SRAM1_BASE;

uint32_t default_input_storage;
uint32_t default_last_timer_value;

uint32_t * input_storage[16] =
{
		&default_input_storage, // channel 0
		&default_input_storage, // channel 1
		&default_input_storage, // channel 2
		&default_input_storage, // channel 3
		&default_input_storage, // channel 4
		&default_input_storage, // channel 5
		&default_input_storage, // channel 6
		&default_input_storage, // channel 7
		&default_input_storage, // channel 8
		&default_input_storage, // channel 9
		&default_input_storage, // channel 10
		&default_input_storage, // channel 11
		&default_input_storage, // channel 12
		&default_input_storage, // channel 13
		&default_input_storage, // channel 14
		&default_input_storage  // channel 15
};
uint32_t * last_timer_value[16] =
{
		&default_last_timer_value, // channel 0
		&default_last_timer_value, // channel 1
		&default_last_timer_value, // channel 2
		&default_last_timer_value, // channel 3
		&default_last_timer_value, // channel 4
		&default_last_timer_value, // channel 5
		&default_last_timer_value, // channel 6
		&default_last_timer_value, // channel 7
		&default_last_timer_value, // channel 8
		&default_last_timer_value, // channel 9
		&default_last_timer_value, // channel 10
		&default_last_timer_value, // channel 11
		&default_last_timer_value, // channel 12
		&default_last_timer_value, // channel 13
		&default_last_timer_value, // channel 14
		&default_last_timer_value  // channel 15
};

void kPWM_EXTI0_IRQ_Handler(void)
{
	// get timer value
	uint32_t timer_value = SysTick->VAL;

	// check if rising or falling edge occurred
	if( (EXTI->RTSR & 1) == 1 ) // rising edge
	{

		// save timer value
		*(last_timer_value[0]) = timer_value;

		// change external interrupt trigger to falling edge
		// disable rising edge trigger
		EXTI->RTSR &= ~1;
		// enable falling edge trigger
		EXTI->FTSR |= 1;


	}else 	// falling edge occurred
	{

		// calculate duty value
		// please note that the SysTick is counting down
		if( *(last_timer_value[0]) > timer_value) // standard situation
		{
			// save new value of pwm duty
			*(input_storage[0]) = *(last_timer_value[0]) - timer_value;


		}else  // timer overflow occurred
		{
			// save new value of pwm duty
			*(input_storage[0]) = *(last_timer_value[0]) + (0x00FFFFFF - timer_value);

		}

		// change external interrupt trigger to rising edge
		// enable rising edge trigger
		EXTI->RTSR |= 1;
		// disable falling edge trigger
		EXTI->FTSR &= ~1;


	}

	// clear pending flag (in fact write one)
	EXTI->PR |= 1;
}


kPWM::kPWM(void)
{

}

kPWM::kPWMHardware::kPWMHardware(void)
{
	this->output = &this->default_CCR;
}
void kPWM::kPWMHardware::setupPWMpin(GPIO_TypeDef * GPIOx, unsigned char pin)
{
	//output type push-pull
	GPIOx->OTYPER &= ~(1<<pin);

	pin *=2;

	//alternate function mode
	GPIOx->MODER &= ~(3<<pin);
	GPIOx->MODER |=  (2<<pin);

	//output speed medium
	GPIOx->OSPEEDR &= ~(3<<pin);
	GPIOx->OSPEEDR |= (1<<pin);
	//no pull resistors
	GPIOx->PUPDR &= ~(3<<pin);
}
void kPWM::kPWMHardware::setupTimxOCx(TIM_TypeDef * TIMx, unsigned char channel_from_zero)
{
	// PWM mode 1, enable preload
	switch(channel_from_zero)
	{
		case 0:
			TIMx->CCMR1 &= ~(7<<4);
			TIMx->CCMR1 |= ((6<<4) | (1<<3));
		break;
		case 1:
			TIMx->CCMR1 &= ~(7<<12);
			TIMx->CCMR1 |= ((6<<12) | (1<<11));
		break;
		case 2:
			TIMx->CCMR2 &= ~(7<<4);
			TIMx->CCMR2 |= ((6<<4) | (1<<3));
		break;
		case 3:
			TIMx->CCMR2 &= ~(7<<12);
			TIMx->CCMR2 |= ((6<<12) | (1<<11));
		break;
	}


	//enable channel
	TIMx->CCER |= (1<<(channel_from_zero*4));

	//register channel in class
	this->output = (uint32_t *)&TIMx->CCR1 + channel_from_zero;

}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer2Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer2;

	//register hardware
	this->tim = TIM2;

	//enable TIM2 clock
	RCC->APB1ENR |= 1;
	//stop TIM2
	TIM2->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTA0

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[0] &= ~(15<<0);
				GPIOA->AFR[0] |= (1<<0);

				this->setupPWMpin(GPIOA,0);
				this->setupTimxOCx(TIM2,0);

			break;
			case 1: // PORTA5

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[0] &= ~(15<<20);
				GPIOA->AFR[0] |= (1<<20);

				this->setupPWMpin(GPIOA,5);
				this->setupTimxOCx(TIM2,0);

			break;
			case 2: // PORTA15

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[1] &= ~(15<<28);
				GPIOA->AFR[1] |= (1<<28);

				this->setupPWMpin(GPIOA,15);
				this->setupTimxOCx(TIM2,0);

			break;

		//OC2

			case 3: // PORTA1

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[0] &= ~(15<<4);
				GPIOA->AFR[0] |= (1<<4);

				this->setupPWMpin(GPIOA,1);
				this->setupTimxOCx(TIM2,1);

			break;
			case 4: // PORTB3

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF01 (TIM2)
				GPIOB->AFR[0] &= ~(15<<12);
				GPIOB->AFR[0] |= (1<<12);

				this->setupPWMpin(GPIOB,3);
				this->setupTimxOCx(TIM2,1);

			break;

		//OC3

			case 5: // PORTA2
				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[0] &= ~(15<<8);
				GPIOA->AFR[0] |= (1<<8);

				this->setupPWMpin(GPIOA,2);
				this->setupTimxOCx(TIM2,2);

			break;
			case 6: // PORTB10

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF01 (TIM2)
				GPIOB->AFR[1] &= ~(15<<8);
				GPIOB->AFR[1] |= (1<<8);

				this->setupPWMpin(GPIOB,10);
				this->setupTimxOCx(TIM2,2);

			break;

		//OC4

			case 7: // PORTA3
				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[0] &= ~(15<<12);
				GPIOA->AFR[0] |= (1<<12);

				this->setupPWMpin(GPIOA,3);
				this->setupTimxOCx(TIM2,3);

			break;
			case 8: // PORTB11

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF01 (TIM2)
				GPIOB->AFR[1] &= ~(15<<12);
				GPIOB->AFR[1] |= (1<<12);

				this->setupPWMpin(GPIOB,11);
				this->setupTimxOCx(TIM2,3);

			break;


		default:
			// unexpected configuration
		break;
	}






	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer1Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer1;

	//register hardware
	this->tim = TIM1;

	//enable TIM1 clock
	RCC->APB2ENR |= 1;
	//stop TIM1
	TIM1->CR1 &= ~(1);

	// main output enable
	TIM1->BDTR |= (1<<15);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTA8

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[1] &= ~(15<<0);
				GPIOA->AFR[1] |= (1<<0);

				this->setupPWMpin(GPIOA,8);
				this->setupTimxOCx(TIM1,0);

			break;
			case 1: // PORTE9

				//enable GPIOE clock
				RCC->AHB1ENR |= (1<<4);
				//PAx alternate function AF01 (TIM2)
				GPIOE->AFR[1] &= ~(15<<4);
				GPIOE->AFR[1] |= (1<<4);

				this->setupPWMpin(GPIOE,9);
				this->setupTimxOCx(TIM1,0);

			break;


		//OC2

			case 2: // PORTA9

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[1] &= ~(15<<4);
				GPIOA->AFR[1] |= (1<<4);

				this->setupPWMpin(GPIOA,9);
				this->setupTimxOCx(TIM1,1);

			break;
			case 3: // PORTE11

				//enable GPIOE clock
				RCC->AHB1ENR |= (1<<4);
				//PAx alternate function AF01 (TIM2)
				GPIOE->AFR[1] &= ~(15<<12);
				GPIOE->AFR[1] |= (1<<12);

				this->setupPWMpin(GPIOE,11);
				this->setupTimxOCx(TIM1,1);

			break;

		//OC3

			case 4: // PORTA10

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[1] &= ~(15<<8);
				GPIOA->AFR[1] |= (1<<8);

				this->setupPWMpin(GPIOA,10);
				this->setupTimxOCx(TIM1,2);

			break;
			case 5: // PORTE13

				//enable GPIOE clock
				RCC->AHB1ENR |= (1<<4);
				//PAx alternate function AF01 (TIM2)
				GPIOE->AFR[1] &= ~(15<<20);
				GPIOE->AFR[1] |= (1<<20);

				this->setupPWMpin(GPIOE,13);
				this->setupTimxOCx(TIM1,2);

			break;

		//OC4

			case 6: // PORTA11
				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF01 (TIM2)
				GPIOA->AFR[1] &= ~(15<<12);
				GPIOA->AFR[1] |= (1<<12);

				this->setupPWMpin(GPIOA,11);
				this->setupTimxOCx(TIM1,3);

			break;
			case 7: // PORTE14

				//enable GPIOE clock
				RCC->AHB1ENR |= (1<<4);
				//PAx alternate function AF01 (TIM2)
				GPIOE->AFR[1] &= ~(15<<24);
				GPIOE->AFR[1] |= (1<<24);

				this->setupPWMpin(GPIOE,14);
				this->setupTimxOCx(TIM1,3);

			break;


		default:
			// unexpected configuration value
		break;
	}






	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer3Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer3;

	//register hardware
	this->tim = TIM3;

	//enable TIM3 clock
	RCC->APB1ENR |= 2;
	//stop TIM3
	TIM3->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTA6

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF02 (TIM3)
				GPIOA->AFR[0] &= ~(15<<24);
				GPIOA->AFR[0] |= (2<<24);

				this->setupPWMpin(GPIOA,6);
				this->setupTimxOCx(TIM3,0);

			break;
			case 1: // PORTB4

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM3)
				GPIOB->AFR[0] &= ~(15<<16);
				GPIOB->AFR[0] |= (2<<16);

				this->setupPWMpin(GPIOB,4);
				this->setupTimxOCx(TIM3,0);

			break;
			case 2: // PORTC6

				//enable GPIOC clock
				RCC->AHB1ENR |= 4;
				//PCx alternate function AF02 (TIM3)
				GPIOC->AFR[0] &= ~(15<<24);
				GPIOC->AFR[0] |= (2<<24);

				this->setupPWMpin(GPIOC,6);
				this->setupTimxOCx(TIM3,0);

			break;

		//OC2

			case 3: // PORTA7

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF02 (TIM3)
				GPIOA->AFR[0] &= ~(15<<28);
				GPIOA->AFR[0] |= (2<<28);

				this->setupPWMpin(GPIOA,7);
				this->setupTimxOCx(TIM3,1);

			break;
			case 4: // PORTB5

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM3)
				GPIOB->AFR[0] &= ~(15<<20);
				GPIOB->AFR[0] |= (2<<20);

				this->setupPWMpin(GPIOB,5);
				this->setupTimxOCx(TIM3,1);

			break;
			case 5: // PORTC7

				//enable GPIOC clock
				RCC->AHB1ENR |= 4;
				//PCx alternate function AF02 (TIM3)
				GPIOC->AFR[0] &= ~(15<<28);
				GPIOC->AFR[0] |= (2<<28);

				this->setupPWMpin(GPIOC,7);
				this->setupTimxOCx(TIM3,1);

			break;

		//OC3

			case 6: // PORTB0

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM3)
				GPIOB->AFR[0] &= ~(15<<0);
				GPIOB->AFR[0] |= (2<<0);

				this->setupPWMpin(GPIOB,0);
				this->setupTimxOCx(TIM3,2);

			break;
			case 7: // PORTC8

				//enable GPIOC clock
				RCC->AHB1ENR |= 4;
				//PCx alternate function AF02 (TIM3)
				GPIOC->AFR[1] &= ~(15<<0);
				GPIOC->AFR[1] |= (2<<0);

				this->setupPWMpin(GPIOC,8);
				this->setupTimxOCx(TIM3,2);

			break;

		//OC4

			case 8: // PORTB1

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM3)
				GPIOB->AFR[0] &= ~(15<<4);
				GPIOB->AFR[0] |= (2<<4);

				this->setupPWMpin(GPIOB,1);
				this->setupTimxOCx(TIM3,3);

			break;
			case 9: // PORTC9

				//enable GPIOC clock
				RCC->AHB1ENR |= 4;
				//PCx alternate function AF02 (TIM3)
				GPIOC->AFR[1] &= ~(15<<4);
				GPIOC->AFR[1] |= (2<<4);

				this->setupPWMpin(GPIOC,9);
				this->setupTimxOCx(TIM3,3);

			break;


		default:
			// unexpected configuration
		break;
	}
	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer4Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer4;

	//register hardware
	this->tim = TIM4;

	//enable TIM4 clock
	RCC->APB1ENR |= 4;
	//stop TIM4
	TIM4->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTB6

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM4)
				GPIOB->AFR[0] &= ~(15<<24);
				GPIOB->AFR[0] |= (2<<24);

				this->setupPWMpin(GPIOB,6);
				this->setupTimxOCx(TIM4,0);

			break;
			case 1: // PORTD12

				//enable GPIOD clock
				RCC->AHB1ENR |= (1<<3);
				//PDx alternate function AF02 (TIM4)
				GPIOD->AFR[1] &= ~(15<<16);
				GPIOD->AFR[1] |= (2<<16);

				this->setupPWMpin(GPIOD,12);
				this->setupTimxOCx(TIM4,0);

			break;

		//OC2

			case 2: // PORTB7

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM4)
				GPIOB->AFR[0] &= ~(15<<28);
				GPIOB->AFR[0] |= (2<<28);

				this->setupPWMpin(GPIOB,7);
				this->setupTimxOCx(TIM4,1);

			break;
			case 3: // PORTD13

				//enable GPIOD clock
				RCC->AHB1ENR |= (1<<3);
				//PDx alternate function AF02 (TIM4)
				GPIOD->AFR[1] &= ~(15<<20);
				GPIOD->AFR[1] |= (2<<20);

				this->setupPWMpin(GPIOD,13);
				this->setupTimxOCx(TIM4,1);

			break;


		//OC3

			case 4: // PORTB8

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM4)
				GPIOB->AFR[1] &= ~(15<<0);
				GPIOB->AFR[1] |= (2<<0);

				this->setupPWMpin(GPIOB,8);
				this->setupTimxOCx(TIM4,2);

			break;
			case 5: // PORTD14

				//enable GPIOD clock
				RCC->AHB1ENR |= (1<<3);
				//PDx alternate function AF02 (TIM4)
				GPIOD->AFR[1] &= ~(15<<24);
				GPIOD->AFR[1] |= (2<<24);

				this->setupPWMpin(GPIOD,14);
				this->setupTimxOCx(TIM4,2);

			break;

		//OC4

			case 6: // PORTB9

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF02 (TIM4)
				GPIOB->AFR[1] &= ~(15<<4);
				GPIOB->AFR[1] |= (2<<4);

				this->setupPWMpin(GPIOB,9);
				this->setupTimxOCx(TIM4,3);

			break;
			case 7: // PORTD15

				//enable GPIOD clock
				RCC->AHB1ENR |= (1<<3);
				//PDx alternate function AF02 (TIM4)
				GPIOD->AFR[1] &= ~(15<<28);
				GPIOD->AFR[1] |= (2<<28);

				this->setupPWMpin(GPIOD,15);
				this->setupTimxOCx(TIM4,3);

			break;


		default:
			// unexpected configuration
		break;
	}
	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer5Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer5;

	//register hardware
	this->tim = TIM5;

	//enable TIM5 clock
	RCC->APB1ENR |= 8;
	//stop TIM5
	TIM5->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTA0

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF02 (TIM5)
				GPIOA->AFR[0] &= ~(15<<0);
				GPIOA->AFR[0] |= (2<<0);

				this->setupPWMpin(GPIOA,0);
				this->setupTimxOCx(TIM5,0);

			break;

		//OC2

			case 1: // PORTA1

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF02 (TIM5)
				GPIOA->AFR[0] &= ~(15<<4);
				GPIOA->AFR[0] |= (2<<4);

				this->setupPWMpin(GPIOA,1);
				this->setupTimxOCx(TIM5,1);

			break;

		//OC3

			case 2: // PORTA2

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF02 (TIM5)
				GPIOA->AFR[0] &= ~(15<<8);
				GPIOA->AFR[0] |= (2<<8);

				this->setupPWMpin(GPIOA,2);
				this->setupTimxOCx(TIM5,2);

			break;

		//OC4

			case 3: // PORTA3

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF02 (TIM5)
				GPIOA->AFR[0] &= ~(15<<12);
				GPIOA->AFR[0] |= (2<<12);

				this->setupPWMpin(GPIOA,3);
				this->setupTimxOCx(TIM5,3);

			break;

		default:
			// unexpected configuration
		break;
	}
	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer9Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer9;

	//register hardware
	this->tim = TIM9;

	//enable TIM9 clock
	RCC->APB2ENR |= (1<<16);
	//stop TIM9
	TIM9->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTA2

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF03 (TIM9)
				GPIOA->AFR[0] &= ~(15<<8);
				GPIOA->AFR[0] |= (3<<8);

				this->setupPWMpin(GPIOA,2);
				this->setupTimxOCx(TIM9,0);

			break;

			case 1: // PORTE5

				//enable GPIOE clock
				RCC->AHB1ENR |= (1<<4);
				//PEx alternate function AF03 (TIM9)
				GPIOE->AFR[0] &= ~(15<<20);
				GPIOE->AFR[0] |= (3<<20);

				this->setupPWMpin(GPIOE,5);
				this->setupTimxOCx(TIM9,0);

			break;

		// OC2

			case 2: // PORTA3

				//enable GPIOA clock
				RCC->AHB1ENR |= 1;
				//PAx alternate function AF03 (TIM9)
				GPIOA->AFR[0] &= ~(15<<12);
				GPIOA->AFR[0] |= (3<<12);

				this->setupPWMpin(GPIOA,3);
				this->setupTimxOCx(TIM9,1);

			break;

			case 3: // PORTE6

				//enable GPIOE clock
				RCC->AHB1ENR |= (1<<4);
				//PEx alternate function AF03 (TIM9)
				GPIOE->AFR[0] &= ~(15<<24);
				GPIOE->AFR[0] |= (3<<24);

				this->setupPWMpin(GPIOE,6);
				this->setupTimxOCx(TIM9,1);

			break;


			default:
				// unexpected configuration
			break;
	}
	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer10Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer10;

	//register hardware
	this->tim = TIM10;

	//enable TIM10 clock
	RCC->APB2ENR |= (1<<17);
	//stop TIM10
	TIM10->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTB8

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF03 (TIM10)
				GPIOB->AFR[1] &= ~(15<<0);
				GPIOB->AFR[1] |= (3<<0);

				this->setupPWMpin(GPIOB,8);
				this->setupTimxOCx(TIM10,0);

			break;

			default:
				// unexpected configuration
			break;
	}
	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer11Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer11;

	//register hardware
	this->tim = TIM11;

	//enable TIM11 clock
	RCC->APB2ENR |= (1<<18);
	//stop TIM10
	TIM11->CR1 &= ~(1);


	switch(reg_add)
	{

		// OC1

			case 0: // PORTB9

				//enable GPIOB clock
				RCC->AHB1ENR |= 2;
				//PBx alternate function AF03 (TIM11)
				GPIOB->AFR[1] &= ~(15<<4);
				GPIOB->AFR[1] |= (3<<4);

				this->setupPWMpin(GPIOB,9);
				this->setupTimxOCx(TIM11,0);

			break;

			default:
				// unexpected configuration
			break;
	}
	return *this;
}
kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_EXTI0_Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::EXTI0;


	//enable clock for system configuration controller
	RCC->APB2ENR |= (1<<14);

	switch(reg_add)
	{
		case 0:	// PORTA0

			//enable GPIOA clock
			RCC->AHB1ENR |= 1;

			//set PORTA0 as input
			GPIOA->MODER &= ~3;

			// enable interrupt request on line 0
			EXTI->IMR |= 1;

			// enable interrupt signal from rising edge
			EXTI->RTSR |= 1;

			// attach input value storages with IRQ handler function
			input_storage[0] = &this->input;
			last_timer_value[0] = &this->last_timer_val;

			// change EXTI0 function handler to handle kPWM library
			kSystem.setIRQHandler(6,kPWM_EXTI0_IRQ_Handler);
			kSystem.enableInterrupt(EXTI0_IRQn,0,1);

		break;

		default:
			// unexpected pwmHard value

		break;
	}

	return *this;
}

void kPWM::run(unsigned short int resolution, unsigned int tick_freq)
{

	unsigned int timer_clock;
	unsigned int prescaler;

	if(this->hardware.tim == TIM1 ||
	   this->hardware.tim == TIM9 ||
	   this->hardware.tim == TIM10 ||
	   this->hardware.tim == TIM11)
	{
		timer_clock = kSystem.APB2_Timer_CLK();

	}else if(this->hardware.tim == TIM2 ||
			 this->hardware.tim == TIM3 ||
			 this->hardware.tim == TIM4 ||
			 this->hardware.tim == TIM5)
	{
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

void kPWM::operator = (unsigned short int value)
{
	*(this->hardware.output) = (uint32_t)value;
}
kPWM::operator unsigned int()
{
	return (unsigned int)this->hardware.input;
}
