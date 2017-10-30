#include "Product.h"
#include "Helper.h"

Product::Product() : Product{"", ""}
{
}

Product::Product(const std::string& name, const std::string& costs_span) : acutal_cost_{0}, name_{name}
{
	if (costs_span != "") {
		Vector<std::string> r;
		Helper::search_for_delimeter(costs_span, "-", r);

		min_ = std::stoi(r[0]);
		max_ = std::stoi(r[1]);
	}
}
 
void Product::recalculate(std::mt19937& mt) const
{
	acutal_cost_ = std::uniform_int_distribution<int>(min_, max_)(mt);
}

const std::string& Product::get_name() const
{
	return name_;
}

const int& Product::get_actual_cost() const
{
	return acutal_cost_;
}

Product::~Product()
{
}
