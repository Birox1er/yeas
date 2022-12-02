#include "Game.h"

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size)
{
	game.position = position;
	game.size = size;
	game.shape.setPosition(position);
	game.shape.setSize(size);
	game.shape.setOrigin(size / 2.f);
	InitPlayer(game.player, position);
	game.enemy = GenerateEnemyAndCreate(size.x, size.y, game.player);

}
void CheckOutsides(Game& game, Player& player) {

	if (player.hitbox.getPosition().x + player.hitbox.getRadius() > game.size.x || player.hitbox.getPosition().x - player.hitbox.getRadius() < 0) {
		player.outWidth = true;
	}
	else {
		player.outWidth = false;
	}
	if (player.hitbox.getPosition().y + player.hitbox.getRadius() > game.size.y || player.hitbox.getPosition().y - player.hitbox.getRadius() < 0) {
		player.outHeight = true;
	}
	else {
		player.outHeight = false;
	}

}
void GameDraw(Game& game, sf::RenderWindow& window)
{
	PlayerDraw(game.player, window);
	EnemyDraw(game.enemy, window);
}
void GameUpdate(Game& game, float deltaTime)
{
	UpdatePlayer(game.player, deltaTime);
	UpdateEnemy(game.enemy, deltaTime);
	CheckOutsides(game, game.player);
}
