#include "Player.h"


Player::Player() : Player(0)
{
}

Player::Player(int gold) : gold_{gold}, ship_(Ship{})
{
}

const int& Player::get_gold() const
{
	return gold_;
}

Ship& Player::get_ship()
{
	return ship_;
}

Ship& Player::get_ship() const
{
	return ship_;
}

void Player::set_ship(Ship ship) const
{
	ship_ = ship;
}

void Player::decrease_gold(const int value)
{
	gold_ -= value;
}

void Player::increase_gold(const int value)
{
	gold_ += value;
}

bool Player::has_ship() const
{
	return ship_.name() != "";
}
