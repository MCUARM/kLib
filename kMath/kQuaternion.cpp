#include "kQuaternion.h"

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
    this->r = this->r*q.r - this->i*q.i - this->j*q.j - this->k*q.k;
    this->i = this->r*q.i + this->i*q.r + this->j*q.k - this->k*q.j;
    this->j = this->r*q.j - this->i*q.k - this->j*q.r + this->k*q.i;
    this->k = this->r*q.k + this->i*q.j - this->j*q.i + this->k*q.r;
}

void kQuaternion::operator *=(float &scalar)
{
    this->r *= scalar;
    this->i *= scalar;
    this->j *= scalar;
    this->k *= scalar;
}

kQuaternion kQuaternion::operator *(kQuaternion &q)
{
    kQuaternion result;

    result.r = this->r*q.r - this->i*q.i - this->j*q.j - this->k*q.k;
    result.i = this->r*q.i + this->i*q.r + this->j*q.k - this->k*q.j;
    result.j = this->r*q.j - this->i*q.k - this->j*q.r + this->k*q.i;
    result.k = this->r*q.k + this->i*q.j - this->j*q.i + this->k*q.r;

    return result;
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

void kQuaternion::operator =(kQuaternion &q)
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
    result.r = square_norm*this->r;
    result.i = square_norm*this->i;
    result.j = square_norm*this->j;
    result.k = square_norm*this->k;

    return result;
}

#include "kQuaternion.h"
