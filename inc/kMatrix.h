#ifndef __kMatrix_H
#define __kMatrix_H


	class kMatrix;
	class kMatrix_2x2;

	#include "kVector.h"

    class kMatrix
    {
		friend class kLKF;

        protected:

            float *buff;
            unsigned char buff_len;
            unsigned char m_rows;
            unsigned char m_cols;
            float * curr_element;

            void operator = (kMatrix & other);
            kMatrix& operator = (float val);
            kMatrix& operator , (float val);

            static void add(kMatrix & result,kMatrix & matrix_1, kMatrix & matrix_2);

            static void subtract(kMatrix & result,kMatrix & matrix_1, kMatrix & matrix_2);

            static void multiply(kMatrix & result,kMatrix & matrix_1, kMatrix & matrix_2);
            static void multiply(kVector & result,kMatrix & matrix, kVector & vector);
            static void transpose(kMatrix & result,kMatrix & matrix);

            static void makeEye(kMatrix & result);

        public:



            kMatrix(void);

            unsigned char rows(void);
            unsigned char cols(void);
            unsigned char size(void);
            float & operator ()(unsigned char row, unsigned char column);

            static void add(kMatrix_2x2 & result,kMatrix_2x2 & matrix_1, kMatrix_2x2 & matrix_2);

            static void subtract(kMatrix_2x2 & result,kMatrix_2x2 & matrix_1, kMatrix_2x2 & matrix_2);

            static void multiply(kMatrix_2x2 & result,kMatrix_2x2 & matrix_1, kMatrix_2x2 & matrix_2);
            static void multiply(kVector2 & result,kMatrix_2x2 & matrix, kVector2 & vector);

            static void transpose(kMatrix_2x2 & result,kMatrix_2x2 & matrix);

            static void invert(kMatrix_2x2 & result,kMatrix_2x2 & matrix);

            static void makeEye(kMatrix_2x2 & result);

    };


    class kMatrix_2x2 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[4];

    	public:

    		kMatrix_2x2(void);
    		kMatrix_2x2& operator = (float val);
    		kMatrix_2x2& operator , (float val);

    		float det(void);
    };

#endif
