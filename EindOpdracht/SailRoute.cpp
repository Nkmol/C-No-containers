#include "SailRoute.h"



SailRoute::SailRoute() : SailRoute("", "", 0)
{
}

SailRoute::SailRoute(const String from, const String to, const int& turns) : from_{from}, to_{to}, turns_{turns}
{
}

SailRoute::~SailRoute()
{
}

const String& SailRoute::from() const
{
	return from_;
}

const String& SailRoute::to() const
{
	return to_;
}

const int& SailRoute::turns() const
{
	return turns_;
}
