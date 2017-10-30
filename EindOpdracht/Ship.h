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
	mutable int cur_laadruimte_;
public:
	static const Ship empty_ship;
	Ship();
	Ship(const std::string& naam, int laadruimte, int kanonnen, int shadepunten, const std::string& bijzonderheden);
	bool operator==(const Ship& b) const;
	const std::string& name() const;
	const int& laadruimte() const;
	const int& cur_laadruimte() const;
	const int& kanonnen() const;
	const int& shadepunten() const;
	const std::string& bijzonderheden() const;
	const int& add_good(int value) const;
};

// https://stackoverflow.com/questions/5171739/tostring-override-in-c
inline std::ostream & operator<<(std::ostream & Str, Ship const & v) {
	Str << v.name() << "   " << v.cur_laadruimte() << "/" << v.laadruimte() << "   " << v.kanonnen() << "   " << v.shadepunten() << "   " << v.bijzonderheden();

	return Str;
}