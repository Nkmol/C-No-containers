#include "Harbour.h"
#include "Ship.h"

Harbour::Harbour(const ship_shop_datatype& data_adapter, Player& player) : adapter_ships_{ data_adapter }, player_(player)
{
}

void Harbour::OpenShipShop()
{
	std::cout << player_ << std::endl;
	std::cout << std::endl;
	std::cout << "type   " << "laadruimte   " << "kanonnen   " << "shadepunten   " << "bijzonderheden   " << "prijs   " << std::endl;;
	for (int i = 0; i < adapter_ships_.used(); i++)
	{
		std::cout << "[" << i << "]. " << adapter_ships_[i].key() << " = " << adapter_ships_[i].value() << std::endl;;
	}

	int number;
	std::cin >> number;
	buy_ship(number);
}

const int& Harbour::get_ship_price(const Ship& ship) const
{
	for (int i = 0; i < adapter_ships_.used(); i++)
	{
		// TODO change to equality operator? check by pointers instead?
		if(adapter_ships_[i].key().name() == ship.name())
		{
			return adapter_ships_[i].value();
		}
	}

	return 0;
}

void Harbour::buy_ship(int ship_index)
{
	if (ship_index < 0) return;

	auto ship_to_buy = adapter_ships_[ship_index];
	auto name = ship_to_buy.key().name();

	system("cls"); // hmm - OS specific and not pure c++
	std::cout << "Buying Ship \"" << name << "\"" << std::endl;

	if(ship_to_buy.value() > player_.get_gold())
	{
		std::cout << "You seem to be " << ship_to_buy.value() - player_.get_gold() << " gold off. Try again later." << std::endl;
		OpenShipShop();
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