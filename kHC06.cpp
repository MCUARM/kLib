#include "kHC06.h"

void kHC06::setName(char * new_name)
{
	*this << "AT+NAME" << new_name;

}
void kHC06::setPin(char * new_pin)
{
	*this << "AT+PIN" << new_pin;
}
