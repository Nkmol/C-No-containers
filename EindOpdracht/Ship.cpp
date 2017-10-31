#include "Ship.h"
#include "Helper.h"

Ship::Ship(): Ship("", 0, 0, 0, "")
{
}

Ship::Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden)
	: shadepunten_{ shadepunten }, laadruimte_{ laadruimte }, kanonnen_{ kanonnen }, naam_{ naam }, cur_laadruimte_ { 0 }
{
	if(bijzonderheden != "")
	{
		Helper::search_for_delimeter(bijzonderheden, ",", bijzonderheden_);

		// Remove whitespace
		for(auto i = 0; i < bijzonderheden_.used(); i++)
		{
			bijzonderheden_[i].remove_spaces();
		}
	}
}

bool Ship::operator==(const Ship& b) const
{
	auto* pntr_a = this;
	auto* pntr_b = &b;

	return pntr_a == pntr_b;
}

const String& Ship::name() const
{
	return naam_;
}

const int& Ship::laadruimte() const
{
	return laadruimte_;
}

const int& Ship::cur_laadruimte() const
{
	return cur_laadruimte_;
}

const int& Ship::kanonnen() const
{
	return kanonnen_;
}

const int& Ship::shadepunten() const
{
	return shadepunten_;
}

void Ship::damage(const int& value)
{
	shadepunten_ -= value;
}

const Vector<String>& Ship::bijzonderheden() const
{
	return bijzonderheden_;
}

const int& Ship::add_good(int value) const
{
	return cur_laadruimte_ += value;
}

bool Ship::has_speciality(const String& value) const
{
	auto result = false;
	for(int i = 0; i < bijzonderheden_.used(); i++)
	{
		const auto check = bijzonderheden_[i];
		if(check == value)
		{
			result = true;
			break;
		}
	}

	return result;
}