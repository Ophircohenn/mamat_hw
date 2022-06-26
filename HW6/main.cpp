#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include <stddef.h>
#include <iostream>
#include "input.h"


int main(int argc, char** argv) //argv is rule std in is pkt
{
	if(check_args(argc,argv) != 0)
	{
		return 1;
	}

	String rule=argv[1];
	String** rule_a=new String*();
	size_t* size_rule_a=new size_t();
	rule.split("=", rule_a, size_rule_a);
	if((*rule_a)[0].equals("src-ip")
	|| (*rule_a)[0].equals("dst-ip"))
	{
		Ip rule_ip((*rule_a)[0]);
		rule_ip.set_value((*rule_a)[1]);
		parse_input(rule_ip);
		delete[](*rule_a);
		delete(size_rule_a);
		delete rule_a;
		return 0;
	}
	else if((*rule_a)[0].equals("src-port")
		|| (*rule_a)[0].equals("dst-port"))
		{
		Port rule_port((*rule_a)[0]);
		rule_port.set_value((*rule_a)[1]);
		parse_input(rule_port);
		delete[](*rule_a);
		delete(size_rule_a);
		delete rule_a;
		return 0;
		}
	else
	{
		delete[](*rule_a);
		delete rule_a;
		delete(size_rule_a);
		return 1;
	}
	delete[](*rule_a);
	delete rule_a;
	delete(size_rule_a);
	return 0;
}
