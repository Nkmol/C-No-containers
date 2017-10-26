#include "Player.h"



Player::Player(): gold_(0)
{
}

Player::Player(int gold) : gold_(gold)
{
}

const int& Player::get_gold() const
{
	return gold_;
}
