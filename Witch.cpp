#include "Witch.h"

Witch::Witch(int windowHeight)
{
	this->windowHeight = windowHeight;
	texture = LoadTexture("assets/textures/witch.png");
	position.y = static_cast<float>(windowHeight / 2);

	collisionRectangle = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
}

Rectangle Witch::getCollisionRectangle()
{
	return collisionRectangle;
}

void Witch::update(float deltaTime)
{
	velocity += gravity * deltaTime;

	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		velocity = jumpForce;
	}

	position.y += velocity * deltaTime;

	if (position.y > windowHeight - texture.height / 1.5f)
	{
		position.y = windowHeight - texture.height / 1.5f;
	}

	if (position.y < -texture.height / 3)
	{
		position.y = -texture.height / 3;
	}

	collisionRectangle.x = position.x;
	collisionRectangle.y = position.y;
}

void Witch::render()
{
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawRectangleLinesEx(collisionRectangle, 5, RED);
}

void Witch::unloadAssets()
{
	UnloadTexture(texture);
}