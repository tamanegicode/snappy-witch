#pragma once
#include "raylib.h"

class Witch
{
	public:
		Witch(int canvasHeight, float collisionRectangleScale = 1.0f);
		void update(float deltaTime);
		void render();
		void unloadAssets();
		Rectangle getCollisionRectangle();
	private:
		Texture flyTexture{};
		Texture jumpTexture{};
		Rectangle collisionRectangle{};
		float collisionRectangleScale{ 1.0f };
		float colRecXOffset{ 1.0f };
		float colRecYOffset{ 1.0f };
		Vector2 position{ 10, 0 };
		int velocity{};		
		int gravity{ 900 };
		int jumpForce{ -200 };
		int canvasHeight{};
};