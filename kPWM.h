
#ifndef __kPWM_H
#define __kPWM_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"

	typedef struct
	{
		unsigned char kPWM_Pin;
	}kPWM_Timer1Pin;

	typedef struct
	{
		kPWM_Timer1Pin PORTA8;
		kPWM_Timer1Pin PORTE9;
	}kPWM_OC1_Timer1;

	typedef struct
	{
		kPWM_Timer1Pin PORTA9;
		kPWM_Timer1Pin PORTE11;
	}kPWM_OC2_Timer1;

	typedef struct
	{
		kPWM_Timer1Pin PORTA10;
		kPWM_Timer1Pin PORTE13;
	}kPWM_OC3_Timer1;

	typedef struct
	{
		kPWM_Timer1Pin PORTA11;
		kPWM_Timer1Pin PORTE14;
	}kPWM_OC4_Timer1;

	typedef struct
	{
		kPWM_OC1_Timer1 OC1;
		kPWM_OC2_Timer1 OC2;
		kPWM_OC3_Timer1 OC3;
		kPWM_OC4_Timer1 OC4;

	}kPWM_Timer1;




	class kPWM
	{
		public:

			typedef enum
			{
				activeHigh,
				activeLow
			}kPWM_ActiveState;

		class kPWMHardware
		{
			public:

				GPIO_TypeDef * gpio;
				unsigned char pin;

				kPWMHardware& operator = (const kPWM_Timer1Pin & pwmHard);
				kPWMHardware& operator , (const kPWM_Timer1Pin & pwmHard);

				kPWMHardware& operator = (const kPWM_ActiveState state);
				kPWMHardware& operator , (const kPWM_ActiveState state);

		};


			kPWMHardware hardware;

			static const kPWM_Timer1 * Timer1;


	};

#endif
