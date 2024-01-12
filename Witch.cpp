#include "Witch.h"

Witch::Witch(int canvasHeight, float collisionRectangleScale)
{
	this->canvasHeight = canvasHeight;
	this->collisionRectangle = collisionRectangle;
	flyTexture = LoadTexture("assets/textures/witch.png");
	jumpTexture = LoadTexture("assets/textures/jumpWitch.png");
	position.y = static_cast<float>(canvasHeight / 2);

	float collisionRectangleWidth = static_cast<float>(flyTexture.width) * collisionRectangleScale;
	float collisionRectangleHeight = static_cast<float>(flyTexture.height) * collisionRectangleScale;

	colRecXOffset = (flyTexture.width - collisionRectangleWidth) / 2;
	colRecYOffset = (flyTexture.height - collisionRectangleHeight) / 2;

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

	if (position.y > canvasHeight - collisionRectangle.height - colRecYOffset)
	{
		position.y = canvasHeight - collisionRectangle.height - colRecYOffset;
	}

	if (position.y < -colRecYOffset)
	{
		position.y =  -colRecYOffset;
	}

	collisionRectangle.y = position.y + colRecYOffset;
}

void Witch::render()
{
	if(velocity > 0)
		DrawTexture(flyTexture, position.x, position.y, WHITE);
	else
		DrawTexture(jumpTexture, position.x, position.y, WHITE);

	DrawRectangleLinesEx(collisionRectangle, 3, RED);
}

void Witch::unloadAssets()
{
	UnloadTexture(flyTexture);
	UnloadTexture(jumpTexture);
}