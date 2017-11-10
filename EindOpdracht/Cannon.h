#pragma once
#include "String.h"
#include <random>
#include "String.h"

class Cannon
{
	int min_;
	int max_;
	int buy_price_;
	String type_;
	int min_damage_;
	int max_damage_;
	mutable int acutal_amount_;
public:
	Cannon(const String& type, const String& amount_span, const int& price, const String& damage_span);
	Cannon();
	~Cannon();
	void Cannon::recalculate(std::mt19937& mt) const;
	const String& get_type() const;
	const int& get_actual_amount() const;
	void reduce_actual_amount(const int& value) const;
	const int& get_price() const;
	const int& min_damage() const;
	const int& max_damage() const;
};
