#include "Harbour.h"
#include "Ship.h"
#include "Helper.h"

Harbour::Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods,
                 const cannons_shop_datatype* cannons, std::mt19937* random,
                 Player* player, const std::string& name)
	: adapter_goods_{goods}, adapter_ships_{ships}, adapter_cannons_{cannons}, player_ {
		player
	}, random_{random}, name_{name}
{
}

Harbour::Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods,
                 const cannons_shop_datatype* cannons, std::mt19937* random, const std::string& name) : Harbour(
	ships, goods, cannons, random, nullptr, name)
{
}

Harbour::Harbour() : Harbour(nullptr, nullptr, nullptr, nullptr, "")
{
	
}

Harbour::~Harbour()
{
}

void Harbour::enter_shop(Player* player)
{
	player_ = player;
	calculate_good_prices();
	calculate_cannon_prices();
}

int Harbour::open_shop() const
{
	std::cout << "Welcome to Harbour " << name_ << ", how may I assist you?" << std::endl;
	std::cout << "[1]. I would like to sell/buy some goods." << std::endl;
	std::cout << "[2]. I would like like to buy/sell kannons." << std::endl;
	std::cout << "[3]. I would like like to buy/sell a new ship." << std::endl;
	std::cout << "[4]. I need some help with direction to the other harbours." << std::endl;
	std::cout << "[5]. Repair my boat (costs 1 gold for 10 damage points)" << std::endl;
	std::cout << "[6]. Quit game" << std::endl;

	int number;
	std::cin >> number;

	return number;
}

void Harbour::process_option(const int& option)
{
	switch (option)
	{
	case 1:
		open_goods_shop();
		break;
	case 2:
		open_cannons_shop();
		break;
	case 3:
		open_ship_shop();
		break;
	case 4:
	case 5:
	case 6:
	default:
		open_shop();
	}
}

void Harbour::open_cannons_shop()
{
	std::cout << "Our cannons: " << std::endl;
	auto& adapter = *adapter_cannons_;
	for (int i = 0; i < adapter.used(); i++)
	{
		auto& cannon = adapter[i];
		std::cout << "[" << i << "]. " << cannon.get_type() << " [" << cannon.get_actual_amount() << "] = " << cannon.get_price() << std::endl;
	}

	int number;
	std::cin >> number;

	buy_cannon(number);
}

void Harbour::buy_cannon(int number)
{
	auto& player_ship = player_->get_ship();
	if (player_ship.cur_laadruimte() + 1 > player_ship.laadruimte())
	{
		std::cout << "It seems that your ship cannot carry any more goods. " << std::endl;
		std::cin.ignore();
		return;
	}


	auto& adapter = *adapter_cannons_;
	if (adapter[number].get_actual_amount() <= 0)
	{
		std::cout << "Seems like this cannon is out of stock" << std::endl;
		return;
	}

	if (adapter[number].get_price() > player_->get_gold())
	{
		std::cout << "You seem to be " << adapter[number].get_price() - player_->get_gold() << " gold off. Try again later."
			<< std::endl;

		return;
	}
	
	player_->decrease_gold(adapter[number].get_price());
	player_ship.add_good(1);
	adapter[number].reduce_actual_amount(1);
}

void Harbour::open_goods_shop()
{
	std::cout << "Our goods: " << std::endl;

	auto& adapter = *adapter_goods_;
	for (int i = 0; i < adapter.used(); i++)
	{
		std::cout << "[" << i << "]. " << adapter[i].get_name() << " = " << adapter[i].get_actual_cost() << std::endl;
	}

	int number;
	std::cin >> number;

	buy_good(number);
}

void Harbour::buy_good(int number)
{
	auto& player_ship = player_->get_ship();
	if (player_ship.cur_laadruimte() + 1 > player_ship.laadruimte())
	{
		std::cout << "It seems that your ship cannot carry any more goods. " << std::endl;
		std::cin.ignore();
		return;
	}

	auto& adapter = *adapter_goods_;
	if (adapter[number].get_actual_cost() > player_->get_gold())
	{
		std::cout << "You seem to be " << adapter[number].get_actual_cost() - player_->get_gold() << " gold off. Try again later."
			<< std::endl;

		return;
	}

	player_->decrease_gold(adapter[number].get_actual_cost());
	player_ship.add_good(1);
}

void Harbour::calculate_cannon_prices()
{
	auto& adapter = *adapter_cannons_;
	for (int i = 0; i < adapter.used(); i++)
	{
		adapter[i].recalculate(*random_);
	}
}

void Harbour::calculate_good_prices()
{
	auto& adapter = *adapter_goods_;
	for (int i = 0; i < adapter.used(); i++)
	{
		adapter[i].recalculate(*random_);
	}
}

void Harbour::open_ship_shop() const
{
	std::cout << "type   " << "laadruimte   " << "kanonnen   " << "shadepunten   " << "bijzonderheden   " << "prijs   " <<
		std::endl;

	auto& adapter = *adapter_ships_;
	for (int i = 0; i < adapter.used(); i++)
	{
		std::cout << "[" << i << "]. " << adapter[i].key() << " = " << adapter[i].value() << std::endl;
	}

	int number;
	std::cin >> number;
	// Ignore enter press in cin buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	buy_ship(number);
}

const int& Harbour::get_ship_price(const Ship& ship) const
{
	auto& adapter = *adapter_ships_;
	for (int i = 0; i < adapter.used(); i++)
	{
		if (adapter[i].key() == ship)
		{
			return adapter[i].value();
		}
	}

	return 0;
}

void Harbour::buy_ship(int ship_index) const
{
	if (ship_index < 0) return;

	auto& adapter = *adapter_ships_;
	const auto& ship_to_buy = adapter[ship_index];
	const auto& name = ship_to_buy.key().name();

	std::cout << "Buying Ship \"" << name << "\"" << std::endl;

	if (ship_to_buy.value() > player_->get_gold())
	{
		std::cout << "You seem to be " << ship_to_buy.value() - player_->get_gold() << " gold off. Try again later." << std::
			endl;

		std::cin.ignore();
		return;
	}

	// if player has ship, sell at 50%
	if (player_->has_ship())
	{
		const int& price = get_ship_price(player_->get_ship());
		player_->increase_gold(price * 0.5);
	}

	player_->decrease_gold(ship_to_buy.value());
	player_->set_ship(ship_to_buy.key());
}

const std::string& Harbour::get_name() const
{
	return name_;
}

void Harbour::set_name(const std::string& name)
{
	name_ = name;
}
