#pragma once
#include "raylib.h"
#include <string>

class BackgroundLayer
{
	public:
		BackgroundLayer(std::string texturePath, int scrollSpeed, int canvasWidth, int canvasHeight, int offset = 0);
		void update(float deltaTime);
		void render();
		void unloadAssets();
	private:
		std::string m_TexturePath{};
		Texture texture{ LoadTexture(m_TexturePath.c_str())};
		Vector2 position{};
		int scrollSpeed{};
		int numberOfSprites{};
		int canvasWidth{};
		int canvasHeight{};
		int offset{};
};