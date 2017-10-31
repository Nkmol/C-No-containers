#include "Ship.h"

const Ship Ship::empty_ship("empty", 0, 0, 0, "");

Ship::Ship(): Ship{ empty_ship }
{
}

Ship::Ship(const String& naam, int laadruimte, int kanonnen, int shadepunten, const String& bijzonderheden)
	: shadepunten_{ shadepunten }, laadruimte_{ laadruimte }, kanonnen_{ kanonnen }, naam_{ naam },
	bijzonderheden_{ bijzonderheden }, cur_laadruimte_ { 0 }
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

const int& Ship::kanonnen() const
{
	return kanonnen_;
}

const int& Ship::shadepunten() const
{
	return shadepunten_;
}

const String& Ship::bijzonderheden() const
{
	return bijzonderheden_;
}

const int& Ship::add_good(int value) const
{
	return cur_laadruimte_ += value;
}