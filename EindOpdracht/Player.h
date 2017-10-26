#pragma once
#include "Ship.h"

class Player
{
	int gold_;
	Ship own_ship_;
public:
	Player();
	explicit Player(const Ship& ship);
};

