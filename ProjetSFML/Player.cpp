#include "Player.h"

void RecalculateAngles(Player& player)
{
    player.dir.x = 10 * sin(player.triangle.getRotation() * (3.141592653589793 / 180));
    player.dir.y = 10 * -cos(player.triangle.getRotation() * (3.141592653589793 / 180));
}
