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

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "AdapterRepositories.h"
#include "Helper.h"


std::stringstream standard_cout_stream(Player& player)
{
	std::stringstream buffer;
	system("cls");
	buffer << player << std::endl;
	buffer << std::endl;

	return buffer;
}

// Encapsulate for memory leak detector
void run_program()
{
	// init randomizer by seed (seed is hardware coupled)
	std::random_device rd;
	std::mt19937 mt(rd());

	// ~ init ~
	// Create player with random amount of money (10000 to 20000)
	const std::uniform_int_distribution<int> dist_gold(10000, 20000);
	Player player{ dist_gold(mt) };

	// After construction, the adapter should not be modified
	const auto adapter_ships = AdapterRepositories::create_ship_shop_adapter();
	const auto adapter_goods = AdapterRepositories::create_goods_shop_adapter();
	const auto adapter_cannons = AdapterRepositories::create_cannons_adapter();
	const auto adapter_routes = AdapterRepositories::create_routes_adapter();

	/// Initalize harbours
	Vector<Harbour> harbours;
	for (int i = 0; i < adapter_goods.used(); i++)
	{
		// link routes and goods (by harbour name from one of the lists)
		// TODO better to intialize independently
		const Vector<SailRoute>* adapter_routes_harbour = nullptr;
		for (int j = 0; i < adapter_routes.used(); i++)
		{
			// Same harbour
			if (adapter_routes[i].key() == adapter_goods[i].key())
			{
				adapter_routes_harbour = &adapter_routes[i].value();
				break;
			}
		}

		const Harbour h{ &adapter_ships, &adapter_goods[i].value(), &adapter_cannons, adapter_routes_harbour, &mt, adapter_goods[i].key() };
		harbours.push_back(h);
	}

	// Choose one of the harbors
	auto& r_harbour = harbours[std::uniform_int_distribution<int>(0, harbours.used())(mt)];
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

		if (option == 4)
		{
			// Simulate sailing
			auto route = r_harbour.get_route(option_sub);

			system("cls");
			while (route.turns() > 0)
			{
				std::cout << "Only " << route.turns() << " turns to go until you have arrived at " << route.to() << std::endl;

				route.sail(player, mt);

				std::cin.ignore();

				if(player.get_ship().shadepunten() <= 0)
				{
					std::cout << "Your ship has been destroyed, thus lost the game" << std::endl;
					Helper::enter_continue();
					return;
				}
			}

			// sailing done -> get "to"-harbour
			for (int i = 0; i < harbours.used(); i++)
			{
				if (harbours[i].get_name() == route.to())
				{
					r_harbour.leave();
					r_harbour = harbours[i];
					r_harbour.enter_shop(&player);
				}
			}
		}

		if (option == 6)
		{
			break;
		}

		std::cin.ignore();
	}
}

int main(int argc, char* argv[])
{
	run_program();

	_CrtDumpMemoryLeaks();
	return 0;
}

