#pragma once
#include "raylib.h"

class Obstacle
{
public:
	Obstacle(Texture texture, int startingPosition, int canvasWidth, int canvasHeight);
	void update(float deltaTime);
	void render();
	void unloadAssets();
	Rectangle getCollisionRectangleTopObstacle();
	Rectangle getCollisionRectangleBottomObstacle();
private:
	Texture texture{};
	Rectangle collisionRectangleTopObstacle{};
	Rectangle collisionRectangleBottomObstacle{};
	Vector2 positionTopObstacle{};
	Vector2 positionBottomObstacle{};
	int scrollSpeed{ 100 };
	int heightOffset{};
	int gapBetweenObstacles{ 90 };
	int canvasWidth{};
	int canvasHeight{};
};