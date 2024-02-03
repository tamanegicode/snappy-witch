#include "Obstacle.h"

Obstacle::Obstacle(Texture& texture, int startingPosition, int canvasWidth, int canvasHeight, float collisionRectangleWidthScale, float collisionRectangleHeightScale)
	:m_Texture(texture), m_CanvasWidth(canvasWidth), m_CanvasHeight(canvasHeight)
{
	positionTopObstacle.x = startingPosition;
	positionBottomObstacle.x = startingPosition;

	heightOffset = GetRandomValue(0, m_CanvasHeight - texture.height*2 - gapBetweenObstacles);

	positionTopObstacle.y = heightOffset;
	positionBottomObstacle.y = positionTopObstacle.y + texture.height + gapBetweenObstacles;

	float collisionRectangleWidth = static_cast<float>(texture.width) * collisionRectangleWidthScale;
	float collisionRectangleHeight = static_cast<float>(texture.height) * collisionRectangleHeightScale;

	colRecXOffset = (texture.width - collisionRectangleWidth) / 2;
	colRecYOffset = (texture.height - collisionRectangleHeight) / 2;

	float collisionRectanglePositionX = positionTopObstacle.x + colRecXOffset;
	float collisionRectangleTopObstaclePositionY = positionTopObstacle.y + colRecYOffset;
	float collisionRectangleBottomObstaclePositionY = positionBottomObstacle.y + colRecYOffset;

	collisionRectangleTopObstacle.x = collisionRectanglePositionX;
	collisionRectangleTopObstacle.y = collisionRectangleTopObstaclePositionY;
	collisionRectangleTopObstacle.width = collisionRectangleWidth;
	collisionRectangleTopObstacle.height = collisionRectangleHeight;

	collisionRectangleBottomObstacle.x = collisionRectanglePositionX;
	collisionRectangleBottomObstacle.y = collisionRectangleBottomObstaclePositionY;
	collisionRectangleBottomObstacle.width = collisionRectangleWidth;
	collisionRectangleBottomObstacle.height = collisionRectangleHeight;
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

	if (static_cast<int>(positionTopObstacle.x) <= -m_Texture.width)
	{
		positionTopObstacle.x = m_CanvasWidth;

		heightOffset = GetRandomValue(0, m_CanvasHeight - m_Texture.height * 2 - gapBetweenObstacles);

		positionTopObstacle.y = heightOffset;
		positionBottomObstacle.y = positionTopObstacle.y + m_Texture.height + gapBetweenObstacles;
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
	DrawTextureRec(m_Texture, Rectangle{ 0, 0, static_cast<float>(m_Texture.width), static_cast<float>(-m_Texture.height) }, Vector2{ positionTopObstacle.x, positionTopObstacle.y }, WHITE);
	DrawTextureRec(m_Texture, Rectangle{ 0, 0, static_cast<float>(m_Texture.width), static_cast<float>(m_Texture.height) }, Vector2{ positionBottomObstacle.x, positionBottomObstacle.y }, WHITE);

	DrawRectangleLinesEx(collisionRectangleTopObstacle, 3, GREEN);
	DrawRectangleLinesEx(collisionRectangleBottomObstacle, 3, GREEN);
}

void Obstacle::unloadAssets()
{
	UnloadTexture(m_Texture);
}