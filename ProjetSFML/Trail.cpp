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
	while (it != trail.trailPoints.end()) {
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
