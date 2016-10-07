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

#ifndef __kMatrix_H
#define __kMatrix_H


	class kMatrix;
	class kMatrix2x2;
	class kMatrix2x3;
	class kMatrix2x4;
	class kMatrix3x2;
	class kMatrix3x3;
	class kMatrix3x4;
	class kMatrix4x2;
	class kMatrix4x3;
	class kMatrix4x4;

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

            static void add(kMatrix2x2 & result,kMatrix2x2 & matrix_1, kMatrix2x2 & matrix_2);
            static void add(kMatrix2x3 & result,kMatrix2x3 & matrix_1, kMatrix2x3 & matrix_2);
            static void add(kMatrix2x4 & result,kMatrix2x4 & matrix_1, kMatrix2x4 & matrix_2);
            static void add(kMatrix3x2 & result,kMatrix3x2 & matrix_1, kMatrix3x2 & matrix_2);
            static void add(kMatrix3x3 & result,kMatrix3x3 & matrix_1, kMatrix3x3 & matrix_2);
            static void add(kMatrix3x4 & result,kMatrix3x4 & matrix_1, kMatrix3x4 & matrix_2);
            static void add(kMatrix4x2 & result,kMatrix4x2 & matrix_1, kMatrix4x2 & matrix_2);
			static void add(kMatrix4x3 & result,kMatrix4x3 & matrix_1, kMatrix4x3 & matrix_2);
			static void add(kMatrix4x4 & result,kMatrix4x4 & matrix_1, kMatrix4x4 & matrix_2);

            static void subtract(kMatrix2x2 & result,kMatrix2x2 & matrix_1, kMatrix2x2 & matrix_2);
            static void subtract(kMatrix2x3 & result,kMatrix2x3 & matrix_1, kMatrix2x3 & matrix_2);
            static void subtract(kMatrix2x4 & result,kMatrix2x4 & matrix_1, kMatrix2x4 & matrix_2);
            static void subtract(kMatrix3x2 & result,kMatrix3x2 & matrix_1, kMatrix3x2 & matrix_2);
            static void subtract(kMatrix3x3 & result,kMatrix3x3 & matrix_1, kMatrix3x3 & matrix_2);
            static void subtract(kMatrix3x4 & result,kMatrix3x4 & matrix_1, kMatrix3x4 & matrix_2);
            static void subtract(kMatrix4x2 & result,kMatrix4x2 & matrix_1, kMatrix4x2 & matrix_2);
			static void subtract(kMatrix4x3 & result,kMatrix4x3 & matrix_1, kMatrix4x3 & matrix_2);
			static void subtract(kMatrix4x4 & result,kMatrix4x4 & matrix_1, kMatrix4x4 & matrix_2);

            static void multiply(kMatrix2x2 & result,kMatrix2x2 & matrix_1, kMatrix2x2 & matrix_2);
            static void multiply(kMatrix2x2 & result,kMatrix2x3 & matrix_1, kMatrix3x2 & matrix_2);
            static void multiply(kMatrix2x2 & result,kMatrix2x4 & matrix_1, kMatrix4x2 & matrix_2);

            static void multiply(kMatrix2x3 & result,kMatrix2x2 & matrix_1, kMatrix2x3 & matrix_2);
            static void multiply(kMatrix2x3 & result,kMatrix2x3 & matrix_1, kMatrix3x3 & matrix_2);
            static void multiply(kMatrix2x3 & result,kMatrix2x4 & matrix_1, kMatrix4x3 & matrix_2);

            static void multiply(kMatrix2x4 & result,kMatrix2x2 & matrix_1, kMatrix2x4 & matrix_2);
            static void multiply(kMatrix2x4 & result,kMatrix2x3 & matrix_1, kMatrix3x4 & matrix_2);
            static void multiply(kMatrix2x4 & result,kMatrix2x4 & matrix_1, kMatrix4x4 & matrix_2);

            static void multiply(kMatrix3x2 & result,kMatrix3x2 & matrix_1, kMatrix2x2 & matrix_2);
            static void multiply(kMatrix3x2 & result,kMatrix3x3 & matrix_1, kMatrix3x2 & matrix_2);
            static void multiply(kMatrix3x2 & result,kMatrix3x4 & matrix_1, kMatrix4x2 & matrix_2);

            static void multiply(kMatrix3x3 & result,kMatrix3x2 & matrix_1, kMatrix2x3 & matrix_2);
            static void multiply(kMatrix3x3 & result,kMatrix3x3 & matrix_1, kMatrix3x3 & matrix_2);
            static void multiply(kMatrix3x3 & result,kMatrix3x4 & matrix_1, kMatrix4x3 & matrix_2);

            static void multiply(kMatrix3x4 & result,kMatrix3x2 & matrix_1, kMatrix2x4 & matrix_2);
            static void multiply(kMatrix3x4 & result,kMatrix3x3 & matrix_1, kMatrix3x4 & matrix_2);
            static void multiply(kMatrix3x4 & result,kMatrix3x4 & matrix_1, kMatrix4x4 & matrix_2);

            static void multiply(kMatrix4x2 & result,kMatrix4x2 & matrix_1, kMatrix2x2 & matrix_2);
            static void multiply(kMatrix4x2 & result,kMatrix4x3 & matrix_1, kMatrix3x2 & matrix_2);
            static void multiply(kMatrix4x2 & result,kMatrix4x4 & matrix_1, kMatrix4x2 & matrix_2);

            static void multiply(kMatrix4x3 & result,kMatrix4x2 & matrix_1, kMatrix2x3 & matrix_2);
            static void multiply(kMatrix4x3 & result,kMatrix4x3 & matrix_1, kMatrix3x3 & matrix_2);
            static void multiply(kMatrix4x3 & result,kMatrix4x4 & matrix_1, kMatrix4x3 & matrix_2);

            static void multiply(kMatrix4x4 & result,kMatrix4x2 & matrix_1, kMatrix2x4 & matrix_2);
            static void multiply(kMatrix4x4 & result,kMatrix4x3 & matrix_1, kMatrix3x4 & matrix_2);
            static void multiply(kMatrix4x4 & result,kMatrix4x4 & matrix_1, kMatrix4x4 & matrix_2);

            static void multiply(kVector2 & result,kMatrix2x2 & matrix, kVector2 & vector);
            static void multiply(kVector2 & result,kMatrix2x3 & matrix, kVector3 & vector);
            static void multyply(kVector2 & result,kMatrix2x4 & matrix, kVector4 & vector);

            static void multiply(kVector3 & result,kMatrix3x2 & matrix, kVector2 & vector);
            static void multiply(kVector3 & result,kMatrix3x3 & matrix, kVector3 & vector);
            static void multyply(kVector3 & result,kMatrix3x4 & matrix, kVector4 & vector);

            static void multiply(kVector4 & result,kMatrix4x2 & matrix, kVector2 & vector);
            static void multiply(kVector4 & result,kMatrix4x3 & matrix, kVector3 & vector);
            static void multyply(kVector4 & result,kMatrix4x4 & matrix, kVector4 & vector);

            static void transpose(kMatrix2x2 & result,kMatrix2x2 & matrix);
            static void transpose(kMatrix2x3 & result,kMatrix3x2 & matrix);
            static void transpose(kMatrix2x4 & result,kMatrix4x2 & matrix);

            static void transpose(kMatrix3x2 & result,kMatrix2x3 & matrix);
            static void transpose(kMatrix3x3 & result,kMatrix3x3 & matrix);
            static void transpose(kMatrix3x4 & result,kMatrix4x3 & matrix);

            static void transpose(kMatrix4x2 & result,kMatrix2x4 & matrix);
            static void transpose(kMatrix4x3 & result,kMatrix4x3 & matrix);
            static void transpose(kMatrix4x4 & result,kMatrix4x4 & matrix);

            static void invert(kMatrix2x2 & result,kMatrix2x2 & matrix);
            static void invert(kMatrix3x3 & result,kMatrix3x3 & matrix);
            static void invert(kMatrix4x4 & result,kMatrix4x4 & matrix);

            static void makeEye(kMatrix2x2 & result);
            static void makeEye(kMatrix3x3 & result);
            static void makeEye(kMatrix4x4 & result);


    };

    class kMatrix2x2 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[4];

    	public:

    		kMatrix2x2(void);
    		kMatrix2x2& operator = (float val);
    		kMatrix2x2& operator , (float val);

    		float det(void);
    };



    class kMatrix2x3 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[6];

    	public:

    		kMatrix2x3(void);
    		kMatrix2x3& operator = (float val);
    		kMatrix2x3& operator , (float val);

    };

    class kMatrix2x4 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[8];

    	public:

    		kMatrix2x4(void);
    		kMatrix2x4& operator = (float val);
    		kMatrix2x4& operator , (float val);

    };


    class kMatrix3x2 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[6];

    	public:

    		kMatrix3x2(void);
    		kMatrix3x2& operator = (float val);
    		kMatrix3x2& operator , (float val);

    };

    class kMatrix3x3 : public kMatrix
     {
     	friend class kMatrix;

     	protected:

     		float m_buffer[9];

     	public:

     		kMatrix3x3(void);
     		kMatrix3x3& operator = (float val);
     		kMatrix3x3& operator , (float val);

     		float det(void);
     };

    class kMatrix3x4 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[12];

    	public:

    		kMatrix3x4(void);
    		kMatrix3x4& operator = (float val);
    		kMatrix3x4& operator , (float val);

    };


    class kMatrix4x2 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[8];

    	public:

    		kMatrix4x2(void);
    		kMatrix4x2& operator = (float val);
    		kMatrix4x2& operator , (float val);

    };

    class kMatrix4x3 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[12];

    	public:

    		kMatrix4x3(void);
    		kMatrix4x3& operator = (float val);
    		kMatrix4x3& operator , (float val);

    };

    class kMatrix4x4 : public kMatrix
    {
    	friend class kMatrix;

    	protected:

    		float m_buffer[16];

    	public:

    		kMatrix4x4(void);
    		kMatrix4x4& operator = (float val);
    		kMatrix4x4& operator , (float val);

    		float det(void);

    };



#endif
