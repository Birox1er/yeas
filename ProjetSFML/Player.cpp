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
    player.hitbox = sf::CircleShape(33);
    player.hitbox.setPosition(player.sprite.getPosition());
    player.hitbox.setOrigin(33,33);
    RecalculateAngles(player);
    player.projManager = CreateProjectileManager(0.5f, 0.5f, player.sprite.getPosition() + player.dir*5.0f);
    player.hitbox.setScale(0.7, 1);
}

void RecalculateAngles(Player& player)
{
    player.dir.x = 10 * sin(player.sprite.getRotation() * (3.141592653589793 / 180));
    player.dir.y = 10 * -cos(player.sprite.getRotation() * (3.141592653589793 / 180));
}

void PlayerPressedSpace(Player& player, float deltaTime)
{
    std::cout << player.projManager.chrono << std::endl;
    RecalculateAngles(player);
    if (player.projManager.chrono > player.projManager.timeBtw) {
        AddProjectileToGame(player.projManager, player.dir, 400, 10,1);
    }
}

void UpdatePlayer(Player& player, float deltaTime,sf::Vector2f size)
{
    RecalculateAngles(player);
    player.projManager.position = player.sprite.getPosition() + player.dir*5.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        //printf("Rotate Right \n");
        player.sprite.setRotation(player.sprite.getRotation() - player.rotateSpeed * deltaTime);
        player.hitbox.setRotation(player.sprite.getRotation());

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //printf("Rotate left \n");
        player.sprite.setRotation(player.sprite.getRotation() + player.rotateSpeed * deltaTime);
        player.hitbox.setRotation(player.sprite.getRotation());

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
        //std::cout << player.speed << std::endl;
        player.sprite.setPosition(pos.x + player.dir.x * player.speed * deltaTime, pos.y + player.dir.y * player.speed * deltaTime);
        player.hitbox.setRotation(player.sprite.getRotation());
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
        //std::cout << player.speed << std::endl;
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
            //std::cout << player.speed << std::endl;
        }
        else if (player.speed < 0) {
            player.speed = 0;
            //std::cout << "Player speed is : " << player.speed << std::endl;

        }
    }
    player.hitbox.setPosition(player.sprite.getPosition());
    UpdateProjectile(player.projManager, deltaTime,size);
}

void PlayerDraw(Player& player, sf::RenderWindow& window)
{
    window.draw(player.hitbox);
    window.draw(player.sprite);
    DrawProjectile(player.projManager, window);
    sf::Vector2f tempPos = player.sprite.getPosition();

    if (player.outWidth && player.sprite.getPosition().x > window.getSize().x*0.001f) {
        player.sprite.setPosition(tempPos.x - window.getSize().x, tempPos.y);
        player.hitbox.setPosition(tempPos.x - window.getSize().x, tempPos.y);
        window.draw(player.sprite);
        window.draw(player.hitbox);
 
    }
    if (player.outWidth && player.sprite.getPosition().x < window.getSize().x*0.001f) {
        player.sprite.setPosition(tempPos.x + window.getSize().x, tempPos.y);
        player.hitbox.setPosition(tempPos.x + window.getSize().x, tempPos.y);
        window.draw(player.sprite);
        window.draw(player.hitbox);
    }
    if (player.outHeight && player.sprite.getPosition().y > window.getSize().y*0.001f) {
        player.sprite.setPosition(tempPos.x, tempPos.y - window.getSize().y);
        player.hitbox.setPosition(tempPos.x, tempPos.y - window.getSize().y);
        window.draw(player.sprite);
        window.draw(player.hitbox);
    }
    if (player.outHeight && player.sprite.getPosition().y < window.getSize().y*0.001f) {
        player.sprite.setPosition(tempPos.x, tempPos.y + window.getSize().y);
        player.hitbox.setPosition(tempPos.x, tempPos.y + window.getSize().y);
        window.draw(player.sprite);
        window.draw(player.hitbox);
    }
    
}
