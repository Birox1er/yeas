#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


struct Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	int rotateSpeed = 100;
	int speed = 20;
	/*Prepare le terrain pour acceleration et deceleration
	int baseSpeed
	int MaxSpeed
	int friction en µ/Maxspeed
	*/
	sf::Vector2<float> dir;
	
};
void RecalculateAngles(Player& player);