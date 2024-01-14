#pragma once
#include "raylib.h"

class BackgroundLayer
{
	public:
		BackgroundLayer();
		BackgroundLayer(Texture texture, int scrollSpeed, int canvasWidth, int canvasHeight, int offset = 0);
		void update(float deltaTime);
		void render();
		void unloadAssets();
	private:
		Texture texture{};
		Vector2 position{};
		int scrollSpeed{};
		int numberOfSprites{};
		int canvasWidth{};
		int canvasHeight{};
		int offset{};
};