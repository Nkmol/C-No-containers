#pragma once
#include "String.h"
#include "Vector.h"
#include "Cannon.h"
#include "Product.h"

class Ship
{
	int max_shadepunten_;
	int cur_shadepunten_;

	int max_cargo_;
	Vector<Product> cargo_;
	int max_cannons_;
	Vector<Cannon> cannons_;
	String naam_;
	Vector<String> bijzonderheden_;
public:
	Ship();
	Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden);
	~Ship();
	bool operator==(const Ship& b) const;
	const String& name() const;
	const int& max_cargo() const;
	const int& cur_cargo() const;
	const Vector<Product>& cargo() const;
	void cargo_clear();
	const Vector<Cannon>& cannons() const;
	const int& max_cannons() const;
	const int& cur_cannons() const;
	void add_cannon(const Cannon value);
	void remove_cannon(const int& index);
	const int& max_shadepunten() const;
	const int& cur_shadepunten() const;
	void damage(const int& value);
	void repair(const int& value);
	const Vector<String>& bijzonderheden() const;
	void add_good(const Product value);
	void remove_good(int index);
	bool sank() const;
	bool has_speciality(const String& value) const;
	int shoot(std::mt19937& random) const;
};

// https://stackoverflow.com/questions/5171739/tostring-override-in-c
inline std::ostream& operator<<(std::ostream& Str, Ship const& v)
{
	Str << v.name() << "   Cargo: " << v.cur_cargo() << "/" << v.max_cargo() << "   Cannons: " << v.cur_cannons() << "/" << v.max_cannons() <<
		"   Damaged: " << v.cur_shadepunten() << "/" << v.max_shadepunten() << "   ";

	// TODO can be replaced by "<<" operator of Vector<T>
	for (int i = 0; i < v.bijzonderheden().used(); i++)
	{
		Str << v.bijzonderheden()[i];
	}

	return Str;
}
