#pragma once
#include "raylib.h"

class Witch
{
	public:
		Witch(int canvasHeight, float collisionRectangleScale = 1.0f);
		void update(float deltaTime);
		void render(float deltaTime);
		void unloadAssets();
		Rectangle getCollisionRectangle();
		float getPositionX();
	private:
		Texture flyTexture{};
		int frameToDraw{ 0 };
		int frameNumber{ 3 };
		float frameTime{ 0.2f };
		float animationTime{ 0.0f };
		Texture jumpTexture{};
		Rectangle collisionRectangle{};
		float collisionRectangleScale{ 1.0f };
		float colRecXOffset{ 1.0f };
		float colRecYOffset{ 1.0f };
		Vector2 position{ 10, 0 };
		int velocity{};		
		int gravity{ 400 };
		int jumpForce{ -190 };
		int canvasHeight{};
};