#include "CSVInterperter.h"
#include "KeyValuePair.h"

const std::string CSVInterperter::delimiter = ";";
// Type that will represent the CSV structure
using CSV_data_type = Vector<Vector<KeyValuePair<std::string, std::string>>>;

CSVInterperter::CSVInterperter(FileHandler& handler) : handler_{handler}
{
}

CSV_data_type CSVInterperter::create_columns()
{
	Vector<Vector<KeyValuePair<std::string, std::string>>> data;
	Vector<std::string> headers;
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
				data.push_back(create_line(values, headers));
			}
		}
	}

	return data;
}

Vector<KeyValuePair<std::string, std::string>> CSVInterperter::create_line(Vector<std::string>& values, Vector<std::string>& headers)
{
	Vector<KeyValuePair<std::string, std::string>> properties;
	for(int i = 0; i < values.used(); i++)
	{
		KeyValuePair<std::string, std::string> kv {headers[i], values[i]};
		properties.push_back(kv);
	}

	return properties;
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
