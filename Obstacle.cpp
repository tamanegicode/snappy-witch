#include "Obstacle.h"

Obstacle::Obstacle(Texture texture, int startingPosition, int windowWidth)
{
	this->texture = texture;
	this->windowWidth = windowWidth;
	positionTopObstacle.x = startingPosition;
	positionBottomObstacle.x = startingPosition;

	int random = GetRandomValue(-200, 200);
	heightOffset = random;

	positionTopObstacle.y = -texture.height / 1.5f + heightOffset;
	positionBottomObstacle.y = texture.height / 1.5f + heightOffset;

	collisionRectangleTopObstacle = { positionTopObstacle.x, positionTopObstacle.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
	collisionRectangleBottomObstacle = { positionBottomObstacle.x, positionBottomObstacle.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
}

Rectangle Obstacle::getCollisionRectangleTopObstacle()
{
	return collisionRectangleTopObstacle;
}

Rectangle Obstacle::getCollisionRectangleBottomObstacle()
{
	return collisionRectangleBottomObstacle;
}

void Obstacle::update(float deltaTime)
{
	positionTopObstacle.x -= scrollSpeed * deltaTime;	

	if (static_cast<int>(positionTopObstacle.x) <= -texture.width)
	{
		positionTopObstacle.x = windowWidth;

		int random = GetRandomValue(-200, 200);
		heightOffset = random;

		positionTopObstacle.y = -texture.height / 1.5f + heightOffset;
		positionBottomObstacle.y = texture.height / 1.5f + heightOffset;
	}

	positionBottomObstacle.x = positionTopObstacle.x;

	collisionRectangleTopObstacle.x = positionTopObstacle.x;
	collisionRectangleTopObstacle.y = positionTopObstacle.y;

	collisionRectangleBottomObstacle.x = positionBottomObstacle.x;
	collisionRectangleBottomObstacle.y = positionBottomObstacle.y;
}

void Obstacle::render()
{
	DrawTexture(texture, static_cast<int>(positionTopObstacle.x), positionTopObstacle.y, WHITE);
	DrawTexture(texture, static_cast<int>(positionBottomObstacle.x), positionBottomObstacle.y, WHITE);

	DrawRectangleLinesEx(collisionRectangleTopObstacle, 5, GREEN);
	DrawRectangleLinesEx(collisionRectangleBottomObstacle, 5, GREEN);
}

void Obstacle::unloadAssets()
{
	UnloadTexture(texture);
}