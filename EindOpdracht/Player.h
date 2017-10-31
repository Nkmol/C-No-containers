#pragma once
#include "Ship.h"

class Player
{
	int gold_;

	mutable Ship ship_;
public:
	Player();
	explicit Player(int gold);
	const int& get_gold() const;
	Ship& get_ship();
	Ship& get_ship() const;
	void set_ship(Ship ship) const;
	void decrease_gold(const int value);
	bool has_ship() const;
	void increase_gold(const int value);
};

inline std::ostream& operator<<(std::ostream& Str, Player const& v)
{
	Str << "-------------------------------------------------------------" << std::endl;
	Str << "                                                             " << std::endl;
	Str << " Gold:     " << v.get_gold() << "                                                  " << std::endl;

	if (!v.has_ship())
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
