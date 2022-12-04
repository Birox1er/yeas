#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Projectile.h"


struct Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	sf::CircleShape hitbox;
	ProjectileManager projManager;
	int rotateSpeed = 100;
	float speed = 0;
	float AccSpeed = 10;
	int MaxSpeed = 25;
	float friction = 10;
	sf::Vector2<float> dir;
	bool wasZ = false;
	bool wasS = false;

	bool outWidth = false;
	bool outHeight = false;
};

void InitPlayer(Player& player, sf::Vector2f position);
void RecalculateAngles(Player& player);
void PlayerPressedSpace(Player& player, float deltaTime);
void UpdatePlayer(Player& player, float deltaTime,sf::Vector2f size);
void PlayerDraw(Player& player, sf::RenderWindow& window);