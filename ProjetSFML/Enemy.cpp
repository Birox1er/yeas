#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

EnemyManager CreateEnemyManager(float timeBtw, sf::Vector2f position, float chrono)
{
    EnemyManager enemymanager{ timeBtw,position,chrono };
    enemymanager.system = CreateParticleSystem(0.2f, 10, 10, 10);
    return enemymanager;
}

void GenerateEnemyAndCreate(EnemyManager& enemyManager, int windoSizeX, int windoSizeY, Player& player)
{

    int seed = rand()% 100;
    std::cout << seed << std::endl;
    sf::Vector2f pos;
    pos.x = (rand() % (windoSizeX-200))+100;
    pos.y = (rand() % (windoSizeY-200))+100;
    int baseSpeed = 500;
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
    else if (seed <= 120) {
        life = 10;
    }
#pragma endregion

    speed = baseSpeed / life;
    size = life;
    Enemy en = CreateEnemy(speed, life, pos, size, player);
    enemyManager.enemies.push_back(en);
}

Enemy CreateEnemy(int speed, int life, sf::Vector2f origine,int size, Player& player)
{

    sf::CircleShape enemyShape(size*10, life);
    enemyShape.setOrigin(size*10, size*10);
    enemyShape.setPosition(origine);
    enemyShape.setFillColor(sf::Color::Black);
    enemyShape.setOutlineColor(sf::Color::White);
    enemyShape.setOutlineThickness(.7f);
    sf::Vector2f direction = (origine - player.sprite.getPosition());
    sf::Vector2f position = origine;
    Enemy enemy{ 100,speed,life,size,enemyShape,origine,position,direction};

    return enemy;
}
void UpdateEnemy(EnemyManager& enemies, float deltaTime,sf::Vector2f size,Player& player) {
    
    if (enemies.chrono >= enemies.timeBtw) {
        enemies.chrono = 0;
        GenerateEnemyAndCreate(enemies, size.x, size.y, player);
    }
    if (enemies.enemies.size()> 0) {
        std::list<Enemy>::iterator it = enemies.enemies.begin();
        while (it != enemies.enemies.end()) {
            
            (*it).enemyShape.setPointCount((*it).life);
            (*it).enemyShape.setRadius((*it).life * 10);
            (*it).enemyShape.setOrigin((*it).enemyShape.getRadius(), (*it).enemyShape.getRadius());
            if ((*it).enemyShape.getPosition().x <= (*it).enemyShape.getRadius() || (*it).enemyShape.getPosition().x >= size.x - (*it).enemyShape.getRadius()) {
                (*it).dir.x = -(*it).dir.x;
            }
            if ((*it).enemyShape.getPosition().y <= (*it).enemyShape.getRadius() || (*it).enemyShape.getPosition().y >= size.y - (*it).enemyShape.getRadius()) {
                (*it).dir.y = -(*it).dir.y;
                std::cout << (*it).dir.x << (*it).dir.y << std::endl;
            }
            sf::Vector2f norm = Normalize((*it).dir);
            (*it).enemyShape.setPosition((*it).enemyShape.getPosition().x + norm.x * (*it).speed * deltaTime, (*it).enemyShape.getPosition().y + norm.y * (*it).speed * deltaTime);
            std::list<Projectile>::iterator it2 = player.projManager.projectiles.begin();
            while (it2 != player.projManager.projectiles.end()) {
                sf::Vector2f distance = (*it).enemyShape.getPosition() - (*it2).shape.getPosition();
                if (Norm(distance) <= (*it).enemyShape.getRadius() + (*it2).shape.getRadius() && (*it2).IsEnemy == false) {
                        (*it).life -= 1;
                        (*it2).direction = (*it2).direction - distance;
                        (*it2).IsEnemy = true;
                }
                it2++;
            }

            sf::Vector2f distance2 = (*it).enemyShape.getPosition() - player.hitboxFront.getPosition();
            if (Norm(distance2) <= (*it).enemyShape.getRadius() + player.hitboxFront.getRadius()) {
                player.life -= 1;
                (*it).life = 2;
            }

            if ((*it).life < 3) {
                enemies.system.chrono2 = 0;
                enemies.system.origine = (*it).enemyShape.getPosition();
                it = enemies.enemies.erase(it);
            }
            if (it != enemies.enemies.end()) {
                it++;
            }
        }
    }
    UpdateParticleSystem(enemies.system, deltaTime);
    enemies.chrono += deltaTime;
}
void EnemyDraw(EnemyManager& enemies, sf::RenderWindow& window)
{
    if (enemies.enemies.size() > 0) {
        std::list<Enemy>::iterator it = enemies.enemies.begin();
        while (it != enemies.enemies.end()) {
            window.draw((*it).enemyShape);
            it++;
        }
    }
    DrawParticleSystem(enemies.system,window);
}