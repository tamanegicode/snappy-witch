#pragma once
#include "raylib.h"

class Obstacle
{
public:
	Obstacle(Texture texture, int startingPosition, int windowWidth);
	void update(float deltaTime);
	void render();
	void unloadAssets();
private:
	Texture texture{};
	Rectangle collisionRectangleTopObstacle{};
	Rectangle collisionRectangleBottomObstacle{};
	Vector2 positionTopObstacle{};
	Vector2 positionBottomObstacle{};
	int scrollSpeed{500};
	int heightOffset{};
	int windowWidth{};
};