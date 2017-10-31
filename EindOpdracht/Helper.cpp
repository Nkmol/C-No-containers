#include "Helper.h"


Helper::Helper()
{
}

void Helper::search_for_delimeter(String to_serach, String delimeter, Vector<String>& result)
{
	size_t pos = 0;
	pos = to_serach.find(static_cast<char*>(delimeter));

	// while((post = s.find()) != npos) does not work?
	while (pos != String::npos)
	{
		const auto properties = to_serach.substr(0, pos);
		result.push_back(properties);

		to_serach.erase(0, pos + delimeter.length());

		pos = to_serach.find(static_cast<char*>(delimeter));
	}

	// Push last value
	result.push_back(to_serach);
}

Helper::~Helper()
{
}
