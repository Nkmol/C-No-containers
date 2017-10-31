#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"
#include "FileHandler.h"
#include "CSVInterperter.h"
#include "Ship.h"
#include "Harbour.h"
#include <sstream>
#include "Product.h"
#include "Cannon.h"
#include "SailRoute.h"
#include "String.h"


std::stringstream standard_cout_stream(Player& player)
{
	std::stringstream buffer;
	system("cls");
	buffer << player << std::endl;
	std::cout << std::endl;

	return buffer;
}

Vector<KeyValuePair<Ship, int>> create_ship_shop_adapter()
{
	FileHandler file_handler;
	file_handler.load_file("schepen.csv");

	auto result = CSVInterperter::create_columns(file_handler);

	// Create [Ship, price]
	// This can be encapsulated to a Map<K, V>
	Vector<KeyValuePair<Ship, int>> ship_shop_adapter;
	for (int i = 0; i < result.used(); i++)
	{
		const auto line = result[i];
		const Ship ship {
			line[0].value(), 
			String::stoi(line[2].value()), 
			String::stoi(line[3].value()), 
			String::stoi(line[4].value()), 
			line[5].value()
		};

		const KeyValuePair<Ship, int> kv{ ship, String::stoi(line[1].value()) };

		ship_shop_adapter.push_back(kv);
	}

	return ship_shop_adapter;
}

Vector<KeyValuePair<String, Vector<Product>>> create_goods_shop_adapter()
{
	FileHandler file_handler;
	file_handler.load_file("goederen prijzen.csv");

	auto result = CSVInterperter::create_columns(file_handler);

	// Create [City_name, [goods_name, span_amount]]
	Vector<KeyValuePair<String, Vector<Product>>> goods_adapter;
	for (int i = 0; i < result.used(); i++)
	{
		String city;
		Vector<Product> goods;
		const auto line = result[i];
		for (int j = 0; j < line.used(); j++)
		{
			const auto& value = line[j];
			if(value.key() == "")
			{
				city = value.value();
				continue;
			}

			Product p { value.key(), value.value() };
			goods.push_back(p);
		}

		KeyValuePair<String, Vector<Product>> kv{ city, goods };
		goods_adapter.push_back(kv);
	}

	return goods_adapter;
}

Vector<Cannon> create_cannons_adapter()
{
	Vector<Cannon> result;

	result.push_back(Cannon{ "light", "0-5", 50 });
	result.push_back(Cannon{ "medium", "0-3", 200 });
	result.push_back(Cannon{ "heavy", "0-2", 1000 });

	return result;
}

Vector<KeyValuePair<String, Vector<SailRoute>>> create_routes_adapter()
{
	FileHandler file_handler;
	file_handler.load_file("afstanden tussen steden.csv");

	auto result = CSVInterperter::create_columns(file_handler);
	Vector<KeyValuePair<String, Vector<SailRoute>>> adapter;

	for (int i = 0; i < result.used(); i++)
	{
		String from;
		Vector<SailRoute> routes;
		const auto line = result[i];
		for (int j = 0; j < line.used(); j++)
		{
			const auto& value = line[j];
			if (value.key() == "")
			{
				from = std::move(value.value());
				continue;
			}

			const SailRoute r{ from, value.key(), String::stoi(value.value()) };
			routes.push_back(r);
		}

		const KeyValuePair<String, Vector<SailRoute>> kv { from, routes };
		adapter.push_back(kv);
	}

	return adapter;
}

int main(int argc, char* argv[])
{
	// init randomizer by seed (seed is hardware coupled)
	std::random_device rd;
	std::mt19937 mt(rd());

	// ~ init ~
	// Create player with random amount of money (10000 to 20000)
	const std::uniform_int_distribution<int> dist_gold(10000, 20000);
	Player player{dist_gold(mt)};

	// After construction, the adapter should not be modified
	const auto adapter_ships = create_ship_shop_adapter();
	const auto adapter_goods = create_goods_shop_adapter();
	const auto adapter_cannons = create_cannons_adapter();
	const auto adapter_routes = create_routes_adapter();

	/// Initalize harbours
	Vector<Harbour> harbours;
	for (int i = 0; i < adapter_goods.used(); i++)
	{
		// link routes and goods (by harbour name from one of the lists)
		// TODO better to intialize independently
		const Vector<SailRoute>* adapter_routes_harbour = nullptr;
		for(int j = 0; i < adapter_routes.used(); i++)
		{
			// Same harbour
			if(adapter_routes[i].key() == adapter_goods[i].key())
			{
				adapter_routes_harbour = &adapter_routes[i].value();
				break;
			}
		}

		const Harbour h { &adapter_ships, &adapter_goods[i].value(), &adapter_cannons, adapter_routes_harbour, &mt, adapter_goods[i].key() };
		harbours.push_back(h);
	}
	
	// Choose one of the harbors
	auto& r_harbour = harbours[std::uniform_int_distribution<int> (0, harbours.used())(mt)];
	r_harbour.enter_shop(&player);

	// First buy a ship
	while (!player.has_ship()) {
		std::cout << standard_cout_stream(player).str();
		std::cout << "First, get yourself a worthy ship" << std::endl;

		r_harbour.open_ship_shop();
	}

	while (true)
	{
		std::cout << standard_cout_stream(player).str();
		const int option = r_harbour.open_shop();

		std::cout << standard_cout_stream(player).str();
		const int option_sub = r_harbour.process_option(option);

		if(option == 4)
		{
			// Simulate sailing
			auto route = r_harbour.get_route(option_sub);

			system("cls");
			while (route.turns() > 0)
			{
				std::cout << "Only " << route.turns() << " turns to go until you have arrived at " << route.to() << std::endl;

				route.sail(player, mt);

				std::cin.clear();
				std::cin.ignore();
			}
			
			// Get "to"-harbour
			for(int i =0; i < harbours.used(); i++)
			{
				if(harbours[i].get_name() == route.to())
				{
					r_harbour = harbours[i];
				}
			}
		}

		std::cin.ignore();
	}
}

