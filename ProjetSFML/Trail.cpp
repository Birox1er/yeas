#include "Trail.h"

void AddShapeToTrail(TrailManager& trail, sf::Vector2f position)
{
	sf::CircleShape circle = sf::CircleShape(3);
	circle.setOrigin(3, 3);
	circle.setPosition(position);
	trail.trailPoints.push_front(circle);
}

void UpdateTrail(TrailManager& trail, float speed, sf::Vector2f position)
{
	trail.length = (int)speed;
	AddShapeToTrail(trail, position);
	std::list<sf::CircleShape>::iterator it = trail.trailPoints.begin();
	int i = 0;
	sf::Color col = sf::Color::Color(255,0,0,255);
	while (it != trail.trailPoints.end()) {
		float k = ((float)i / (float)trail.trailPoints.size())*3;
		if (k < 1) {
			col.r = Lerp(col.r, col.g, k);
			col.g = Lerp(col.g, col.r, k);
		}
		if (k < 2) {
			k -= 1;
			col.g = Lerp(col.g, col.b, k);
			col.b = Lerp(col.b, col.g, k);
		}
		if (k < 3) {
			k -= 2;
			col.b = Lerp(col.b, col.r, k);
			col.r = Lerp(col.r, col.g, k);
		}
		(*it).setFillColor(col);
		if (i > trail.length * 2) {
			(*it).setRadius((*it).getRadius() - 0.1);
		}
		if ((*it).getRadius() <= 0) {
			it = trail.trailPoints.erase(it);
		}
		else {
			it++;
			i++;
		}
	}
}

void DrawTrail(TrailManager& trail, sf::RenderWindow& window)
{
	std::list<sf::CircleShape>::iterator it = trail.trailPoints.begin();
	while (it != trail.trailPoints.end()) {
		window.draw((*it));
		it++;
	}
}

float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
