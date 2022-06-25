
#include <stddef.h>
#include <iostream>
#include "string.h"
#include "field.h"
#include "ip.h"

//match the value
//return when succes
bool Ip::match_value(String value) const //value =192.168.1.1
{
	if(mask==0)
	{
		return true;
	}
	else
	{
		String** packet_adr=new String*();
		size_t* size_p_a=new size_t();
		value.split(".",packet_adr, size_p_a);
		int bin_adr_val=
				((*packet_adr)[0].to_integer()<<24
				| (*packet_adr)[1].to_integer()<<16
				|(*packet_adr)[2].to_integer()<<8
				|(*packet_adr)[3].to_integer());
		bin_adr_val=bin_adr_val>>(32-this->mask);
		delete[](*packet_adr);
		delete(size_p_a);
		return (bin_adr_val==this->bin_ip);
	}

}

Ip::Ip(String pattern) : Field(pattern)
{
	this->address=new String*();
	this->size_a=new size_t();
	this->mask=0;
	this->bin_ip=0;
}
Ip::Ip(const Ip &ip) : Field(ip)
{
	this->mask=ip.mask;
	this->address=new String*();
	this->size_a=new size_t();
	this->bin_ip=ip.bin_ip;
	for(size_t i=0; i<*(ip.size_a)-1; i++)
	{
		*(this->address)[i]=*(ip.address)[i];
	}

	*(this->size_a)=*(ip.size_a);
}
Ip::~Ip()
{
	delete[](*address);
	delete(size_a);
}
//sets the value
//return when succes
bool Ip::set_value(String val)
{//we have in pattern "src-ip"/"dst-ip"
	//others are empty
	String** mask_check=new String*();
	size_t* size_mask_check=new size_t();
	if(mask_check==NULL)
	{
		std::cout<<"output undefined";
		return false;
	}
	val.split("/", mask_check, size_mask_check);
	if((*size_mask_check)>2)
		{
			delete[](*mask_check);
			delete(size_mask_check);
			return false;//!need checkif musthave mask
		}
	if((*size_mask_check)==2)
	{
		if((*mask_check)[1].to_integer()>32
			||(*mask_check)[1].to_integer()<0)///need check with -1
		{
			return false;
		}
	}

	this->mask=(*mask_check)[1].to_integer();


	((*mask_check)[0]).split(".", this->address, this->size_a);
	//192.168.0.2/85
	if(*size_a!=4)
	{
		return false;
	}

	for(size_t i=0;i<(*(this->size_a));i++)
	{
		//need to handle EROR on to integer
		if(((((*(this->address))[i].to_integer())<0) ||
		  (((*(this->address))[i].to_integer())>255)))
		{
			return false;
		}
	}
	this->bin_ip=
			((*(this->address))[0].to_integer()<<24 |
			(*(this->address))[1].to_integer()<<16
			|(*(this->address))[2].to_integer()<<8 |
			(*(this->address))[3].to_integer());
	this->bin_ip=this->bin_ip>>(32-(this->mask));
	delete[](*mask_check);
	delete(size_mask_check);
	return true;
}


