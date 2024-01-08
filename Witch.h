#pragma once
#include "raylib.h"

class Witch
{
	public:
		Witch(int windowHeight, float collisionRectangleScale = 1.0f);
		void update(float deltaTime);
		void render();
		void unloadAssets();
		Rectangle getCollisionRectangle();
	private:
		Texture texture{};
		Rectangle collisionRectangle{};
		float collisionRectangleScale{ 1.0f };
		float colRecXOffset{ 1.0f };
		float colRecYOffset{ 1.0f };
		Vector2 position{ 100, 0 };
		int velocity{};		
		int gravity{ 1500 };
		int jumpForce{ -500 };
		int windowHeight{};
};