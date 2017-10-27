#pragma once
#include <string>
#include "Vector.h"

class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	const size_t& size() const;
	void load_file(const std::string& path);
	void process(std::istream& str);
	std::string const& operator[](size_t index) const;
private:
	Vector<std::string> data_;
};

