#include "kString.h"



kString::kString(void)
{
	this->leng = 0;

	this->buff[0] = new unsigned char[8];
    this->buff[0][0] = 0;

	this->currentBuffer=0;
	this->buff_leng=8;

}
kString::~kString(void)
{
	delete [] this->buff[this->currentBuffer];
}

unsigned char kString::shadowBuffer(void) const
{
	if(this->currentBuffer==0) return 1;
	return 0;
}

void kString::reallocateMemory(unsigned short buff_len)
{
	unsigned short i;
	unsigned char shadow = this->shadowBuffer();

	this->buff[shadow] = new unsigned char[buff_len];
	this->buff_leng = buff_len;

	for(i=0;i<this->leng;i++)
	{
		this->buff[shadow][i] = this->buff[this->currentBuffer][i];
	}
    this->buff[shadow][this->leng] = 0;

	delete [] this->buff[this->currentBuffer];
	this->currentBuffer = shadow;
}

unsigned short kString::length(void) const
{
	return this->leng;
}
bool kString::isEmpty(void)
{
	if(this->buff_leng == 0) return true;
	return false;
}
void kString::operator = (const char * str)
{

	delete [] this->buff[this->currentBuffer];
	this->buff[this->currentBuffer] = new unsigned char[8];
	this->buff_leng=8;
	this->leng=0;

	while(*str != 0)
	{
		if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
		this->buff[this->currentBuffer][this->leng] = *str;

		this->leng++;
		str++;
	}
    if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
    else this->buff[this->currentBuffer][this->leng]=0;

}

unsigned char * kString::c_str(void) const
{
	return this->buff[this->currentBuffer];
}

void kString::operator += (const char * str)
{
	while(*str != 0)
	{
		if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
		this->buff[this->currentBuffer][this->leng] = *str;

		this->leng++;
		str++;
	}
    if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
    else this->buff[this->currentBuffer][this->leng]=0;

}
void kString::operator += (const kString & str)
{
	unsigned char * cstr = str.c_str();
	unsigned short i,length;
	length = str.length();

	for(i=0;i<length;i++)
	{
		if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
		this->buff[this->currentBuffer][this->leng] = *cstr;

		this->leng++;
		cstr++;
	}
    if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
    else this->buff[this->currentBuffer][this->leng]=0;

}
void kString::operator = (const kString & str)
{
	unsigned char * cstr = str.c_str();
	unsigned short i,length;
	length = str.length();

	this->buff_leng=8;
	while(this->buff_leng < length) this->buff_leng *=2;

	delete [] this->buff[this->currentBuffer];
	this->buff[this->currentBuffer] = new unsigned char[this->buff_leng];
	this->leng=0;


	for(i=0;i<length;i++)
	{
		this->buff[this->currentBuffer][this->leng] = *cstr;
		this->leng++;
		cstr++;
	}
    if(this->leng == this->buff_leng) this->reallocateMemory(this->buff_leng*2);
    else this->buff[this->currentBuffer][this->leng]=0;


}
kString::kString(const kString & other)
{
	*this = other;
}
kString::kString(const char * str)
{
	*this = str;
}
const kString kString::operator +(const kString &str)
{
	kString res = *this;
	res += str;

	return res;
}

const kString kString::operator +(const char * str)
{
	kString res = *this;
	res += str;
	return res;
}
const kString operator +(const char * str1,const kString &str2)
{
	kString res = str1;
	res += str2;

	return res;
}
char * kString::number(int number,char * buffer)
{
	long long div=1;
	unsigned int digit;

	char buff[2];


	if(number < 0)
	{
		(*buffer) = '-';
		buffer++;
		number *= (-1);
	}

	while(div <= number)
	{
		div*=10;
	}
	if(number == 0) div*=10;
	div /= 10;

    buff[1] = 0;
	while(div)
	{
		digit = number/div;
		number = number % div;
		div /=10;


		buff[0] = ((char)(digit + 48));


		(*buffer) = buff[0];
		buffer++;

	}

	return buffer;
}
kString kString::number(int number)
{
	long long div=1;
	unsigned int digit;

	char buff[2];

	kString res;

	if(number < 0)
	{
		res = "-";
		number *= (-1);
	}

	while(div <= number)
	{
		div*=10;
	}
	if(number == 0) div*=10;
	div /= 10;

    buff[1] = 0;
	while(div)
	{
		digit = number/div;
		number = number % div;
		div /=10;


		buff[0] = ((char)(digit + 48));


		res += buff;

	}

	return res;
}

const kString kString::number(float number, unsigned char precision)
{
	long long temp;
	int num1,num2;
	kString res;
	unsigned long prec;

	prec = 1;
	while(precision)
	{
		prec *=10;
		precision--;
	}


	if(number < 0)
	{
		res = "-";
		number *= (-1);
	}
	num1 = number;
	res += kString::number(num1);

	if(prec/10)
	{
		res += ".";
		number *= prec;
		temp = number;
		num2 = temp % prec;
		temp = prec/10;
		while(temp > num2)
		{
			res += "0";
			temp /=10;
		}
		if(num2) res += kString::number(num2);
	}

	return res;
}
kString kString::getSubstring(char delimiter,unsigned char returned_part)
{
	unsigned char delimiter_counter=0,i;
	char * p;
	char *end;
	char *start;
	kString res;


	p=(char*)this->c_str();

	for(i=0;i<this->leng;i++)
	{
		if(delimiter_counter == returned_part)
		{
			start = p;
			break;
		}
		if(*p == delimiter) delimiter_counter++;
		p++;
	}
	for(;i<this->leng;i++)
	{
		if(*p == delimiter) delimiter_counter++;
		if(delimiter_counter > returned_part)
		{
			end=p;
			break;
		}
		p++;
	}
	if(i == this->leng)
	{
		if(this->leng == this->buff_leng)
		{
			unsigned int start_offset;
			start_offset = (unsigned int)start - (unsigned int)this->c_str();
			this->reallocateMemory(this->buff_leng*2);

			start =(char*)(((unsigned int)this->c_str()) + ((unsigned int)start_offset));

		}
		end =  (char*)&(this->buff[this->currentBuffer][this->leng]);
	}

	// use as temporary storage
	delimiter_counter = *end;
	*end = 0;

	res = start;
	*end = delimiter_counter;

	return res;
}

int kString::toInt(void)
{
	//go to back
	unsigned char i=0;
	unsigned char isNegative=0;

	if(this->buff[this->currentBuffer][i] == '-')
	{
		isNegative = 1;
		i++;
	}



	while(this->buff[this->currentBuffer][i] > 47 && this->buff[this->currentBuffer][i] < 58)
	{
		i++;
		if(i == this->buff_leng) break;
	}

	unsigned int multi=1;
	int res=0;
	i--;
	while(this->buff[this->currentBuffer][i] > 47 && this->buff[this->currentBuffer][i] < 58)
	{
		res += (this->buff[this->currentBuffer][i] - 48)*multi;
		if(i==0) break;
		multi*=10;
		i--;
	}

	if(isNegative) res *= (-1);

    return res;
}

float kString::toFloat()
{
    if(!this->leng) return 0;
    int res=0;
    unsigned int multi = 1;
    unsigned int div=0;
    unsigned char *p = &(this->buff[this->currentBuffer][this->leng]);
    float fres;


    p--;
    while(*p > 47 && *p < 58)
    {
        res += (*p -48)*multi;
        multi*=10;

        if(p==this->buff[this->currentBuffer]) break;
        p--;

    }
    if(*p == '.') div=multi;

    while(p != this->buff[this->currentBuffer])
    {
        p--;

        if(*p > 47 && *p < 58)
        {
            res += (*p -48)*multi;
            multi*=10;
        }else
        {
            if(*p == '-') res *= (-1);
            break;

        }
    }


    fres=res;
    if(div) fres /= div;

    return fres;
}

char * kString::copy(const char * source,char * destination)
{
	while(*source)
	{
		(*destination) = (*source);
		destination++;
		source++;
	}
	return destination;
}
char * kString::skipOneWord(const char * string)
{
	//skip white space
	while((*string) && ((*string) == ' ')) string++;

	//append current word
	while((*string) && ((*string) != ' ')) string++;

	//skip white space
	while((*string) && ((*string) == ' ')) string++;

	return (char*)string;
}
char * kString::find(const char * string,char chr)
{
	while(((*string) != 0) && (*string) != chr)string++;
	if(!(*string)) return 0;
	return (char*)string;
}
char * kString::skipWhiteSpace(const char * string)
{
	//skip white space
	while((*string) && ((*string) == ' ')) string++;
	return (char*)string;
}
char * kString::copyOneWord(const char * source,char * destination)
{
	source = kString::skipWhiteSpace(source);
	if(!(*source)) return destination;


	while((*source) > 32)
	{
		(*destination) = (*source);
		source++;
		destination++;
	}
	return destination;
}
char kString::compare(const char * string_1,const char * string_2)
{
	char res=-1;
	while((*string_1) == (*string_2))
	{
		string_1++;
		string_2++;

		if((*string_1) == 0 && (*string_2) != 0)
		{
			res = -1;
			break;
		}
		if((*string_1) != 0 && (*string_2) == 0)
		{
			res = 1;
			break;
		}
		if((*string_1) == 0 && (*string_2) == 0)
		{
			res = 0;
			break;
		}
	}

	return res;
}
bool kString::firstWordCompare(const char * string,const char * word)
{
	string = kString::skipWhiteSpace(string);
	if(!(*string)) return false;
	if(kString::compare(string,word) >= 0) return true;

	return false;
}
int kString::toInt(const char * string)
{
	//go to back
	unsigned char i=0;
	unsigned char isNegative=0;

	if(string[i] == '-')
	{
		isNegative = 1;
		i++;
	}



	while(string[i] > 47 && string[i] < 58)
	{
		i++;
	}

	unsigned int multi=1;
	int res=0;
	i--;
	while(string[i] > 47 && string[i] < 58)
	{
		res += (string[i] - 48)*multi;
		if(i==0) break;
		multi*=10;
		i--;
	}

	if(isNegative) res *= (-1);

    return res;
}
