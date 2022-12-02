#include "Player.h"

void InitPlayer(Player& player, sf::Vector2f position)
{
    player.texture.loadFromFile("../Sprites/Player.png");
    if (!player.texture.loadFromFile("../Sprites/Player.png")) {
        std::cout << "failed to load Texture" << std::endl;
    }
    player.sprite.setTexture(player.texture);
    player.sprite.setOrigin(player.texture.getSize().x / 2, player.texture.getSize().y / 2);

    //Set pos to middle screen
    player.sprite.setPosition(position.x+11/2, position.y+11 / 2);
    //oui elle est grande l'image
    player.sprite.setScale(.2f, .2f);
}

void RecalculateAngles(Player& player)
{
    player.dir.x = 10 * sin(player.sprite.getRotation() * (3.141592653589793 / 180));
    player.dir.y = 10 * -cos(player.sprite.getRotation() * (3.141592653589793 / 180));
}

void UpdatePlayer(Player& player, float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        //printf("Rotate Right \n");
        player.sprite.setRotation(player.sprite.getRotation() - player.rotateSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //printf("Rotate left \n");
        player.sprite.setRotation(player.sprite.getRotation() + player.rotateSpeed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        //printf("Move Forward \n");
        player.wasS = false;
        player.wasZ = true;
        RecalculateAngles(player);
        sf::Vector2f pos = player.sprite.getPosition();

        player.speed += player.AccSpeed * deltaTime;

        if (player.speed > player.MaxSpeed) {
            player.speed = player.MaxSpeed;
        }
        std::cout << player.speed << std::endl;
        player.sprite.setPosition(pos.x + player.dir.x * player.speed * deltaTime, pos.y + player.dir.y * player.speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //printf("Move Backward \n");
        player.wasZ = false;
        player.wasS = true;
        RecalculateAngles(player);

        player.speed -= player.AccSpeed * deltaTime;

        //if (player.speed > player.MaxSpeed/3) {
        //    player.speed -= player.AccSpeed;
        //}else if (player.speed <= player.MaxSpeed/3) {
        //    player.speed += player.AccSpeed;
        //}

        if (player.speed < 0) {
            player.speed = 0;
        }
        std::cout << player.speed << std::endl;
        player.sprite.move(player.dir.x * -player.speed * deltaTime * 1.5, player.dir.y * -player.speed * deltaTime * 1.5);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
        if (player.speed > 0) {
            player.speed -= player.friction * deltaTime;
            if (player.wasZ) {
                player.sprite.move(player.dir.x * player.speed * deltaTime, player.dir.y * player.speed * deltaTime);
            }
            else if (player.wasS) {
                player.sprite.move(player.dir.x * -player.speed * deltaTime, player.dir.y * -player.speed * deltaTime);
            }
            std::cout << player.speed << std::endl;
        }
        else if (player.speed < 0) {
            player.speed = 0;
            std::cout << player.speed << std::endl;

        }
    }
}
