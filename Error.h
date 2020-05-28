#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>

void error(std::string msg)
{
	std::cerr << msg << std::endl;
	exit(0);
}

#endif /* ERROR_H_ */
