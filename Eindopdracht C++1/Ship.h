#pragma once
class Ship
{
public:
	Ship();
	~Ship();

private:
	char name[16];
	int price;
	int loadSpace;
	int cannonCount;
	int health;
	enum Uncommons
	{
		klein, licht, log
	};

};

Ship::Ship()
{
}

Ship::~Ship()
{
}