#include "Helper.h"
#include <string>
#include "Vector.h"


Helper::Helper()
{
}

void Helper::search_for_delimeter(std::string to_serach, std::string delimeter, Vector<std::string>& result)
{
	size_t pos = 0;
	while ((pos = to_serach.find(delimeter)) != std::string::npos)
	{
		auto properties = to_serach.substr(0, pos);
		result.push_back(properties);

		to_serach.erase(0, pos + delimeter.length());
	}

	// Push last value
	result.push_back(to_serach);
}

Helper::~Helper()
{
}
