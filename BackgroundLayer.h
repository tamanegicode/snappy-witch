#pragma once
#include "raylib.h"

class BackgroundLayer
{
	public:
		BackgroundLayer(Texture texture, int scrollSpeed, int windowWidth, int windowHeight, int offset = 0);
		void update(float deltaTime);
		void render();
		void unloadAssets();
	private:
		Texture texture{};
		Vector2 position{};
		int scrollSpeed{};
		int numberOfSprites{};
		int windowWidth{};
		int windowHeight{};
		int offset{};
};