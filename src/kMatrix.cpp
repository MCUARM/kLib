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




void kMatrix::add(kMatrix_2x2 & result,kMatrix_2x2 & matrix_1, kMatrix_2x2 & matrix_2)
{
	kMatrix::add((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::subtract(kMatrix_2x2 & result,kMatrix_2x2 & matrix_1, kMatrix_2x2 & matrix_2)
{
	kMatrix::subtract((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kMatrix_2x2 & result,kMatrix_2x2 & matrix_1, kMatrix_2x2 & matrix_2)
{
	kMatrix::multiply((kMatrix&)result,(kMatrix&)matrix_1,(kMatrix&)matrix_2);
}
void kMatrix::multiply(kVector2 & result,kMatrix_2x2 & matrix, kVector2 & vector)
{
	kMatrix::multiply((kVector&)result,(kMatrix&)matrix,(kVector&)vector);
}

void kMatrix::transpose(kMatrix_2x2 & result,kMatrix_2x2 & matrix)
{
	kMatrix::transpose((kMatrix&)result,(kMatrix&)matrix);
}
void kMatrix::invert(kMatrix_2x2 & result,kMatrix_2x2 & matrix)
{
	float scale = 1/matrix.det();

	result.buff[0] =  matrix.buff[3]*scale;
	result.buff[1] = -matrix.buff[1]*scale;
	result.buff[2] = -matrix.buff[2]*scale;
	result.buff[3] =  matrix.buff[0]*scale;
}
void kMatrix::makeEye(kMatrix_2x2 & result)
{
	kMatrix::makeEye((kMatrix&)result);
}


kMatrix_2x2::kMatrix_2x2(void)
{
	this->buff_len = 4;
	this->m_cols = 2;
	this->m_rows = 2;
	this->buff = this->m_buffer;
}
kMatrix_2x2& kMatrix_2x2::operator = (float val)
{
	return (kMatrix_2x2&)kMatrix::operator=(val);
}
kMatrix_2x2& kMatrix_2x2::operator , (float val)
{
	return (kMatrix_2x2&)kMatrix::operator,(val);
}
float kMatrix_2x2::det(void)
{
	float res = this->buff[0]*this->buff[3];
	res -= this->buff[1]*this->buff[2];
	return res;
}
