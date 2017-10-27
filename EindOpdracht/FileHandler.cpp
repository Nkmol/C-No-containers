#include "FileHandler.h"
#include <fstream>


FileHandler::FileHandler()
{
}


FileHandler::~FileHandler()
{
}

const size_t& FileHandler::size() const
{
	return data_.used();
}

void FileHandler::load_file(const std::string& path)
{
	std::ifstream file(path);
	process(file);
	file.close();
}

void FileHandler::process(std::istream& str)
{
	// Todo make this line-by-line iteratable
	std::string line;
	while (getline(str, line))
	{
		data_.push_back(line);
	}
}

std::string const& FileHandler::operator[](size_t index) const
{
	return data_[index];
}
