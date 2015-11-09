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

#include "kMatrix.h"
