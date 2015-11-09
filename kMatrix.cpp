#include "kMatrix.h"

kMatrix::kMatrix()
{
    this->buff = new float[9];
    this->buff_len = 9;
    this->m_cols=3;
    this->m_rows=3;
}

kMatrix::kMatrix(unsigned char rows, unsigned char cols)
{
    this->buff = new float[rows*cols];
    this->buff_len = rows*cols;
    this->m_cols=cols;
    this->m_rows=rows;
}

kMatrix::~kMatrix()
{
    delete [] this->buff;
}

float &kMatrix::operator ()(unsigned char row, unsigned char column)
{
    return this->buff[row*this->m_cols + column];
}

void kMatrix::operator =(const kMatrix &other)
{
    delete [] this->buff;
    this->buff_len = other.buff_len;
    this->m_cols = other.m_cols;
    this->m_rows = other.m_rows;

    this->buff = new float[this->buff_len];

    unsigned char i;
    for(i=0;i<this->buff_len;i++)
    {
        this->buff[i] = other.buff[i];
    }
}

void kMatrix::operator +=(const kMatrix &other)
{
    unsigned char i;
    for(i=0;i<this->buff_len;i++)
    {
        this->buff[i] += other.buff[i];
    }
}

void kMatrix::operator -=(const kMatrix &other)
{
    unsigned char i;
    for(i=0;i<this->buff_len;i++)
    {
        this->buff[i] -= other.buff[i];
    }
}

void kMatrix::operator *=(const kMatrix &other)
{

}

kMatrix operator -(const kMatrix &m1, const kMatrix &m2)
{
    kMatrix res(m1.m_rows,m1.m_cols);
    unsigned char i;

    for(i=0;i<res.buff_len;i++)
    {
        res.buff[i] = m1.buff[i] - m2.buff[i];
    }

    return res;
}

kMatrix operator +(const kMatrix &m1, const kMatrix &m2)
{
    kMatrix res(m1.m_rows,m1.m_cols);
    unsigned char i;

    for(i=0;i<res.buff_len;i++)
    {
        res.buff[i] = m1.buff[i] + m2.buff[i];
    }

    return res;
}
