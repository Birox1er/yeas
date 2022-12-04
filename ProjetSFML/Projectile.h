#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

struct Projectile
{
	int speed;
	int rebound;
	sf::Vector2f direction;
	sf::CircleShape shape;
	bool IsEnemy = false;
};
struct ProjectileManager {
	float timeBtw;
	sf::Vector2f position;
	float chrono;
	std::list<Projectile> projectiles;
};

ProjectileManager CreateProjectileManager(float timeBtw, float chrono, sf::Vector2f position);
void AddProjectileToGame(ProjectileManager& projectileManager,sf::Vector2f direction,int speed,int radius,int rebound);
void UpdateProjectile(ProjectileManager& projManager, float timeDeltaTime, sf::Vector2f size);
void DrawProjectile(ProjectileManager& projManager, sf::RenderWindow& window);
sf::Vector2f Normalize(sf::Vector2f vector);


