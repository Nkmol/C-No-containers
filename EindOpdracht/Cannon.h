#pragma once
#include <string>
#include <random>

class Cannon
{
	int min_;
	int max_;
	int buy_price_;
	std::string type_;
	mutable int acutal_amount_;
public:
	Cannon(const std::string& type, const std::string& amount_span, const int& price);
	Cannon();
	~Cannon();
	void Cannon::recalculate(std::mt19937& mt) const;
	const std::string& get_type() const;
	const int& get_actual_amount() const;
	void reduce_actual_amount(const int& value) const;
	const int& get_price() const;
};

