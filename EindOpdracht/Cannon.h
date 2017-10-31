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
	mutable int acutal_amount_;
public:
	Cannon(const String& type, const String& amount_span, const int& price);
	Cannon();
	~Cannon();
	void Cannon::recalculate(std::mt19937& mt) const;
	const String& get_type() const;
	const int& get_actual_amount() const;
	void reduce_actual_amount(const int& value) const;
	const int& get_price() const;
};

