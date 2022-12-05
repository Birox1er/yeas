#include "Projectile.h"
#include "Player.h"

void AddProjectileToGame(ProjectileManager& projectileManager, sf::Vector2f direction, int speed, int radius,int rebound)
{
	projectileManager.chrono = 0;
	Projectile proj{ speed,rebound,direction };
	proj.shape.setRadius(radius);
	proj.shape.setOrigin(radius, radius);
	proj.shape.setPosition(projectileManager.position);
	proj.shape.setFillColor(sf::Color::Black);
	proj.shape.setOutlineThickness(.8f);
	projectileManager.projectiles.push_back(proj);

}

ProjectileManager CreateProjectileManager(float timeBtw, float chrono, sf::Vector2f position)
{
	ProjectileManager projManager{ timeBtw,position,chrono };
	return projManager;
}

void UpdateProjectile(ProjectileManager& projManager, float deltaTime, sf::Vector2f size, Player& player)
{
	if (projManager.projectiles.size() > 0) {
		std::list<Projectile>::iterator it = projManager.projectiles.begin();
		if (!player.returntome) {
			while (it != projManager.projectiles.end()) {
				if ((*it).shape.getPosition().x <= (*it).shape.getRadius() || (*it).shape.getPosition().x >= size.x - (*it).shape.getRadius()) {
					(*it).direction.x = -(*it).direction.x;
					it->IsEnemy = !it->IsEnemy;
				}
				if ((*it).shape.getPosition().y <= (*it).shape.getRadius() || (*it).shape.getPosition().y >= size.y - (*it).shape.getRadius()) {
					(*it).direction.y = -(*it).direction.y;
					//std::cout << (*it).direction.x << (*it).direction.y << std::endl;
					it->IsEnemy = !it->IsEnemy;
				}
				if (it->IsEnemy) {
					it->shape.setOutlineColor(sf::Color::Red);
				}
				else {
					it->shape.setOutlineColor(sf::Color::White);
				}
				sf::Vector2f norm = Normalize((*it).direction);
				(*it).shape.setPosition((*it).shape.getPosition().x + norm.x * (*it).speed * deltaTime, (*it).shape.getPosition().y + norm.y * (*it).speed * deltaTime);
				it++;
			}
		}
		else {
			while (it != projManager.projectiles.end()) {
				(*it).shape.setOutlineColor(sf::Color::Green);
				(*it).direction = player.sprite.getPosition() - (*it).shape.getPosition();
				float norm = Norm((*it).direction);
				(*it).shape.setPosition((*it).shape.getPosition().x + Normalize((*it).direction).x * (*it).speed * deltaTime, (*it).shape.getPosition().y + Normalize((*it).direction).y * (*it).speed * deltaTime);

				if (norm <= (*it).shape.getRadius() + player.hitboxFront.getRadius()) {
					it = projManager.projectiles.erase(it);
					std::cout << "ERASE \n";
				}else {
					it++; 
				}
			}
			if (player.projManager.projectiles.size() == 0) {
				player.returntome = false;
			}
		}
	}
	projManager.chrono += deltaTime;
}
void DrawProjectile(ProjectileManager& projManager, sf::RenderWindow& window) {
	if (projManager.projectiles.size() > 0) {
		std::list<Projectile>::iterator it = projManager.projectiles.begin();
		while (it != projManager.projectiles.end()) {
			window.draw((*it).shape);
			it++;
		}
		//std::cout << "drawn \n";
	}
}
float Norm(sf::Vector2f vector)
{
	float norm = sqrt(vector.x * vector.x + vector.y * vector.y);
	return norm;
}
sf::Vector2f Normalize(sf::Vector2f vector) {
	
	float norm = Norm(vector);
	return sf::Vector2f(vector.x / norm, vector.y / norm);
}
