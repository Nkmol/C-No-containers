#include "Harbour.h"
#include "Ship.h"

Harbour::Harbour(const ship_shop_datatype& data_adapter, Player& player) : adapter_ships_{ data_adapter }, player_(player)
{
}

int Harbour::open_shop() const
{
	std::cout << "Welcome to Harbour X, how may I assist you?" << std::endl;
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

void Harbour::process_option(const int& option) const
{
	switch (option)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		OpenShipShop();
		break;
	case 5:
	case 6:
	default:
		OpenShipShop();
	}
}

void Harbour::OpenShipShop() const
{
	std::cout << "type   " << "laadruimte   " << "kanonnen   " << "shadepunten   " << "bijzonderheden   " << "prijs   " << std::endl;;
	for (int i = 0; i < adapter_ships_.used(); i++)
	{
		std::cout << "[" << i << "]. " << adapter_ships_[i].key() << " = " << adapter_ships_[i].value() << std::endl;;
	}

	int number;
	std::cin >> number;
	// Ignore enter press in cin buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	buy_ship(number);
}

const int& Harbour::get_ship_price(const Ship& ship) const
{
	for (int i = 0; i < adapter_ships_.used(); i++)
	{
		if(adapter_ships_[i].key() == ship)
		{
			return adapter_ships_[i].value();
		}
	}

	return 0;
}

void Harbour::buy_ship(int ship_index) const
{
	if (ship_index < 0) return;

	const auto& ship_to_buy = adapter_ships_[ship_index];
	const auto& name = ship_to_buy.key().name();

	std::cout << "Buying Ship \"" << name << "\"" << std::endl;

	if(ship_to_buy.value() > player_.get_gold())
	{
		std::cout << "You seem to be " << ship_to_buy.value() - player_.get_gold() << " gold off. Try again later." << std::endl;

		std::cin.ignore();
		return;
	}

	// if player has ship, sell at 50%
	if(player_.has_ship())
	{
		const int& price = get_ship_price(player_.get_ship());
		player_.increase_gold(price*0.5);
	}

	player_.decrease_gold(ship_to_buy.value());
	player_.set_ship(ship_to_buy.key());
}
