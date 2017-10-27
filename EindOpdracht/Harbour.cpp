#include "Harbour.h"



Harbour::Harbour()
{
	menu();
	std::cin.get();
	//while (inHarbour) {
	//	std::cout << "What do you want to do? ";
	//	std::cin >> option;
	//	std::cout << option;
	//}
}

void Harbour::menu() {

		choice2 = 0;
		mainMenu();

		switch (Harbour::choice1) {
		case 1:
			std::cout << "1 - Inkopen/Verkopen goederen\n";
			break;
		case 2:
			std::cout << "2 - Kopen/verkopen kannonen\n";
			break;
		case 3:
			std::cout << "3 - Kopen/verkopen schepen\n";
			break;
		case 4:
			std::cout << "4 - Weg varen\n";
			break;
		case 5:
			std::cout << "5 - Reparen boot\n";
			break;
		case 6:
			std::cout << "6 - Weg varen\n";
			break;
		case 7:
			std::cout << "7 - Exit\n";
			break;
		}

}

void Harbour::options(void) {

	do {
		optionsMenu();

		switch (choice2) {

		case 1:
			std::cout << "So difficult!\n";
			break;

		case 2:
			std::cout << "Beep!\n";
			break;

		case 3:
			break;

		default:
			break;

		}

	} while (choice2 != 3);


}

void Harbour::mainMenu(void) {



	std::cout << "Menu\n";
	std::cout << "1 - Inkopen/Verkopen goederen\n";
	std::cout << "2 - Kopen/verkopen kannonen\n";
	std::cout << "3 - Kopen/verkopen schepen\n";
	std::cout << "4 - Weg varen\n";
	std::cout << "5 - Reparen boot\n";
	std::cout << "6 - Weg varen\n";
	std::cout << "7 - Exit\n";
	std::cout << "Please choose: ";
	std::cin >> choice1;

}

void Harbour::optionsMenu(void) {

	std::cout << "Options Menu\n";
	std::cout << "1 - Difficulty\n";
	std::cout << "2 - Sound";
	std::cout << "3 - Back\n";
	std::cout << "Please choose: ";
	std::cin >> choice2;

}
