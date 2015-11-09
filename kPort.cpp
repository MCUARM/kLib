#include "kPort.h"

kPort::kPort(GPIO_TypeDef * GPIO)
{
	this->gpio = GPIO;
}

kPort PORTA(GPIOA);
kPort PORTB(GPIOB);
kPort PORTC(GPIOC);
kPort PORTD(GPIOD);
kPort PORTE(GPIOE);
kPort PORTF(GPIOF);
kPort PORTG(GPIOG);
kPort PORTH(GPIOH);
kPort PORTI(GPIOI);

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
