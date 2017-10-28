#pragma once
#include <string>
#include "KeyValuePair.h"
#include "Vector.h"

class Ship
{
	int shadepunten_;
	int laadruimte_;
	int kanonnen_;
	std::string naam_;
	std::string bijzonderheden_;
public:
	Ship();
	Ship(const std::string& naam, int laadruimte, int kanonnen, int shadepunten, const std::string& bijzonderheden);
	Ship(Vector<KeyValuePair<std::string, std::string>>& data);
	const std::string& name() const;
	const int& laadruimte() const;
	const int& kanonnen() const;
	const int& shadepunten() const;
	const std::string& bijzonderheden() const;
};

// https://stackoverflow.com/questions/5171739/tostring-override-in-c
inline std::ostream & operator<<(std::ostream & Str, Ship const & v) {
	Str << v.name() << "   " << v.laadruimte() << "   " << v.kanonnen() << "   " << v.shadepunten() << "   " << v.bijzonderheden();

	return Str;
}