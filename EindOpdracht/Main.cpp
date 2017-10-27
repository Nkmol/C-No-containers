#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"
#include "FileHandler.h"
#include "Map.h"


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

	for (size_t i = 0; i < file_handler.size(); i++)
	{
		std::cout << file_handler[i] << std::endl;
	}

	Vector<std::string> vector;
	vector.push_back("my value");
	vector.push_back("my value 2");
	for (size_t i = 0; i < vector.used(); i++)
	{
		std::cout << vector[i] << std::endl;
	}

	Map<std::string, std::string> map;
	map.insert("testkey", "value1");
	map.insert("testkey2", "value3");
	map.insert("testkey", "value2");

	auto find = map.find("testkey");
	for (size_t i = 0; i < find.used(); i++)
	{
		std::cout << find[i] << std::endl;
	}

	std::cin.get();
}
