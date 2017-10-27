#include "CSVInterperter.h"

const std::string CSVInterperter::delimiter = ";";

CSVInterperter::CSVInterperter(FileHandler& handler) : handler_{handler}
{
}

Map<std::string, std::string> CSVInterperter::create_columns() const
{
	Vector<std::string> headers;
	Map<std::string, std::string> result;
	for (size_t i = 0; i < handler_.size(); i++)
	{
		auto line = handler_[i];
		Vector<std::string> values = process_line(line);

		if (values.used() > 0) {
			if (headers.used() == 0)
			{
				headers = values;
			}
			else
			{
				add_values(values, headers, result);
			}
		}
	}

	return result;
}

void CSVInterperter::add_values(Vector<std::string>& values, Vector<std::string>& headers, Map<std::string, std::string>& result)
{
	for(int i = 0; i < values.used(); i++)
	{
		result.insert(headers[i], values[i]);
	}
}

Vector<std::string> CSVInterperter::process_line(std::string& line)
{
	Vector<std::string> values;

	// TODO Improve way of ignoring comments
	if(line.substr(0, 1) == "#" )
	{
		return values;
	}

	size_t pos = 0;
	while ((pos = line.find(delimiter)) != std::string::npos) {
		//const std::string token = line.substr(0, pos);

		values.push_back(line.substr(0, pos));

		line.erase(0, pos + delimiter.length());
	}

	// Push last value
	values.push_back(line);

	return values;
}

CSVInterperter::~CSVInterperter()
{
}
