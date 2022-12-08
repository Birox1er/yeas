#pragma once
#include "Player.h"
#include "Enemy.h"

struct Game
{
	float score;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape shape;
	Player player;
	EnemyManager enemies; 

};

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size);
void GameUpdate(Game& game, float deltaTime);
void CheckOutsides(Game& game, Player& player);
void GameDraw(Game& game, sf::RenderWindow& window);
void PressedSpace(Game& game, float deltaTime);
void PressedE(Game& game);