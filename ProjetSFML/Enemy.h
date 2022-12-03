#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Projectile.h"

struct Player;

struct Enemy
{
	int baseSpeed = 100;
	int speed;
	int life;
	int size;
	sf::CircleShape enemyShape;
	sf::Vector2f origine;
	sf::Vector2f position;
	sf::Vector2f dir;
	sf::Sprite sprite;
	sf::Texture texture;

};

Enemy GenerateEnemyAndCreate(int windoSizeX, int windoSizeY, Player& player);
Enemy CreateEnemy(int speed, int life, sf::Vector2f origine, int size, Player& player);

void UpdateEnemy(Enemy& enemy, float deltaTime);
void EnemyDraw(Enemy& enemy, sf::RenderWindow& window);