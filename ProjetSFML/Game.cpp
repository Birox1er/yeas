#include "Game.h"

void InitGame(Game& game, sf::Vector2f position, sf::Vector2f size)
{
	game.multiplier = 1;
	game.score = 0;
	game.position = position;
	game.size = size;
	game.shape.setPosition(position);
	game.shape.setSize(size);
	game.shape.setOrigin(size / 2.f);
	InitPlayer(game.player, position);
	game.enemies = CreateEnemyManager(5.0f,game.position,10.0f);

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
	PlayerDraw(game.player, window,game.score);
	EnemyDraw(game.enemies, window);
}
void GameUpdate(Game& game, float deltaTime)
{
	if (game.hasPressedSpace) {
		game.cd -= deltaTime;
		if (game.cd <= 0) {
			game.hasPressedSpace = false;
			game.cd = .4f;
		}
	}
	if (!game.canPressDSpace) {
		game.reuseCD -= deltaTime;
		if (game.reuseCD <= 0) {
			game.reuseCD = 2.0f;
			game.canPressDSpace = true;
		}
	}
	if (game.player.isSheidOn) {
		game.multiplier = 1.5f;
	}
	else {
		game.multiplier = 1;
	}
	game.score += (deltaTime*game.multiplier);
	UpdatePlayer(game.player, deltaTime, game.size, game.canPressDSpace);
	UpdateEnemy(game.enemies, deltaTime,game.size,game.player,game.score,game.multiplier);
	CheckOutsides(game, game.player);
}

void PressedSpace(Game& game, float deltaTime)
{
	if (game.hasPressedSpace && game.canPressDSpace) {
		PlayerPressedDoubleSpace(game.player, deltaTime);
		game.hasPressedSpace = false;
		game.canPressDSpace = false;
		game.cd = .4f;
	}
	else {
		game.hasPressedSpace = true;
		PlayerPressedSpace(game.player, deltaTime);
	}
}
void PressedE(Game& game) {
	PlayerPressedE(game.player);
}
