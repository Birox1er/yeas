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
