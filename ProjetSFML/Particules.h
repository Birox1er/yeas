#pragma once
#include <list>
#include <iostream>
#include<SFML/Graphics.hpp>
struct Particle
{
	float particleLifeTime;
	float timeLeft;
	sf::Vector2f dir;
	sf::CircleShape circle;
};
struct ParticleSystem
{
	float chrono;
	float chrono2;
	float timeBtw;
	float rayonSpawn;
	float particleRadiusMax;
	float particleRadiusMin;
	sf::Vector2f origine;
	std::list<Particle> particles;
};
ParticleSystem CreateParticleSystem( float timeBtw, float rayonSpawn, float particleRadiusMax, float particleRadiusMin);
void AddParticleToSystem(ParticleSystem& particleSystem, float particleLifeTime,sf::Vector2f origine);
void UpdateParticleSystem(ParticleSystem& particleSystem, float timeDeltaTime);
void DrawParticleSystem(ParticleSystem& particleSystem, sf::RenderWindow& window);


