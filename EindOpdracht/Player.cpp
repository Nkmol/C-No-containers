#include "Player.h"



Player::Player(): gold_(0)
{
}

Player::Player(const Ship& ship) : gold_(0), own_ship_ {ship}
{
}
