#pragma once
#include <SFML/Graphics.hpp>
#include <list>

struct TrailManager
{
	int length;
	std::list<sf::CircleShape> trailPoints;
	sf::Color colors[7] = {
		sf::Color::Red,
		sf::Color::Color(255,165,0,255),
		sf::Color::Yellow,
		sf::Color::Green,
		sf::Color::Cyan,
		sf::Color::Blue,
		sf::Color::Magenta
	};
};
void AddShapeToTrail(TrailManager& trail, sf::Vector2f position);
void UpdateTrail(TrailManager& trail, float speed, sf::Vector2f position, bool oui);
void DrawTrail(TrailManager& trail, sf::RenderWindow& window);
float Lerp(float a, float b, float t);