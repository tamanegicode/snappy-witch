#pragma once
#include "raylib.h"

class Bat
{
public:
	Bat(Vector2 &witchPosition);
	void update(float deltaTime);
	void render(float deltaTime);
	void unloadAssets();
private:
	Texture texture{ LoadTexture("assets/textures/bat.png") };
	int frameToDraw{ 0 };
	int frameNumber{ 6 };
	float frameTime{ 0.05f };
	float animationTime{ 0.0f };
	Vector2 position{};
	Vector2* m_WitchPosition{};
	Vector2 direction{};
	Vector2 offset{ 60, 20 };
	float speed{ 100 };
};