#pragma once
#include "String.h"
#include "Player.h"
#include <random>
#include "Cannon.h"
#include "KeyValuePair.h"

class SailRoute
{
	String from_;
	String to_;
	int turns_;

	std::mt19937* random_;
public:
	SailRoute(const String from, const String to, const int& turns);
	SailRoute();
	~SailRoute();
	const String& from() const;
	const String& to() const;
	const int& turns() const;
	void sail(const Player& player, std::mt19937& random, const Vector<KeyValuePair<Ship, int>>& ship_adapter,
	          const Vector<Cannon>
	          cannon_adapter);
	void not_moved() const;
	void normal_wind();
	void pirate_event(const Player& player, std::mt19937& random, const Vector<KeyValuePair<Ship, int>>& ship_adapter,
	                  const Vector<Cannon>
	                  cannon_adapter) const;
	void pirate_event_surrender(Ship& player_ship) const;
	bool pirate_event_flee(Ship& player_ship, Ship& pirate_ship) const;
	void pirate_event_shoot(Ship& player_ship, Ship& pirate_ship) const;
	void pirate_shoot(Ship& player_ship, Ship& pirate_ship) const;
	void player_shoot(Ship& player_ship, Ship& pirate_ship) const;
};
