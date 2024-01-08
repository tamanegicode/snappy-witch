#include "Witch.h"

Witch::Witch(int windowHeight, float collisionRectangleScale)
{
	this->windowHeight = windowHeight;
	this->collisionRectangle = collisionRectangle;
	texture = LoadTexture("assets/textures/witch.png");
	position.y = static_cast<float>(windowHeight / 2);

	float collisionRectangleWidth = static_cast<float>(texture.width) * collisionRectangleScale;
	float collisionRectangleHeight = static_cast<float>(texture.height) * collisionRectangleScale;

	colRecXOffset = (texture.width - collisionRectangleWidth) / 2;
	colRecYOffset = (texture.height - collisionRectangleHeight) / 2;

	float collisionRectanglePositionX = position.x + colRecXOffset;
	float collisionRectanglePositionY = position.y + colRecYOffset;

	collisionRectangle = { collisionRectanglePositionX , collisionRectanglePositionY, collisionRectangleWidth, collisionRectangleHeight };
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

	if (position.y > windowHeight - collisionRectangle.height - colRecYOffset)
	{
		position.y = windowHeight - collisionRectangle.height - colRecYOffset;
	}

	if (position.y < -colRecYOffset)
	{
		position.y =  -colRecYOffset;
	}

	collisionRectangle.y = position.y + colRecYOffset;
}

void Witch::render()
{
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawRectangleLinesEx(collisionRectangle, 3, RED);
}

void Witch::unloadAssets()
{
	UnloadTexture(texture);
}