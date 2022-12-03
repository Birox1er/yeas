#pragma once
#include "Player.h"
#include "Enemy.h"

struct Game
{
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape shape;
	Player player;
	Enemy enemy;

};

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size);
void GameUpdate(Game& game, float deltaTime);
void PressedSpace(Game& game, float deltaTime);
void CheckOutsides(Game& game, Player& player);
void GameDraw(Game& game, sf::RenderWindow& window);