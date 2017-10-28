#include "Ship.h"

Ship::Ship(): shadepunten_(0), laadruimte_(0), kanonnen_(0)
{
}

//Ship::Ship(const int& shadepunten, const int& laadruimte, const int& kanonnen, const std::string& naam,
//	const std::string& bijzonderheden)
//	: shadepunten_{ shadepunten }, laadruimte_{ laadruimte }, kanonnen_{ kanonnen }, naam_{ naam },
//	bijzonderheden_{ bijzonderheden }
//{
//}

// TODO quickfix
Ship::Ship(const std::string& naam, int laadruimte, int kanonnen, int shadepunten, const std::string& bijzonderheden)
	: shadepunten_{ shadepunten }, laadruimte_{ laadruimte }, kanonnen_{ kanonnen }, naam_{ naam },
	bijzonderheden_{ bijzonderheden }
{
}

Ship::Ship(Vector<KeyValuePair<std::string, std::string>>& data) : Ship(data[0].value() , stoi(data[2].value()), stoi(data[3].value()), stoi(data[4].value()), data[5].value())
{
}

const std::string& Ship::name() const
{
	return naam_;
}

const int& Ship::laadruimte() const
{
	return laadruimte_;
}

const int& Ship::kanonnen() const
{
	return kanonnen_;
}

const int& Ship::shadepunten() const
{
	return shadepunten_;
}

const std::string& Ship::bijzonderheden() const
{
	return bijzonderheden_;
}
