#include "Projectile.h"

void AddProjectileToGame(ProjectileManager& projectileManager, sf::Vector2f direction, int speed, int radius,int rebound)
{
	projectileManager.chrono = 0;
	Projectile proj{ speed,rebound,direction };
	proj.shape.setRadius(radius);
	proj.shape.setOrigin(radius, radius);
	proj.shape.setPosition(projectileManager.position);
	projectileManager.projectiles.push_back(proj);

}

ProjectileManager CreateProjectileManager(float timeBtw, float chrono, sf::Vector2f position)
{
	ProjectileManager projManager{ timeBtw,position,chrono };
	return projManager;
}

void UpdateProjectile(ProjectileManager& projManager, float timeDeltaTime)
{
	if (projManager.projectiles.size() > 0) {
		std::list<Projectile>::iterator it = projManager.projectiles.begin();
		while (it != projManager.projectiles.end()) {
			sf::Vector2f norm = Normalize((*it).direction);
			(*it).shape.setPosition((*it).shape.getPosition().x+norm.x * (*it).speed * timeDeltaTime, (*it).shape.getPosition().y+norm.y * (*it).speed * timeDeltaTime);
			it++;
		}
	}
	projManager.chrono += timeDeltaTime;
}
void DrawProjectile(ProjectileManager& projManager, sf::RenderWindow& window) {
	if (projManager.projectiles.size() > 0) {
		std::list<Projectile>::iterator it = projManager.projectiles.begin();
		while (it != projManager.projectiles.end()) {
			window.draw((*it).shape);
			it++;
		}
		std::cout << "drawn \n";
	}
}
sf::Vector2f Normalize(sf::Vector2f vector) {
	float norme = sqrt(vector.x * vector.x + vector.y * vector.y);

	return sf::Vector2f(vector.x / norme, vector.y / norme);
}
