#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Ship.h"
#include "Player.h"

class Harbour
{
	using ship_shop_datatype = Vector<KeyValuePair<Ship, int>>;
	const ship_shop_datatype& adapter_ships_;
	Player& player_;

public:
	Harbour(const ship_shop_datatype& data_adapter, Player& player);
	void OpenShipShop();
	const int& get_ship_price(const Ship& ship) const;
	void buy_ship(int ship_index);
};
