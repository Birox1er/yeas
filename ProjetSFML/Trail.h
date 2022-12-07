#pragma once
#include <SFML/Graphics.hpp>
#include <list>

struct TrailManager
{
	int length;
	std::list<sf::CircleShape> trailPoints;
};
void AddShapeToTrail(TrailManager& trail, sf::Vector2f position);
void UpdateTrail(TrailManager& trail, float speed, sf::Vector2f position);
void DrawTrail(TrailManager& trail, sf::RenderWindow& window);
