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
	Vector2 position{};
	int scrollSpeed{500};
	int heightOffset{};
	int windowWidth{};
};