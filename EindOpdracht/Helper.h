#pragma once
#include "Vector.h"

class Helper
{
	Helper();
public:
	static void search_for_delimeter(std::string to_serach, std::string delimeter, Vector<std::string>& result);
	~Helper();
};

