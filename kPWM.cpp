#include "kPWM.h"

const kPWM_Timer1 * kPWM::Timer1 = (kPWM_Timer1 *)SRAM1_BASE;
const kPWM_Timer2 * kPWM::Timer2 = (kPWM_Timer2 *)SRAM1_BASE;
const kPWM_Timer3 * kPWM::Timer3 = (kPWM_Timer3 *)SRAM1_BASE;
const kPWM_Timer4 * kPWM::Timer4 = (kPWM_Timer4 *)SRAM1_BASE;
const kPWM_Timer5 * kPWM::Timer5 = (kPWM_Timer5 *)SRAM1_BASE;
const kPWM_Timer9 * kPWM::Timer9 = (kPWM_Timer9 *)SRAM1_BASE;
const kPWM_Timer10 * kPWM::Timer10 = (kPWM_Timer10 *)SRAM1_BASE;
const kPWM_Timer11 * kPWM::Timer11 = (kPWM_Timer11 *)SRAM1_BASE;

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
	TIM2->CR1 &= ~(1);


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
void kPWM::run(unsigned short int resolution, unsigned int tick_freq)
{

	unsigned int timer_clock;
	unsigned int prescaler;

	if(this->hardware.tim == TIM1)
	{
		timer_clock = kSystem.APB2_Timer_CLK();
	}else if(this->hardware.tim == TIM2 || this->hardware.tim == TIM3)
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
