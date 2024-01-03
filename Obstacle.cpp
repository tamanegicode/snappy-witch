#include "Obstacle.h"

Obstacle::Obstacle(Texture texture, int startingPosition, int windowWidth)
{
	this->texture = texture;
	this->windowWidth = windowWidth;
	position.x = startingPosition;

	int random = GetRandomValue(-200, 200);
	heightOffset = random;
}

void Obstacle::update(float deltaTime)
{
	position.x -= scrollSpeed * deltaTime;
	if (static_cast<int>(position.x) <= -texture.width)
	{
		position.x = windowWidth;

		int random = GetRandomValue(-200, 200);
		heightOffset = random;
	}
}

void Obstacle::render()
{
	DrawTexture(texture, static_cast<int>(position.x), texture.height / 1.5f + heightOffset, WHITE);
	DrawTexture(texture, static_cast<int>(position.x), -texture.height / 1.5f + heightOffset, WHITE);
}

void Obstacle::unloadAssets()
{
	UnloadTexture(texture);
}