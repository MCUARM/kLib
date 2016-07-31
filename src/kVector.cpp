#include "kVector.h"
#include "kQuaternion.h"

void kVector::add(kVector & result,kVector & vector_1, kVector & vector_2)
{
	unsigned char i;
	for(i=0;i<result.elements;i++) result.buff[i] = vector_1.buff[i] + vector_2.buff[i];
}
void kVector::subtract(kVector & result,kVector & vector_1, kVector & vector_2)
{
	unsigned char i;
	for(i=0;i<result.elements;i++) result.buff[i] = vector_1.buff[i] - vector_2.buff[i];
}
void kVector::multiply(kVector & result,kVector & vector,float value)
{
	unsigned char i;
	for(i=0;i<result.elements;i++) result.buff[i] = vector.buff[i]*value;
}


void kVector::operator = (kVector & v)
{
	unsigned char i;
	for(i=0;i<this->elements;i++) this->buff[i] = v.buff[i];
}
void kVector::operator += (kVector & v)
{
	unsigned char i;
	for(i=0;i<this->elements;i++) this->buff[i] += v.buff[i];
}
void kVector::operator -= (kVector & v)
{
	unsigned char i;
	for(i=0;i<this->elements;i++) this->buff[i] -= v.buff[i];
}
bool kVector::operator == (kVector & v)
{
	unsigned char i;
	for(i=0;i<this->elements;i++)
	{
		if(this->buff[i] != v.buff[i]) return false;
	}

	return true;
}




void kVector::operator *= (float scalar)
{
	unsigned char i;
	for(i=0;i<this->elements;i++) this->buff[i] *= scalar;
}
float kVector::length(void)
{
	float res=0;
	unsigned char i;
	for(i=0;i<this->elements;i++)
	{
		res+= this->buff[i]*this->buff[i];
	}
	return sqrtf(res);
}
void kVector::makeUnit(void)
{
	float scale = this->length();
	(*this) *= 1/scale;
}

void kVector::add(kVector2 & result,kVector2 & vector_1, kVector2 & vector_2)
{
	kVector::add((kVector&)result,(kVector&)vector_1,(kVector&)vector_2);
}
void kVector::subtract(kVector2 & result,kVector2 & vector_1, kVector2 & vector_2)
{
	kVector::subtract((kVector&)result,(kVector&)vector_1,(kVector&)vector_2);
}
void kVector::multiply(kVector2 & result,kVector2 & vector,float value)
{
	kVector::multiply((kVector&)result,(kVector&)vector,value);
}










kVector2::kVector2(void)
{
	this->buff = &this->x;
	this->elements = 2;
}
kVector2::kVector2(kVector2 & other)
{
	this->buff = &this->x;
	this->elements = 2;

	this->x = other.x;
	this->y = other.y;
}
kVector2::kVector2(float X, float Y)
{
	this->buff = &this->x;
	this->elements = 2;

	this->x = X;
	this->y = Y;
}

void kVector2::operator += (kVector2 & v)
{
	kVector::operator +=((kVector&)v);
}
void kVector2::operator -= (kVector2 & v)
{
	kVector::operator -=((kVector&)v);
}
void kVector2::operator = (kVector2 & v)
{
	kVector::operator =((kVector&)v);
}
bool kVector2::operator == (kVector2 & v)
{
	return kVector::operator ==((kVector&)v);
}

void kVector2::rotate(float angle)
{
	float cos_angle = cosf(angle);
	float sin_angle = sinf(angle);

	float res_x;

	res_x =   cos_angle*this->x
			- sin_angle*this->y;

	this->y =   sin_angle*this->x
			  + cos_angle*this->y;

	this->x = res_x;
}
kVector3::kVector3(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
kVector3::kVector3(kVector3 & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}
kVector3::kVector3(float X, float Y, float Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}

void kVector3::operator += (kVector3 & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
void kVector3::operator -= (kVector3 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
void kVector3::operator *= (float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}
kVector3 kVector3::operator +(kVector3 & v)
{
	kVector3 res(this->x+v.x,this->y+v.y,this->z+v.z);
	return res;
}
kVector3 kVector3::operator -(kVector3 & v)
{
	kVector3 res(this->x-v.x,this->y-v.y,this->z-v.z);
	return res;
}
kVector3 kVector3::operator *(float scalar)
{
	kVector3 res(this->x*scalar,this->y*scalar,this->z*scalar);
	return res;
}
void kVector3::operator = (const kVector3 & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
void kVector3::operator = (const kQuaternion & q)
{
	this->x = q.i;
	this->y = q.j;
	this->z = q.k;
}

bool kVector3::operator == (kVector3 & v)
{
	if(this->x != v.x) return false;
	if(this->y != v.y) return false;
	if(this->z != v.z) return false;
	return true;
}

float kVector3::length(void)
{
	float res = sqrt(	this->x*this->x+
						this->y*this->y+
						this->z*this->z);
	return res;
}
void kVector3::makeUnit(void)
{
	*this *= 1/this->length();
}
void kVector3::crossProduct(kVector3 & vector_1, kVector3 & vector_2)
{
	this->x = vector_1.y*vector_2.z - vector_1.z*vector_2.y;
	this->y = vector_1.z*vector_2.x - vector_1.x*vector_2.z;
	this->z = vector_1.x*vector_2.y - vector_1.y*vector_2.x;
}
void kVector3::dotProduct(kVector3 & vector_1, kVector3 & vector_2)
{
	this->x = vector_1.x*vector_2.x;
	this->y = vector_1.y*vector_2.y;
	this->z = vector_1.z*vector_2.z;
}
void kVector3::rotateX(float angle)
{
	float cos_angle=cosf(angle);
	float sin_angle=sinf(angle);

	float res_y = cos_angle*this->y - sin_angle*this->z;

	this->z = sin_angle*this->y + cos_angle*this->z;
	this->y = res_y;
}
void kVector3::rotateY(float angle)
{
	float cos_angle=cosf(angle);
	float sin_angle=sinf(angle);

	float res_x = cos_angle*this->x + sin_angle*this->z;

	this->z = -sin_angle*this->x + cos_angle*this->z;
	this->x = res_x;
}
void kVector3::rotateZ(float angle)
{
	float cos_angle=cosf(angle);
	float sin_angle=sinf(angle);

	float res_x = cos_angle*this->x - sin_angle*this->y;

	this->x = sin_angle*this->x + cos_angle*this->y;
	this->y = res_x;
}
void kVector3::rotateXY(kVector2 & angles)
{
	float cos_phi = cosf(angles.x);
	float sin_phi = sinf(angles.x);
	float cos_theta = cosf(angles.y);
	float sin_theta = sinf(angles.y);

	float res_x;
	float res_y;

	res_x =   cos_theta*this->x
			+ sin_phi*sin_theta*this->y
			+ cos_phi*sin_theta*this->z;

	res_y =   cos_phi*this->y
			- sin_phi*this->z;

	this->z = - sin_theta*this->x
			  + sin_phi*cos_theta*this->y
			  + cos_phi*cos_theta*this->z;

	this->x = res_x;
	this->y = res_y;


}
void kVector3::rotateXZ(kVector2 & angles)
{
	float cos_phi = cosf(angles.x);
	float sin_phi = sinf(angles.x);
	float cos_psi = cosf(angles.y);
	float sin_psi = sinf(angles.y);

	float res_x;
	float res_y;

	res_x =   cos_psi*this->x
			- cos_phi*sin_psi*this->y
			+ sin_phi*sin_psi*this->z;

	res_y =   sin_psi*this->x
			+ cos_phi*cos_psi*this->y
			- sin_phi*cos_psi*this->z;

	this->z =   sin_phi*this->y
			  + cos_phi*this->z;

	this->x = res_x;
	this->y = res_y;

}
void kVector3::rotateYX(kVector2 & angles)
{
	float cos_theta = cosf(angles.x);
	float sin_theta = sinf(angles.x);
	float cos_phi = cosf(angles.y);
	float sin_phi = sinf(angles.y);

	float res_x;
	float res_y;

	res_x =   cos_theta*this->x
		    + sin_theta*this->z;

	res_y =   sin_phi*sin_theta*this->x
			+ cos_phi*this->y
			- sin_phi*cos_theta*this->z;

	this->z = - sin_theta*this->x
			  + sin_phi*this->y
			  + cos_phi*cos_theta*this->z;

	this->x = res_x;
	this->y = res_y;
}
void kVector3::rotateYZ(kVector2 & angles)
{
	float cos_theta = cosf(angles.x);
	float sin_theta = sinf(angles.x);
	float cos_psi = cosf(angles.y);
	float sin_psi = sinf(angles.y);

	float res_x;
	float res_y;

	res_x =   cos_theta*cos_psi*this->x
			- sin_psi*this->y
			+ sin_theta*cos_psi*this->z;

	res_y =   cos_theta*sin_psi*this->x
			+ cos_psi*this->y
			+ sin_theta*sin_psi*this->z;

	this->z = - sin_theta*this->x
			  + cos_theta*this->z;

	this->x = res_x;
	this->y = res_y;
}
void kVector3::rotateZX(kVector2 & angles)
{
	float cos_psi = cosf(angles.x);
	float sin_psi = sinf(angles.x);
	float cos_phi = cosf(angles.y);
	float sin_phi = sinf(angles.y);


	float res_x;
	float res_y;

	res_x =	  cos_psi*this->x
			- sin_psi*this->y;

	res_y =   cos_phi*sin_psi*this->x
			+ cos_phi*cos_psi*this->y
			- sin_phi*this->z;

	this->z =   sin_phi*sin_psi*this->x
			  + cos_phi*cos_psi*this->y
			  - sin_phi*this->z;

	this->x = res_x;
	this->y = res_y;
}
void kVector3::rotateZY(kVector2 & angles)
{
	float cos_psi = cosf(angles.x);
	float sin_psi = sinf(angles.x);
	float cos_theta = cosf(angles.y);
	float sin_theta = sinf(angles.y);


	float res_x;
	float res_y;

	res_x =   cos_theta*cos_psi*this->x
			- cos_theta*sin_psi*this->y
			+ sin_theta*this->z;

	res_y =   sin_psi*this->x
			+ cos_psi*this->y;

	this->z = - sin_theta*cos_psi*this->x
			  + sin_theta*sin_psi*this->y
			  + cos_theta*this->z;

	this->x = res_x;
	this->y = res_y;

}
