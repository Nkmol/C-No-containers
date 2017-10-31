#pragma once
#include "String.h"
#include "Vector.h"

class Ship
{
	int shadepunten_;
	int laadruimte_;
	int kanonnen_;
	String naam_;
	Vector<String> bijzonderheden_;
	mutable int cur_laadruimte_;
public:
	static const Ship empty_ship;
	Ship();
	Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden);
	bool operator==(const Ship& b) const;
	const String& name() const;
	const int& laadruimte() const;
	const int& cur_laadruimte() const;
	const int& kanonnen() const;
	const int& shadepunten() const;
	void damage(const int& value);
	const Vector<String>& bijzonderheden() const;
	const int& add_good(int value) const;
	bool has_speciality(const String& value) const;
};

// https://stackoverflow.com/questions/5171739/tostring-override-in-c
inline std::ostream & operator<<(std::ostream & Str, Ship const & v) {
	Str << v.name() << "   " << v.cur_laadruimte() << "/" << v.laadruimte() << "   " << v.kanonnen() << "   " << v.shadepunten() << "   ";
	
	// TODO can be replaced by "<<" operator of Vector<T>
	for (int i = 0; i < v.bijzonderheden().used(); i++)
	{
		Str << v.bijzonderheden()[i];
	}

	return Str;
}