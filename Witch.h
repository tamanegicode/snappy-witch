#pragma once
#include "raylib.h"

class Witch
{
	public:
		Witch(int windowHeight);
		void update(float deltaTime);
		void render();
		void unloadAssets();
	private:
		Texture texture{};
		Vector2 position{ 100, 0 };
		int velocity{};		
		int gravity{ 1500 };
		int jumpForce{ -500 };
		int windowHeight{};
};