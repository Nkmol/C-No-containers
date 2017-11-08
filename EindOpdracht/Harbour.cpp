#include "Harbour.h"
#include "Ship.h"
#include "Helper.h"

Harbour::Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods,
                 const cannons_shop_datatype* cannons, const routes_datatype* routes,
                 std::mt19937* random,
                 Player* player, const String& name)
	: adapter_goods_{goods}, adapter_ships_{ships}, adapter_cannons_{cannons}, adapter_routes_{routes}, player_ {
		player
	}, random_{random}, name_{name}
{
}

Harbour::Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods,
                 const cannons_shop_datatype* cannons, const routes_datatype* routes, std::mt19937* random,
                 const String& name) : Harbour(
	ships, goods, cannons, routes, random, nullptr, name)
{
}

// Only used for vector allocation
Harbour::Harbour() : Harbour(nullptr, nullptr, nullptr, nullptr, nullptr, "")
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

const SailRoute& Harbour::get_route(int index) const
{
	return (*adapter_routes_)[index];
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

	const auto number = Helper::request_int(1, 6);

	return number;
}

int Harbour::process_option(const int& option)
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
		return open_harbour_list();
		break;
	case 5:
		repair();
	case 6:
	default:
		break;
	}

	return -1;
}

void Harbour::repair()
{
	if (1 > player_->get_gold())
	{
		std::cout << "You don't have enough gold for a simple repair?" << std::endl;
		Helper::enter_continue();
		return;
	}

	if (player_->get_ship().cur_shadepunten() == 0)
	{
		std::cout << "Your ship is already fully repaired." << std::endl;
		Helper::enter_continue();
		return;
	}

	player_->decrease_gold(1);
	player_->get_ship().repair(10);
}

int Harbour::open_harbour_list() const
{
	std::cout << "Choose a harbour you would like to sail to. " << std::endl;
	std::cout << "Current: " << name_ << std::endl;

	auto& adapter = *adapter_routes_;
	for (int i = 0; i < adapter.used(); i++)
	{
		auto& route = adapter[i];
		if (route.to() != name_)
		{
			std::cout << "[" << i << "]. " << route.to() << " in " << route.turns() << " turns." << std::endl;
		}
	}

	const auto number = Helper::request_int(0, adapter.used() - 1);

	return number;
}

void Harbour::open_cannons_shop()
{
	std::cout << "[0]. Sell cannons" << std::endl 
	<< std::endl;

	std::cout << "Our cannons: " << std::endl;
	auto& adapter = *adapter_cannons_;
	for (int i = 0; i < adapter.used(); i++)
	{
		auto& cannon = adapter[i];
		std::cout << "[" << i+1 << "]. " << cannon.get_type() << " [" << cannon.get_actual_amount() << "] = " << cannon.
			get_price() << std::endl;
	}

	const auto number = Helper::request_int(0, adapter.used());

	if(number == 0)
	{
		open_cannon_sell();
	}
	else {
		buy_cannon(number - 1); // to index based
	}
}

void Harbour::buy_cannon(int number) const
{
	auto& player_ship = player_->get_ship();
	if (player_ship.cur_cannons() + 1 > player_ship.max_cannons())
	{
		std::cout << "It seems that your ship cannot carry any more cannons. " << std::endl;
		Helper::enter_continue();
		return;
	}

	auto& adapter = *adapter_cannons_;
	if (adapter[number].get_actual_amount() <= 0)
	{
		std::cout << "Seems like this cannon is out of stock" << std::endl;
		Helper::enter_continue();
		return;
	}

	if (adapter[number].get_price() > player_->get_gold())
	{
		std::cout << "You seem to be " << adapter[number].get_price() - player_->get_gold() << " gold off. Try again later."
			<< std::endl;
		Helper::enter_continue();
		return;
	}

	if(player_ship.has_speciality("licht") && adapter[number].get_type() == "heavy")
	{
		std::cout << "This cannon would be too heavy for your ship. A light ship can only carry Medium or Light cannons. " << std::endl;
		Helper::enter_continue();
		return;
	}

	player_->decrease_gold(adapter[number].get_price());
	player_ship.add_cannon(adapter[number]);
	adapter[number].reduce_actual_amount(1);
}

void Harbour::open_cannon_sell() const
{
	std::cout << std::endl;
	std::cout << "List of cannons your ship currently has. Choose a cannon to sell" << std::endl;
	std::cout << "A cannon is sold at 50% of the official bought price." << std::endl;
	
	auto& player_ship = player_->get_ship();
	auto& cannons = player_ship.cannons();

	if(cannons.used() == 0)
	{
		std::cout << "Your ship seems to not have any cannons." << std::endl;
		Helper::enter_continue();
		return;
	}

	for(int i = 0; i < cannons.used(); i++)
	{
		auto& cannon = cannons[i];
		std::cout << "[" << i << "]. a " << cannon.get_type() << " cannon will sell for " << cannon.get_price() * 0.5 << std::endl;
	}

	const auto number = Helper::request_int(0, cannons.used() - 1);

	sell_cannon(number);
}

void Harbour::sell_cannon(int index) const
{
	auto& player_ship = player_->get_ship();
	auto& cannons = player_ship.cannons();

	const int sell_price = cannons[index].get_price() * 0.5;
	player_->increase_gold(sell_price);
	player_->get_ship().remove_cannon(index);
}

void Harbour::open_goods_shop() const
{
	std::cout << "[0]. Sell goods" << std::endl
		<< std::endl;

	std::cout << "Our goods: " << std::endl;

	auto& adapter = *adapter_goods_;
	for (int i = 0; i < adapter.used(); i++)
	{
		std::cout << "[" << i+1 << "]. " << adapter[i].get_name() << " = " << adapter[i].get_actual_cost() << std::endl;
	}

	const auto number = Helper::request_int(0, adapter.used());

	if (number == 0)
	{
		open_goods_sell();
	}
	else {
		buy_good(number - 1); // to index based
	}
}

void Harbour::buy_good(int number) const
{
	auto& player_ship = player_->get_ship();
	if (player_ship.cur_cargo() + 1 > player_ship.max_cargo())
	{
		std::cout << "It seems that your ship cannot carry any more goods. " << std::endl;
		Helper::enter_continue();
		return;
	}

	auto& adapter = *adapter_goods_;
	if (adapter[number].get_actual_cost() > player_->get_gold())
	{
		std::cout << "You seem to be " << adapter[number].get_actual_cost() - player_->get_gold() <<
			" gold off. Try again later."
			<< std::endl;
		Helper::enter_continue();
		return;
	}

	player_->decrease_gold(adapter[number].get_actual_cost());
	player_ship.add_good(adapter[number]);
}

void Harbour::open_goods_sell() const
{
	std::cout << std::endl;
	std::cout << "List of goods your ship is currently carrying." << std::endl;
	std::cout << "A product is sold at 50% of the official bought price." << std::endl;

	auto& player_ship = player_->get_ship();
	auto& player_goods = player_ship.cargo();

	if(player_goods.used() == 0)
	{
		std::cout << "You seem to not own any product." << std::endl;
		Helper::enter_continue();
		return;
	}

	for(int i = 0; i < player_goods.used(); i++)
	{
		auto& product = player_goods[i];
		std::cout << "[" << i << "]. a " << product.get_name() << " will sell for " << product.get_actual_cost() * 0.5 << std::endl;
	}

	const auto number = Helper::request_int(0, player_goods.used() - 1);

	sell_product(number);
}

void Harbour::sell_product(int index) const
{
	auto& player_ship = player_->get_ship();
	auto& player_goods = player_ship.cargo();

	const int sell_price = player_goods[index].get_actual_cost() * 0.5;
	player_->increase_gold(sell_price);
	player_->get_ship().remove_good(index);
}

void Harbour::calculate_cannon_prices() const
{
	auto& adapter = *adapter_cannons_;
	for (int i = 0; i < adapter.used(); i++)
	{
		adapter[i].recalculate(*random_);
	}
}

void Harbour::calculate_good_prices() const
{
	auto& adapter = *adapter_goods_;
	for (int i = 0; i < adapter.used(); i++)
	{
		adapter[i].recalculate(*random_);
	}
}

void Harbour::open_ship_shop() const
{
	/*std::cout << "type   " << "laadruimte   " << "kanonnen   " << "shadepunten   " << "bijzonderheden   " << "prijs   " <<
		std::endl;*/

	auto& adapter = *adapter_ships_;
	for (int i = 0; i < adapter.used(); i++)
	{
		std::cout << "[" << i << "]. " << adapter[i].key() << " = " << adapter[i].value() << std::endl;
	}

	const auto number = Helper::request_int(0, adapter.used() - 1);

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
	auto& ship_to_buy = adapter[ship_index];
	const auto& name = ship_to_buy.key().name();

	std::cout << "Buying Ship \"" << name << "\"" << std::endl;

	if (ship_to_buy.value() > player_->get_gold())
	{
		std::cout << "You seem to be " << ship_to_buy.value() - player_->get_gold() << " gold off. Try again later." << std::
			endl;
		Helper::enter_continue();
		return;
	}

	// if player has ship, sell at 50%
	if (player_->has_ship())
	{
		const auto& price = get_ship_price(player_->get_ship());
		player_->increase_gold(price * 0.5);
	}

	player_->decrease_gold(ship_to_buy.value());

	// Copy of adapter value
	player_->set_ship(ship_to_buy.key());
}

const String& Harbour::get_name() const
{
	return name_;
}

void Harbour::set_name(const String& name)
{
	name_ = name;
}

void Harbour::leave()
{
	player_ = nullptr;
}
