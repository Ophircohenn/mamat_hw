
#include <stddef.h>
#include <iostream>
#include "string.h"

String::String()
{
	data=NULL;
	length=0;
}

/**
 * @brief Initiates string from other string
 */
String::String(const String &str)
{
	length=str.length;
	data=new char[length+1];
	for(size_t i=0;i<length+1;i++)
	{
		data[i]=str.data[i];
	}
}
/**
 * @brief Initiates a string from char array
 */

String::String(const char *str)
{
	int size=0;
	int i=0;
	while((str[i]) != 0)
	{
		size++;
		i++;
	}
	length=size;
	data=new char[length+1];
	for(size_t i=0;i<length+1;i++)
	{
		data[i]=str[i];
	}
}
String::~String()
{
	delete[] data;
	length=0;
}
/**
 * @brief Changes this from String
 */
String& String:: operator=(const String &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	this->length=rhs.length;
	delete[](this->data);
	this->data=new char[this->length+1];
	for(size_t i=0;i<this->length+1;i++)
		{
			this->data[i]=rhs.data[i];
		}
	return *this;
}
/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str)
{
	if(this->data == str)
	{
		return *this;
	}
	int size=0;
	while(*str!=0)
	{
		size++;
		str++;
	}
	str=str-size;
	this->length=size;
	delete[](this->data);
	this->data=new char[this->length+1];
	for(size_t i=0;i<this->length+1;i++)
		{
			this->data[i]=str[i];
		}
	return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const
{
	if(this->length!=rhs.length) return false;
	for(size_t i=0;i<this->length+1;i++)
		{
			if(this->data[i]!=rhs.data[i]) return false;
		}
	return true;
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const
{
	size_t size=0;
	while(*rhs!=0)
	{
		size++;
		rhs++;
	}
	rhs-=size;
	if(this->length!=size) return false;
		for(size_t i=0;i<this->length+1;i++)
			{
				if(this->data[i]!=rhs[i]) return false;
			}
		return true;

}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @no
 * te If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const
{

	int size_of_del=0;
	size_t counter_of_del=0;//num of substrings +1;
	while(delimiters[size_of_del] != 0)
	{
		size_of_del++;
	}
	for(size_t i=0;i<((this->length)+1);i++)
	{
		for(int j=0;j<size_of_del;j++)
		{
			if(delimiters[j]==this->data[i])
			{
				counter_of_del++;
			}
		}
	}
	counter_of_del++;
	*size=counter_of_del;
	if(output==NULL)
	{
		return;
	}

	*output=new String[counter_of_del];
	int counter_of_output=0;
	int sub_string_counter=0;
	for(size_t i=0;i<((this->length)+1);i++)
	{
		for(int j=0;j<size_of_del;j++)
		{

			if(this->data[i]==delimiters[j] ||
			((this->data[i]==0)&&(i<((this->length)+1))))
			{
				char* tmp2=new char[sub_string_counter+1];
				//going in output[i]
				for(int t=0;t<sub_string_counter;t++)
				{
					tmp2[t]=this->data[(i-sub_string_counter)+t];
				}
				tmp2[sub_string_counter]=0;
				(*output)[counter_of_output]=tmp2;
				sub_string_counter=0;
				delete[](tmp2);
				counter_of_output++;
				i++;
			}
		}
		sub_string_counter++;
	}
*size=counter_of_del;
return;
}


/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const
{
	int temp=0;
	for(size_t i=0;i < this->length;i++)//we start from the end
	{
		if(this->data[i]< '0' || this->data[i]>'9') return -1;
		temp *=10;
		temp+=this->data[i]-'0';
	}
	return temp;
}
/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const
{
	int front=0,back=this->length-1;
	while(this->data[front] == ' ')
	{
		front++;
	}
	while(this->data[back] == ' ')
	{
		back--;
	}
	char* tmp=new char[(back- front) + 1];
	//tmp="";
	for(int i=0; i<((back- front)+1);i++)
	{
		tmp[i]=0;
	}
	for(int i=front;i<=back;i++)
	{
		tmp[i-front]=this->data[i];
	}
	tmp[(back- front) + 1]=0;
	String new_string(tmp);
	delete[](tmp);
	return new_string;

}
/*
int String::get_len() const
{
	return this->length;
}
*/

/*int main()
{
String a;
char* aa="abcd";
a=aa;
char* del=";@";
String** t;
String b(aa);
String ac(b);
const String bb("    sdo@lksdlp;kdsamp;asd@m  ");
const String bb2("a@bcd;e;f;");
size_t* s;
bb2.split(del, t, s);
String cc("784984");
int x =cc.to_integer();
bool VV=b.equals(cc);
String cc2("784984");
bool VVV=cc2.equals(cc);
String trimm(bb.trim());
String trimm2(bb2.trim());
return 0;

}
*/
