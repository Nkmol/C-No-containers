#include "CSVInterperter.h"
#include "KeyValuePair.h"
#include "Helper.h"
#include "String.h"

const String CSVInterperter::delimiter = ";";
const String CSVInterperter::ignore = "#";

CSV_data_type CSVInterperter::create_columns(const FileHandler& handler)
{
	CSV_data_type data;
	Vector<String> headers;
	for (size_t i = 0; i < handler.size(); i++)
	{
		const auto& line = handler[i];
		auto values = process_line(line);

		if (values.used() > 0)
		{
			if (headers.used() == 0)
			{
				headers = values;
			}
			else
			{
				const auto line_data = create_line(values, headers);
				data.push_back(line_data);
			}
		}
	}

	return data;
}

CSVInterperter::CSVInterperter()
{
}

Vector<KeyValuePair<String, String>> CSVInterperter::create_line(
	const Vector<String>& values, const Vector<String>& headers)
{
	Vector<KeyValuePair<String, String>> properties;
	for (int i = 0; i < values.used(); i++)
	{
		const KeyValuePair<String, String> kv{headers[i], values[i]};
		properties.push_back(kv);
	}

	return properties;
}

Vector<String> CSVInterperter::process_line(String line)
{
	Vector<String> values;

	const auto check = line.substr(0, 1);
	if (check == ignore)
	{
		return values;
	}

	Helper::search_for_delimeter(line, delimiter, values);

	return values;
}

CSVInterperter::~CSVInterperter()
{
}
