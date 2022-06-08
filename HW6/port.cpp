#include <stddef.h>
#include <iostream>
#include "string.h"
#include "field.h"
#include "port.h"

Port::Port(String pattern) : Field(pattern)
{
	low=0;
	high=0;

}

Port::Port(const Port &port)
{
	high=port.high;
	low=port.low;
}
//sets the value
//rturn when succes
bool Port::set_value(String val)
{
	String** range=new String*();
	size_t* size_range=new size_t();
	if(range==NULL)
	{
		std::cout<<"output undefined";
		return false;
	}
	val.split("-", range, size_range);
	if((*size_range)!=2 || (((*range)[1].to_integer()==-1 )
		|| ((*range)[0].to_integer() == -1)))
	{
		delete[](*range);
		delete(size_range);
		return false;
	}
	int flag =0;
	int high=(*range)[1].to_integer();
	int low=(*range)[0].to_integer();

	if(low>65535||low<0)
		{
			flag=1;
		}
	if(high>65535||high<0)
		{
			flag=1;
		}
	if(high<low|| (flag==1))
	{

		delete[](*range);
		delete(size_range);
		return false;
	}
	this->high=(unsigned short)(*range)[1].to_integer();
	this->low=(unsigned short)(*range)[0].to_integer();
	delete[](*range);
	delete(size_range);
	return true;
}
//match the values with internals value. return true when value
//r
bool Port::match_value(String value) const //value = 64string
{
	if(value.to_integer()>=this->low)
	{
		if(value.to_integer()<=this->high)
		{
			return true;
		}
	}
	return false;

}

Port::~Port(){}

