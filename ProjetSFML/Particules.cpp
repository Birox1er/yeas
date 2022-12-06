#include "Particules.h"
#include "Projectile.h"

ParticleSystem CreateParticleSystem( float timeBtw, float rayonSpawn, float particleRadiusMax, float particleRadiusMin)
{
    ParticleSystem syst{0,1,timeBtw,rayonSpawn,particleRadiusMax,particleRadiusMin };
    return syst;
}

void AddParticleToSystem(ParticleSystem& particleSystem, float particleLifeTime,sf::Vector2f origine)
{
    float particleRadius = particleSystem.particleRadiusMin + (particleSystem.particleRadiusMax - particleSystem.particleRadiusMin) * (float)rand() / RAND_MAX;
    Particle part{ particleLifeTime,particleLifeTime };
    part.circle = sf::CircleShape(particleRadius, 3);
    part.circle.setOrigin(particleRadius, particleRadius);
    const float PI = 3.14159265;
    float angle = PI * 2.0f * (float)rand() / RAND_MAX;
    float distance = particleSystem.rayonSpawn * sqrt((float)rand() / RAND_MAX);
    float x =origine.x + cos(angle)*distance;
    float y =origine.y + sin(angle)*distance;
    part.dir = Normalize({ x * distance,y * distance });
    part.circle.setPosition(x, y);
    part.circle.setFillColor(sf::Color::Black);
    part.circle.setOutlineColor(sf::Color::White);
    part.circle.setOutlineThickness(.7f);
    particleSystem.particles.push_back(part);
    std::cout << "created" << std::endl;
}

void UpdateParticleSystem(ParticleSystem& particleSystem, float deltaTime)
{
    particleSystem.chrono += deltaTime;
    particleSystem.chrono2 += deltaTime;
    if (particleSystem.particles.size() > 0) {
        std::list<Particle>::iterator it = particleSystem.particles.begin();
        while (it != particleSystem.particles.end()) {
            const float PI = 3.14159265;
            float scale = sin(PI * (*it).timeLeft / (*it).particleLifeTime);
            (*it).circle.setScale(scale, scale);
            (*it).timeLeft -= deltaTime;
            (*it).circle.setPosition((*it).circle.getPosition() + (*it).dir * deltaTime);
            if ((*it).timeLeft <= 0) {
                it = particleSystem.particles.erase(it);
                std::cout << "died" << std::endl;
            }
            else {
                it++;
            }
        }
    }
    if (particleSystem.chrono > particleSystem.timeBtw&& particleSystem.chrono2<2) {
        AddParticleToSystem(particleSystem,2,particleSystem.origine);
        particleSystem.chrono = 0;
    }
}

void DrawParticleSystem(ParticleSystem& particleSystem, sf::RenderWindow& window) {
    if (particleSystem.particles.size() > 0) {
        std::list<Particle>::iterator it = particleSystem.particles.begin();
        while (it != particleSystem.particles.end()) {
            window.draw((*it).circle);
            it++;
        }
    }
}
