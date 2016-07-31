#include "kAngle.h"


float kAngle::setInBounds_0_to_2pi(float angle_in_radians)
{
	int int_part = (int)((float)(angle_in_radians/kMath::_2pi));
	if(int_part < 0) int_part++;
	return (angle_in_radians - ((float)(int_part))*kMath::_2pi);
}
float kAngle::setInBounds_minus_pi_to_pi(float angle_in_radians)
{
	int int_part = (int)((float)(angle_in_radians/kMath::_pi));
	if(int_part < 0) int_part++;
	return (angle_in_radians - ((float)(int_part))*kMath::_pi);
}

float kAngle::getAngleError(kAngle_0_to_2pi & reference_signal,kAngle_0_to_2pi & signal)
{
	float res;
	float path_1,path_2,abs_path_1,abs_path_2;

	// get path 1
	path_1 = reference_signal.value - signal.value;

	// get path 2
	// two cases:
	if( reference_signal.value > signal.value )
	{
		path_2  = reference_signal.value - kMath::_2pi;
		path_2 -= signal.value;
	}else
	{
		path_2 =  kMath::_2pi - signal.value;
		path_2 += reference_signal.value;
	}

	// get absolute values of two paths
	abs_path_1 = path_1;
	if(abs_path_1 < 0) abs_path_1 *= (-1);

	abs_path_2 = path_2;
	if(abs_path_2 < 0) abs_path_2 *= (-1);

	// select shorter path
	if(abs_path_1 < abs_path_2)
	{
		res = path_1;
	}else
	{
		res = path_2;
	}


	return res;
}
float kAngle::getAngleError(kAngle_minus_pi_to_pi & reference_signal,kAngle_minus_pi_to_pi & signal)
{
	kAngle_0_to_2pi ang1 = reference_signal;
	kAngle_0_to_2pi ang2 = signal;
	return kAngle::getAngleError(ang1,ang2);
}









kAngle_0_to_2pi::kAngle_0_to_2pi(const kAngle_minus_pi_to_pi & other)
{
	this->value = kAngle::setInBounds_0_to_2pi(other.value);
}

kAngle_0_to_2pi::kAngle_0_to_2pi(const float & f)
{
	this->value = kAngle::setInBounds_0_to_2pi(f);
}
kAngle_0_to_2pi::operator float()
{
	return this->value;
}
void kAngle_0_to_2pi::operator = (float & val)
{
	this->value = val;
	this->value = kAngle::setInBounds_0_to_2pi(this->value);
}
void kAngle_0_to_2pi::operator += (float & val)
{
	this->value+=val;
	this->value = kAngle::setInBounds_0_to_2pi(this->value);
}
void kAngle_0_to_2pi::operator -= (float & val)
{
	this->value-=val;
	this->value = kAngle::setInBounds_0_to_2pi(this->value);
}
void kAngle_0_to_2pi::operator *= (float & val)
{
	this->value *=val;
	this->value = kAngle::setInBounds_0_to_2pi(this->value);
}
void kAngle_0_to_2pi::operator /= (float & val)
{
	this->value /= val;
	this->value = kAngle::setInBounds_0_to_2pi(this->value);
}



void kAngle_0_to_2pi::operator = (kAngle_0_to_2pi & ang)
{
	this->value = kAngle::setInBounds_0_to_2pi(ang.value);
}
void kAngle_0_to_2pi::operator += (kAngle_0_to_2pi & ang)
{
	(*this) += ang.value;
}
void kAngle_0_to_2pi::operator -= (kAngle_0_to_2pi & ang)
{
	(*this) -= ang.value;
}
void kAngle_0_to_2pi::operator *= (kAngle_0_to_2pi & ang)
{
	(*this) *= ang.value;
}
void kAngle_0_to_2pi::operator /= (kAngle_0_to_2pi & ang)
{
	(*this) /= ang.value;
}

float kAngle_0_to_2pi::operator +(kAngle_0_to_2pi & ang)
{
	return ((*this)+ang.value);
}
float kAngle_0_to_2pi::operator -(kAngle_0_to_2pi & ang)
{
	return ((*this)-ang.value);
}
float kAngle_0_to_2pi::operator *(kAngle_0_to_2pi & ang)
{
	return ((*this)*ang.value);
}
float kAngle_0_to_2pi::operator /(kAngle_0_to_2pi & ang)
{
	return ((*this)/ang.value);
}


bool kAngle_0_to_2pi::operator == (kAngle_0_to_2pi & ang)
{
	return (this->value == ang.value);
}
bool kAngle_0_to_2pi::operator > (kAngle_0_to_2pi & ang)
{
	return (this->value > ang.value);
}
bool kAngle_0_to_2pi::operator < (kAngle_0_to_2pi & ang)
{
	return (this->value < ang.value);
}
void kAngle_0_to_2pi::operator = (kAngle_minus_pi_to_pi & ang)
{
	this->value = kAngle::setInBounds_0_to_2pi(ang.value);
}










kAngle_minus_pi_to_pi::kAngle_minus_pi_to_pi(const kAngle_0_to_2pi & other)
{
	this->value = kAngle::setInBounds_minus_pi_to_pi(other.value);
}

kAngle_minus_pi_to_pi::kAngle_minus_pi_to_pi(const float & f)
{
	this->value = kAngle::setInBounds_minus_pi_to_pi(f);
}
kAngle_minus_pi_to_pi::operator float()
{
	return this->value;
}
void kAngle_minus_pi_to_pi::operator = (float & val)
{
	this->value = val;
	this->value = kAngle::setInBounds_minus_pi_to_pi(this->value);
}
void kAngle_minus_pi_to_pi::operator += (float & val)
{
	this->value+=val;
	this->value = kAngle::setInBounds_minus_pi_to_pi(this->value);
}
void kAngle_minus_pi_to_pi::operator -= (float & val)
{
	this->value-=val;
	this->value = kAngle::setInBounds_minus_pi_to_pi(this->value);
}
void kAngle_minus_pi_to_pi::operator *= (float & val)
{
	this->value *=val;
	this->value = kAngle::setInBounds_minus_pi_to_pi(this->value);
}
void kAngle_minus_pi_to_pi::operator /= (float & val)
{
	this->value /= val;
	this->value = kAngle::setInBounds_minus_pi_to_pi(this->value);
}



void kAngle_minus_pi_to_pi::operator = (kAngle_minus_pi_to_pi & ang)
{
	this->value = kAngle::setInBounds_minus_pi_to_pi(ang.value);
}
void kAngle_minus_pi_to_pi::operator += (kAngle_minus_pi_to_pi & ang)
{
	(*this) += ang.value;
}
void kAngle_minus_pi_to_pi::operator -= (kAngle_minus_pi_to_pi & ang)
{
	(*this) -= ang.value;
}
void kAngle_minus_pi_to_pi::operator *= (kAngle_minus_pi_to_pi & ang)
{
	(*this) *= ang.value;
}
void kAngle_minus_pi_to_pi::operator /= (kAngle_minus_pi_to_pi & ang)
{
	(*this) /= ang.value;
}

float kAngle_minus_pi_to_pi::operator +(kAngle_minus_pi_to_pi & ang)
{
	return ((*this)+ang.value);
}
float kAngle_minus_pi_to_pi::operator -(kAngle_minus_pi_to_pi & ang)
{
	return ((*this)-ang.value);
}
float kAngle_minus_pi_to_pi::operator *(kAngle_minus_pi_to_pi & ang)
{
	return ((*this)*ang.value);
}
float kAngle_minus_pi_to_pi::operator /(kAngle_minus_pi_to_pi & ang)
{
	return ((*this)/ang.value);
}


bool kAngle_minus_pi_to_pi::operator == (kAngle_minus_pi_to_pi & ang)
{
	return (this->value == ang.value);
}
bool kAngle_minus_pi_to_pi::operator > (kAngle_minus_pi_to_pi & ang)
{
	return (this->value > ang.value);
}
bool kAngle_minus_pi_to_pi::operator < (kAngle_minus_pi_to_pi & ang)
{
	return (this->value < ang.value);
}

void kAngle_minus_pi_to_pi::operator = (kAngle_0_to_2pi & ang)
{
	this->value = kAngle::setInBounds_minus_pi_to_pi(ang.value);
}
