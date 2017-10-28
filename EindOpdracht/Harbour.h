#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Ship.h"
#include "Player.h"

class Harbour
{
	using ship_shop_datatype = Vector<KeyValuePair<Ship, int>>;
	ship_shop_datatype adapter_ships_;
	Player player_;

public:
	Harbour(ship_shop_datatype& data_adapter, const Player& player);
	void OpenShipShop();
	const int& get_ship_price(const Ship& ship) const;
	void buy_ship(int ship_index);
};
