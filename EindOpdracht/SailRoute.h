#pragma once
#include "String.h"

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
};

