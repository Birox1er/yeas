#pragma once
#include <SFML/Graphics.hpp>

struct Enemy
{
	int speed;
	int life;
	int size;
	sf::CircleShape enemyShape;
	sf::Vector2f origine;
	//sf::Vector2f direction;
	sf::Vector2f position;
};

Enemy CreateEnemy(int speed, int life, sf::Vector2f origine, int size);

