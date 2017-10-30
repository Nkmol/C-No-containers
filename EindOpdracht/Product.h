#pragma once
#include <string>
#include <random>

class Product
{
	//std::string costs_span_;
	int max_;
	int min_;
	mutable int acutal_cost_;
	std::string name_;
public:
	Product();
	Product(const std::string& name, const std::string& costs_span);
	~Product();
	void Product::recalculate(std::mt19937& mt) const;
	const std::string& get_name() const;
	const int& get_actual_cost() const;
};

