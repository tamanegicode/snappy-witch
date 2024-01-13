#include "Obstacle.h"

Obstacle::Obstacle(Texture texture, int startingPosition, int canvasWidth, int canvasHeight, float collisionRectangleWidthScale, float collisionRectangleHeightScale)
{
	this->texture = texture;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
	positionTopObstacle.x = startingPosition;
	positionBottomObstacle.x = startingPosition;

	heightOffset = GetRandomValue(0, canvasHeight - texture.height*2 - gapBetweenObstacles);

	positionTopObstacle.y = heightOffset;
	positionBottomObstacle.y = positionTopObstacle.y + texture.height + gapBetweenObstacles;

	float collisionRectangleWidth = static_cast<float>(texture.width) * collisionRectangleWidthScale;
	float collisionRectangleHeight = static_cast<float>(texture.height) * collisionRectangleHeightScale;

	colRecXOffset = (texture.width - collisionRectangleWidth) / 2;
	colRecYOffset = (texture.height - collisionRectangleHeight) / 2;

	float collisionRectanglePositionX = positionTopObstacle.x + colRecXOffset;
	float collisionRectangleTopObstaclePositionY = positionTopObstacle.y + colRecYOffset;
	float collisionRectangleBottomObstaclePositionY = positionBottomObstacle.y + colRecYOffset;

	collisionRectangleTopObstacle = { collisionRectanglePositionX, collisionRectangleTopObstaclePositionY, collisionRectangleWidth, collisionRectangleHeight };
	collisionRectangleBottomObstacle = { collisionRectanglePositionX, collisionRectangleBottomObstaclePositionY, collisionRectangleWidth, collisionRectangleHeight };
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

	collisionRectangleTopObstacle.x = positionTopObstacle.x + colRecXOffset;
	collisionRectangleTopObstacle.y = positionTopObstacle.y + colRecYOffset;

	collisionRectangleBottomObstacle.x = positionTopObstacle.x + colRecXOffset;
	collisionRectangleBottomObstacle.y = positionBottomObstacle.y + colRecYOffset;
}

float Obstacle::getPositionX()
{
	return positionTopObstacle.x;
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