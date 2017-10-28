#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"
#include "FileHandler.h"
#include "CSVInterperter.h"
#include "Ship.h"
#include "Harbour.h"

int main(int argc, char* argv[])
{
	// init randomizer by seed (seed is hardware coupled)
	std::random_device rd;
	std::mt19937 mt(rd());

	// ~ init ~
	// Create player with random amount of money (10000 to 20000)
	const std::uniform_int_distribution<int> dist_gold(10000, 20000);
	const Player player{dist_gold(mt)};

	FileHandler file_handler;
	file_handler.load_file("schepen.csv");

	CSVInterperter interperter{ file_handler };
	auto result = interperter.create_columns();

	// Create [Ship, price]
	// This can be encapsulated to a Map<K, V>
	Vector<KeyValuePair<Ship, int>> ship_shop_adapter;
	for (int i = 0; i < result.used(); i++)
	{
		const auto line = result[i];
		Ship ship{ line[0].value(), stoi(line[2].value()), stoi(line[3].value()), stoi(line[4].value()), line[5].value() };

		KeyValuePair<Ship, int> kv { ship, stoi(line[1].value()) };

		ship_shop_adapter.push_back(kv);
	}

	Harbour harbor{ ship_shop_adapter, player};

	while(true)
	{
		harbor.OpenShipShop();

		std::cin.get();
		system("cls"); // hmm - OS specific and not pure c++
	}
}
