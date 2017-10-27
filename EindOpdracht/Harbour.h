#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

class Harbour
{
	void menu();
	void mainMenu();
	void optionsMenu();
	void options();
	int choice1 = 0;
	int choice2 = 3;

public:
	Harbour();
private:
	bool inHarbour = true;
};


