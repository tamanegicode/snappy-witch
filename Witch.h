#pragma once
#include "raylib.h"

class Witch
{
	public:
		Witch(int canvasHeight, float collisionRectangleWidthScale = 1.0f, float collisionRectangleHeightScale = 1.0f);
		void update(float deltaTime);
		void render(float deltaTime);
		void unloadAssets();
		Rectangle getCollisionRectangle();
		float getPositionX();
		Vector2* getPosition();
		bool getDead() const;
		void setDead();
	private:
		Texture flyTexture{ LoadTexture("assets/textures/spritesheetWitch.png") };
		int frameToDraw{ 0 };
		int frameNumber{ 3 };
		float frameTime{ 0.2f };
		float animationTime{ 0.0f };
		Texture jumpTexture{ LoadTexture("assets/textures/jumpWitch.png") };
		Sound jumpSound{ LoadSound("assets/sounds/jump.mp3") };
		Texture fallTexture{ LoadTexture("assets/textures/fallWitch.png") };
		Rectangle collisionRectangle{};
		float colRecXOffset{ 1.0f };
		float colRecYOffset{ 1.0f };
		Vector2 position{ 10, 0 };
		int velocity{};
		int gravity{ 400 };
		int jumpForce{ -180 };
		int m_CanvasHeight{};
		bool dead{ false };
};