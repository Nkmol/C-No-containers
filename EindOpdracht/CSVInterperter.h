#pragma once
#include "FileHandler.h"
#include "KeyValuePair.h"
#include "String.h"

using CSV_data_type = Vector<Vector<KeyValuePair<String, String>>>;

class CSVInterperter
{
	// Type that will represent the CSV structure
	static const String delimiter_;
	static const String ignore;
	CSVInterperter();
	static Vector<KeyValuePair<String, String>> create_line(const Vector<String>& values,
	                                                                  const Vector<String>& headers);
	static Vector<String> process_line(String line);
public:
	static CSV_data_type create_columns(const FileHandler& handler);
	~CSVInterperter();
};
