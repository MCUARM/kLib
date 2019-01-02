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



#include "kPort.h"

#ifdef kPort_config_USE_PORTA_OBJECT
 	kPort PORTA(GPIOA);
#endif
#ifdef kPort_config_USE_PORTB_OBJECT
 	kPort PORTB(GPIOB);
#endif
#ifdef kPort_config_USE_PORTC_OBJECT
 	kPort PORTC(GPIOC);
#endif
#ifdef kPort_config_USE_PORTD_OBJECT
 	kPort PORTD(GPIOD);
#endif
#ifdef kPort_config_USE_PORTE_OBJECT
 	kPort PORTE(GPIOE);
#endif
#ifdef kPort_config_USE_PORTF_OBJECT
 	kPort PORTF(GPIOF);
#endif
#ifdef kPort_config_USE_PORTG_OBJECT
 	kPort PORTG(GPIOG);
#endif
#ifdef kPort_config_USE_PORTH_OBJECT
 	kPort PORTH(GPIOH);
#endif
#ifdef kPort_config_USE_PORTI_OBJECT
 	kPort PORTI(GPIOI);
#endif
#ifdef kPort_config_USE_PORTJ_OBJECT
 	kPort PORTJ(GPIOJ);
#endif
#ifdef kPort_config_USE_PORTK_OBJECT
 	kPort PORTK(GPIOK);
#endif

kPort::kPort(GPIO_TypeDef * GPIO) : gpio(GPIO)
{

}



kPin kPort::operator [](const unsigned char pin)
{
	kPin res;

	res.gpio = this->gpio;
	res.pin = pin;

	return res;
}



kPin::operator unsigned char()
{
	unsigned int val = this->gpio->IDR;
	val &= (unsigned int)(1 << this->pin);
	val = val >> this->pin;

	return (unsigned char)val;
}

kPort::operator unsigned short int()
{
	return (unsigned short int)this->gpio->IDR;
}
void kPort::operator =(const unsigned int state)
{
	this->gpio->ODR = (state & 0x0000FFFF);
}
void kPin::operator = (unsigned char state)
{
	state &= 0x01;

	unsigned int mask = (unsigned int)(1 << this->pin);
	mask = ~mask;
	unsigned int val = this->gpio->ODR & mask;
	val |= (unsigned int)(state << this->pin);
	this->gpio->ODR = val;
}
const kPin& kPin::operator = (kPinMode mode)
{
	unsigned int mask =  (unsigned int)(0x03 << (this->pin << 1));
	mask = ~mask;
	unsigned int reg = this->gpio->MODER;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)mode << (this->pin << 1));

	this->gpio->MODER = reg;

	return *this;
}
const kPin& operator , (const kPin& pin, kPin::kPinMode mode)
{
	unsigned int mask =  (unsigned int)(0x03 << (pin.pin << 1));
	mask = ~mask;
	unsigned int reg = pin.gpio->MODER;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)mode << (pin.pin << 1));

	pin.gpio->MODER = reg;

	return pin;
}
const kPin& kPin::operator = (kPullResistor pullResistor)
{
	unsigned int mask =  (unsigned int)(0x03 << (this->pin << 1));
	mask = ~mask;
	unsigned int reg = this->gpio->PUPDR;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)pullResistor << (this->pin << 1));

	this->gpio->PUPDR = reg;

	return *this;
}
const kPin& operator , (const kPin& pin, kPin::kPullResistor pullResistor)
{
	unsigned int mask =  (unsigned int)(0x03 << (pin.pin << 1));
	mask = ~mask;
	unsigned int reg = pin.gpio->PUPDR;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)pullResistor << (pin.pin << 1));

	pin.gpio->PUPDR = reg;

	return pin;
}
const kPin& kPin::operator = (kPinSpeed speed)
{
	unsigned int mask = (unsigned int)(0x03 << (this->pin << 1));
	mask = ~mask;
	unsigned int reg = this->gpio->OSPEEDR;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)speed << (this->pin << 1));

	this->gpio->OSPEEDR = reg;

	return *this;
}
const kPin& operator , (const kPin& pin, kPin::kPinSpeed speed)
{
	unsigned int mask =  (unsigned int)(0x03 << (pin.pin << 1));
	mask = ~mask;
	unsigned int reg = pin.gpio->OSPEEDR;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)speed << (pin.pin << 1));

	pin.gpio->OSPEEDR = reg;

	return pin;
}
const kPin& kPin::operator = (kPinOutType outType)
{
	unsigned int mask =  (unsigned int)(0x01 << this->pin);
	mask = ~mask;
	unsigned int reg = this->gpio->OTYPER;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)outType << this->pin);

	this->gpio->OTYPER = reg;

	return *this;
}
const kPin& operator , (const kPin& pin, kPin::kPinOutType outType)
{
	unsigned int mask =  (unsigned int)(0x01 << pin.pin);
	mask = ~mask;
	unsigned int reg = pin.gpio->OTYPER;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)outType << pin.pin);

	pin.gpio->OTYPER = reg;

	return pin;
}
void kPort::operator = (kPortPower power)
{
	// get bit position in RCC_AHB1ENR register
	unsigned int bitPos = ((unsigned int)this->gpio) - ((unsigned int)GPIOA_BASE);
	bitPos = bitPos >> 10;

	unsigned int mask = (unsigned int)(0x01 << bitPos);
	mask = ~mask;
	unsigned int reg = RCC->AHB1ENR;
	reg &= mask;
	reg |= (unsigned int)((unsigned int)power << bitPos);

	RCC->AHB1ENR = reg;
}
void kPin::operator = (kPin & pin)
{
	unsigned char val = pin;
	*this = val;
}
void kPin::operator = (kPin::kPIN_PIN new_pin)
{
	this->pin = (((unsigned char)new_pin)&0x0F);

	this->gpio = (GPIO_TypeDef*)(((unsigned int)AHB1PERIPH_BASE)+((((unsigned int)new_pin)& 0x000000F0) << 6));
}
kPin::kPin(GPIO_TypeDef * GPIO,unsigned char PIN)
{
	this->gpio = GPIO;
	this->pin = PIN;
}
kPin::kPin(void)
{

}
kPin::kPin(const kPin & pin)
{
	this->gpio = pin.gpio;
	this->pin = pin.pin;
}
void kPin::set(void)
{
	this->gpio->ODR |= (unsigned int)(1 << this->pin);
}
void kPin::reset(void)
{
	this->gpio->ODR &= ~(unsigned int)(1 << this->pin);
}
void kPin::toggle(void)
{
	this->gpio->ODR ^= (unsigned int)(1 << this->pin);
}
unsigned char kPin::get(void)
{
	unsigned int val = this->gpio->IDR;
	val &= (unsigned int)(1 << this->pin);
	val = val >> this->pin;

	return (unsigned char)val;
}

// examples
/**
  * @example kPort_example_LED.cpp
  * @brief This example shows how to use kPin class to control LED diode
  */

