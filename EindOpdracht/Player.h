#pragma once
#include "Ship.h"

class Player
{
	int gold_;
public:
	Player();
	explicit Player(int gold);
	const int& get_gold() const;
};

