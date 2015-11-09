#include "kSystem.h"

k_System kSystem;

k_System::k_System(void)
{
	this->timerReady = 0;
	SysTick->LOAD = 0xFFFFFF;
	// enable SystemTick
	SysTick->CTRL |= 1;

	this->init();
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

			//N mulit
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
