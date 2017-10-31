#include "SailRoute.h"
#include <random>
#include <random>


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

void SailRoute::sail(const Player& player, std::mt19937& random)
{
	const std::uniform_int_distribution<int> dist_int(1, 20);
	const int random_int = dist_int(random);

	Ship ship = player.get_ship();

	if(random_int >= 1 && random_int <= 2 )
	{
		std::cout << "Wind status: No wind" << std::endl;
		not_moved();
	}
	else if (random_int >= 3 && random_int <= 4)
	{
		std::cout << "Wind status: Light breeze" << std::endl;
		if(ship.has_speciality("licht"))
		{
			normal_wind();
		}
		else
		{
			not_moved();
		}
	}
	else if (random_int >= 5 && random_int <= 7)
	{
		std::cout << "Wind status: Weak" << std::endl;
		if (ship.has_speciality("log"))
		{
			not_moved();
		}
		else
		{
			normal_wind();
		}
	}
	else if (random_int >= 8 && random_int <= 17)
	{
		std::cout << "Wind status: Normal" << std::endl;
		normal_wind();
	}
	else if (random_int >= 18 && random_int <= 19)
	{
		std::cout << "Wind status: Strong" << std::endl;
		std::cout << "The ship has moved with 2 turns." << std::endl;
		turns_ -= 2;
	}
	else if (random_int == 20)
	{
		std::cout << "Wind status: Storm" << std::endl;

		const std::uniform_int_distribution<int> dist_storm_event(1, 100);
		const int storm_event = dist_storm_event(random);

		if(storm_event <= 40)
		{
			std::cout << "The storm has blown you off course. You loose 1 turn." << std::endl;
			turns_++;
		}
		else if(storm_event > 40 && storm_event <= 80)
		{
			std::cout << "Because of the storm you have not moved any turn closer to your destination." << std::endl;
		}
		else
		{
			std::cout << "Luckily, the storm did not affect your timing." << std::endl;
			normal_wind();
		}

		const std::uniform_int_distribution<int> dist_damage(1, 100);
		int damage = dist_damage(random);

		std::cout << "Because of the storm, your ship has been damaged with a value of " << damage << std::endl;
		ship.damage(damage);
	}
}

void SailRoute::not_moved() const
{
	std::cout << "There is not enough wind, so the ship has not moved." << std::endl;
}

void SailRoute::normal_wind()
{
	std::cout << "The ship has moved with 1 turn." << std::endl;
	turns_--;
}