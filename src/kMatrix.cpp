/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
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

#include "kMatrix.h"

kMatrix::kMatrix()
{
    this->buff_len = 0;
    this->m_cols=0;
    this->m_rows=0;
}

unsigned char kMatrix::rows()
{
    return this->m_rows;
}

unsigned char kMatrix::cols()
{
    return this->m_cols;
}
unsigned char kMatrix::size()
{
    return this->buff_len;
}
float &kMatrix::operator ()(unsigned char row, unsigned char column)
{
    return this->buff[row*this->m_cols + column];
}
void kMatrix::operator = (kMatrix & other)
{
	unsigned char i;
	for(i=0;i<this->buff_len;i++) this->buff[i] = other.buff[i];
}
kMatrix& kMatrix::operator = (float val)
{
	*(this->buff) = val;
	this->curr_element = &this->buff[1];
	return (*this);
}
kMatrix& kMatrix::operator , (float val)
{
	*(this->curr_element) = val;
	this->curr_element++;
	return (*this);
}
void kMatrix::add(kMatrix & result,kMatrix & matrix_1, kMatrix & matrix_2)
{
	unsigned char i;
	for(i=0;i<result.buff_len;i++)
	{
		result.buff[i] = matrix_1.buff[i] + matrix_2.buff[i];
	}
}
void kMatrix::subtract(kMatrix & result,kMatrix & matrix_1, kMatrix & matrix_2)
{
	unsigned char i;
	for(i=0;i<result.buff_len;i++)
	{
		result.buff[i] = matrix_1.buff[i] - matrix_2.buff[i];
	}
}
void kMatrix::multiply(kMatrix & result,kMatrix & matrix_1, kMatrix & matrix_2)
{
	unsigned char i,j,k;
	float * item;

	for(i=0;i<matrix_1.m_rows;i++)
	{
		for(j=0;j<matrix_2.m_cols;j++)
		{
			item = &result(i,j);
			*item = 0;
			for(k=0;k<matrix_1.m_cols;k++)
			{
				(*item) += matrix_1(i,k)*matrix_2(j,k);
			}
		}
	}
}
void kMatrix::multiply(kVector & result,kMatrix & matrix, kVector & vector)
{
	unsigned char i,j;

	for(i=0;i<matrix.m_rows;i++)
	{
		result.buff[i]=0;
		for(j=0;j<matrix.m_cols;i++)
		{
			result.buff[i] += (matrix.operator ()(i,j))*vector.buff[j];
		}
	}
}


void kMatrix::transpose(kMatrix & result,kMatrix & matrix)
{
	float *item=result.buff;
	unsigned char i,j;

	for(i=0;i<matrix.m_cols;i++)
	{
		for(j=0;j<matrix.m_rows;j++)
		{
			*item = matrix(j,i);
			item++;
		}
	}


}
void kMatrix::makeEye(kMatrix & result)
{
	unsigned char i,j;
	float * item = result.buff;
	for(i=0;i<result.m_rows;i++)
	{
		for(j=0;j<result.m_cols;j++)
		{
			if(i==j) *item = 1;
			else *item = 0;

			item++;
		}
	}
}




void kMatrix::add(kMatrix2x2 & result,kMatrix2x2 & matrix_1, kMatrix2x2 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix2x3 & result,kMatrix2x3 & matrix_1, kMatrix2x3 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix2x4 & result,kMatrix2x4 & matrix_1, kMatrix2x4 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix3x2 & result,kMatrix3x2 & matrix_1, kMatrix3x2 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix3x3 & result,kMatrix3x3 & matrix_1, kMatrix3x3 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix3x4 & result,kMatrix3x4 & matrix_1, kMatrix3x4 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix4x2 & result,kMatrix4x2 & matrix_1, kMatrix4x2 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix4x3 & result,kMatrix4x3 & matrix_1, kMatrix4x3 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::add(kMatrix4x4 & result,kMatrix4x4 & matrix_1, kMatrix4x4 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::subtract(kMatrix2x2 & result,kMatrix2x2 & matrix_1, kMatrix2x2 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix2x3 & result,kMatrix2x3 & matrix_1, kMatrix2x3 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix2x4 & result,kMatrix2x4 & matrix_1, kMatrix2x4 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix3x2 & result,kMatrix3x2 & matrix_1, kMatrix3x2 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix3x3 & result,kMatrix3x3 & matrix_1, kMatrix3x3 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix3x4 & result,kMatrix3x4 & matrix_1, kMatrix3x4 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix4x2 & result,kMatrix4x2 & matrix_1, kMatrix4x2 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix4x3 & result,kMatrix4x3 & matrix_1, kMatrix4x3 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix4x4 & result,kMatrix4x4 & matrix_1, kMatrix4x4 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix2x2 & result,kMatrix2x2 & matrix_1, kMatrix2x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix2x2 & result,kMatrix2x3 & matrix_1, kMatrix3x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix2x2 & result,kMatrix2x4 & matrix_1, kMatrix4x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix2x3 & result,kMatrix2x2 & matrix_1, kMatrix2x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix2x3 & result,kMatrix2x3 & matrix_1, kMatrix3x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix2x3 & result,kMatrix2x4 & matrix_1, kMatrix4x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix2x4 & result,kMatrix2x2 & matrix_1, kMatrix2x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix2x4 & result,kMatrix2x3 & matrix_1, kMatrix3x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix2x4 & result,kMatrix2x4 & matrix_1, kMatrix4x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix3x2 & result,kMatrix3x2 & matrix_1, kMatrix2x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix3x2 & result,kMatrix3x3 & matrix_1, kMatrix3x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix3x2 & result,kMatrix3x4 & matrix_1, kMatrix4x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix3x3 & result,kMatrix3x2 & matrix_1, kMatrix2x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix3x3 & result,kMatrix3x3 & matrix_1, kMatrix3x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix3x3 & result,kMatrix3x4 & matrix_1, kMatrix4x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix3x4 & result,kMatrix3x2 & matrix_1, kMatrix2x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix3x4 & result,kMatrix3x3 & matrix_1, kMatrix3x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix3x4 & result,kMatrix3x4 & matrix_1, kMatrix4x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix4x2 & result,kMatrix4x2 & matrix_1, kMatrix2x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix4x2 & result,kMatrix4x3 & matrix_1, kMatrix3x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix4x2 & result,kMatrix4x4 & matrix_1, kMatrix4x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix4x3 & result,kMatrix4x2 & matrix_1, kMatrix2x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix4x3 & result,kMatrix4x3 & matrix_1, kMatrix3x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix4x3 & result,kMatrix4x4 & matrix_1, kMatrix4x3 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}

void kMatrix::multiply(kMatrix4x4 & result,kMatrix4x2 & matrix_1, kMatrix2x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix4x4 & result,kMatrix4x3 & matrix_1, kMatrix3x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix4x4 & result,kMatrix4x4 & matrix_1, kMatrix4x4 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}


void kMatrix::transpose(kMatrix2x2 & result,kMatrix2x2 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::transpose(kMatrix2x3 & result,kMatrix3x2 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::transpose(kMatrix2x4 & result,kMatrix4x2 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}

void kMatrix::transpose(kMatrix3x2 & result,kMatrix2x3 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::transpose(kMatrix3x3 & result,kMatrix3x3 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::transpose(kMatrix3x4 & result,kMatrix4x3 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}

void kMatrix::transpose(kMatrix4x2 & result,kMatrix2x4 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::transpose(kMatrix4x3 & result,kMatrix4x3 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::transpose(kMatrix4x4 & result,kMatrix4x4 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}



void kMatrix::invert(kMatrix2x2 & result,kMatrix2x2 & matrix)
{
	float scale = 1/matrix.det();

	result.buff[0] =  matrix.buff[3]*scale;
	result.buff[1] = -matrix.buff[1]*scale;
	result.buff[2] = -matrix.buff[2]*scale;
	result.buff[3] =  matrix.buff[0]*scale;
}
void kMatrix::makeEye(kMatrix2x2 & result)
{
	kMatrix::makeEye((kMatrix&)result);
}
void kMatrix::makeEye(kMatrix3x3 & result)
{
	kMatrix::makeEye((kMatrix&)result);
}
void kMatrix::makeEye(kMatrix4x4 & result)
{
	kMatrix::makeEye((kMatrix&)result);
}


kMatrix2x2::kMatrix2x2(void)
{
	this->buff_len = 4;
	this->m_cols = 2;
	this->m_rows = 2;
	this->buff = this->m_buffer;
}
kMatrix2x2& kMatrix2x2::operator = (float val)
{
	return (kMatrix2x2&)kMatrix::operator=(val);
}
kMatrix2x2& kMatrix2x2::operator , (float val)
{
	return (kMatrix2x2&)kMatrix::operator,(val);
}
float kMatrix2x2::det(void)
{
	float res = this->buff[0]*this->buff[3];
	res -= this->buff[1]*this->buff[2];
	return res;
}





kMatrix2x3::kMatrix2x3(void)
{
	this->buff_len = 6;
	this->m_cols = 3;
	this->m_rows = 2;
	this->buff = this->m_buffer;
}
kMatrix2x3& kMatrix2x3::operator = (float val)
{
	return (kMatrix2x3&)kMatrix::operator=(val);
}
kMatrix2x3& kMatrix2x3::operator , (float val)
{
	return (kMatrix2x3&)kMatrix::operator,(val);
}

kMatrix3x2::kMatrix3x2(void)
{
	this->buff_len = 6;
	this->m_cols = 2;
	this->m_rows = 3;
	this->buff = this->m_buffer;
}
kMatrix3x2& kMatrix3x2::operator = (float val)
{
	return (kMatrix3x2&)kMatrix::operator=(val);
}
kMatrix3x2& kMatrix3x2::operator , (float val)
{
	return (kMatrix3x2&)kMatrix::operator,(val);
}



kMatrix3x3::kMatrix3x3(void)
{
	this->buff_len = 9;
	this->m_cols = 3;
	this->m_rows = 3;
	this->buff = this->m_buffer;
}
kMatrix3x3& kMatrix3x3::operator = (float val)
{
	return (kMatrix3x3&)kMatrix::operator=(val);
}
kMatrix3x3& kMatrix3x3::operator , (float val)
{
	return (kMatrix3x3&)kMatrix::operator,(val);
}
float kMatrix3x3::det(void)
{
	float 	res  = this->buff[0]*this->buff[4]*this->buff[8];
			res += this->buff[1]*this->buff[5]*this->buff[6];
			res += this->buff[2]*this->buff[3]*this->buff[7];

			res -= this->buff[2]*this->buff[4]*this->buff[6];
			res -= this->buff[1]*this->buff[3]*this->buff[8];
			res -= this->buff[0]*this->buff[5]*this->buff[7];

	return res;
}

kMatrix4x2::kMatrix4x2(void)
{
	this->buff_len = 8;
	this->m_cols = 2;
	this->m_rows = 4;
	this->buff = this->m_buffer;
}
kMatrix4x2& kMatrix4x2::operator = (float val)
{
	return (kMatrix4x2&)kMatrix::operator=(val);
}
kMatrix4x2& kMatrix4x2::operator , (float val)
{
	return (kMatrix4x2&)kMatrix::operator,(val);
}

kMatrix4x3::kMatrix4x3(void)
{
	this->buff_len = 12;
	this->m_cols = 3;
	this->m_rows = 4;
	this->buff = this->m_buffer;
}
kMatrix4x3& kMatrix4x3::operator = (float val)
{
	return (kMatrix4x3&)kMatrix::operator=(val);
}
kMatrix4x3& kMatrix4x3::operator , (float val)
{
	return (kMatrix4x3&)kMatrix::operator,(val);
}

kMatrix4x4::kMatrix4x4(void)
{
	this->buff_len = 16;
	this->m_cols = 4;
	this->m_rows = 4;
	this->buff = this->m_buffer;
}
kMatrix4x4& kMatrix4x4::operator = (float val)
{
	return (kMatrix4x4&)kMatrix::operator=(val);
}
kMatrix4x4& kMatrix4x4::operator , (float val)
{
	return (kMatrix4x4&)kMatrix::operator,(val);
}

float kMatrix4x4::det(void)
{
	float res;
	float temp1,temp2;


	temp1 = (	((*this)(0,0))*((*this)(1,1))	-	((*this)(0,1))*((*this)(1,0)));
	temp2 = (	((*this)(2,2))*((*this)(3,3))	-	((*this)(2,3))*((*this)(3,2)));

	res = temp1*temp2;


	temp1 = (	((*this)(0,0))*((*this)(1,2))	-	((*this)(0,2))*((*this)(2,0)));
	temp2 = (	((*this)(2,1))*((*this)(3,3))	-	((*this)(2,3))*((*this)(3,1)));

	res -= temp1*temp2;


	temp1 = (	((*this)(0,0))*((*this)(1,3))	-	((*this)(0,3))*((*this)(1,0)));
	temp2 = (	((*this)(2,1))*((*this)(3,2))	-	((*this)(2,2))*((*this)(3,1)));

	res += temp1*temp2;





	temp1 = (	((*this)(0,1))*((*this)(1,2))	-	((*this)(0,2))*((*this)(1,1)));
	temp2 = (	((*this)(2,0))*((*this)(3,3))	-	((*this)(2,3))*((*this)(3,0)));

	res += temp1*temp2;


	temp1 = (	((*this)(0,1))*((*this)(1,3))	-	((*this)(0,3))*((*this)(1,1)));
	temp2 = (	((*this)(2,0))*((*this)(3,2))	-	((*this)(2,2))*((*this)(3,0)));

	res -= temp1*temp2;


	temp1 = (	((*this)(0,2))*((*this)(1,3))	-	((*this)(1,2))*((*this)(0,3)));
	temp2 = (	((*this)(2,0))*((*this)(3,1))	-	((*this)(2,1))*((*this)(3,0)));

	res += temp1*temp2;


	return res;
}
