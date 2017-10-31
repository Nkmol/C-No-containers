#pragma once
#include "Vector.h"
#include "String.h"

class Helper
{
	Helper();
public:
	static void search_for_delimeter(String to_serach, String delimeter, Vector<String>& result);
	~Helper();
};

