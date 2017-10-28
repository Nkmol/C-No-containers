#pragma once
#include "FileHandler.h"
#include "KeyValuePair.h"

using CSV_data_type = Vector<Vector<KeyValuePair<std::string, std::string>>>;

class CSVInterperter
{
	// Type that will represent the CSV structure
	static const std::string delimiter_;
	static const std::string ignore;
	CSVInterperter();
	static Vector<KeyValuePair<std::string, std::string>> create_line(const Vector<std::string>& values,
	                                                                  const Vector<std::string>& headers);
	static Vector<std::string> process_line(std::string line);
public:
	static CSV_data_type create_columns(const FileHandler& handler);
	~CSVInterperter();
};
