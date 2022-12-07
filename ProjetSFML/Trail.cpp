#include "Trail.h"

void AddShapeToTrail(TrailManager& trail, sf::Vector2f position)
{
	sf::CircleShape circle = sf::CircleShape(3);
	circle.setOrigin(3, 3);
	circle.setPosition(position);
	trail.trailPoints.push_front(circle);
}

void UpdateTrail(TrailManager& trail, float speed, sf::Vector2f position, bool oui)
{
	trail.length = (int)speed;
	AddShapeToTrail(trail, position);
	std::list<sf::CircleShape>::iterator it = trail.trailPoints.begin();
	int i = 0;
	sf::Color col = sf::Color::Color(0,0,0,255);
	while (it != trail.trailPoints.end()) {
		if (oui) {
			float k = ((float)i / (float)trail.trailPoints.size()) * 6;
			int startCol = (int)k;
			if (startCol == 6) {
				startCol--;
			}
			float t = k - startCol;
			sf::Color c1 = trail.colors[startCol];
			sf::Color c2 = trail.colors[startCol + 1];
			col.r = Lerp(c1.r, c2.r, t);
			col.g = Lerp(c1.g, c2.g, t);
			col.b = Lerp(c1.b, c2.b, t);

			if (speed / 45 * .9f)
				(*it).setFillColor(col);
		}
		else {
			(*it).setFillColor(sf::Color::White);
		}
		
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
