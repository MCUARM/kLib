
#ifndef __kPWM_H
#define __kPWM_H


	/*Issues
	 *
	 * At this time library support following hardware
	 * TIM1, TIM2, TIM3, TIM4, TIM5, TIM9, TIM10
	 *
	 *
	 * TIM1
	 * -all channels work properly
	 *
	 * TIM2
	 * -OC2 doesn't work at PORTA1
	 * -OC3 doesn't work at PORTA2
	 *
	 * TIM3
	 * -all channels work properly
	 *
	 * TIM4
	 * -all channels work properly
	 *
	 * TIM5
	 * -OC2 doesn't work at PORTA1
	 * -OC3 doesn't work at PORTA2
	 *
	 * TIM9
	 * -OC1 doesn't work at PORTA2
	 *
	 * TIM10
	 * -OC1 available, work properly
	 *
	 * TIM11
	 * -OC1 available, work properly
	 *
	 * tested under stm32f429xx/
	*/

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "misc.h"
	#include "kSystem.h"


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

	typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_Timer3Pin;

		typedef struct
		{
			kPWM_Timer3Pin PORTA6;
			kPWM_Timer3Pin PORTB4;
			kPWM_Timer3Pin PORTC6;
		}kPWM_OC1_Timer3;

		typedef struct
		{
			kPWM_Timer3Pin PORTA7;
			kPWM_Timer3Pin PORTB5;
			kPWM_Timer3Pin PORTC7;
		}kPWM_OC2_Timer3;

		typedef struct
		{
			kPWM_Timer3Pin PORTB0;
			kPWM_Timer3Pin PORTC8;
		}kPWM_OC3_Timer3;

		typedef struct
		{
			kPWM_Timer3Pin PORTB1;
			kPWM_Timer3Pin PORTC9;
		}kPWM_OC4_Timer3;

		typedef struct
		{
			kPWM_OC1_Timer3 OC1;
			kPWM_OC2_Timer3 OC2;
			kPWM_OC3_Timer3 OC3;
			kPWM_OC4_Timer3 OC4;

		}kPWM_Timer3;

		typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_Timer4Pin;

		typedef struct
		{
			kPWM_Timer4Pin PORTB6;
			kPWM_Timer4Pin PORTD12;
		}kPWM_OC1_Timer4;

		typedef struct
		{
			kPWM_Timer4Pin PORTB7;
			kPWM_Timer4Pin PORTD13;
		}kPWM_OC2_Timer4;

		typedef struct
		{
			kPWM_Timer4Pin PORTB8;
			kPWM_Timer4Pin PORTD14;
		}kPWM_OC3_Timer4;

		typedef struct
		{
			kPWM_Timer4Pin PORTB9;
			kPWM_Timer4Pin PORTD15;
		}kPWM_OC4_Timer4;

		typedef struct
		{
			kPWM_OC1_Timer4 OC1;
			kPWM_OC2_Timer4 OC2;
			kPWM_OC3_Timer4 OC3;
			kPWM_OC4_Timer4 OC4;

		}kPWM_Timer4;

		typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_Timer5Pin;

		typedef struct
		{
			kPWM_Timer5Pin PORTA0;
		}kPWM_OC1_Timer5;

		typedef struct
		{
			kPWM_Timer5Pin PORTA1;
		}kPWM_OC2_Timer5;

		typedef struct
		{
			kPWM_Timer5Pin PORTA2;
		}kPWM_OC3_Timer5;

		typedef struct
		{
			kPWM_Timer5Pin PORTA3;
		}kPWM_OC4_Timer5;

		typedef struct
		{
			kPWM_OC1_Timer5 OC1;
			kPWM_OC2_Timer5 OC2;
			kPWM_OC3_Timer5 OC3;
			kPWM_OC4_Timer5 OC4;

		}kPWM_Timer5;


		typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_Timer9Pin;

		typedef struct
		{
			kPWM_Timer9Pin PORTA2;
			kPWM_Timer9Pin PORTE5;
		}kPWM_OC1_Timer9;

		typedef struct
		{
			kPWM_Timer9Pin PORTA3;
			kPWM_Timer9Pin PORTE6;
		}kPWM_OC2_Timer9;

		typedef struct
		{
			kPWM_OC1_Timer9 OC1;
			kPWM_OC2_Timer9 OC2;

		}kPWM_Timer9;

		typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_Timer10Pin;

		typedef struct
		{
			kPWM_Timer10Pin PORTB8;
		}kPWM_OC1_Timer10;

		typedef struct
		{
			kPWM_OC1_Timer10 OC1;
		}kPWM_Timer10;

		typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_Timer11Pin;

		typedef struct
		{
			kPWM_Timer11Pin PORTB9;
		}kPWM_OC1_Timer11;

		typedef struct
		{
			kPWM_OC1_Timer11 OC1;
		}kPWM_Timer11;

		typedef struct
		{
			unsigned char kPWM_Pin;
		}kPWM_EXTI0_Pin;

		typedef struct
		{
			kPWM_EXTI0_Pin PORTA0;
			kPWM_EXTI0_Pin PORTB0;
			kPWM_EXTI0_Pin PORTC0;
			kPWM_EXTI0_Pin PORTD0;
			kPWM_EXTI0_Pin PORTE0;
			kPWM_EXTI0_Pin PORTF0;
			kPWM_EXTI0_Pin PORTG0;
		}kPWM_EXTI0;


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
			private:

				uint32_t last_timer_val;

				void setupPWMpin(GPIO_TypeDef * GPIOx, unsigned char pin);
				void setupTimxOCx(TIM_TypeDef * TIMx, unsigned char channel_from_zero);

				uint32_t default_CCR;

			public:


				TIM_TypeDef * tim;
				uint32_t * output;
				uint32_t input;

				kPWMHardware(void);



				kPWMHardware& operator = (const kPWM_Timer2Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer1Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer3Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer4Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer5Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer9Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer10Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_Timer11Pin & pwmHard);

				kPWMHardware& operator = (const kPWM::kPWM_ActiveState state);

				kPWMHardware& operator = (const kPWM_EXTI0_Pin & pwmHard);



		};


			kPWM(void);


			void run(unsigned short int resolution, unsigned int tick_freq);

			void operator = (unsigned short int value);

			//extract input pwm duty
			operator unsigned int();


			kPWMHardware hardware;

			static const kPWM_Timer1 * Timer1;
			static const kPWM_Timer2 * Timer2;
			static const kPWM_Timer3 * Timer3;
			static const kPWM_Timer4 * Timer4;
			static const kPWM_Timer5 * Timer5;
			static const kPWM_Timer9 * Timer9;
			static const kPWM_Timer10 * Timer10;
			static const kPWM_Timer11 * Timer11;

			static const kPWM_EXTI0 * EXTI0;

	};


#endif
