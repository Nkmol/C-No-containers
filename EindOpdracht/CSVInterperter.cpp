#include "CSVInterperter.h"
#include "KeyValuePair.h"
#include "Helper.h"

const std::string CSVInterperter::delimiter_ = ";";
const std::string CSVInterperter::ignore = "#";

CSV_data_type CSVInterperter::create_columns(const FileHandler& handler)
{
	CSV_data_type data;
	Vector<std::string> headers;
	for (size_t i = 0; i < handler.size(); i++)
	{
		const auto& line = handler[i];
		Vector<std::string> values = process_line(line);

		if (values.used() > 0)
		{
			if (headers.used() == 0)
			{
				headers = values;
			}
			else
			{
				auto line_data = create_line(values, headers);
				data.push_back(line_data);
			}
		}
	}

	return data;
}

CSVInterperter::CSVInterperter()
{
}

Vector<KeyValuePair<std::string, std::string>> CSVInterperter::create_line(
	const Vector<std::string>& values, const Vector<std::string>& headers)
{
	Vector<KeyValuePair<std::string, std::string>> properties;
	for (int i = 0; i < values.used(); i++)
	{
		KeyValuePair<std::string, std::string> kv{headers[i], values[i]};
		properties.push_back(kv);
	}

	return properties;
}

Vector<std::string> CSVInterperter::process_line(std::string line)
{
	Vector<std::string> values;

	// TODO Improve way of ignoring comments
	if (line.substr(0, 1) == ignore)
	{
		return values;
	}

	Helper::search_for_delimeter(line, delimiter_, values);

	return values;
}

CSVInterperter::~CSVInterperter()
{
}
