#pragma once
#include "Ship.h"
#include "Player.h"
#include <random>
#include "Product.h"
#include "Cannon.h"
#include "SailRoute.h"
#include "KeyValuePair.h"
#include "String.h"

class Harbour
{
	using ships_shop_datatype = Vector<KeyValuePair<Ship, int>>;
	using goods_shop_datatype = Vector<Product>;
	using cannons_shop_datatype = Vector<Cannon>;
	using routes_datatype = Vector<SailRoute>;

	const goods_shop_datatype* adapter_goods_;
	const ships_shop_datatype* adapter_ships_;
	const cannons_shop_datatype* adapter_cannons_;
	const routes_datatype* adapter_routes_;

	Player* player_;
	std::mt19937* random_;

	String name_;
public:
	Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods, const cannons_shop_datatype* cannons, const routes_datatype* routes,
		std::mt19937* random, Player* player, const String& name);
	Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods, const cannons_shop_datatype* cannons, const routes_datatype* routes,
		std::mt19937* random, const String& name);
	Harbour();
	~Harbour();
	void enter_shop(Player* player);
	const SailRoute& get_route(int index) const;
	int open_shop() const;
	int process_option(const int& option);
	int open_harbour_list();
	void open_cannons_shop();
	void buy_cannon(int number);
	void open_goods_shop();
	void buy_good(int number);
	void calculate_cannon_prices();
	void calculate_good_prices();
	void open_ship_shop() const;
	const int& get_ship_price(const Ship& ship) const;
	void buy_ship(int ship_index) const;
	const String& get_name() const;
	void set_name(const String& name);
};
