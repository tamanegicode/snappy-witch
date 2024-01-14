#pragma once
#include "raylib.h"

class Obstacle
{
public:
	Obstacle();
	Obstacle(Texture texture, int startingPosition, int canvasWidth, int canvasHeight, float collisionRectangleWidthScale = 1.0f, float collisionRectangleHeightScale = 1.0f);
	void update(float deltaTime);
	void render();
	void unloadAssets();
	Rectangle getCollisionRectangleTopObstacle();
	Rectangle getCollisionRectangleBottomObstacle();
	float getPositionX();
private:
	Texture texture{};
	Rectangle collisionRectangleTopObstacle{};
	Rectangle collisionRectangleBottomObstacle{};
	Vector2 positionTopObstacle{};
	Vector2 positionBottomObstacle{};
	float colRecXOffset{ 1.0f };
	float colRecYOffset{ 1.0f };
	int scrollSpeed{ 100 };
	int heightOffset{};
	int gapBetweenObstacles{ 90 };
	int canvasWidth{};
	int canvasHeight{};
};