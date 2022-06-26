#ifndef IP_H
#define IP_H
#include <stddef.h>
#include <iostream>
#include "string.h"
#include "field.h"

class Ip: public Field
{
	private:
		String** address;
		size_t* size_a;
		int mask;
		int bin_ip;

	protected:
		/* Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
		   matches 1.1.*.*) */

	public:
		Ip(String pattern);

		Ip(const Ip &ip);

		~Ip();

		bool set_value(String val);
		bool match_value(String value) const;
};

#endif