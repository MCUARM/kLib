#include "kQuaternion.h"


kQuaternion::kQuaternion(void)
{

}
kQuaternion::kQuaternion(float r,float i, float j, float k)
{
	this->r = r;
	this->i = i;
	this->j = j;
	this->k = k;
}
kQuaternion::kQuaternion(kVector3 & v)
{
	this->r = 0;
	this->i = v.x;
	this->j = v.y;
	this->k = v.z;
}


void kQuaternion::operator +=(kQuaternion &q)
{
    this->r += q.r;
    this->i += q.i;
    this->j += q.j;
    this->k += q.k;
}

void kQuaternion::operator -=(kQuaternion &q)
{
    this->r -= q.r;
    this->i -= q.i;
    this->j -= q.j;
    this->k -= q.k;
}

void kQuaternion::operator *=(kQuaternion &q)
{
	kQuaternion tmp = (*this);
	(*this) = tmp*q;
}

void kQuaternion::operator *=(float &scalar)
{
    this->r *= scalar;
    this->i *= scalar;
    this->j *= scalar;
    this->k *= scalar;
}
void kQuaternion::operator *= (kVector3 v)
{
	kQuaternion tmp = (*this);
	(*this) = tmp*v;
}
kQuaternion kQuaternion::operator *(kQuaternion &q)
{
    kQuaternion result;

    result.r = this->r*q.r - this->i*q.i - this->j*q.j - this->k*q.k;
    result.i = this->r*q.i + this->i*q.r + this->j*q.k - this->k*q.j;
    result.j = this->r*q.j - this->i*q.k + this->j*q.r + this->k*q.i;
    result.k = this->r*q.k + this->i*q.j - this->j*q.i + this->k*q.r;

    return result;
}
kQuaternion kQuaternion::operator *(kVector3 v)
{
	kQuaternion qv(v);
	return (*this)*qv;
}

kQuaternion kQuaternion::operator +(kQuaternion &q)
{
    kQuaternion res;

    res.r = this->r + q.r;
    res.i = this->i + q.i;
    res.j = this->j + q.j;
    res.k = this->k + q.k;

    return res;
}

kQuaternion kQuaternion::operator -(kQuaternion &q)
{
    kQuaternion res;

    res.r = this->r - q.r;
    res.i = this->i - q.i;
    res.j = this->j - q.j;
    res.k = this->k - q.k;

    return res;
}

void kQuaternion::operator =(kQuaternion q)
{
    this->r = q.r;
    this->i = q.i;
    this->j = q.j;
    this->k = q.k;
}

bool kQuaternion::operator ==(kQuaternion &q)
{
    if(this->r != q.r) return false;
    if(this->i != q.i) return false;
    if(this->j != q.j) return false;
    if(this->k != q.k) return false;

    return true;
}

float kQuaternion::norm()
{
    float res;
    res = this->r*this->r + this->i*this->i + this->j*this->j + this->k*this->k;
    res = sqrtf(res);
    return res;
}

kQuaternion kQuaternion::inv()
{
    kQuaternion result;

    result.r = this->r;
    result.i = -this->i;
    result.j = -this->j;
    result.k = -this->k;

    return result;
}

kQuaternion kQuaternion::versor()
{
    kQuaternion result;

    // quaternion_NORM
    float norm;
    norm = this->r*this->r + this->i*this->i + this->j*this->j + this->k*this->k;
    norm = sqrtf(norm);

    norm = 1/norm;

    // quaternion_SCALAR_MULTIPLY
    result.r = norm*this->r;
    result.i = norm*this->i;
    result.j = norm*this->j;
    result.k = norm*this->k;

    return result;
}

kQuaternion kQuaternion::conjugate()
{
    kQuaternion result;

    result.r = this->r;
    result.i = -this->i;
    result.j = -this->j;
    result.k = -this->k;

    return result;
}

kQuaternion kQuaternion::reciprocal()
{
    kQuaternion result;

    float square_norm;

    //quaternion_CONJUGATE
    result.r = this->r;
    result.i = -this->i;
    result.j = -this->j;
    result.k = -this->k;

    //quaternion square norm
    square_norm = this->r*this->r + this->i*this->i + this->j*this->j + this->k*this->k;

    // avoid to many slow divide operations
    square_norm = 1/square_norm;

    //quaternion_SCALAR_MULTIPLY
    result.r *= square_norm;
    result.i *= square_norm;
    result.j *= square_norm;
    result.k *= square_norm;

    return result;
}

kVector3 kQuaternion::toEulerAngles(void)
{
	kVector3 res;
	float nom,denom;

	// get phi
	nom = 2*(this->r*this->i + this->j*this->k);
	denom = 1- 2*(this->i*this->i + this->j*this->j);
	res.x = atan2f(nom,denom);

	// get theta
	nom = 2*(this->r*this->j - this->k*this->i);
	res.y = asinf(nom);

	// get psi
	nom = 2*(this->r*this->k + this->i*this->j);
	denom = 1- 2*(this->j*this->j + this->k*this->k);
	res.z = atan2f(nom,denom);


	return res;
}
kAxisAngle kQuaternion::toAxisAngle(void)
{
	kAxisAngle res;

	res.angle = acosf(this->r)*2;
	if(res.angle == 0)
	{
		res.axis.x = 1;
		res.axis.y = 0;
		res.axis.z = 0;

		return res;
	}

	float scale = 1/sqrt(1-this->r*this->r);

	res.axis.x = this->i*scale;
	res.axis.y = this->j*scale;
	res.axis.z = this->k*scale;

	return res;
}


kQuaternion  kQuaternion::fromAxisAngle(kAxisAngle & axis_angle)
{
	kQuaternion res;
	float angle_rad = axis_angle.angle*0.5;

	res.r = cosf(angle_rad);

	// use angle_rad as temporary storage
	angle_rad = sinf(angle_rad)/axis_angle.axis.length();

	res.i = angle_rad*axis_angle.axis.x;
	res.j = angle_rad*axis_angle.axis.y;
	res.k = angle_rad*axis_angle.axis.z;

	return res;
}
kQuaternion  kQuaternion::fromEulerAngles(kVector3 Euler_angles)
{
	kQuaternion res;
	float cos_phi,cos_theta,cos_psi;
	float sin_phi,sin_theta,sin_psi;

	Euler_angles *= 0.5;

	cos_phi = cosf(Euler_angles.x);
	sin_phi = sinf(Euler_angles.x);

	cos_theta = cosf(Euler_angles.y);
	sin_theta = sinf(Euler_angles.y);

	cos_psi = cosf(Euler_angles.z);
	sin_psi = sinf(Euler_angles.z);


	res.r =  cos_psi*cos_theta*cos_phi + sin_psi*sin_theta*sin_phi;
	res.i = -sin_psi*sin_theta*cos_phi + cos_psi*cos_theta*sin_phi;
	res.j =  cos_psi*sin_theta*cos_phi + sin_psi*cos_theta*sin_phi;
	res.k =  sin_psi*cos_theta*cos_phi - cos_psi*sin_theta*sin_phi;


	return res;
}

kQuaternion kQuaternion::create(float r,float i, float j, float k)
{
	kQuaternion res(r,i,j,k);
	return res;
}
kQuaternion kQuaternion::create(kVector3 & v)
{
	kQuaternion res(v);
	return res;
}

kQuaternion kQuaternion::SLERP(kQuaternion & begin, kQuaternion end, float normalized_time)
{
	kQuaternion res;
	float cosHalfTheta =  begin.r*end.r
						+ begin.i*end.i
						+ begin.j*end.j
						+ begin.k*end.k;

	if (cosHalfTheta < 0) {
	  end.r = -end.r;
	  end.i = -end.i;
	  end.j = -end.j;
	  end.k = -end.k;
	  cosHalfTheta = -cosHalfTheta;
	}

	// check if begin == end
	if (kMath::abs(cosHalfTheta) >= 1.0)
	{
		res.r = begin.r;
		res.i = begin.i;
		res.j = begin.j;
		res.k = begin.k;

		return res;
	}

	float halfTheta = acosf(cosHalfTheta);
	float sinHalfTheta = sqrtf(1.0 - cosHalfTheta*cosHalfTheta);

	// if theta = 180 degrees then result is not fully defined
	// we could rotate around any axis normal to begin or end
	if (kMath::abs(sinHalfTheta) < 0.000001)
	{
		res.r = (begin.r * 0.5 + end.r * 0.5);
		res.i = (begin.i * 0.5 + end.i * 0.5);
		res.j = (begin.j * 0.5 + end.j * 0.5);
		res.k = (begin.k * 0.5 + end.k * 0.5);
		return res;
	}

	float ratioA = sinf((1 - normalized_time) * halfTheta) / sinHalfTheta;
	float ratioB = sinf(normalized_time * halfTheta) / sinHalfTheta;

	//calculate quaternion.
	res.r = (begin.r * ratioA + end.r * ratioB);
	res.i = (begin.i * ratioA + end.i * ratioB);
	res.j = (begin.j * ratioA + end.j * ratioB);
	res.k = (begin.k * ratioA + end.k * ratioB);

	return res;
}
