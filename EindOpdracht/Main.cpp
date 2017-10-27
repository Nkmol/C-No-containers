#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"
#include "FileHandler.h"

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

	// Let player visit one of the harbors
	//  https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
	auto vector_int = Vector<std::string>{2};
	std::cout << vector_int.capcity() << std::endl;


	FileHandler file_handler;
	file_handler.load_file("schepen.csv");

	for (size_t i = 0; i < file_handler.size(); i++)
	{
		std::cout << file_handler[i] << std::endl;
	}

	std::cin.get();
}
