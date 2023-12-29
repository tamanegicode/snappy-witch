#pragma once
#include "raylib.h"

class BackgroundLayer
{
	public:
		BackgroundLayer(Texture texture, int scrollSpeed);
		void update(float deltaTime);
		void render();
		void unloadAssets();
	private:
		Texture texture{};
		Vector2 position{};
		int scrollSpeed{};
};