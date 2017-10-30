#pragma once
#include "Vector.h"

class String : public Vector<char>
{
public:
	String();
	~String();

	// Implicit
	String::String(char* input);
};

inline std::ostream & operator<<(std::ostream & str, String const & v) 
{
	for (int i = 0; i < v.used(); i++)
	{
		str << v[i];
	}

	return str;
}

inline String::String()
{
	
}

inline String::~String()
{
	
}

inline String::String(char* input)
{
	const int length = strlen(input) + 1;
	clear();

	for (int i = 0; i < length; i++)
	{
		push_back(*(input + i));
	}
}




