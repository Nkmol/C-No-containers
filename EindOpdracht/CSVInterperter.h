#pragma once
#include "FileHandler.h"
#include "Map.h"

class CSVInterperter
{
	FileHandler& handler_;
	static const std::string delimiter;
	static Vector<std::string> process_line(std::string& line);
	static void add_values(Vector<std::string>& values, Vector<std::string>& headers, Map<std::string, std::string>& result);
public:
	CSVInterperter(FileHandler& handler);
	Map<std::string, std::string> create_columns() const;
	~CSVInterperter();
};

