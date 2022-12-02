#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


struct Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	int rotateSpeed = 100;
	float speed = 0;
	float AccSpeed = 10;
	int MaxSpeed = 25;
	float friction = 10;
	sf::Vector2<float> dir;
	bool wasZ = false;
	bool wasS = false;
};

void InitPlayer(Player& player, sf::Vector2f position);
void RecalculateAngles(Player& player);