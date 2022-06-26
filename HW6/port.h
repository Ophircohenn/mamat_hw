#ifndef PORT_H
#define PORT_H


#include <stddef.h>
#include <iostream>
#include "string.h"
#include "field.h"

class Port: public Field
{
	private:
	unsigned short high;
	unsigned short low;
	protected:
		/* Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
		   matches 1.1.*.*) */

	public:
		Port(String pattern);

		Port(const Port &port);

		~Port();

		bool set_value(String val);
		bool match_value(String value) const;
};

#endif