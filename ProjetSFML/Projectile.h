#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

struct Player;

struct Projectile
{
	int speed;
	int rebound;
	sf::Vector2f direction;
	sf::CircleShape shape;
	bool IsEnemy = false;
	bool canHit = true;
};
struct ProjectileManager {
	float timeBtw;
	sf::Vector2f position;
	float chrono;
	std::list<Projectile> projectiles;
};

ProjectileManager CreateProjectileManager(float timeBtw, float chrono, sf::Vector2f position);
void AddProjectileToGame(ProjectileManager& projectileManager,sf::Vector2f direction,int speed,int radius,int rebound);
void UpdateProjectile(ProjectileManager& projManager, float deltaTime, sf::Vector2f size, Player& player);
void DrawProjectile(ProjectileManager& projManager, sf::RenderWindow& window);
sf::Vector2f Normalize(sf::Vector2f vector);
float Norm(sf::Vector2f vector);


