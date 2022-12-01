#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


struct Player
{
	sf::CircleShape triangle;
	int rotateSpeed = 100;
	sf::Vector2<float> dir;
	
};
void RecalculateAngles(Player& player);