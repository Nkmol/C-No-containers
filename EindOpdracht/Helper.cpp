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

int Helper::request_int(int min, int max)
{
	std::cout << std::endl;

	int i;
	for (;;)
	{
		std::cout << "Please enter in your choice [" << min << " - " << max << "] : ";
		if (std::cin >> i)
		{
			if (i >= min && i <= max)
				break;
			std::cout << "Please enter a value that is in range." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
		}
		else
		{
			std::cout << "Please enter a valid integer" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	// Ignore "leaked"  space
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return i;
}

void Helper::enter_continue()
{
	std::cout << "Press enter to continue..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
