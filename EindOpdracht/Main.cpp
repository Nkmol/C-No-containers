#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"
#include "FileHandler.h"
#include "CSVInterperter.h"
#include "Ship.h"
#include "Harbour.h"
#include <sstream>


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
		const Ship ship{
			line[0].value(), std::stoi(line[2].value()), std::stoi(line[3].value()), std::stoi(line[4].value()), line[5].value()
		};

		KeyValuePair<Ship, int> kv{ ship, std::stoi(line[1].value()) };

		ship_shop_adapter.push_back(kv);
	}

	return ship_shop_adapter;
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
	const auto& adapter = create_ship_shop_adapter();
	Harbour harbor{ adapter, player };

	while (!player.has_ship()) {
		std::cout << standard_cout_stream(player).str();
		std::cout << "First, get yourself a worthy ship" << std::endl;

		harbor.OpenShipShop();
	}
	

	while (true)
	{
		std::cout << standard_cout_stream(player).str();
		const int option = harbor.open_shop();

		std::cout << standard_cout_stream(player).str();
		harbor.process_option(option);

		std::cin.ignore();
	}
}

