#include "Witch.h"

Witch::Witch(int canvasHeight, float collisionRectangleWidthScale, float collisionRectangleHeightScale)
{
	this->canvasHeight = canvasHeight;
	this->collisionRectangle = collisionRectangle;
	flyTexture = LoadTexture("assets/textures/spritesheetWitch.png");
	jumpTexture = LoadTexture("assets/textures/jumpWitch.png");
	position.y = static_cast<float>(canvasHeight / 2);

	float collisionRectangleWidth = static_cast<float>(flyTexture.width) / frameNumber * collisionRectangleWidthScale;
	float collisionRectangleHeight = static_cast<float>(flyTexture.height) * collisionRectangleHeightScale;

	colRecXOffset = (flyTexture.width / frameNumber - collisionRectangleWidth) / 2;
	colRecYOffset = (flyTexture.height - collisionRectangleHeight) / 2;

	float collisionRectanglePositionX = position.x + colRecXOffset;
	float collisionRectanglePositionY = position.y + colRecYOffset;

	collisionRectangle = { collisionRectanglePositionX , collisionRectanglePositionY, collisionRectangleWidth, collisionRectangleHeight };
}

Rectangle Witch::getCollisionRectangle()
{
	return collisionRectangle;
}

float Witch::getPositionX()
{
	return position.x;
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

void Witch::render(float deltaTime)
{
	animationTime += deltaTime;

	if (animationTime > frameTime)
	{
		frameToDraw == frameNumber-1 ? frameToDraw = 0 : frameToDraw += 1;
		animationTime = 0;
	}

	if (velocity > 0)
		DrawTexturePro(flyTexture,
			Rectangle{ static_cast<float>(flyTexture.width / frameNumber) * frameToDraw, 0, static_cast<float>(flyTexture.width / frameNumber), static_cast<float>(flyTexture.height) },
			Rectangle{ position.x, position.y, static_cast<float>(flyTexture.width / frameNumber), static_cast<float>(flyTexture.height) },
			Vector2{ 0, 0 },
			0.0f,
			WHITE);
	else
		DrawTexture(jumpTexture, position.x, position.y, WHITE);

	DrawRectangleLinesEx(collisionRectangle, 3, RED);
}

void Witch::unloadAssets()
{
	UnloadTexture(flyTexture);
	UnloadTexture(jumpTexture);
}