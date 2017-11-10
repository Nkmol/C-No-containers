#include "Ship.h"
#include "Helper.h"
#include <random>

Ship::Ship(): Ship("", 0, 0, 0, "")
{
}

Ship::Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden)
	: max_shadepunten_{shadepunten}, cur_shadepunten_{0}, max_cargo_{laadruimte}, cargo_ {0}, max_cannons_{kanonnen},
	  naam_{naam}
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

const int& Ship::max_cargo() const
{
	return max_cargo_;
}

const int& Ship::cur_cargo() const
{
	return cargo_.used();
}

const Vector<Product>& Ship::cargo() const
{
	return cargo_;
}

void Ship::cargo_clear()
{
	cargo_.clear();
}

const Vector<Cannon>& Ship::cannons() const
{
	return cannons_;
}

const int& Ship::max_cannons() const
{
	return max_cannons_;
}

const int& Ship::cur_cannons() const
{
	return cannons_.used();
}

// Add copy
void Ship::add_cannon(const Cannon value)
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

// Add copy
void Ship::add_good(const Product value)
{
	cargo_.push_back(value);
}

void Ship::remove_good(int index)
{
	cargo_.remove(index);
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

int Ship::shoot(std::mt19937& random) const
{
	int total_damage = 0;
	for(int i = 0; i < cannons_.used(); i++)
	{
		const auto& cannon = cannons_[i];
		const std::uniform_int_distribution<int> dist_damage(cannon.min_damage(), cannon.max_damage());
		total_damage += dist_damage(random);
	}

	return total_damage;
}