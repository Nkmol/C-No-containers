#include "Player.h"



Player::Player() : Player(0)
{
}

// Right way of initalizing empty object?
Player::Player(int gold) : gold_(gold), ship_{ "empty", 0, 0, 0, "" }
{
}

const int& Player::get_gold() const
{
	return gold_;
}

const Ship& Player::get_ship() const
{
	return ship_;
}

void Player::set_ship(const Ship& ship)
{
	ship_ = ship;
}

void Player::decrease_gold(const int value)
{
	gold_ -= value;
}
