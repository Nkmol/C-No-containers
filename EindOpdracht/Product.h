#pragma once
#include "String.h"
#include <random>

class Product
{
	//String costs_span_;
	int max_;
	int min_;
	mutable int acutal_cost_;
	String name_;
public:
	Product();
	Product(const String& name, const String& costs_span);
	~Product();
	void Product::recalculate(std::mt19937& mt) const;
	const String& get_name() const;
	const int& get_actual_cost() const;
};
