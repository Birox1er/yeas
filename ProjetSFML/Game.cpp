#include "Game.h"

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size)
{
	game.position = position;
	game.size = size;
	game.shape.setPosition(position);
	game.shape.setSize(size);
	game.shape.setOrigin(size / 2.f);
	InitPlayer(game.player, position);
}
