#include "Enemy.h"
#include "Player.h"

Enemy GenerateEnemyAndCreate(int windoSizeX, int windoSizeY, Player& player)
{

    int seed = rand()% 100;
    std::cout << seed << std::endl;
    sf::Vector2f pos;
    pos.x = rand() % windoSizeX;
    pos.y = rand() % windoSizeY;
    int baseSpeed = 100;
    int speed;
    int life;
    int size;

    #pragma region RANDOM
    if (seed < 27) {
        life = 3;
    }
    else if (seed < 47) {
        life = 4;
    }
    else if (seed < 62) {
        life = 5;
    }
    else if (seed < 75) {
        life = 6;
    }
    else if (seed < 85) {
        life = 7;
    }
    else if (seed < 90) {
        life =8;
    }
    else if (seed < 95) {
        life = 9;
    }
    else if (seed <= 100) {
        life = 10;
    }
#pragma endregion

    speed = baseSpeed / life;
    size = life;
    Enemy en = CreateEnemy(speed, life, pos, size, player);
    return en;
}

Enemy CreateEnemy(int speed, int life, sf::Vector2f origine,int size, Player& player)
{
    sf::CircleShape enemyShape(size*10, life);
    enemyShape.setOrigin(size, size);
    enemyShape.setPosition(origine);
    sf::Vector2f direction = (origine - player.sprite.getPosition());
    sf::Vector2f position = origine;
    Enemy enemy{ 100,speed,life,size,enemyShape,origine,position,direction};

    return enemy;
}
