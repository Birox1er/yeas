#pragma once
#include "Player.h"
#include "Enemy.h"

struct Game
{
	float multiplier;
	float score;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape shape;
	Player player;
	EnemyManager enemies; 
	bool hasPressedSpace = false;
	bool canPressDSpace = false;
	float cd = .4f;
	float reuseCD = 3.0f;
};

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size);
void GameUpdate(Game& game, float deltaTime);
void CheckOutsides(Game& game, Player& player);
void GameDraw(Game& game, sf::RenderWindow& window);
void PressedSpace(Game& game, float deltaTime);
void PressedE(Game& game);