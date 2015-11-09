#ifndef __kMatrix_H
#define __kMatrix_H

    class kMatrix
    {
        private:

            float *buff;
            unsigned char buff_len;
            unsigned char m_rows;
            unsigned char m_cols;

        public:


            kMatrix(void);
            kMatrix(unsigned char rows, unsigned char cols);

            ~kMatrix(void);

            float & operator ()(unsigned char row, unsigned char column);

            void operator = (const kMatrix & other);

            void operator += (const kMatrix & other);
            void operator -= (const kMatrix & other);
            void operator *= (const kMatrix & other);

            friend kMatrix operator + (const kMatrix & m1, const kMatrix & m2);
            friend kMatrix operator - (const kMatrix & m1, const kMatrix & m2);




    };

#endif
