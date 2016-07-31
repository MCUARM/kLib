#include "kAxisAngle.h"

kAxisAngle::kAxisAngle(void)
{

}
kAxisAngle::kAxisAngle(kVector3 & axis, float angle)
{
	this->axis.x = axis.x;
	this->axis.y = axis.y;
	this->axis.z = axis.z;
	this->angle = angle;
}
kAxisAngle::kAxisAngle(float x, float y, float z, float angle)
{
	this->axis.x = x;
	this->axis.y = y;
	this->axis.z = z;
	this->angle = angle;
}

kAxisAngle kAxisAngle::create(kVector3 & axis, float angle)
{
	kAxisAngle res(axis,angle);
	return res;
}
kAxisAngle kAxisAngle::create(float x, float y, float z, float angle)
{
	kAxisAngle res(x,y,z,angle);
	return res;
}
