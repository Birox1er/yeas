#pragma once
#include "Player.h"

struct Game
{
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape shape;
	Player player;

};

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size);
