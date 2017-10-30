#include "SailRoute.h"



SailRoute::SailRoute() : SailRoute("", "", 0)
{
}

SailRoute::SailRoute(const std::string from, const std::string to, const int& turns) : from_{from}, to_{to}, turns_{turns}
{
}

SailRoute::~SailRoute()
{
}

const std::string& SailRoute::from() const
{
	return from_;
}

const std::string& SailRoute::to() const
{
	return to_;
}

const int& SailRoute::turns() const
{
	return turns_;
}
