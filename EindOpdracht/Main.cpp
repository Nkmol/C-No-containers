#include "Player.h"
#include <random>
#include <iostream>
#include "Vector.h"

int main(int argc, char* argv[])
{
	// init randomizer by seed (seed is hardware coupled)
	std::random_device rd;
	std::mt19937 mt(rd());

	// ~ init ~
	// Create player with random amount of money (10000 to 20000)
	std::uniform_int_distribution<int> distGold(10000, 20000);
	const Player player { distGold(mt) } ;
	std::cout << "Player gold: " << player.get_gold() << std::endl;

	// Let player visit one of the harbors
	auto vector_int = Vector<std::string>{ 2 };
	std::cout << vector_int.capcity() << std::endl;

	std::cin.get();
}
