#include "Obstacle.h"

Obstacle::Obstacle(Texture texture, int startingPosition, int canvasWidth, int canvasHeight)
{
	this->texture = texture;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
	positionTopObstacle.x = startingPosition;
	positionBottomObstacle.x = startingPosition;

	heightOffset = GetRandomValue(0, canvasHeight - texture.height*2 - gapBetweenObstacles);

	positionTopObstacle.y = heightOffset;
	positionBottomObstacle.y = positionTopObstacle.y + texture.height + gapBetweenObstacles;

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
		positionTopObstacle.x = canvasWidth;

		heightOffset = GetRandomValue(0, canvasHeight - texture.height * 2 - gapBetweenObstacles);

		positionTopObstacle.y = heightOffset;
		positionBottomObstacle.y = positionTopObstacle.y + texture.height + gapBetweenObstacles;
	}

	positionBottomObstacle.x = positionTopObstacle.x;

	collisionRectangleTopObstacle.x = positionTopObstacle.x;
	collisionRectangleTopObstacle.y = positionTopObstacle.y;

	collisionRectangleBottomObstacle.x = positionBottomObstacle.x;
	collisionRectangleBottomObstacle.y = positionBottomObstacle.y;
}

void Obstacle::render()
{
	DrawTextureRec(texture, Rectangle{ 0, 0, static_cast<float>(texture.width), static_cast<float>(-texture.height) }, Vector2{ positionTopObstacle.x, positionTopObstacle.y }, WHITE);
	DrawTexture(texture, static_cast<int>(positionBottomObstacle.x), positionBottomObstacle.y, WHITE);

	DrawRectangleLinesEx(collisionRectangleTopObstacle, 3, GREEN);
	DrawRectangleLinesEx(collisionRectangleBottomObstacle, 3, GREEN);
}

void Obstacle::unloadAssets()
{
	UnloadTexture(texture);
}