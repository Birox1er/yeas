#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) 
{
	if (!font.loadFromFile("Fonts/dominique/Dominique-win.ttf")) {
		std::cout << "No font avalaible";
	}

	//Bouton Play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 200);

	//Bouton Options
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Options");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 400);

	//Bouton Quit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Quit");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 600);


	MainMenuSelected = -1;
}

MainMenu::~MainMenu() {

}

void MainMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; i++) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() {
	
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		std::cout << MainMenuSelected << std::endl;
		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown() {
	
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		std::cout << MainMenuSelected << std::endl;
		MainMenuSelected++;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}