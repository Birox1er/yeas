#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Projectile.h"
#include "Trail.h"

struct Player
{
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Sprite spritesheild;
	sf::Texture Texturesheild;
	bool isSheidOn = false;
	bool canSheildBeOn = true;

	sf::CircleShape hitboxFront;


	ProjectileManager projManager;
	TrailManager trail;

	int life = 5;
	int rotateSpeed = 150;
	float speed = 0;
	float AccSpeed = 15;
	int MaxSpeed = 45;
	float friction = 10;
	sf::Vector2<float> dir;
	bool wasZ = false;
	bool wasS = false;

	bool outWidth = false;
	bool outHeight = false;

	bool returntome = false;

};

void InitPlayer(Player& player, sf::Vector2f position);
void RecalculateAngles(Player& player);
void UpdatePlayer(Player& player, float deltaTime,sf::Vector2f size);
void PlayerDraw(Player& player, sf::RenderWindow& window,float score);
void PlayerPressedSpace(Player& player, float deltaTime);
void PlayerPressedE(Player& player);
