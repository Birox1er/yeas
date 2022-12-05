#include "Game.h"

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size)
{
	game.position = position;
	game.size = size;
	game.shape.setPosition(position);
	game.shape.setSize(size);
	game.shape.setOrigin(size / 2.f);
	InitPlayer(game.player, position);
	game.enemies = CreateEnemyManager(10.0f,game.position,10.0f);

}
void CheckOutsides(Game& game, Player& player) {

	if (player.hitboxFront.getPosition().x + player.hitboxFront.getRadius() > game.size.x || player.hitboxFront.getPosition().x - player.hitboxFront.getRadius() < 0) {
		player.outWidth = true;
	}
	else {
		player.outWidth = false;
	}
	if (player.hitboxFront.getPosition().y + player.hitboxFront.getRadius() > game.size.y || player.hitboxFront.getPosition().y - player.hitboxFront.getRadius() < 0) {
		player.outHeight = true;
	}
	else {
		player.outHeight = false;
	}

}
void GameDraw(Game& game, sf::RenderWindow& window)
{
	PlayerDraw(game.player, window);
	EnemyDraw(game.enemies, window);
}
void GameUpdate(Game& game, float deltaTime)
{
	UpdatePlayer(game.player, deltaTime, game.size);
	UpdateEnemy(game.enemies, deltaTime,game.size,game.player);
	CheckOutsides(game, game.player);
}

void PressedSpace(Game& game, float deltaTime)
{
	PlayerPressedSpace(game.player, deltaTime);
}
void PressedE(Game& game) {
	PlayerPressedE(game.player);
}
