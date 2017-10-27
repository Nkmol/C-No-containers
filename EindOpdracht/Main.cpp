#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"
#include "FileHandler.h"
#include "CSVInterperter.h"


int main(int argc, char* argv[])
{
	// init randomizer by seed (seed is hardware coupled)
	std::random_device rd;
	std::mt19937 mt(rd());

	// ~ init ~
	// Create player with random amount of money (10000 to 20000)
	const std::uniform_int_distribution<int> dist_gold(10000, 20000);
	const Player player{dist_gold(mt)};
	std::cout << "Player gold: " << player.get_gold() << std::endl;

	FileHandler file_handler;
	file_handler.load_file("schepen.csv");

	CSVInterperter interperter{ file_handler };
	auto result = interperter.create_columns();

	// Get all types of ships
	std::cout << std::endl;
	for (int i = 0; i < result.used(); i++)
	{
		const auto line = result[i];
		for(int j = 0; j < line.used(); j++)
		{
			std::cout << line[j].value() << "[ " << line[j].key() << " ]" << std::endl;
		}

		std::cout << "Ship created" << std::endl;
		std::cout << std::endl;
	}

	std::cin.get();
}
