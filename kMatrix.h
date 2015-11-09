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

    };

#endif
