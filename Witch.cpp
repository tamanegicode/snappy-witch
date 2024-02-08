#include "Witch.h"

Witch::Witch(int canvasHeight, float collisionRectangleWidthScale, float collisionRectangleHeightScale)
	: m_CanvasHeight(canvasHeight)
{
	float collisionRectangleWidth = static_cast<float>(flyTexture.width) / frameNumber * collisionRectangleWidthScale;
	float collisionRectangleHeight = static_cast<float>(flyTexture.height) * collisionRectangleHeightScale;

	colRecXOffset = (flyTexture.width / frameNumber - collisionRectangleWidth) / 2;
	colRecYOffset = (flyTexture.height - collisionRectangleHeight) / 2;

	float collisionRectanglePositionX = position.x + colRecXOffset;
	float collisionRectanglePositionY = position.y + colRecYOffset;

	collisionRectangle.x = collisionRectanglePositionX;
	collisionRectangle.y = collisionRectanglePositionY;
	collisionRectangle.width = collisionRectangleWidth;
	collisionRectangle.height = collisionRectangleHeight;
}

Rectangle Witch::getCollisionRectangle()
{
	return collisionRectangle;
}

float Witch::getPositionX()
{
	return position.x;
}

Vector2* Witch::getPosition()
{
	return &position;
}

bool Witch::getDead() const
{
	return dead;
}

void Witch::setDead()
{
	dead = true;
}

void Witch::update(float deltaTime)
{
	velocity += gravity * deltaTime;

	if (!dead && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
	{
		velocity = jumpForce;
		PlaySound(jumpSound);
	}

	position.y += velocity * deltaTime;

	if (!dead)
	{
		if (position.y > m_CanvasHeight - collisionRectangle.height - colRecYOffset)
		{
			position.y = m_CanvasHeight - collisionRectangle.height - colRecYOffset;
		}

		if (position.y < -colRecYOffset)
		{
			position.y = -colRecYOffset;
		}
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

	if (dead)
		DrawTexture(fallTexture, position.x, position.y, WHITE);
	else if (velocity > 0)
		DrawTexturePro(flyTexture,
			Rectangle{ static_cast<float>(flyTexture.width / frameNumber) * frameToDraw, 0, static_cast<float>(flyTexture.width / frameNumber), static_cast<float>(flyTexture.height) },
			Rectangle{ position.x, position.y, static_cast<float>(flyTexture.width / frameNumber), static_cast<float>(flyTexture.height) },
			Vector2{ 0, 0 },
			0.0f,
			WHITE);
	else
		DrawTexture(jumpTexture, position.x, position.y, WHITE);

	//Uncomment to make collision rectangles visible for testing purposes
	//DrawRectangleLinesEx(collisionRectangle, 3, RED);
}

void Witch::unloadAssets()
{
	UnloadTexture(flyTexture);
	UnloadTexture(jumpTexture);
	UnloadTexture(fallTexture);
	UnloadSound(jumpSound);
}