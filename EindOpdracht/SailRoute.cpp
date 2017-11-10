#include "SailRoute.h"
#include "Helper.h"

SailRoute::SailRoute() : SailRoute("", "", 0)
{
}

SailRoute::SailRoute(const String from, const String to, const int& turns) : from_{from}, to_{to}, turns_{turns},
                                                                             random_(nullptr)
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

void SailRoute::sail(const Player& player, std::mt19937& random, const Vector<KeyValuePair<Ship, int>>& ship_adapter,
                     const Vector<Cannon> cannon_adapter)
{
	random_ = &random;
	// Pirate ship chance
	const std::uniform_int_distribution<int> dist_pirate_event(1, 100);
	const int pirate_event_chance = dist_pirate_event(random);
	if (pirate_event_chance <= 20)
	{
		pirate_event(player, random, ship_adapter, cannon_adapter);
		system("cls");
		return;
	}

	const std::uniform_int_distribution<int> dist_int(1, 20);
	const int random_int = dist_int(random);

	Ship& ship = player.get_ship();

	if (random_int >= 1 && random_int <= 2)
	{
		std::cout << "Wind status: No wind" << std::endl;
		not_moved();
	}
	else if (random_int >= 3 && random_int <= 4)
	{
		std::cout << "Wind status: Light breeze" << std::endl;
		if (ship.has_speciality("licht"))
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

		if (storm_event <= 40)
		{
			std::cout << "The storm has blown you off course. You loose 1 turn." << std::endl;
			turns_++;
		}
		else if (storm_event > 40 && storm_event <= 80)
		{
			std::cout << "Because of the storm you have not moved any turn closer to your destination." << std::endl;
		}
		else
		{
			std::cout << "Luckily, the storm did not affect your timing." << std::endl;
			normal_wind();
		}

		const std::uniform_int_distribution<int> dist_damage(1, 100);
		const int damage = dist_damage(random);

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

void SailRoute::pirate_event(const Player& player, std::mt19937& random,
                             const Vector<KeyValuePair<Ship, int>>& ship_adapter,
                             const Vector<Cannon> cannon_adapter) const
{
	std::cout << std::endl;
	std::cout << "A ship approaches you... It is a pirate ship!" << std::endl;
	Helper::enter_continue();

	const std::uniform_int_distribution<int> dist_pirate_ship(0, ship_adapter.used());
	const int pirate_ship_index = dist_pirate_ship(random);

	// Create random pirate ship
	auto r_ship = ship_adapter[pirate_ship_index].key();
	const std::uniform_int_distribution<int> dist_amount_cannonns(0, r_ship.max_cannons());
	const int amount_cannons = dist_amount_cannonns(random);

	for (int i = 0; i < amount_cannons; i++)
	{
		auto cannon_index = 0;
		if (r_ship.has_speciality("licht"))
		{
			const std::uniform_int_distribution<int> dist_random_cannon(0, cannon_adapter.used() - 2);
			cannon_index = dist_random_cannon(random);
		}
		else
		{
			const std::uniform_int_distribution<int> dist_random_cannon(0, cannon_adapter.used() - 1);
			cannon_index = dist_random_cannon(random);
		}

		r_ship.add_cannon(cannon_adapter[cannon_index]);
	}

	auto& player_ship = player.get_ship();

	while (!r_ship.sank() && !player_ship.sank())
	{
		system("cls");
		std::cout << "Pirate ship: " << r_ship << std::endl;
		std::cout << "Your ship: " << player_ship << std::endl;
		std::cout << std::endl;

		std::cout << "Choose on of the options" << std::endl;
		std::cout << "[0]. Shoot!" << std::endl;
		std::cout << "[1]. Flee!" << std::endl;
		std::cout << "[2]. Surrender" << std::endl;

		const auto number = Helper::request_int(0, 2);

		switch (number)
		{
		case 0:
			pirate_event_shoot(player_ship, r_ship);
			break;
		case 1:
			{
				const auto result = pirate_event_flee(player_ship, r_ship);
				if (result)
				{
					std::cout << "Succesfully fled the pirate ship!" << std::endl;
					Helper::enter_continue();
					return;
				}

				std::cout << "Failed to flee the pirate ship!" << std::endl;
				pirate_shoot(player_ship, r_ship);
				break;
			}
		case 2:
			pirate_event_surrender(player_ship);
			Helper::enter_continue();
			return;
		default:
			break;
		}

		Helper::enter_continue();
	}
}

void SailRoute::pirate_event_surrender(Ship& player_ship) const
{
	std::cout << "The pirates spare your lives, but take away all your cargo and throw away what they cannot carry." << std
		::endl;
	std::cout << "You lost " << player_ship.cur_cargo() << " different goods." << std::endl;

	player_ship.cargo_clear();
}

bool SailRoute::pirate_event_flee(Ship& player_ship, Ship& pirate_ship) const
{
	const std::uniform_int_distribution<int> dist_flee_chance(1, 100);
	const auto flee_chance = dist_flee_chance(*random_);

	auto chance_to_flee = 0;
	if (player_ship.has_speciality("licht"))
	{
		if (pirate_ship.has_speciality("licht"))
			chance_to_flee = 50;
		else if (pirate_ship.has_speciality("log"))
			chance_to_flee = 75;
		else
			chance_to_flee = 60;
	}
	else if (player_ship.has_speciality("log"))
	{
		if (pirate_ship.has_speciality("licht"))
			chance_to_flee = 30;
		else if (pirate_ship.has_speciality("log"))
			chance_to_flee = 40;
		else
			chance_to_flee = 55;
	}
	else
	{
		if (pirate_ship.has_speciality("licht"))
			chance_to_flee = 5;
		else if (pirate_ship.has_speciality("log"))
			chance_to_flee = 15;
		else
			chance_to_flee = 30;
	}

	return flee_chance >= chance_to_flee;
}

void SailRoute::pirate_event_shoot(Ship& player_ship, Ship& pirate_ship) const
{
	player_shoot(player_ship, pirate_ship);

	if (player_ship.sank())
	{
		std::cout << "You have destroyed the pirate ship!" << std::endl;
		Helper::enter_continue();

		return;
	}

	pirate_shoot(player_ship, pirate_ship);
}

void SailRoute::pirate_shoot(Ship& player_ship, Ship& pirate_ship) const
{
	int damage = pirate_ship.shoot(*random_);
	std::cout << "The pirate ship shoots its cannon with the damage of " << damage << std::endl;
	player_ship.damage(damage);
}

void SailRoute::player_shoot(Ship& player_ship, Ship& pirate_ship) const
{
	int damage = player_ship.shoot(*random_);
	std::cout << "You shoot your cannons with the damage of " << damage << std::endl;
	pirate_ship.damage(damage);
}
