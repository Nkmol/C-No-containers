#include "Ship.h"
#include "Helper.h"

Ship::Ship(): Ship("", 0, 0, 0, "")
{
}

Ship::Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden)
	: max_shadepunten_{shadepunten}, cur_shadepunten_{0}, laadruimte_{laadruimte}, max_cannons_{kanonnen}, naam_{naam},
	  cur_laadruimte_ {0}
{
	if (bijzonderheden != "")
	{
		Helper::search_for_delimeter(bijzonderheden, ",", bijzonderheden_);

		// Remove whitespace
		for (auto i = 0; i < bijzonderheden_.used(); i++)
		{
			bijzonderheden_[i].remove_spaces();
		}
	}
}

Ship::~Ship()
{
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

const int& Ship::max_cannons() const
{
	return max_cannons_;
}

const int& Ship::cur_cannons() const
{
	return cannons_.used();
}

void Ship::add_cannon(const Cannon& value)
{
	cannons_.push_back(value);
}

void Ship::remove_cannon(const int& index)
{
	cannons_.remove(index);
}

const int& Ship::max_shadepunten() const
{
	return max_shadepunten_;
}

const int& Ship::cur_shadepunten() const
{
	return cur_shadepunten_;
}

void Ship::damage(const int& value)
{
	cur_shadepunten_ += value;
}

void Ship::repair(const int& value)
{
	cur_shadepunten_ -= value;
	if (cur_shadepunten_ < 0)
		cur_shadepunten_ = 0;
}

const Vector<String>& Ship::bijzonderheden() const
{
	return bijzonderheden_;
}

const int& Ship::add_good(int value) const
{
	return cur_laadruimte_ += value;
}

bool Ship::sank() const
{
	return cur_shadepunten_ >= max_shadepunten_;
}

// klein, licht, log
bool Ship::has_speciality(const String& value) const
{
	auto result = false;
	for (int i = 0; i < bijzonderheden_.used(); i++)
	{
		const auto check = bijzonderheden_[i];
		if (check == value)
		{
			result = true;
			break;
		}
	}

	return result;
}
