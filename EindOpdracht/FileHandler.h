#pragma once
#include <string>
#include "Vector.h"
#include "String.h"

class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	const size_t& size() const;
	void load_file(const std::string& path);
	void process(std::istream& str);
	String const& operator[](size_t index) const;
private:
	Vector<String> data_;
};

