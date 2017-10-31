#pragma once
#include "String.h"
#include "Player.h"
#include <random>

class SailRoute
{
	String from_;
	String to_;
	int turns_;
public:
	SailRoute(const String from, const String to, const int& turns);
	SailRoute();
	~SailRoute();
	const String& from() const;
	const String& to() const;
	const int& turns() const;
	void sail(const Player& player, std::mt19937& random);
	void not_moved() const;
	void normal_wind();
};
