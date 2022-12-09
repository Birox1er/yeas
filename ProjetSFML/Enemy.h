#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Projectile.h"
#include "Particules.h"

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

struct EnemyManager {
	float timeBtw;
	sf::Vector2f position;
	float chrono;
	ParticleSystem system;
	std::list<Enemy> enemies ;
};

EnemyManager CreateEnemyManager(float timeBtw, sf::Vector2f position, float chrono);
void GenerateEnemyAndCreate(EnemyManager& enemymanager,int windoSizeX, int windoSizeY, Player& player);
Enemy CreateEnemy(int speed, int life, sf::Vector2f origine, int size, Player& player);
void UpdateEnemy(EnemyManager& enemies, float deltaTime,sf::Vector2f size, Player& player, float& score,float multiplier);
void EnemyDraw(EnemyManager& enemies, sf::RenderWindow& window);