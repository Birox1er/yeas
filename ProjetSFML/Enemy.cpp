#include "Enemy.h"

Enemy CreateEnemy(int speed, int life, sf::Vector2f origine,int size)
{
    sf::CircleShape enemyShape(size, life);
    // sf::Vector2f direction = (origine - cible.position);
    sf::Vector2f position = origine;
    Enemy enemy{ speed,life,size,enemyShape,origine,position };
    return enemy;
}
