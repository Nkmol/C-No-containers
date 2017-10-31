#pragma once
#include "String.h"
#include "Vector.h"

class Ship
{
	int max_shadepunten_;
	int cur_shadepunten_;

	int laadruimte_;
	int kanonnen_;
	String naam_;
	Vector<String> bijzonderheden_;
	mutable int cur_laadruimte_;
public:
	Ship();
	Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden);
	~Ship();
	bool operator==(const Ship& b) const;
	const String& name() const;
	const int& laadruimte() const;
	const int& cur_laadruimte() const;
	const int& kanonnen() const;
	const int& max_shadepunten() const;
	const int& cur_shadepunten() const;
	void damage(const int& value);
	void repair(const int& value);
	const Vector<String>& bijzonderheden() const;
	const int& add_good(int value) const;
	bool sank() const;
	bool has_speciality(const String& value) const;
};

// https://stackoverflow.com/questions/5171739/tostring-override-in-c
inline std::ostream& operator<<(std::ostream& Str, Ship const& v)
{
	Str << v.name() << "   Cargo: " << v.cur_laadruimte() << "/" << v.laadruimte() << "   Cannons: " << v.kanonnen() <<
		"   Damaged: " << v.cur_shadepunten() << "/" << v.max_shadepunten() << "   ";

	// TODO can be replaced by "<<" operator of Vector<T>
	for (int i = 0; i < v.bijzonderheden().used(); i++)
	{
		Str << v.bijzonderheden()[i];
	}

	return Str;
}
