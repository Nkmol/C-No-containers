#include "Ship.h"

Ship::Ship(): shadepunten_(0), laadruimte_(0), kanonnen_(0)
{
}

Ship::Ship(const int& shadepunten, const int& laadruimte, const int& kanonnen, const std::string& naam,
	const std::string& bijzonderheden)
	: shadepunten_{ shadepunten }, laadruimte_{ laadruimte }, kanonnen_{ kanonnen }, naam_{ naam },
	bijzonderheden_{ bijzonderheden }
{
}