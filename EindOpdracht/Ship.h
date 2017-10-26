#pragma once
#include <string>

class Ship
{
	int shadepunten_;
	int laadruimte_;
	int kanonnen_;
	std::string naam_;
	std::string bijzonderheden_;
public:
	Ship();
	Ship(const int& shadepunten, const int& laadruimte, const int& kanonnen, const std::string& naam,
		const std::string& bijzonderheden);
};

