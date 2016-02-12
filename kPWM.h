
#ifndef __kPWM_H
#define __kPWM_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "kSystem.h"
	#include "stm32f4xx_tim.h"

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




	typedef struct
	{
		unsigned char kPWM_Pin;
	}kPWM_Timer2Pin;

	typedef struct
	{
		kPWM_Timer2Pin PORTA0;
		kPWM_Timer2Pin PORTA5;
		kPWM_Timer2Pin PORTA15;
	}kPWM_OC1_Timer2;

	typedef struct
	{
		kPWM_Timer2Pin PORTA1;
		kPWM_Timer2Pin PORTB3;
	}kPWM_OC2_Timer2;

	typedef struct
	{
		kPWM_Timer2Pin PORTA2;
		kPWM_Timer2Pin PORTB10;
	}kPWM_OC3_Timer2;

	typedef struct
	{
		kPWM_Timer2Pin PORTA3;
		kPWM_Timer2Pin PORTB11;
	}kPWM_OC4_Timer2;

	typedef struct
	{
		kPWM_OC1_Timer2 OC1;
		kPWM_OC2_Timer2 OC2;
		kPWM_OC3_Timer2 OC3;
		kPWM_OC4_Timer2 OC4;

	}kPWM_Timer2;



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
			uint32_t default_CCR;

			public:


				TIM_TypeDef * tim;
				uint32_t * output;

				kPWMHardware(void);

				kPWMHardware& operator = (const kPWM_Timer2Pin & pwmHard);
				kPWMHardware& operator , (const kPWM_Timer2Pin & pwmHard);

				kPWMHardware& operator = (const kPWM::kPWM_ActiveState state);
				kPWMHardware& operator , (const kPWM::kPWM_ActiveState state);




		};


			kPWM(void);


			void start(unsigned short int resolution, unsigned int tick_freq);

			kPWMHardware hardware;

			static const kPWM_Timer1 * Timer1;
			static const kPWM_Timer2 * Timer2;


	};


#endif
