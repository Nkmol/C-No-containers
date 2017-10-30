#pragma once
#include <string>

class SailRoute
{
	std::string from_;
	std::string to_;
	int turns_;
public:
	SailRoute(const std::string from, const std::string to, const int& turns);
	SailRoute();
	~SailRoute();
	const std::string& from() const;
	const std::string& to() const;
	const int& turns() const;
};

