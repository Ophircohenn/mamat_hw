#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

/*	Field::Field()
	{
		pattern="";
	}*/
    Field::Field(String pattern)
	{
    	this->pattern=pattern;
	}

    Field:: ~Field(){}
    //match the value
    //return when succes
    /* Returns true iff "packet" matches "this" */
    bool Field::match(String packet)
    {

    	String** packet_a=new String*();
    	size_t* size_packet_a=new size_t();

    	packet.split("=,", packet_a, size_packet_a);
    	for(size_t i=0;i<*size_packet_a;i++)
    	{
    		(*packet_a)[i]=(*packet_a)[i].trim();
    		if((*packet_a)[i].equals(this->pattern))
    		{
				(*packet_a)[i+1]=(*packet_a)[i+1].trim();
				String tmp=(*packet_a)[i+1];
				delete[](*packet_a);
				delete packet_a;
				delete(size_packet_a);
				return (this->match_value(tmp));
    		}
		}
		delete[](*packet_a);
		delete packet_a;
		delete(size_packet_a);
    	return false;
	}
