#pragma once
#include "FileHandler.h"
#include "KeyValuePair.h"

class CSVInterperter
{
	FileHandler& handler_;
	static const std::string delimiter;
	static Vector<std::string> process_line(std::string& line);
public:
	CSVInterperter(FileHandler& handler);
	Vector<Vector<KeyValuePair<std::string, std::string>>> create_columns();
	static Vector<KeyValuePair<std::string, std::string>> create_line(Vector<std::string>& values, Vector<std::string>& headers);
	~CSVInterperter();
};

