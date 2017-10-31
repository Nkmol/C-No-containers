#include "Cannon.h"
#include "Helper.h"


Cannon::Cannon(const String& type, const String& amount_span, const int& price) : buy_price_{price}, type_ {type},
                                                                                  acutal_amount_{0}
{
	if (amount_span != "")
	{
		Vector<String> r;
		Helper::search_for_delimeter(amount_span, "-", r);

		min_ = String::stoi(r[0]);
		max_ = String::stoi(r[1]);
	}
}

Cannon::Cannon() : Cannon("", "", 0)
{
}


Cannon::~Cannon()
{
}

void Cannon::recalculate(std::mt19937& mt) const
{
	acutal_amount_ = std::uniform_int_distribution<int>(min_, max_)(mt);
}

const String& Cannon::get_type() const
{
	return type_;
}

const int& Cannon::get_actual_amount() const
{
	return acutal_amount_;
}

void Cannon::reduce_actual_amount(const int& value) const
{
	acutal_amount_ -= value;
	if (acutal_amount_ < 0) acutal_amount_ = 0;
}

const int& Cannon::get_price() const
{
	return buy_price_;
}
