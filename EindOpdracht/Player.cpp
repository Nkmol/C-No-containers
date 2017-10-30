#include "Player.h"



Player::Player() : Player(0)
{
}

// Right way of initalizing empty object?
Player::Player(int gold) : gold_{ gold }, ship_{ &Ship::empty_ship }
{
}

const int& Player::get_gold() const
{
	return gold_;
}

const Ship& Player::get_ship() const
{
	return *ship_;
}

void Player::set_ship(const Ship& ship) const
{
	ship_ = &ship;
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
	return !(ship_ == &Ship::empty_ship);
}

