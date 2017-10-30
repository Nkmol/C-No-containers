#pragma once
#include <string>
#include "Ship.h"
#include "Player.h"
#include <random>
#include "Product.h"
#include "Cannon.h"

class Harbour
{
	using ships_shop_datatype = Vector<KeyValuePair<Ship, int>>;
	using goods_shop_datatype = Vector<Product>;
	using cannons_shop_datatype = Vector<Cannon>;

	const goods_shop_datatype* adapter_goods_;
	const ships_shop_datatype* adapter_ships_;
	const cannons_shop_datatype* adapter_cannons_;

	Player* player_;
	std::mt19937* random_;

	std::string name_;
public:
	Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods, const cannons_shop_datatype* cannons, std::mt19937* random, Player* player, const std::string& name);
	Harbour(const ships_shop_datatype* ships, const goods_shop_datatype* goods, const cannons_shop_datatype* cannons, std::mt19937* random, const std::string& name);
	Harbour();
	~Harbour();
	void enter_shop(Player* player);
	int open_shop() const;
	void process_option(const int& option);
	void open_cannons_shop();
	void buy_cannon(int number);
	void open_goods_shop();
	void buy_good(int number);
	void calculate_cannon_prices();
	void calculate_good_prices();
	void open_ship_shop() const;
	const int& get_ship_price(const Ship& ship) const;
	void buy_ship(int ship_index) const;
	const std::string& get_name() const;
	void set_name(const std::string& name);
};
