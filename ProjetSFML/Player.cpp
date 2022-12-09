#include "Player.h"

void InitPlayer(Player& player, sf::Vector2f position)
{
    player.trail.chrono = 0;
    player.texture.loadFromFile("Sprites/Player.png");
    if (!player.texture.loadFromFile("Sprites/Player.png")) {
        std::cout << "failed to load Texture" << std::endl;
    }
    player.sprite.setTexture(player.texture);
    player.sprite.setOrigin(player.texture.getSize().x / 2, player.texture.getSize().y / 2);
    player.sprite.setScale(.15f, .15f);
    player.sprite.setPosition(position.x, position.y);

    player.Texturesheild.loadFromFile("Sprites/heatSheild.png");
    if (!player.texture.loadFromFile("Sprites/heatSheild.png")) {
        std::cout << "failed to load Texture" << std::endl;
    }
    player.spritesheild.setTexture(player.Texturesheild);
    player.spritesheild.setOrigin(player.Texturesheild.getSize().x / 2, player.Texturesheild.getSize().y / 2);
    player.spritesheild.setScale(.15f, .15f);
    player.spritesheild.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y + 10);

    RecalculateAngles(player);
    player.projManager = CreateProjectileManager(0, 0, player.sprite.getPosition() + player.dir*5.0f);
    
    
    player.hitboxFront = sf::CircleShape(25);
    player.hitboxFront.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y + 10);
    player.hitboxFront.setOrigin(25,25);
    player.hitboxFront.setScale(0.7, 1);
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
        AddProjectileToGame(player.projManager, player.dir, 400, 5,1);
    }
}
void PlayerPressedE(Player& player) {
    player.returntome = true;
    player.MaxSpeed = 25;
}

void UpdatePlayer(Player& player, float deltaTime,sf::Vector2f size)
{
    RecalculateAngles(player);
    UpdateTrail(player.trail, player.speed, player.sprite.getPosition() - player.dir * 3.0f, player.isSheidOn,deltaTime);
    player.projManager.position = player.sprite.getPosition() + player.dir*5.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        //printf("Rotate Right \n");
        player.sprite.setRotation(player.sprite.getRotation() - player.rotateSpeed * deltaTime);
        player.hitboxFront.setRotation(player.sprite.getRotation());

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //printf("Rotate left \n");
        player.sprite.setRotation(player.sprite.getRotation() + player.rotateSpeed * deltaTime);
        player.hitboxFront.setRotation(player.sprite.getRotation());

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
        player.hitboxFront.setRotation(player.sprite.getRotation());
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

    std::list<Projectile>::iterator it = player.projManager.projectiles.begin();
    while (it != player.projManager.projectiles.end()) {
        sf::Vector2f distance = player.hitboxFront.getPosition() - (*it).shape.getPosition();
        if (Norm(distance) <= player.hitboxFront.getRadius() + (*it).shape.getRadius() && (*it).IsEnemy && (*it).canHit) {
            //player.life -= 1;
            it = player.projManager.projectiles.erase(it);
            std::cout << player.life << std::endl;
        }
        else {
            it++;
        }
    }
    switch (player.life)
    {
    case(5):
        player.texture.loadFromFile("Sprites/Player.png");
        break;
    case(4):
        player.texture.loadFromFile("Sprites/Player_2.png");
        break;
    case(3):     
        player.texture.loadFromFile("Sprites/Player_3.png");
        break;
    case(2):
        player.texture.loadFromFile("Sprites/Player_4.png");
        break;
    case(1):
        player.texture.loadFromFile("Sprites/Player_5.png");
        break;
    }

    player.spritesheild.setRotation(player.sprite.getRotation());
    player.spritesheild.setPosition(player.sprite.getPosition() + player.dir * 3.5f);
    player.hitboxFront.setPosition(player.sprite.getPosition());
    UpdateProjectile(player.projManager, deltaTime,size, player);
}

void PlayerDraw(Player& player, sf::RenderWindow& window,float score)
{
    DrawTrail(player.trail, window);
    if (player.life > 0) {
        //window.draw(player.hitboxFront);
        if (player.speed >= player.MaxSpeed * .9f && !player.returntome && player.canSheildBeOn) {
            player.isSheidOn = true;
            window.draw(player.spritesheild);
        }
        else {
            player.isSheidOn = false;
        }
        window.draw(player.sprite);
        DrawProjectile(player.projManager, window);
        sf::Font font;
        if (!font.loadFromFile("Fonts/dominique/Dominique-win.ttf")) {
            std::cout << "failed to load Font" << std::endl;
        }
        sf::Text lifetxt;
        lifetxt.setFont(font);
        std::string t = "Life : " + std::to_string(player.life);
        lifetxt.setString(t);
        lifetxt.setFillColor(sf::Color::Blue);
        //lifetxt.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        lifetxt.setCharacterSize(42);
        window.draw(lifetxt);
        sf::Text scoretxt;
        scoretxt.setFont(font);
        std::string t2 = "Score : " + std::to_string((int)score);
        scoretxt.setString(t2);
        scoretxt.setFillColor(sf::Color::Blue);
        scoretxt.setPosition(scoretxt.getPosition().x, scoretxt.getPosition().y+50);
        scoretxt.setCharacterSize(42);
        window.draw(scoretxt);
#pragma region TELEPORT
        sf::Vector2f tempPos = player.sprite.getPosition();
        if (player.outWidth && player.sprite.getPosition().x > window.getSize().x * 0.001f) {
            player.sprite.setPosition(tempPos.x - window.getSize().x, tempPos.y);
            player.hitboxFront.setPosition(tempPos.x - window.getSize().x, tempPos.y);
            window.draw(player.sprite);
            //window.draw(player.hitboxFront);

        }
        if (player.outWidth && player.sprite.getPosition().x < window.getSize().x * 0.001f) {
            player.sprite.setPosition(tempPos.x + window.getSize().x, tempPos.y);
            player.hitboxFront.setPosition(tempPos.x + window.getSize().x, tempPos.y);
            window.draw(player.sprite);
            //window.draw(player.hitboxFront);
        }
        if (player.outHeight && player.sprite.getPosition().y > window.getSize().y * 0.001f) {
            player.sprite.setPosition(tempPos.x, tempPos.y - window.getSize().y);
            player.hitboxFront.setPosition(tempPos.x, tempPos.y - window.getSize().y);
            window.draw(player.sprite);
            //window.draw(player.hitboxFront);
        }
        if (player.outHeight && player.sprite.getPosition().y < window.getSize().y * 0.001f) {
            player.sprite.setPosition(tempPos.x, tempPos.y + window.getSize().y);
            player.hitboxFront.setPosition(tempPos.x, tempPos.y + window.getSize().y);
            window.draw(player.sprite);
            //window.draw(player.hitboxFront);
        }
#pragma endregion
    }
    else {
        if (player.isSheidOn) {
            score *= 1.5f;
        }
        std::cout << "score : " << (int)score*10 << std::endl;
        window.close();
    }
    
    
    
}
