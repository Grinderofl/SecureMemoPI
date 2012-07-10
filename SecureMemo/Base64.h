#ifndef __BASE64__H
#define __BASE64__H

#include <iostream>

class Base64
{
public:
	std::string Encode(unsigned char const* toEncode, unsigned int len);
	//const char* Encode(const char* data);
};

#endif