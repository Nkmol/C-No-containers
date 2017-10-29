#pragma once
#include "Ship.h"

class Player
{
	int gold_;

	// I can now change the actual ship, but I am not allowed to call non-const functions of the ship (for example `(*ship_).name = "new name"`)
	mutable const Ship* ship_;
public:
	Player();
	explicit Player(int gold);
	const int& get_gold() const;
	const Ship& get_ship() const;
	void set_ship(const Ship& ship) const;
	void decrease_gold(const int value);
	bool has_ship() const;
	void increase_gold(const int value);
};

inline std::ostream & operator<<(std::ostream & Str, Player const & v) {
	Str << "-------------------------------------------------------------" << std::endl;
	Str << "                                                             " << std::endl;
	Str << " Gold:     " << v.get_gold() << "                                                  " << std::endl;

	if(!v.has_ship())
	{
		Str << " No ship                                                            " << std::endl;
	}
	else
	{
		Str << " " << v.get_ship() << "                                                            " << std::endl;
	}
	Str << "-------------------------------------------------------------" << std::endl;
	Str << std::endl;

	return Str;
}